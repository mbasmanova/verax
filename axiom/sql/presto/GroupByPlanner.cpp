/*
 * Copyright (c) Meta Platforms, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "axiom/sql/presto/GroupByPlanner.h"
#include <set>
#include "axiom/sql/presto/ColumnsExpansion.h"
#include "axiom/sql/presto/SortProjection.h"
#include "axiom/sql/presto/ast/DefaultTraversalVisitor.h"
#include "folly/container/F14Set.h"
#include "velox/common/base/BitUtil.h"
#include "velox/exec/Aggregate.h"

namespace axiom::sql::presto {

using namespace facebook::velox;

namespace lp = facebook::axiom::logical_plan;

namespace {

template <typename V>
using ExprMap =
    folly::F14FastMap<core::ExprPtr, V, core::IExprHash, core::IExprEqual>;

// Set of aggregate expressions for deduplication. Uses IExpr equality which
// includes AggregateCallExpr options (DISTINCT, FILTER, ORDER BY).
using AggregateExprSet =
    folly::F14FastSet<core::ExprPtr, core::IExprHash, core::IExprEqual>;

// Maps aggregate expressions to their rewritten output columns.
using AggregateExprMap = folly::
    F14FastMap<core::ExprPtr, core::ExprPtr, core::IExprHash, core::IExprEqual>;

// Rewrites each IExpr in the WindowSpec's PARTITION BY and ORDER BY keys using
// 'rewrite' and returns the rewritten spec.
lp::WindowSpec rewriteWindowSpec(
    const lp::WindowSpec& spec,
    const std::function<core::ExprPtr(const core::ExprPtr&)>& rewrite) {
  auto result = spec;
  if (!result.partitionKeys().empty()) {
    std::vector<lp::ExprApi> newKeys;
    for (const auto& key : result.partitionKeys()) {
      newKeys.push_back(lp::ExprApi(rewrite(key.expr())));
    }
    result.partitionBy(std::move(newKeys));
  }

  if (!result.orderByKeys().empty()) {
    std::vector<lp::SortKey> newKeys;
    for (const auto& key : result.orderByKeys()) {
      newKeys.emplace_back(
          lp::ExprApi(rewrite(key.expr.expr())), key.ascending, key.nullsFirst);
    }
    result.orderBy(std::move(newKeys));
  }
  return result;
}

// Rewrites a window function expression: replaces column references in the
// function arguments, PARTITION BY keys, and ORDER BY keys using the provided
// rewrite function.
lp::ExprApi rewriteWindowExpr(
    const lp::ExprApi& item,
    const std::function<core::ExprPtr(const core::ExprPtr&)>& rewriteIExpr) {
  const auto windowSpec = item.windowSpec();
  VELOX_CHECK_NOT_NULL(windowSpec);

  // Rewrite function arguments.
  std::vector<core::ExprPtr> newInputs;
  bool changed = false;
  for (const auto& input : item.expr()->inputs()) {
    auto newInput = rewriteIExpr(input);
    changed |= (newInput.get() != input.get());
    newInputs.push_back(std::move(newInput));
  }

  auto newExpr =
      changed ? item.expr()->replaceInputs(std::move(newInputs)) : item.expr();

  return lp::ExprApi(std::move(newExpr), item.name())
      .over(rewriteWindowSpec(*windowSpec, rewriteIExpr));
}

// Given an expression, and pairs of search-and-replace sub-expressions,
// produces a new expression with sub-expressions replaced. Uses keyReplacements
// for grouping keys and aggregateReplacements for aggregates. If
// 'onUnreplacedLeaf' is provided, invokes the callback for any
// FieldAccessExpr that is not in the replacement map and whose children were
// not replaced either. Used to detect invalid column references in HAVING.
core::ExprPtr replaceInputs(
    const core::ExprPtr& expr,
    const ExprMap<core::ExprPtr>& keyReplacements,
    const AggregateExprMap& aggregateReplacements,
    const std::function<void(const core::FieldAccessExpr&)>& onUnreplacedLeaf =
        nullptr) {
  // First try grouping keys.
  auto keyIt = keyReplacements.find(expr);
  if (keyIt != keyReplacements.end()) {
    return keyIt->second;
  }

  // Then try aggregates.
  auto aggIt = aggregateReplacements.find(expr);
  if (aggIt != aggregateReplacements.end()) {
    return aggIt->second;
  }

  std::vector<core::ExprPtr> newInputs;
  bool hasNewInput = false;
  for (const auto& input : expr->inputs()) {
    auto newInput = replaceInputs(
        input, keyReplacements, aggregateReplacements, onUnreplacedLeaf);
    if (newInput.get() != input.get()) {
      hasNewInput = true;
    }
    newInputs.push_back(newInput);
  }

  if (!hasNewInput && onUnreplacedLeaf &&
      expr->is(core::IExpr::Kind::kFieldAccess)) {
    onUnreplacedLeaf(*expr->as<core::FieldAccessExpr>());
  }

  if (hasNewInput) {
    return expr->replaceInputs(std::move(newInputs));
  }

  return expr;
}

using WindowOptionsMap = std::unordered_map<const core::IExpr*, lp::WindowSpec>;

// Walks the expression tree looking for aggregate function calls and appending
// these calls to 'aggregates' after deduplication through 'aggregateSet'.
// When 'windowOptions' is non-null, expressions found in the map are treated
// as window functions (not aggregates): their children and WindowSpec keys are
// searched for real aggregates instead.
void findAggregates(
    const core::ExprPtr& expr,
    std::vector<lp::ExprApi>& aggregates,
    AggregateExprSet& aggregateSet,
    const WindowOptionsMap* windowOptions = nullptr) {
  // Check if this expression is a window function (not an aggregate).
  if (windowOptions != nullptr && windowOptions->count(expr.get())) {
    for (const auto& input : expr->inputs()) {
      findAggregates(input, aggregates, aggregateSet, windowOptions);
    }
    const auto& windowSpec = windowOptions->at(expr.get());
    for (const auto& key : windowSpec.partitionKeys()) {
      findAggregates(key.expr(), aggregates, aggregateSet, windowOptions);
    }
    for (const auto& key : windowSpec.orderByKeys()) {
      findAggregates(key.expr.expr(), aggregates, aggregateSet, windowOptions);
    }
    return;
  }

  switch (expr->kind()) {
    case core::IExpr::Kind::kInput:
      return;
    case core::IExpr::Kind::kFieldAccess:
      return;
    case core::IExpr::Kind::kAggregate: {
      if (aggregateSet.emplace(expr).second) {
        aggregates.emplace_back(expr);
      }
      return;
    }
    case core::IExpr::Kind::kCall: {
      // Plain CallExpr that is registered as an aggregate (no DISTINCT/FILTER/
      // ORDER BY). This happens for simple aggregates like count(*).
      if (exec::getAggregateFunctionEntry(expr->as<core::CallExpr>()->name())) {
        if (aggregateSet.emplace(expr).second) {
          aggregates.emplace_back(expr);
        }
      } else {
        for (const auto& input : expr->inputs()) {
          findAggregates(input, aggregates, aggregateSet, windowOptions);
        }
      }
      return;
    }
    case core::IExpr::Kind::kCast:
      findAggregates(
          expr->as<core::CastExpr>()->input(),
          aggregates,
          aggregateSet,
          windowOptions);
      return;
    case core::IExpr::Kind::kConstant:
      return;
    case core::IExpr::Kind::kLambda:
      // TODO: Reject aggregates in lambda expressions.
      return;
    case core::IExpr::Kind::kSubquery:
      // TODO: Handle aggregates in subqueries.
      return;
    case core::IExpr::Kind::kConcat:
      for (const auto& input : expr->inputs()) {
        findAggregates(input, aggregates, aggregateSet, windowOptions);
      }
      return;
    default:
      VELOX_UNSUPPORTED(
          "Unsupported expression kind in findAggregates: {}",
          expr->toString());
  }
}

// Finds aggregates in an ExprApi. For window functions (top-level or nested),
// recurses into arguments and WindowSpec keys to find real aggregates.
void findAggregates(
    const lp::ExprApi& expr,
    const WindowOptionsMap& windowOptions,
    std::vector<lp::ExprApi>& aggregates,
    AggregateExprSet& aggregateSet) {
  const WindowOptionsMap* windowOptionsPtr =
      windowOptions.empty() ? nullptr : &windowOptions;

  if (const auto& windowSpec = expr.windowSpec()) {
    for (const auto& input : expr.expr()->inputs()) {
      findAggregates(input, aggregates, aggregateSet, windowOptionsPtr);
    }
    for (const auto& key : windowSpec->partitionKeys()) {
      findAggregates(key.expr(), aggregates, aggregateSet, windowOptionsPtr);
    }
    for (const auto& key : windowSpec->orderByKeys()) {
      findAggregates(
          key.expr.expr(), aggregates, aggregateSet, windowOptionsPtr);
    }
  } else {
    findAggregates(expr.expr(), aggregates, aggregateSet, windowOptionsPtr);
  }
}

// Analyzes the expression to find out whether there are any aggregate function
// calls and to verify that aggregate calls are not nested, e.g. sum(count(x))
// is not allowed.
class ExprAnalyzer : public DefaultTraversalVisitor {
 public:
  bool hasAggregate() const {
    return numAggregates_ > 0;
  }

 protected:
  void visitExistsPredicate(ExistsPredicate* node) override {
    // Aggregate function calls within a subquery do not count.
  }

  void visitFunctionCall(FunctionCall* node) override {
    const auto& name = node->name()->suffix();
    if (exec::getAggregateFunctionEntry(name) && node->window() == nullptr) {
      VELOX_USER_CHECK(
          !aggregateName_.has_value(),
          "Cannot nest aggregations inside aggregation: {}({})",
          aggregateName_.value(),
          name);

      aggregateName_ = name;
      ++numAggregates_;
    }

    DefaultTraversalVisitor::visitFunctionCall(node);

    aggregateName_.reset();
  }

  void visitSubqueryExpression(SubqueryExpression* node) override {
    // Aggregate function calls within a subquery do not count.
  }

 private:
  size_t numAggregates_{0};
  std::optional<std::string> aggregateName_;
};

// Finds sub-expressions in an IExpr tree whose raw pointers match keys in
// 'targets'. Collects the ExprPtrs and appends matches to 'order' in traversal
// order for deterministic plan generation.
void findWindowExprPtrs(
    const core::ExprPtr& expr,
    const std::unordered_map<const core::IExpr*, lp::WindowSpec>& targets,
    std::unordered_map<const core::IExpr*, core::ExprPtr>& found,
    std::vector<const core::IExpr*>& order) {
  if (targets.count(expr.get())) {
    if (found.emplace(expr.get(), expr).second) {
      order.push_back(expr.get());
    }
    return;
  }
  for (const auto& input : expr->inputs()) {
    findWindowExprPtrs(input, targets, found, order);
  }
}

// Extracts nested window functions from projections into a separate plan node.
// For each window function in 'windowOptions':
// 1. Rewrites its arguments to reference aggregate output columns.
// 2. Creates a window projection using builder.with().
// 3. Adds the OLD ExprPtr to 'keyInputs' so replaceInputs substitutes it with
//    a column reference during the subsequent projection rewrite.
void extractNestedWindowFunctions(
    const std::vector<lp::ExprApi>& projections,
    const WindowOptionsMap& windowOptions,
    const std::function<core::ExprPtr(const core::ExprPtr&)>& rewriteIExpr,
    lp::PlanBuilder& builder,
    ExprMap<core::ExprPtr>& keyInputs) {
  std::unordered_map<const core::IExpr*, core::ExprPtr> windowExprPtrs;
  std::vector<const core::IExpr*> windowOrder;
  for (const auto& item : projections) {
    findWindowExprPtrs(item.expr(), windowOptions, windowExprPtrs, windowOrder);
  }

  if (windowOrder.empty()) {
    return;
  }

  std::vector<lp::ExprApi> windowExprs;
  windowExprs.reserve(windowOrder.size());
  for (const auto* exprPtr : windowOrder) {
    auto rewrittenExpr = rewriteIExpr(windowExprPtrs.at(exprPtr));
    auto rewrittenSpec =
        rewriteWindowSpec(windowOptions.at(exprPtr), rewriteIExpr);
    windowExprs.push_back(
        lp::ExprApi(std::move(rewrittenExpr)).over(rewrittenSpec));
  }

  builder.with(windowExprs);

  auto outputColumns =
      builder.findOrAssignOutputNames(/*includeHiddenColumns=*/false);

  auto numInputColumns = outputColumns.size() - windowOrder.size();
  for (size_t i = 0; i < windowOrder.size(); ++i) {
    const auto& column = outputColumns.at(numInputColumns + i);
    keyInputs.emplace(windowExprPtrs.at(windowOrder[i]), column.toCol().expr());
  }
}

// ROLLUP(a,b,c) -> {(a,b,c), (a,b), (a), ()}
std::vector<std::vector<lp::ExprApi>> expandRollup(
    const std::vector<lp::ExprApi>& expressions) {
  std::vector<std::vector<lp::ExprApi>> groupingSets;
  groupingSets.reserve(expressions.size() + 1);

  for (size_t i = expressions.size(); i > 0; --i) {
    std::vector<lp::ExprApi> groupingSet(
        expressions.begin(), expressions.begin() + i);
    groupingSets.push_back(std::move(groupingSet));
  }
  groupingSets.emplace_back();
  return groupingSets;
}

// CUBE(a,b) -> {(a,b), (a), (b), ()}
std::vector<std::vector<lp::ExprApi>> expandCube(
    const std::vector<lp::ExprApi>& expressions) {
  const size_t n = expressions.size();
  // Presto limits CUBE to 30 columns (2^30 possible grouping sets).
  // https://github.com/prestodb/presto/issues/27096
  VELOX_USER_CHECK_LE(n, 30, "CUBE supports at most 30 columns");
  const size_t numGroupingSets = 1ULL << n;
  std::vector<std::vector<lp::ExprApi>> groupingSets;
  groupingSets.reserve(numGroupingSets);

  for (size_t mask = numGroupingSets; mask > 0; --mask) {
    size_t bits = mask - 1;
    std::vector<lp::ExprApi> groupingSet;
    for (size_t i = 0; i < n; ++i) {
      if (bits & (1ULL << (n - 1 - i))) {
        groupingSet.push_back(expressions[i]);
      }
    }
    groupingSets.push_back(std::move(groupingSet));
  }
  return groupingSets;
}

// Computes Cartesian product of accumulatedSets and newSets.
std::vector<std::vector<lp::ExprApi>> crossProductGroupingSets(
    const std::vector<std::vector<lp::ExprApi>>& accumulatedSets,
    std::vector<std::vector<lp::ExprApi>> newSets) {
  if (accumulatedSets.empty()) {
    return newSets;
  }
  if (newSets.empty()) {
    return accumulatedSets;
  }
  std::vector<std::vector<lp::ExprApi>> combined;
  combined.reserve(accumulatedSets.size() * newSets.size());
  for (const auto& base : accumulatedSets) {
    for (const auto& addition : newSets) {
      std::vector<lp::ExprApi> merged = base;
      merged.insert(merged.end(), addition.begin(), addition.end());
      combined.push_back(std::move(merged));
    }
  }
  return combined;
}

// Removes duplicate grouping sets from 'groupingSetsIndices'. Two sets are
// duplicates if they contain the same key indices (order-insensitive).
void deduplicateGroupingSets(
    std::vector<std::vector<int32_t>>& groupingSetsIndices) {
  std::set<std::vector<int32_t>> seen;
  size_t next = 0;
  for (size_t i = 0; i < groupingSetsIndices.size(); ++i) {
    std::sort(groupingSetsIndices[i].begin(), groupingSetsIndices[i].end());
    if (seen.insert(groupingSetsIndices[i]).second) {
      if (next != i) {
        groupingSetsIndices[next] = std::move(groupingSetsIndices[i]);
      }
      ++next;
    }
  }
  groupingSetsIndices.resize(next);
}

} // namespace

void GroupByPlanner::plan(
    const std::vector<GroupingElementPtr>& groupingElements,
    bool distinct,
    const std::vector<SelectItemPtr>& selectItems,
    const ExpressionPtr& having,
    const OrderByPtr& orderBy) && {
  // Expand ROLLUP, CUBE, GROUPING SETS into a list of grouping sets, then
  // extract deduplicated grouping keys and per-set index vectors.
  // Populates: groupingSets_, groupingKeys_, groupingSetsIndices_.
  groupingSets_ = expandGroupingSets(groupingElements, selectItems);
  deduplicateGroupingKeys();
  // GROUP BY DISTINCT removes duplicate grouping sets after expansion
  // (order-insensitive comparison).
  if (distinct) {
    deduplicateGroupingSets(groupingSetsIndices_);
  }

  // Walk SELECT, HAVING, and ORDER BY expressions to collect aggregate
  // function calls, then add the Aggregate plan node.
  // Populates: aggregates_, projections_, filter_,
  //   sortingKeyExprs_, outputNames_.
  collectAggregates(selectItems, having, orderBy);

  addAggregate(groupingSetsIndices_.size() > 1);

  // Rewrite filter_, projections_, and sortingKeyExprs_ to reference the
  // aggregate output columns instead of the original input expressions.
  // Populates: flatInputs_.
  // Mutates: filter_, projections_, sortingKeyExprs_.
  rewritePostAggregateExprs();

  // Resolve sorting key ordinals before projecting: ORDER BY expressions
  // that are not in the SELECT list are appended to projections_ so they
  // are included in the project node. Must happen before builder_->project().
  auto sortingKeyOrdinals = resolveSortOrdinals(orderBy);

  // Apply HAVING filter, then project.
  if (filter_.has_value()) {
    builder_->filter(filter_.value());
  }

  if (!isIdentityProjection()) {
    builder_->project(projections_);
  }

  // Sort and drop any extra projections added for ORDER BY.
  if (orderBy != nullptr && !sortingKeyOrdinals.empty()) {
    SortProjection::sortAndTrim(
        *builder_,
        orderBy->sortItems(),
        sortingKeyOrdinals,
        selectItems.size());
  }
}

bool GroupByPlanner::tryPlanGlobalAgg(
    const std::vector<SelectItemPtr>& selectItems,
    const ExpressionPtr& having) && {
  for (const auto& item : selectItems) {
    if (item->is(NodeType::kAllColumns) || item->is(NodeType::kSelectColumns)) {
      return false;
    }
  }

  bool hasAggregate = false;
  for (const auto& item : selectItems) {
    VELOX_CHECK(item->is(NodeType::kSingleColumn));
    auto* singleColumn = item->as<SingleColumn>();

    ExprAnalyzer exprAnalyzer;
    singleColumn->expression()->accept(&exprAnalyzer);

    if (exprAnalyzer.hasAggregate()) {
      hasAggregate = true;
      break;
    }
  }

  if (!hasAggregate) {
    return false;
  }

  std::move(*this).plan(
      {}, /*distinct=*/false, selectItems, having, /*orderBy=*/nullptr);
  return true;
}

std::vector<std::vector<lp::ExprApi>> GroupByPlanner::expandGroupingSets(
    const std::vector<GroupingElementPtr>& groupingElements,
    const std::vector<SelectItemPtr>& selectItems) {
  std::vector<std::vector<lp::ExprApi>> groupingSets;
  for (const auto& element : groupingElements) {
    switch (element->type()) {
      case NodeType::kSimpleGroupBy: {
        const auto* simple = element->as<SimpleGroupBy>();
        auto exprs = resolveWithCache(simple->expressions(), selectItems);
        groupingSets =
            crossProductGroupingSets(groupingSets, {std::move(exprs)});
        break;
      }

      case NodeType::kRollup: {
        const auto* rollup = element->as<Rollup>();
        auto rollupSets =
            expandRollup(resolveWithCache(rollup->expressions(), selectItems));
        groupingSets =
            crossProductGroupingSets(groupingSets, std::move(rollupSets));
        break;
      }

      case NodeType::kCube: {
        const auto* cube = element->as<Cube>();
        auto cubeSets =
            expandCube(resolveWithCache(cube->expressions(), selectItems));
        groupingSets =
            crossProductGroupingSets(groupingSets, std::move(cubeSets));
        break;
      }

      case NodeType::kGroupingSets: {
        const auto* groupingSetsNode = element->as<GroupingSets>();
        std::vector<std::vector<lp::ExprApi>> explicitSets;
        explicitSets.reserve(groupingSetsNode->sets().size());
        for (const auto& set : groupingSetsNode->sets()) {
          explicitSets.push_back(resolveWithCache(set, selectItems));
        }
        groupingSets =
            crossProductGroupingSets(groupingSets, std::move(explicitSets));
        break;
      }

      default:
        VELOX_NYI(
            "Grouping element type not supported: {}",
            NodeTypeName::toName(element->type()));
    }
  }
  return groupingSets;
}

void GroupByPlanner::deduplicateGroupingKeys() {
  core::ExprMap<int32_t> exprToIndex;
  for (const auto& groupingSet : groupingSets_) {
    std::vector<int32_t> indices;
    indices.reserve(groupingSet.size());
    for (const auto& expr : groupingSet) {
      int32_t idx = static_cast<int32_t>(groupingKeys_.size());
      auto [it, inserted] = exprToIndex.try_emplace(expr.expr(), idx);
      if (inserted) {
        groupingKeys_.push_back(expr);
      }
      // Deduplicate keys within a single grouping set: GROUP BY (a, a)
      // collapses to (a).
      if (std::find(indices.begin(), indices.end(), it->second) ==
          indices.end()) {
        indices.push_back(it->second);
      }
    }
    groupingSetsIndices_.push_back(std::move(indices));
  }
}

void GroupByPlanner::collectAggregates(
    const std::vector<SelectItemPtr>& selectItems,
    const ExpressionPtr& having,
    const OrderByPtr& orderBy) {
  // Go over SELECT expressions and figure out for each: whether a grouping
  // key, a function of one or more grouping keys, a constant, an aggregate
  // or a function over one or more aggregates and possibly grouping keys.
  //
  // Collect all individual aggregates. A single select item 'sum(x) /
  // sum(y)' will produce 2 aggregates: sum(x), sum(y).

  // When window functions are nested inside scalar expressions (e.g.
  // sum(a) / sum(sum(a)) OVER ()), pass windowOptionsMap_ to toExpr so
  // window calls are returned as plain function calls and their specs are
  // stored in the map. This avoids the Call() assertion that rejects
  // window functions as arguments to scalar functions.
  const bool hasNestedWindow =
      ExpressionPlanner::hasNestedWindowFunction(selectItems);
  auto* windowOptions = hasNestedWindow ? &windowOptionsMap_ : nullptr;

  AggregateExprSet aggregateSet;
  for (const auto& item : selectItems) {
    VELOX_CHECK(item->is(NodeType::kSingleColumn));
    auto* singleColumn = item->as<SingleColumn>();

    lp::ExprApi expr = [&]() {
      auto it = exprCache_.find(singleColumn->expression().get());
      if (it != exprCache_.end()) {
        return it->second;
      }
      return exprPlanner_.toExpr(singleColumn->expression(), windowOptions);
    }();

    findAggregates(expr, windowOptionsMap_, aggregates_, aggregateSet);

    if (!aggregates_.empty() &&
        aggregates_.back().expr().get() == expr.expr().get()) {
      // Preserve the alias.
      if (singleColumn->alias() != nullptr) {
        aggregates_.back() = aggregates_.back().as(
            canonicalizeIdentifier(*singleColumn->alias()));
      }
    }

    if (singleColumn->alias() != nullptr) {
      expr = expr.as(canonicalizeIdentifier(*singleColumn->alias()));
    }

    projections_.emplace_back(expr);
  }

  if (having != nullptr) {
    lp::ExprApi expr = exprPlanner_.toExpr(having);
    findAggregates(expr.expr(), aggregates_, aggregateSet);
    filter_ = expr;
  }

  if (orderBy != nullptr) {
    const auto& sortItems = orderBy->sortItems();
    for (const auto& item : sortItems) {
      auto expr = exprPlanner_.toExpr(item->sortKey());
      findAggregates(expr.expr(), aggregates_, aggregateSet);
      sortingKeyExprs_.emplace_back(expr);
    }
  }
}

void GroupByPlanner::addAggregate(bool useGroupingSets) {
  std::vector<lp::ExprApi> aggregateExprs;
  aggregateExprs.reserve(aggregates_.size());
  for (const auto& agg : aggregates_) {
    aggregateExprs.push_back(agg);
  }

  if (useGroupingSets) {
    builder_->aggregate(
        groupingKeys_,
        groupingSetsIndices_,
        aggregateExprs,
        "$grouping_set_id");
  } else {
    builder_->aggregate(groupingKeys_, aggregateExprs);
  }

  auto outputColumns = builder_->findOrAssignOutputNames();
  outputNames_.clear();
  outputNames_.reserve(outputColumns.size());
  for (const auto& column : outputColumns) {
    VELOX_CHECK(
        !column.alias.has_value(),
        "Unexpected ambiguous column after aggregate: {}",
        column.name);
    outputNames_.emplace_back(column.name);
  }
}

void GroupByPlanner::rewritePostAggregateExprs() {
  ExprMap<core::ExprPtr> keyInputs;
  AggregateExprMap aggregateInputs;

  size_t index = 0;
  for (const auto& key : groupingKeys_) {
    flatInputs_.emplace_back(lp::Col(outputNames_.at(index)));
    keyInputs.emplace(key.expr(), flatInputs_.back().expr());
    ++index;
  }

  for (const auto& agg : aggregates_) {
    flatInputs_.emplace_back(lp::Col(outputNames_.at(index)));
    aggregateInputs.emplace(agg.expr(), flatInputs_.back().expr());
    ++index;
  }

  if (filter_.has_value()) {
    filter_ = replaceInputs(
        filter_.value().expr(),
        keyInputs,
        aggregateInputs,
        [](const core::FieldAccessExpr& expr) {
          VELOX_USER_FAIL(
              "HAVING clause cannot reference column: {}", expr.name());
        });
  }

  // Rewrites an IExpr to reference post-aggregate columns.
  auto rewriteIExpr = [&](const core::ExprPtr& expr) {
    return replaceInputs(expr, keyInputs, aggregateInputs);
  };

  // Rewrites an ExprApi to reference post-aggregate columns. For window
  // functions, replaces the arguments of the call AND the PARTITION BY /
  // ORDER BY expressions in the WindowSpec.
  auto rewriteExpr = [&](lp::ExprApi& item) {
    const auto windowSpec = item.windowSpec();
    if (windowSpec) {
      item = rewriteWindowExpr(item, rewriteIExpr);
    } else {
      item = lp::ExprApi(rewriteIExpr(item.expr()), item.name());
    }
  };

  // Extract nested window functions: project them using builder_->with()
  // and add replacements to keyInputs so the projection rewrite below
  // substitutes window sub-expressions with column references.
  if (!windowOptionsMap_.empty()) {
    extractNestedWindowFunctions(
        projections_, windowOptionsMap_, rewriteIExpr, *builder_, keyInputs);
  }

  // Replace sub-expressions in SELECT projections with column references to
  // the aggregate output (and window output, if any).

  // TODO: Verify that SELECT expressions don't depend on anything other
  // than grouping keys and aggregates.

  for (auto& item : projections_) {
    rewriteExpr(item);
  }

  // Replace sorting key expressions too.
  for (auto& expr : sortingKeyExprs_) {
    rewriteExpr(expr);
  }
}

std::vector<size_t> GroupByPlanner::resolveSortOrdinals(
    const OrderByPtr& orderBy) {
  if (sortingKeyExprs_.empty()) {
    return {};
  }

  VELOX_CHECK_EQ(orderBy->sortItems().size(), sortingKeyExprs_.size());
  std::vector<size_t> preResolved(sortingKeyExprs_.size(), 0);
  for (size_t i = 0; i < sortingKeyExprs_.size(); ++i) {
    const auto& sortKey = orderBy->sortItems().at(i)->sortKey();
    if (sortKey->is(NodeType::kLongLiteral)) {
      preResolved.at(i) = sortKey->as<LongLiteral>()->value();
    }
  }

  return SortProjection::widenProjections(
      sortingKeyExprs_, preResolved, projections_);
}

bool GroupByPlanner::isIdentityProjection() const {
  if (flatInputs_.size() != projections_.size()) {
    return false;
  }

  for (size_t i = 0; i < projections_.size(); ++i) {
    if (projections_.at(i).expr() != flatInputs_.at(i).expr()) {
      return false;
    }

    const auto& alias = projections_.at(i).alias();
    if (alias.has_value() && alias.value() != outputNames_.at(i)) {
      return false;
    }
  }

  return true;
}

lp::ExprApi GroupByPlanner::resolveGroupingExpression(
    const ExpressionPtr& expr,
    const std::vector<SelectItemPtr>& selectItems) {
  if (expr->is(NodeType::kLongLiteral)) {
    const auto n = expr->as<LongLiteral>()->value();
    VELOX_USER_CHECK_GE(n, 1, "GROUP BY position is not in select list: {}", n);
    VELOX_USER_CHECK_LE(
        n,
        selectItems.size(),
        "GROUP BY position is not in select list: {}",
        n);

    const auto& item = selectItems.at(n - 1);
    VELOX_CHECK(item->is(NodeType::kSingleColumn));

    const auto* singleColumn = item->as<SingleColumn>();
    return exprPlanner_.toExpr(singleColumn->expression());
  }
  return exprPlanner_.toExpr(expr);
}

lp::ExprApi GroupByPlanner::resolveWithCache(
    const ExpressionPtr& expr,
    const std::vector<SelectItemPtr>& selectItems) {
  const Expression* cacheKey = expr.get();
  if (expr->is(NodeType::kLongLiteral)) {
    const auto ordinal = expr->as<LongLiteral>()->value();
    VELOX_USER_CHECK_GE(
        ordinal, 1, "GROUP BY position is not in select list: {}", ordinal);
    VELOX_USER_CHECK_LE(
        ordinal,
        selectItems.size(),
        "GROUP BY position is not in select list: {}",
        ordinal);
    const auto& selectItem = selectItems.at(ordinal - 1);
    if (selectItem->is(NodeType::kSingleColumn)) {
      cacheKey = selectItem->as<SingleColumn>()->expression().get();
    }
  }
  auto it = exprCache_.find(cacheKey);
  if (it != exprCache_.end()) {
    return it->second;
  }
  auto resolved = resolveGroupingExpression(expr, selectItems);
  exprCache_.emplace(cacheKey, resolved);
  return resolved;
}

std::vector<lp::ExprApi> GroupByPlanner::resolveWithCache(
    const std::vector<ExpressionPtr>& exprs,
    const std::vector<SelectItemPtr>& selectItems) {
  std::vector<lp::ExprApi> result;
  result.reserve(exprs.size());
  for (const auto& expr : exprs) {
    auto resolved = resolveWithCache(expr, selectItems);

    // Expand COLUMNS() calls to multiple grouping keys.
    auto expanded = ColumnsExpansion::expand(resolved, *builder_);
    if (!expanded.empty()) {
      result.insert(
          result.end(),
          std::make_move_iterator(expanded.begin()),
          std::make_move_iterator(expanded.end()));
    } else {
      result.push_back(std::move(resolved));
    }
  }
  return result;
}

} // namespace axiom::sql::presto
