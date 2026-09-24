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

#include "axiom/optimizer/v2/ExprSimplifier.h"

#include <algorithm>
#include "axiom/optimizer/Domain.h"
#include "axiom/optimizer/FunctionRegistry.h"
#include "axiom/optimizer/QueryGraph.h"
#include "axiom/optimizer/v2/ExprEmitter.h"
#include "axiom/optimizer/v2/ExprFactory.h"
#include "velox/expression/ConstantExpr.h"
#include "velox/vector/ComplexVector.h"
#include "velox/vector/SelectivityVector.h"

namespace facebook::axiom::optimizer::v2 {

namespace {

// If `orExpr` is an OR call and its disjuncts share AND-conjuncts,
// appends those common conjuncts to `common` and sets `*residual` to
// the rewritten OR (or nullptr when a disjunct was fully subsumed and
// the OR is trivially true once `common` holds). Returns true iff
// any factoring was performed; on false, `common` and `*residual`
// are unmodified.
bool tryFactorOr(
    Builder& builder,
    ExprCP orExpr,
    ExprVector& common,
    ExprCP* residual) {
  if (!orExpr->is(PlanType::kCallExpr) ||
      orExpr->as<Call>()->name() != SpecialFormCallNames::kOr) {
    return false;
  }
  ExprVector disjuncts = ExprFactory::flattenOr(orExpr);

  // Dedup disjuncts. Hash-cons guarantees pointer equality for
  // structurally identical exprs.
  folly::F14FastSet<ExprCP> seen;
  ExprVector uniqueDisjuncts;
  uniqueDisjuncts.reserve(disjuncts.size());
  for (ExprCP disjunct : disjuncts) {
    if (seen.insert(disjunct).second) {
      uniqueDisjuncts.push_back(disjunct);
    }
  }
  if (uniqueDisjuncts.size() < 2) {
    return false;
  }

  // Flatten each disjunct into its AND-conjuncts.
  std::vector<ExprVector> perDisjunctConjuncts;
  perDisjunctConjuncts.reserve(uniqueDisjuncts.size());
  for (ExprCP disjunct : uniqueDisjuncts) {
    perDisjunctConjuncts.push_back(ExprFactory::flattenAnd(disjunct));
  }

  // Intersect across all disjuncts.
  folly::F14FastSet<ExprCP> commonSet(
      perDisjunctConjuncts[0].begin(), perDisjunctConjuncts[0].end());
  for (size_t i = 1; i < perDisjunctConjuncts.size(); ++i) {
    folly::F14FastSet<ExprCP> next(
        perDisjunctConjuncts[i].begin(), perDisjunctConjuncts[i].end());
    folly::F14FastSet<ExprCP> intersected;
    for (ExprCP conjunct : commonSet) {
      if (next.contains(conjunct)) {
        intersected.insert(conjunct);
      }
    }
    commonSet = std::move(intersected);
  }
  if (commonSet.empty()) {
    return false;
  }

  // Build residuals; any empty residual means that disjunct is fully
  // subsumed by `common`, so the OR is trivially true given `common`.
  ExprFactory factory(builder);
  ExprVector residualDisjuncts;
  residualDisjuncts.reserve(uniqueDisjuncts.size());
  bool subsumed = false;
  for (auto& conjuncts : perDisjunctConjuncts) {
    ExprVector remaining;
    remaining.reserve(conjuncts.size());
    for (ExprCP conjunct : conjuncts) {
      if (!commonSet.contains(conjunct)) {
        remaining.push_back(conjunct);
      }
    }
    if (remaining.empty()) {
      subsumed = true;
      break;
    }
    residualDisjuncts.push_back(factory.andAll(remaining));
  }

  // Append common in first-disjunct order to keep deterministic output.
  for (ExprCP conjunct : perDisjunctConjuncts[0]) {
    if (commonSet.contains(conjunct)) {
      common.push_back(conjunct);
    }
  }
  *residual = subsumed ? nullptr : factory.orAll(residualDisjuncts);
  return true;
}

// Returns the value of `expr` if it is a non-null boolean literal.
std::optional<bool> constantBoolean(ExprCP expr) {
  if (!expr->is(PlanType::kLiteralExpr)) {
    return std::nullopt;
  }
  const auto& variant = expr->as<Literal>()->literal();
  if (variant.isNull() || variant.kind() != velox::TypeKind::BOOLEAN) {
    return std::nullopt;
  }
  return variant.value<bool>();
}

velox::Variant typedIntegralValue(TypeCP type, int64_t value) {
  switch (type->kind()) {
    case velox::TypeKind::TINYINT:
      return velox::Variant(static_cast<int8_t>(value));
    case velox::TypeKind::SMALLINT:
      return velox::Variant(static_cast<int16_t>(value));
    case velox::TypeKind::INTEGER:
      return velox::Variant(static_cast<int32_t>(value));
    case velox::TypeKind::BIGINT:
      return velox::Variant(value);
    default:
      VELOX_UNREACHABLE();
  }
}

ExprCP makeIntegralLiteral(Builder& builder, ColumnCP column, int64_t value) {
  return builder.makeLiteral(
      typedIntegralValue(column->value().type, value), column->value().type);
}

ExprCP rangeBoundToFilter(
    Builder& builder,
    ExprFactory& factory,
    ColumnCP column,
    const Bound& bound,
    bool isLower,
    int64_t typeLimit) {
  const auto value = bound.value.value<int64_t>();
  if (bound.inclusive && value == typeLimit) {
    return nullptr;
  }
  auto* literal = makeIntegralLiteral(builder, column, value);
  if (isLower) {
    return bound.inclusive ? factory.makeGreaterThanOrEqual(column, literal)
                           : factory.makeGreaterThan(column, literal);
  }
  return bound.inclusive ? factory.makeLessThanOrEqual(column, literal)
                         : factory.makeLessThan(column, literal);
}

ExprCP nonNullDomainToFilter(
    Builder& builder,
    ExprFactory& factory,
    ColumnCP column,
    const Domain& domain,
    const Domain& nonNullValues) {
  const auto& ranges = domain.ranges();
  const bool allSingleValues =
      std::all_of(ranges.begin(), ranges.end(), [](const Range& range) {
        return range.isSingleValue();
      });
  if (allSingleValues) {
    ExprVector values;
    values.reserve(ranges.size());
    for (const auto& range : ranges) {
      values.push_back(builder.makeLiteral(
          typedIntegralValue(
              column->value().type, range.low()->value.value<int64_t>()),
          column->value().type));
    }
    return values.size() == 1 ? factory.makeEq(column, values.front())
                              : factory.makeIn(column, std::move(values));
  }

  ExprVector disjuncts;
  disjuncts.reserve(ranges.size());
  const auto minimum =
      nonNullValues.ranges().front().low()->value.value<int64_t>();
  const auto maximum =
      nonNullValues.ranges().front().high()->value.value<int64_t>();
  for (const auto& range : ranges) {
    if (range.low().has_value() && range.high().has_value() &&
        range.lowInclusive() && range.highInclusive() &&
        range.low()->value.value<int64_t>() != minimum &&
        range.high()->value.value<int64_t>() != maximum) {
      disjuncts.push_back(factory.makeBetween(
          column,
          makeIntegralLiteral(
              builder, column, range.low()->value.value<int64_t>()),
          makeIntegralLiteral(
              builder, column, range.high()->value.value<int64_t>())));
      continue;
    }

    ExprVector bounds;
    if (range.low().has_value()) {
      if (auto* filter = rangeBoundToFilter(
              builder,
              factory,
              column,
              *range.low(),
              /*isLower=*/true,
              minimum)) {
        bounds.push_back(filter);
      }
    }
    if (range.high().has_value()) {
      if (auto* filter = rangeBoundToFilter(
              builder,
              factory,
              column,
              *range.high(),
              /*isLower=*/false,
              maximum)) {
        bounds.push_back(filter);
      }
    }
    VELOX_CHECK(!bounds.empty());
    disjuncts.push_back(factory.andAll(bounds));
  }
  return factory.orAll(disjuncts);
}

ExprCP domainToFilter(Builder& builder, ColumnCP column, Domain domain) {
  const auto nonNullValues = *integralTypeDomain(*column->value().type);
  const auto allValues = nonNullValues.unite(Domain::onlyNull());
  domain = domain.intersect(allValues);
  if (domain == allValues) {
    return nullptr;
  }

  ExprFactory factory(builder);
  const auto nonNullResult = domain.intersect(Domain::notNull());
  ExprCP nonNullFilter{nullptr};
  if (nonNullResult == nonNullValues) {
    nonNullFilter = factory.makeNot(factory.makeIsNull(column));
  } else if (!nonNullResult.isNone()) {
    const auto excluded = nonNullValues.subtract(nonNullResult);
    if (excluded.ranges().size() < nonNullResult.ranges().size()) {
      nonNullFilter = factory.makeNot(nonNullDomainToFilter(
          builder, factory, column, excluded, nonNullValues));
    } else {
      nonNullFilter = nonNullDomainToFilter(
          builder, factory, column, nonNullResult, nonNullValues);
    }
  }

  if (!domain.nullsAllowed()) {
    return nonNullFilter;
  }
  ExprCP nullFilter = factory.makeIsNull(column);
  return nonNullFilter == nullptr ? nullFilter
                                  : factory.makeOr(nullFilter, nonNullFilter);
}

} // namespace

ExprCP ExprSimplifier::simplify(ExprCP expr) {
  return tryFoldConjunct(tryFoldConstant(expr));
}

ExprCP ExprSimplifier::tryFoldConjunct(ExprCP expr) {
  if (!expr->is(PlanType::kCallExpr)) {
    return expr;
  }
  const auto* call = expr->as<Call>();
  const bool isAnd = call->name() == SpecialFormCallNames::kAnd;
  if (!isAnd && call->name() != SpecialFormCallNames::kOr) {
    return expr;
  }

  ExprVector remaining;
  remaining.reserve(call->args().size());
  for (ExprCP arg : call->args()) {
    const auto value = constantBoolean(arg);
    if (!value.has_value()) {
      remaining.push_back(arg);
    } else if (value.value() != isAnd) {
      // AND is false as soon as one argument is false, even if the others are
      // null or throw; OR is the mirror image.
      return arg;
    }
  }

  if (remaining.size() == call->args().size()) {
    return expr;
  }
  if (remaining.empty()) {
    return builder_.makeLiteral(
        velox::Variant(isAnd), toType(velox::BOOLEAN()));
  }
  if (remaining.size() == 1) {
    return remaining.front();
  }
  const FunctionSet functions = Call::unionArgFunctions(
      functionBits(call->name(), /*specialForm=*/true), remaining);
  // A literal argument is never the one that determined the call's
  // cardinality, so dropping it leaves `value()` valid.
  return builder_.makeCall(
      call->name(), call->value(), std::move(remaining), functions);
}

bool ExprSimplifier::simplifyFilter(ExprCP predicate, ExprVector& into) {
  ExprVector flattened = ExprFactory::flattenAnd(predicate);
  ExprVector candidates;
  candidates.reserve(flattened.size());
  for (ExprCP conjunct : flattened) {
    ExprCP simplified = simplify(conjunct);
    if (simplified->is(PlanType::kLiteralExpr)) {
      const auto& variant = simplified->as<Literal>()->literal();
      VELOX_CHECK_EQ(
          variant.kind(),
          velox::TypeKind::BOOLEAN,
          "Conjunct simplified to a non-boolean literal");
      if (variant.isNull() || !variant.value<bool>()) {
        return true;
      }
      // Literal `true` — drop.
      continue;
    }
    ExprCP residual = nullptr;
    if (tryFactorOr(builder_, simplified, candidates, &residual)) {
      if (residual != nullptr) {
        candidates.push_back(residual);
      }
      continue;
    }
    candidates.push_back(simplified);
  }

  struct ColumnDomain {
    Domain values;
    size_t outputIndex;
  };
  folly::F14FastMap<ColumnCP, ColumnDomain> domains;
  ExprVector surviving;
  surviving.reserve(candidates.size());
  for (ExprCP candidate : candidates) {
    if (candidate->columns().size() != 1) {
      surviving.push_back(candidate);
      continue;
    }
    const auto* column = candidate->columns().onlyObject<Column>();
    if (!integralTypeDomain(*column->value().type).has_value()) {
      surviving.push_back(candidate);
      continue;
    }
    auto domain = exprToDomain(candidate);
    if (!domain.has_value()) {
      surviving.push_back(candidate);
      continue;
    }

    auto it = domains.find(column);
    if (it == domains.end()) {
      domains.emplace(
          column, ColumnDomain{std::move(*domain), surviving.size()});
      surviving.push_back(nullptr);
    } else {
      it->second.values = it->second.values.intersect(*domain);
    }
  }

  for (const auto& [column, domain] : domains) {
    if (domain.values.isNone()) {
      return true;
    }
    surviving[domain.outputIndex] =
        domainToFilter(builder_, column, domain.values);
  }

  for (ExprCP expr : surviving) {
    if (expr != nullptr) {
      into.push_back(expr);
    }
  }
  return false;
}

ExprCP ExprSimplifier::tryFoldConstant(ExprCP expr) {
  if (expr->is(PlanType::kLiteralExpr)) {
    return expr;
  }

  // A call with default null behavior (result is null whenever any argument is
  // null) folds to null if any argument is the constant null -- even when its
  // other arguments reference columns. Special forms are given
  // kNonDefaultNullBehavior unconditionally, so they are excluded.
  // `Call::functions()` aggregates the arguments' bits, so the call's own bits
  // are recomputed here.
  if (expr->is(PlanType::kCallExpr)) {
    const auto* call = expr->as<Call>();
    const FunctionSet ownFunctions = functionBits(
        call->name(), SpecialFormCallNames::isSpecialForm(call->name()));
    if (!ownFunctions.contains(FunctionSet::kNonDefaultNullBehavior)) {
      for (ExprCP arg : call->args()) {
        if (arg->is(PlanType::kLiteralExpr) &&
            arg->as<Literal>()->literal().isNull()) {
          return builder_.makeNull(call->value().type);
        }
      }
    }
  }

  if (!expr->columns().empty()) {
    return expr;
  }

  velox::Variant variant;
  velox::TypePtr type;
  try {
    auto typedExpr = ExprEmitter{evaluator_.pool()}.toTypedExpr(expr);
    auto exprSet = evaluator_.compile(typedExpr);
    const auto& first = *exprSet->exprs().front();
    if (!first.isConstant()) {
      return expr;
    }
    const auto& constantExpr =
        static_cast<const velox::exec::ConstantExpr&>(first);
    variant = constantExpr.value()->variantAt(0);
    type = constantExpr.type();
  } catch (const velox::VeloxException&) {
    // Data-dependent evaluation failure on constant args (e.g.
    // division-by-zero, invalid cast). Leave the call unchanged so the
    // error surfaces at execution.
    return expr;
  }

  return builder_.makeLiteral(std::move(variant), toType(type));
}

velox::Variant ExprSimplifier::evaluate(ExprCP expr) {
  if (expr->is(PlanType::kLiteralExpr)) {
    return expr->as<Literal>()->literal();
  }

  VELOX_CHECK(
      expr->columns().empty(),
      "Expression to evaluate must not reference columns");

  if (emptyInput_ == nullptr) {
    emptyInput_ = std::make_shared<velox::RowVector>(
        evaluator_.pool(),
        velox::ROW({}),
        /*nulls=*/nullptr,
        /*length=*/1,
        std::vector<velox::VectorPtr>{});
  }

  auto typedExpr = ExprEmitter{evaluator_.pool()}.toTypedExpr(expr);
  auto exprSet = evaluator_.compile(typedExpr);
  velox::SelectivityVector rows(1);
  velox::VectorPtr result;
  evaluator_.evaluate(exprSet.get(), rows, *emptyInput_, result);
  return result->variantAt(0);
}

} // namespace facebook::axiom::optimizer::v2
