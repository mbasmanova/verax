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

#include "axiom/connectors/SchemaResolver.h"

namespace facebook::axiom::connector {

void SchemaResolver::setTargetTable(
    const std::string& connectorId,
    const SchemaTableName& tableName,
    TablePtr table) {
  VELOX_CHECK_NULL(targetTable_);

  targetConnectorId_ = connectorId;
  targetTableName_ = tableName;
  targetTable_ = std::move(table);
}

TablePtr SchemaResolver::findTable(
    const std::string& connectorId,
    const SchemaTableName& tableName) const {
  if (targetTable_ && connectorId == targetConnectorId_ &&
      tableName == targetTableName_) {
    return targetTable_;
  }

  return ConnectorMetadata::metadata(connectorId)->findTable(tableName);
}

} // namespace facebook::axiom::connector
