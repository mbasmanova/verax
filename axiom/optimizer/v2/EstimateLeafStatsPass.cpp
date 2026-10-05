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

#include "axiom/optimizer/v2/EstimateLeafStatsPass.h"

#include <algorithm>
#include <cmath>

#include "axiom/optimizer/v2/Builder.h"
#include "axiom/optimizer/v2/NodeRewriter.h"
#include "axiom/optimizer/v2/PrecomputeProjections.h"
#include "axiom/optimizer/v2/ScanHandle.h"

#include <folly/container/F14Set.h>
#include "folly/coro/BlockingWait.h"
#include "folly/coro/Collect.h"

#include "axiom/connectors/ConnectorMetadata.h"
#include "axiom/optimizer/OptimizerMetrics.h"
#include "axiom/optimizer/QueryGraph.h"
#include "axiom/optimizer/QueryGraphContext.h"
#include "axiom/optimizer/Schema.h"
#include "axiom/optimizer/StatsFilterSelectivityEstimator.h"

namespace facebook::axiom::optimizer::v2 {

namespace {

// Collects the Scan nodes reachable from 'node'.
void collectScans(NodeCP node, std::vector<ScanCP>& scans) {
  if (node->is(NodeType::kScan)) {
    scans.push_back(node->as<Scan>());
    return;
  }

  for (NodeCP input : node->inputs()) {
    collectScans(input, scans);
  }
}

// Overwrites 'column''s Value with connector-provided per-column statistics.
void applyColumnStats(
    ColumnCP column,
    const connector::ColumnStatistics& stats) {
  const auto& existing = column->value();
  const_cast<Value&>(existing) =
      Value::fromColumnStatistics(existing.type, stats);
}

// Scales 'count', a number of rows or splits a scan of 'baseTable' produces
// without sampling, by its TABLESAMPLE SYSTEM rate, which keeps each split
// with that probability.
std::optional<uint64_t> sampled(
    const BaseTable& baseTable,
    std::optional<uint64_t> count) {
  if (!count.has_value() || !baseTable.sampledPercentage.has_value()) {
    return count;
  }
  return static_cast<uint64_t>(
      std::llround(*count * (*baseTable.sampledPercentage / 100.0)));
}

// Applies one base table's connector stats result. Sets filteredCardinality to
// the connector's post-filter row count. A nullopt result (the connector does
// not support stats) leaves filteredCardinality at 0 so downstream estimation
// falls back to constraint-based selectivity.
bool applyFilteredStats(
    const Scan& scan,
    const std::vector<ColumnCP>& statColumns,
    const std::optional<connector::FilteredTableStats>& stats) {
  if (!stats.has_value()) {
    return false;
  }

  auto* baseTable = const_cast<BaseTable*>(scan.baseTable());

  baseTable->numRawInputRows = sampled(*baseTable, stats->numRawInputRows);
  baseTable->numRawInputBytesPerRow = stats->numRawInputBytesPerRow;
  baseTable->numSplits = sampled(*baseTable, stats->numSplits);

  if (!stats->columnStats.empty()) {
    VELOX_CHECK_EQ(stats->columnStats.size(), statColumns.size());
    for (size_t i = 0; i < stats->columnStats.size(); ++i) {
      applyColumnStats(statColumns[i], stats->columnStats[i]);
    }
  }

  // numRows is post-filter for the filters the connector took; the refused
  // ones are estimated at the Filter above the scan.
  baseTable->filteredCardinality = std::max<float>(1, stats->numRows);
  return stats->isKnownEmpty;
}

// Carries a proven-empty result from a child to its parent.
struct KnownEmptyContext {
  bool isKnownEmpty{false};
};

// Propagates proven-empty scans through operators and materializes Values where
// the fact cannot propagate farther or at the root.
class KnownEmptyRewriter : public NodeRewriter<KnownEmptyContext> {
 public:
  KnownEmptyRewriter(
      Builder& builder,
      folly::F14FastSet<ScanCP> knownEmptyScans)
      : NodeRewriter(builder), knownEmptyScans_(std::move(knownEmptyScans)) {}

 protected:
  NodeCP rewriteScan(const Scan* node, KnownEmptyContext& context) override {
    context.isKnownEmpty |= knownEmptyScans_.contains(node);
    return node;
  }

  NodeCP rewriteValues(const Values* node, KnownEmptyContext& context)
      override {
    context.isKnownEmpty |= node->cardinality() == 0;
    return node;
  }

  NodeCP rewriteAggregate(const Aggregate* node, KnownEmptyContext& context)
      override {
    KnownEmptyContext childContext;
    NodeCP newInput = rewrite(node->input(), childContext);
    if (childContext.isKnownEmpty) {
      const bool emitsRowOnEmptyInput =
          node->groupingKeys().empty() || !node->globalGroupingSets().empty();
      if (!emitsRowOnEmptyInput) {
        context.isKnownEmpty = true;
        return node;
      }
      newInput = makeEmptyValues(node->input());
    }
    if (newInput == node->input()) {
      return node;
    }
    return builder().make<Aggregate>(
        {.input = newInput,
         .groupingKeys = node->groupingKeys(),
         .aggregates = node->aggregates(),
         .outputColumns = node->outputColumns(),
         .step = node->step(),
         .groupId = node->groupId(),
         .globalGroupingSets = node->globalGroupingSets()});
  }

  NodeCP rewriteJoin(const Join* node, KnownEmptyContext& context) override {
    KnownEmptyContext leftContext;
    KnownEmptyContext rightContext;
    NodeCP newLeft = rewrite(node->left(), leftContext);
    NodeCP newRight = rewrite(node->right(), rightContext);
    if (Join::isKnownEmpty(
            node->joinType(),
            leftContext.isKnownEmpty,
            rightContext.isKnownEmpty)) {
      context.isKnownEmpty = true;
      return node;
    }
    if (leftContext.isKnownEmpty != rightContext.isKnownEmpty) {
      NodeCP remaining = leftContext.isKnownEmpty ? newRight : newLeft;
      auto expressions = builder().paddedExpressions(
          remaining->outputColumns(),
          node->sourceColumns(),
          /*falsePadding=*/Join::projectsMark(node->joinType()));
      return projectExpressions(
          remaining, std::move(expressions), node->outputColumns());
    }
    if (leftContext.isKnownEmpty) {
      newLeft = makeEmptyValues(node->left());
    }
    if (rightContext.isKnownEmpty) {
      newRight = makeEmptyValues(node->right());
    }
    if (newLeft == node->left() && newRight == node->right()) {
      return node;
    }
    if (node->joinType() == velox::core::JoinType::kInner &&
        node->leftKeys().empty() && node->filter().empty()) {
      if (Values::isSingleRowNoColumns(newLeft)) {
        return projectColumns(
            newRight, node->outputColumns(), node->outputColumns());
      }
      if (Values::isSingleRowNoColumns(newRight)) {
        return projectColumns(
            newLeft, node->outputColumns(), node->outputColumns());
      }
    }
    return builder().make<Join>(
        {newLeft,
         newRight,
         node->joinType(),
         node->leftKeys(),
         node->rightKeys(),
         node->filter(),
         node->nullAware(),
         node->nullAsValue(),
         node->outputColumns(),
         node->sourceColumns()});
  }

  NodeCP rewriteUnionAll(const UnionAll* node, KnownEmptyContext& context)
      override {
    NodeVector newInputs;
    newInputs.reserve(node->inputs().size());
    QGVector<ColumnVector> newLegColumns;
    newLegColumns.reserve(node->legColumns().size());
    bool changed{false};
    for (size_t i = 0; i < node->inputs().size(); ++i) {
      NodeCP input = node->inputs()[i];
      KnownEmptyContext childContext;
      NodeCP newInput = rewrite(input, childContext);
      if (childContext.isKnownEmpty) {
        changed = true;
        continue;
      }
      changed |= newInput != input;
      newInputs.push_back(newInput);
      newLegColumns.push_back(node->legColumns()[i]);
    }

    if (newInputs.empty()) {
      context.isKnownEmpty = true;
      return node;
    }

    if (newInputs.size() == 1) {
      return projectColumns(
          newInputs.front(), newLegColumns.front(), node->outputColumns());
    }

    return changed ? builder().make<UnionAll>(
                         {std::move(newInputs),
                          std::move(newLegColumns),
                          node->outputColumns()})
                   : static_cast<NodeCP>(node);
  }

  NodeCP rewriteEnforceSingleRow(
      const EnforceSingleRow* node,
      KnownEmptyContext& /*context*/) override {
    KnownEmptyContext childContext;
    NodeCP newInput = rewrite(node->input(), childContext);
    if (childContext.isKnownEmpty) {
      return makeNullRowValues(node);
    }
    return newInput == node->input()
        ? static_cast<NodeCP>(node)
        : builder().make<EnforceSingleRow>({newInput, node->outputColumns()});
  }

  NodeCP rewriteTableWrite(
      const TableWrite* node,
      KnownEmptyContext& /*context*/) override {
    KnownEmptyContext childContext;
    NodeCP newInput = rewrite(node->input(), childContext);
    if (childContext.isKnownEmpty) {
      newInput = makeEmptyValues(node->input());
    }
    return newInput == node->input()
        ? static_cast<NodeCP>(node)
        : builder().make<TableWrite>(
              {newInput, node->table(), node->kind(), node->columnExprs()});
  }

  NodeCP rewriteFixedPoint(const FixedPoint* node, KnownEmptyContext& context)
      override {
    KnownEmptyContext anchorContext;
    NodeCP newAnchor = rewrite(node->anchor(), anchorContext);
    if (anchorContext.isKnownEmpty) {
      context.isKnownEmpty = true;
      return node;
    }

    KnownEmptyContext stepContext;
    NodeCP newStep = rewrite(node->step(), stepContext);
    if (stepContext.isKnownEmpty) {
      return newAnchor;
    }
    if (newStep->requiredStates() != node->step()->requiredStates()) {
      newStep = node->step();
    }

    KnownEmptyContext convergenceContext;
    NodeCP newConvergence = rewrite(node->convergence(), convergenceContext);
    if (newConvergence->requiredStates() !=
        node->convergence()->requiredStates()) {
      newConvergence = node->convergence();
    }

    if (newAnchor == node->anchor() && newStep == node->step() &&
        newConvergence == node->convergence()) {
      return node;
    }
    return builder().make<FixedPoint>({
        .anchor = newAnchor,
        .step = newStep,
        .convergence = newConvergence,
        .name = node->name(),
        .outputColumns = node->outputColumns(),
        .sourceColumns = node->sourceColumns(),
        .maxIterations = node->maxIterations(),
        .recursiveNumDrivers = node->recursiveNumDrivers(),
    });
  }

 private:
  // Projects 'expressions' onto 'outputColumns', composing an input Project
  // when safe and removing an identity Project.
  NodeCP projectExpressions(
      NodeCP input,
      ExprVector expressions,
      const ColumnVector& outputColumns) {
    PrecomputeProjections::inlineInputProject(input, expressions, builder());
    if (input->outputColumns() == outputColumns &&
        std::equal(
            expressions.begin(), expressions.end(), outputColumns.begin())) {
      return input;
    }
    return builder().make<Project>(
        {input, std::move(expressions), outputColumns});
  }

  // Projects 'inputColumns' onto 'outputColumns'.
  NodeCP projectColumns(
      NodeCP input,
      const ColumnVector& inputColumns,
      const ColumnVector& outputColumns) {
    return projectExpressions(
        input,
        ExprVector(inputColumns.begin(), inputColumns.end()),
        outputColumns);
  }

  NodeCP makeEmptyValues(NodeCP node) {
    return builder().makeEmptyValues(node->outputColumns());
  }

  // Returns one row containing a typed NULL for each output column of 'node'.
  NodeCP makeNullRowValues(NodeCP node) {
    std::vector<velox::Variant> row;
    row.reserve(node->outputColumns().size());
    for (ColumnCP column : node->outputColumns()) {
      row.push_back(velox::Variant::null(column->value().type->kind()));
    }

    return builder().makeSingleRowValues(std::move(row), node->outputColumns());
  }

  // Scans whose accepted filters were proven to match no rows.
  const folly::F14FastSet<ScanCP> knownEmptyScans_;
};

} // namespace

NodeCP EstimateLeafStatsPass::run(
    NodeCP root,
    Builder& builder,
    const OptimizerSession& session) {
  std::vector<ScanCP> scans;
  collectScans(root, scans);

  // One stats request per scan.
  struct TableTask {
    ScanCP scan;
    std::vector<ColumnCP> statColumns;
  };
  std::vector<TableTask> tasks;
  std::vector<folly::coro::Task<std::optional<connector::FilteredTableStats>>>
      requests;

  // Shared helper offered to each connector's co_estimateStats. Outlives the
  // coroutines below, which run under blockingWait before this returns.
  StatsFilterSelectivityEstimator estimator;

  for (ScanCP scan : scans) {
    const auto* baseTable = scan->baseTable();
    const ScanHandle* handle = scan->scanHandle();
    VELOX_CHECK_NOT_NULL(
        handle, "Filtered-table stats need the connector's read handle");

    const auto* layout = baseTable->schemaTable->columnGroups[0]->layout;
    auto connectorSession =
        session.context()->sessionFor(layout->connectorId());

    // Subfield columns have no connector-level statistics.
    std::vector<ColumnCP> statColumns;
    std::vector<std::string> columnNames;
    for (ColumnCP column : scan->outputColumns()) {
      if (column->topColumn() == nullptr) {
        statColumns.push_back(column);
        columnNames.emplace_back(column->name());
      }
    }

    tasks.push_back(TableTask{scan, std::move(statColumns)});
    requests.push_back(layout->co_estimateStats(
        std::move(connectorSession),
        handle->tableHandle,
        std::move(columnNames),
        estimator));
  }

  if (requests.empty()) {
    return root;
  }

  // No optimizer-time executor is available, so the requests run inline. They
  // are still launched together so a connector that suspends on I/O can
  // overlap them.
  auto estimateStart = std::chrono::steady_clock::now();
  auto results = folly::coro::blockingWait(
      folly::coro::collectAllRange(std::move(requests)));
  session.statsWriter().addTiming(
      OptimizerMetrics::kEstimateStatsWallNanos,
      std::chrono::steady_clock::now() - estimateStart);

  folly::F14FastSet<ScanCP> knownEmptyScans;
  for (size_t i = 0; i < tasks.size(); ++i) {
    if (applyFilteredStats(*tasks[i].scan, tasks[i].statColumns, results[i])) {
      knownEmptyScans.insert(tasks[i].scan);
    }
  }
  if (knownEmptyScans.empty()) {
    return root;
  }

  KnownEmptyContext context;
  NodeCP rewritten =
      KnownEmptyRewriter{builder, std::move(knownEmptyScans)}.rewrite(
          root, context);
  return context.isKnownEmpty ? builder.makeEmptyValues(root->outputColumns())
                              : rewritten;
}

} // namespace facebook::axiom::optimizer::v2
