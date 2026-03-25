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

#include "axiom/optimizer/ExplainIo.h"

#include <algorithm>

#include <folly/dynamic.h>
#include <folly/json.h>

#include "axiom/optimizer/QueryGraph.h"

namespace facebook::axiom::optimizer {

namespace {

// Serializes a table reference (catalog + schema + table) to JSON.
folly::dynamic tableToJson(
    const std::string& connectorId,
    const SchemaTableName& tableName) {
  return folly::dynamic::object("catalog", connectorId)(
      "schemaTable",
      folly::dynamic::object("schema", tableName.schema)(
          "table", tableName.table));
}

// Recursively collects all BaseTables from a DerivedTable tree.
void collectBaseTables(
    DerivedTableCP dt,
    std::vector<BaseTableCP>& baseTables) {
  for (auto* table : dt->tables) {
    if (table->is(PlanType::kTableNode)) {
      baseTables.push_back(table->as<BaseTable>());
    } else if (table->is(PlanType::kDerivedTableNode)) {
      collectBaseTables(table->as<DerivedTable>(), baseTables);
    }
  }
  for (auto* child : dt->children) {
    collectBaseTables(child, baseTables);
  }
}

} // namespace

std::string explainIo(
    DerivedTableCP rootDt,
    std::optional<CatalogSchemaTableName> outputTable) {
  std::vector<BaseTableCP> baseTables;
  collectBaseTables(rootDt, baseTables);

  // Sort by connector ID, schema, table for deterministic output.
  std::sort(baseTables.begin(), baseTables.end(), [](auto* lhs, auto* rhs) {
    auto leftTable = lhs->schemaTable;
    auto rightTable = rhs->schemaTable;
    if (leftTable->connectorId() != rightTable->connectorId()) {
      return leftTable->connectorId() < rightTable->connectorId();
    }
    if (leftTable->name().schema != rightTable->name().schema) {
      return leftTable->name().schema < rightTable->name().schema;
    }
    return leftTable->name().table < rightTable->name().table;
  });

  folly::dynamic tableInfos = folly::dynamic::array;

  for (auto* baseTable : baseTables) {
    folly::dynamic tableInfo = folly::dynamic::object;
    tableInfo["table"] = tableToJson(
        baseTable->schemaTable->connectorId(), baseTable->schemaTable->name());
    tableInfo["columnConstraints"] = folly::dynamic::array;
    tableInfos.push_back(std::move(tableInfo));
  }

  folly::dynamic root = folly::dynamic::object;
  root["inputTableColumnInfos"] = std::move(tableInfos);

  if (outputTable) {
    root["outputTable"] =
        tableToJson(outputTable->catalogName, outputTable->schemaTableName);
  }

  folly::json::serialization_opts opts;
  opts.pretty_formatting = true;
  opts.sort_keys = false;
  return folly::json::serialize(root, opts);
}

} // namespace facebook::axiom::optimizer
