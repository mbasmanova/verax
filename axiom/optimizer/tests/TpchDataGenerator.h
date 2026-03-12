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

#pragma once

#include <functional>
#include "velox/dwio/common/Options.h"
#include "velox/tpch/gen/TpchGen.h"

namespace facebook::axiom::optimizer::test {

class TpchDataGenerator {
 public:
  /// Called before each table is created. Receives the table name.
  using TableStartingCallback = std::function<void(std::string_view tableName)>;

  /// Called after each table is created. Receives the table name and row count.
  using TableCreatedCallback =
      std::function<void(std::string_view tableName, int64_t numRows)>;

  /// Creates TPC-H tables via CTAS SQL, producing data files and persisted
  /// write-time stats (.stats files) for each table.
  static void createTables(
      const std::vector<velox::tpch::Table>& tables,
      std::string_view path,
      double scaleFactor = 0.1,
      velox::dwio::common::FileFormat format =
          velox::dwio::common::FileFormat::PARQUET,
      const TableStartingCallback& onTableStarting = nullptr,
      const TableCreatedCallback& onTableCreated = nullptr);
};

} // namespace facebook::axiom::optimizer::test
