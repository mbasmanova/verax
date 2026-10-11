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

#include "axiom/logical_plan/ReferencedTableCollector.h"

namespace facebook::axiom::logical_plan {

// static
ReferencedTables ReferencedTableCollector::collect(
    const LogicalPlanNode& plan) {
  ReferencedTables tables;
  plan.forEachNode([&](const LogicalPlanNode& node) {
    if (node.is(NodeKind::kTableScan)) {
      const auto* scan = node.as<TableScanNode>();
      tables.inputTables.insert(
          {.catalogName = scan->connectorId(),
           .schemaTableName = scan->tableName()});
      return;
    }

    if (!node.is(NodeKind::kTableWrite)) {
      return;
    }

    const auto* write = node.as<TableWriteNode>();
    CatalogSchemaTableName outputTable{
        .catalogName = write->connectorId(),
        .schemaTableName = write->tableName()};
    VELOX_USER_CHECK(
        !tables.outputTable.has_value(),
        "Plan cannot write more than one table: {} and {}",
        tables.outputTable.value(),
        outputTable);
    tables.outputTable = std::move(outputTable);
  });
  return tables;
}

} // namespace facebook::axiom::logical_plan
