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

#include <string>
#include "velox/common/memory/MemoryPool.h"
#include "velox/connectors/hive/HiveConnector.h"
#include "velox/dwio/common/Options.h"

namespace facebook::axiom::connector::hive {

/// Scans a directory of data files to produce .schema and .stats metadata
/// artifacts. After building, the table directory contains everything
/// LocalHiveConnectorMetadata needs to serve queries without reading file
/// headers at init time.
///
/// Usage:
///   LocalTableBuilder builder(pool, fileFormat, connector);
///   builder.build("/path/to/table_dir");
///
/// Reads all data files, infers schema from file headers, collects
/// per-column statistics (min, max, null count), estimates NDV by
/// sampling, and writes .schema and .stats files.
class LocalTableBuilder {
 public:
  /// Constructs a builder. 'pool' is used for DWIO readers and sampling.
  /// 'fileFormat' is the file format (e.g., DWRF, PARQUET); all data files in
  /// the table directory are expected to use this format. 'connector' is used
  /// for creating data sources during NDV sampling (only public APIs are used).
  /// Pass nullptr to skip NDV sampling. 'samplePct' is the percentage of rows
  /// to sample (automatically reduced for tables > 1M rows).
  LocalTableBuilder(
      velox::memory::MemoryPool* pool,
      velox::dwio::common::FileFormat fileFormat,
      velox::connector::hive::HiveConnector* connector = nullptr,
      float samplePct = 10.0f);

  /// Scans data files in 'tablePath', infers schema from file headers and
  /// computes column statistics. Writes .schema and .stats files. If .schema
  /// already exists, uses it instead of inferring from file headers. Overwrites
  /// any existing .stats file. All files must have the same schema. Currently
  /// supports unpartitioned tables only.
  void build(const std::string& tablePath);

 private:
  // Samples data to estimate NDV for each column. Uses the connector's
  // public createDataSource() API. Updates the .stats file with NDV estimates.
  void sampleNumDistincts(
      const std::string& tablePath,
      const velox::RowTypePtr& schema,
      uint64_t totalRows);

  // Memory pool for DWIO readers and sampling.
  velox::memory::MemoryPool* const pool_;

  // File format for reading data files. All files are expected to use the
  // same format.
  const velox::dwio::common::FileFormat fileFormat_;

  // Hive connector for creating data sources during NDV sampling.
  velox::connector::hive::HiveConnector* const connector_;

  // Percentage of rows to sample for NDV estimation.
  const float samplePct_;
};

} // namespace facebook::axiom::connector::hive
