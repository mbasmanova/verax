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

#include "axiom/optimizer/v2/ScanHandle.h"

#include "axiom/optimizer/QueryGraph.h"
#include "axiom/optimizer/Schema.h"
#include "axiom/optimizer/v2/ExprEmitter.h"

namespace facebook::axiom::optimizer::v2 {

ScanHandle ScanHandle::build(
    const Scan& scan,
    const OptimizerSession& session,
    velox::core::ExpressionEvaluator& evaluator) {
  const auto* baseTable = scan.baseTable();
  const auto* layout = baseTable->schemaTable->columnGroups[0]->layout;
  auto connectorSession =
      session.toConnectorSession(layout->connector()->connectorId());

  // Read schema is the consumer output columns plus the columns referenced
  // only by filters; the latter keep their schema names.
  folly::F14FastSet<Name> seenSchemaNames;
  const ColumnVector& consumerColumns = scan.outputColumns();
  for (ColumnCP column : consumerColumns) {
    seenSchemaNames.insert(column->name());
  }
  ColumnVector filterOnlyColumns;
  PlanObjectSet filterColumns;
  filterColumns.unionColumns(scan.filters());
  filterColumns.forEach<Column>([&](ColumnCP column) {
    if (seenSchemaNames.insert(column->name()).second) {
      filterOnlyColumns.push_back(column);
    }
  });

  std::vector<velox::connector::ColumnHandlePtr> columnHandles;
  columnHandles.reserve(consumerColumns.size() + filterOnlyColumns.size());
  for (ColumnCP column : consumerColumns) {
    columnHandles.push_back(layout->createColumnHandle(
        connectorSession, column->name(), /*subfields=*/{}));
  }
  for (ColumnCP column : filterOnlyColumns) {
    columnHandles.push_back(layout->createColumnHandle(
        connectorSession, column->name(), /*subfields=*/{}));
  }

  // Build the filters as TypedExpr, keeping an aligned ExprCP list.
  // createTableHandle reports the rejected filters by index into this list, so
  // each can be mapped back to its ExprCP for the optimizer to post-apply its
  // selectivity.
  ExprEmitter exprEmitter{evaluator.pool()};
  ExprVector conjunctExprs;
  std::vector<velox::core::TypedExprPtr> filters;
  filters.reserve(scan.filters().size());
  for (ExprCP filter : scan.filters()) {
    conjunctExprs.push_back(filter);
    filters.push_back(
        exprEmitter.toTypedExpr(filter, ColumnNaming::kSchemaName));
  }
  std::vector<velox::core::TypedExprPtr> allConjuncts = filters;

  std::vector<int32_t> rejectedFilterIndices;
  velox::connector::ConnectorTableHandlePtr tableHandle =
      layout->createTableHandle(
          connectorSession,
          columnHandles,
          evaluator,
          std::move(filters),
          rejectedFilterIndices);

  // Each rejected index selects a conjunct to apply as a Filter above the scan
  // (as TypedExpr) and to post-apply selectivity for (as ExprCP).
  std::vector<velox::core::TypedExprPtr> rejectedFilters;
  ExprVector rejectedExprs;
  for (int32_t index : rejectedFilterIndices) {
    VELOX_CHECK_GE(
        index,
        0,
        "createTableHandle returned a negative rejected filter index");
    VELOX_CHECK_LT(
        index,
        static_cast<int32_t>(conjunctExprs.size()),
        "createTableHandle returned an out-of-range rejected filter index");
    rejectedFilters.push_back(allConjuncts[index]);
    rejectedExprs.push_back(conjunctExprs[index]);
  }

  return ScanHandle{
      .tableHandle = std::move(tableHandle),
      .columnHandles = std::move(columnHandles),
      .filterOnlyColumns = std::move(filterOnlyColumns),
      .rejectedFilters = std::move(rejectedFilters),
      .rejectedExprs = std::move(rejectedExprs),
  };
}

const ScanHandle& ScanHandleCache::getOrBuild(
    const Scan& scan,
    const OptimizerSession& session,
    velox::core::ExpressionEvaluator& evaluator) {
  const int32_t id = scan.baseTable()->id();
  auto it = byBaseTableId_.find(id);
  if (it != byBaseTableId_.end()) {
    return it->second;
  }
  return byBaseTableId_.emplace(id, ScanHandle::build(scan, session, evaluator))
      .first->second;
}

const ScanHandle* ScanHandleCache::find(const Scan& scan) const {
  auto it = byBaseTableId_.find(scan.baseTable()->id());
  return it != byBaseTableId_.end() ? &it->second : nullptr;
}

} // namespace facebook::axiom::optimizer::v2
