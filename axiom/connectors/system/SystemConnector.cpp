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

#include "axiom/connectors/system/SystemConnector.h"

#include <algorithm>

#include "axiom/connectors/system/SystemConnectorMetadata.h"
#include "velox/common/base/Exceptions.h"
#include "velox/vector/ComplexVector.h"
#include "velox/vector/FlatVector.h"

namespace facebook::axiom::connector::system {

namespace {

/// Indices into the full queries table schema, matching the column order
/// returned by queriesTableSchema().
enum class QueryColumn : int32_t {
  kQueryId = 0,
  kState,
  kQuery,
  kCatalog,
  kSchema,
  kUser,
  kSource,
  kQueryType,
  kPlanningTimeMs,
  kOptimizationTimeMs,
  kQueueTimeMs,
  kExecutionTimeMs,
  kElapsedTimeMs,
  kCpuTimeMs,
  kWallTimeMs,
  kTotalSplits,
  kQueuedSplits,
  kRunningSplits,
  kFinishedSplits,
  kOutputRows,
  kOutputBytes,
  kProcessedRows,
  kProcessedBytes,
  kWrittenRows,
  kWrittenBytes,
  kPeakMemoryBytes,
  kSpilledBytes,
  kCreateTime,
  kStartTime,
  kEndTime,
  kNumColumns
};

// Converts a system_clock time_point to a Velox Timestamp.
// Returns a null Timestamp (0, 0) for the epoch (default-constructed
// time_point), which we treat as "not set".
velox::Timestamp toTimestamp(std::chrono::system_clock::time_point tp) {
  auto epoch = tp.time_since_epoch();
  auto secs = std::chrono::duration_cast<std::chrono::seconds>(epoch).count();
  auto nanos =
      std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count() %
      1'000'000'000;
  return velox::Timestamp(secs, nanos);
}

bool isEpoch(std::chrono::system_clock::time_point tp) {
  return tp == std::chrono::system_clock::time_point{};
}

} // namespace

// ===================== Data Sources (internal) =====================

// Reads live query state from a QueryInfoProvider.
class SystemDataSource : public velox::connector::DataSource {
 public:
  SystemDataSource(
      const velox::RowTypePtr& outputType,
      const velox::connector::ColumnHandleMap& columnHandles,
      const QueryInfoProvider* queryInfoProvider,
      velox::memory::MemoryPool* pool);

  void addSplit(
      std::shared_ptr<velox::connector::ConnectorSplit> split) override;

  std::optional<velox::RowVectorPtr> next(
      uint64_t size,
      velox::ContinueFuture& future) override;

  void addDynamicFilter(
      velox::column_index_t,
      const std::shared_ptr<velox::common::Filter>&) override {}

  uint64_t getCompletedBytes() override {
    return 0;
  }

  uint64_t getCompletedRows() override {
    return completedRows_;
  }

  std::unordered_map<std::string, velox::RuntimeMetric> getRuntimeStats()
      override {
    return {};
  }

 private:
  velox::RowVectorPtr buildQueryResults();

  const velox::RowTypePtr outputType_;
  const QueryInfoProvider* queryInfoProvider_;
  velox::memory::MemoryPool* pool_;
  std::shared_ptr<SystemSplit> split_;
  std::vector<velox::column_index_t> outputColumnMappings_;
  uint64_t completedRows_{0};
  bool needData_{true};
};

// Reads session properties from a SessionPropertiesProvider.
class SessionPropertiesDataSource : public velox::connector::DataSource {
 public:
  SessionPropertiesDataSource(
      const velox::RowTypePtr& outputType,
      const velox::connector::ColumnHandleMap& columnHandles,
      const SessionPropertiesProvider* provider,
      velox::memory::MemoryPool* pool);

  void addSplit(
      std::shared_ptr<velox::connector::ConnectorSplit> split) override;

  std::optional<velox::RowVectorPtr> next(
      uint64_t size,
      velox::ContinueFuture& future) override;

  void addDynamicFilter(
      velox::column_index_t,
      const std::shared_ptr<velox::common::Filter>&) override {}

  uint64_t getCompletedBytes() override {
    return 0;
  }

  uint64_t getCompletedRows() override {
    return completedRows_;
  }

  std::unordered_map<std::string, velox::RuntimeMetric> getRuntimeStats()
      override {
    return {};
  }

 private:
  velox::RowVectorPtr buildResults();

  const velox::RowTypePtr outputType_;
  const SessionPropertiesProvider* provider_;
  velox::memory::MemoryPool* pool_;
  std::shared_ptr<SystemSplit> split_;
  std::vector<velox::column_index_t> outputColumnMappings_;
  uint64_t completedRows_{0};
  bool needData_{true};
};

// ===================== SystemTableHandle =====================

SystemTableHandle::SystemTableHandle(
    const std::string& connectorId,
    const TableLayout& layout,
    std::vector<velox::connector::ColumnHandlePtr> columnHandles)
    : ConnectorTableHandle(connectorId),
      name_(layout.table().name().toString()),
      layout_(&layout),
      columnHandles_(std::move(columnHandles)) {}

SystemTableHandle::SystemTableHandle(
    const std::string& connectorId,
    std::string tableName,
    std::vector<velox::connector::ColumnHandlePtr> columnHandles)
    : ConnectorTableHandle(connectorId),
      name_(std::move(tableName)),
      layout_(nullptr),
      columnHandles_(std::move(columnHandles)) {}

velox::connector::ConnectorTableHandlePtr SystemTableHandle::create(
    const folly::dynamic& obj,
    void* /*context*/) {
  auto connectorId = obj["connectorId"].asString();
  auto tableName = obj["tableName"].asString();
  std::vector<velox::connector::ColumnHandlePtr> handles;
  for (const auto& handleObj : obj["columnHandles"]) {
    handles.push_back(
        velox::ISerializable::deserialize<SystemColumnHandle>(handleObj));
  }
  return std::make_shared<SystemTableHandle>(
      connectorId, std::move(tableName), std::move(handles));
}

// ===================== SystemDataSource =====================

SystemDataSource::SystemDataSource(
    const velox::RowTypePtr& outputType,
    const velox::connector::ColumnHandleMap& columnHandles,
    const QueryInfoProvider* queryInfoProvider,
    velox::memory::MemoryPool* pool)
    : outputType_(outputType),
      queryInfoProvider_(queryInfoProvider),
      pool_(pool) {
  auto fullSchema = queriesTableSchema();
  outputColumnMappings_.reserve(outputType_->size());
  for (const auto& name : outputType_->names()) {
    VELOX_CHECK(
        columnHandles.contains(name), "No handle for output column '{}'", name);
    auto handle = columnHandles.find(name)->second;
    auto idx = fullSchema->getChildIdxIfExists(handle->name());
    VELOX_CHECK(
        idx.has_value(),
        "Column '{}' not found in system.runtime.queries schema",
        handle->name());
    outputColumnMappings_.push_back(idx.value());
  }
}

void SystemDataSource::addSplit(
    std::shared_ptr<velox::connector::ConnectorSplit> split) {
  split_ = std::dynamic_pointer_cast<SystemSplit>(split);
  VELOX_CHECK(split_, "Expected SystemSplit");
  needData_ = true;
}

std::optional<velox::RowVectorPtr> SystemDataSource::next(
    uint64_t /*size*/,
    velox::ContinueFuture& /*future*/) {
  VELOX_CHECK(split_, "No split added to SystemDataSource");

  if (!needData_) {
    return nullptr;
  }
  needData_ = false;

  return buildQueryResults();
}

velox::RowVectorPtr SystemDataSource::buildQueryResults() {
  // If no query info provider is available (e.g. CLI mode), return empty
  // results.
  if (!queryInfoProvider_) {
    return velox::RowVector::createEmpty(outputType_, pool_);
  }

  auto queries = queryInfoProvider_->getQueryInfos();

  auto numRows = queries.size();
  completedRows_ += numRows;

  if (numRows == 0) {
    return velox::RowVector::createEmpty(outputType_, pool_);
  }

  auto fullSchema = queriesTableSchema();
  auto numFullColumns = static_cast<int32_t>(QueryColumn::kNumColumns);

  // Build all columns of the full schema.
  std::vector<velox::VectorPtr> allColumns(numFullColumns);

  for (size_t outIdx = 0; outIdx < outputColumnMappings_.size(); ++outIdx) {
    auto fullIdx = outputColumnMappings_[outIdx];

    // Skip if already built (possible but unlikely with column pruning).
    if (allColumns[fullIdx]) {
      continue;
    }

    auto col = static_cast<QueryColumn>(fullIdx);
    auto type = fullSchema->childAt(fullIdx);

    switch (col) {
      // VARCHAR columns
      case QueryColumn::kQueryId: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].queryId));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kState: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].state));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kQuery: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].query));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kCatalog: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].catalog));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kSchema: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].schema));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kUser: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].user));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kSource: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          if (queries[r].source.has_value()) {
            flat->set(r, velox::StringView(queries[r].source.value()));
          } else {
            vec->setNull(r, true);
          }
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kQueryType: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::StringView>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, velox::StringView(queries[r].queryType));
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }

      // BIGINT columns (time in ms)
      case QueryColumn::kPlanningTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].planningTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kOptimizationTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].optimizationTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kQueueTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].queueTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kExecutionTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].executionTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kElapsedTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].elapsedTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kCpuTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].cpuTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kWallTimeMs: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].wallTimeMs);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }

      // BIGINT columns (split counts)
      case QueryColumn::kTotalSplits: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].totalSplits);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kQueuedSplits: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].queuedSplits);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kRunningSplits: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].runningSplits);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kFinishedSplits: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].finishedSplits);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }

      // BIGINT columns (data volumes)
      case QueryColumn::kOutputRows: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].outputRows);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kOutputBytes: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].outputBytes);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kProcessedRows: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].processedRows);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kProcessedBytes: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].processedBytes);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kWrittenRows: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].writtenRows);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kWrittenBytes: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].writtenBytes);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kPeakMemoryBytes: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].peakMemoryBytes);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kSpilledBytes: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<int64_t>();
        for (size_t r = 0; r < numRows; ++r) {
          flat->set(r, queries[r].spilledBytes);
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }

      // TIMESTAMP columns
      case QueryColumn::kCreateTime: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::Timestamp>();
        for (size_t r = 0; r < numRows; ++r) {
          auto tp = queries[r].createTime;
          if (!isEpoch(tp)) {
            flat->set(r, toTimestamp(tp));
          } else {
            vec->setNull(r, true);
          }
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kStartTime: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::Timestamp>();
        for (size_t r = 0; r < numRows; ++r) {
          auto tp = queries[r].startTime;
          if (!isEpoch(tp)) {
            flat->set(r, toTimestamp(tp));
          } else {
            vec->setNull(r, true);
          }
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }
      case QueryColumn::kEndTime: {
        auto vec = velox::BaseVector::create(type, numRows, pool_);
        auto* flat = vec->asFlatVector<velox::Timestamp>();
        for (size_t r = 0; r < numRows; ++r) {
          auto tp = queries[r].endTime;
          if (!isEpoch(tp)) {
            flat->set(r, toTimestamp(tp));
          } else {
            vec->setNull(r, true);
          }
        }
        allColumns[fullIdx] = std::move(vec);
        break;
      }

      default:
        VELOX_FAIL("Unknown system column index: {}", fullIdx);
    }
  }

  // Build output vector with only the requested columns.
  std::vector<velox::VectorPtr> children;
  children.reserve(outputType_->size());
  for (size_t i = 0; i < outputColumnMappings_.size(); ++i) {
    children.push_back(allColumns[outputColumnMappings_[i]]);
  }

  return std::make_shared<velox::RowVector>(
      pool_, outputType_, nullptr, numRows, std::move(children));
}

// ===================== SessionPropertiesDataSource =====================

SessionPropertiesDataSource::SessionPropertiesDataSource(
    const velox::RowTypePtr& outputType,
    const velox::connector::ColumnHandleMap& columnHandles,
    const SessionPropertiesProvider* provider,
    velox::memory::MemoryPool* pool)
    : outputType_(outputType), provider_(provider), pool_(pool) {
  auto fullSchema = sessionPropertiesTableSchema();
  outputColumnMappings_.reserve(outputType_->size());
  for (const auto& name : outputType_->names()) {
    VELOX_CHECK(
        columnHandles.contains(name), "No handle for output column '{}'", name);
    auto handle = columnHandles.find(name)->second;
    auto idx = fullSchema->getChildIdxIfExists(handle->name());
    VELOX_CHECK(
        idx.has_value(),
        "Column '{}' not found in system.metadata.session_properties schema",
        handle->name());
    outputColumnMappings_.push_back(idx.value());
  }
}

void SessionPropertiesDataSource::addSplit(
    std::shared_ptr<velox::connector::ConnectorSplit> split) {
  split_ = std::dynamic_pointer_cast<SystemSplit>(split);
  VELOX_CHECK(split_, "Expected SystemSplit");
  needData_ = true;
}

std::optional<velox::RowVectorPtr> SessionPropertiesDataSource::next(
    uint64_t /*size*/,
    velox::ContinueFuture& /*future*/) {
  VELOX_CHECK(split_, "No split added to SessionPropertiesDataSource");

  if (!needData_) {
    return nullptr;
  }
  needData_ = false;

  return buildResults();
}

velox::RowVectorPtr SessionPropertiesDataSource::buildResults() {
  if (!provider_) {
    return velox::RowVector::createEmpty(outputType_, pool_);
  }

  auto properties = provider_->getSessionProperties();
  auto numRows = properties.size();
  completedRows_ += numRows;

  if (numRows == 0) {
    return velox::RowVector::createEmpty(outputType_, pool_);
  }

  // All 6 columns are VARCHAR. Build only the requested ones.
  // Column indices: 0=component, 1=name, 2=type, 3=default_value,
  // 4=current_value, 5=description.
  auto fullSchema = sessionPropertiesTableSchema();

  // Accessor for each column by index.
  auto getValue = [&](size_t row,
                      velox::column_index_t col) -> const std::string& {
    switch (col) {
      case 0:
        return properties[row].component;
      case 1:
        return properties[row].name;
      case 2:
        return properties[row].type;
      case 3:
        return properties[row].defaultValue;
      case 4:
        return properties[row].currentValue;
      case 5:
        return properties[row].description;
      default:
        VELOX_FAIL("Unknown session_properties column index: {}", col);
    }
  };

  std::vector<velox::VectorPtr> children;
  children.reserve(outputType_->size());
  for (auto fullIdx : outputColumnMappings_) {
    auto vec =
        velox::BaseVector::create(fullSchema->childAt(fullIdx), numRows, pool_);
    auto* flat = vec->asFlatVector<velox::StringView>();
    for (size_t row = 0; row < numRows; ++row) {
      flat->set(row, velox::StringView(getValue(row, fullIdx)));
    }
    children.push_back(std::move(vec));
  }

  return std::make_shared<velox::RowVector>(
      pool_, outputType_, nullptr, numRows, std::move(children));
}

// ===================== SystemConnector =====================

SystemConnector::SystemConnector(
    const std::string& id,
    const QueryInfoProvider* queryInfoProvider,
    const SessionPropertiesProvider* sessionPropertiesProvider)
    : Connector(id),
      queryInfoProvider_(queryInfoProvider),
      sessionPropertiesProvider_(sessionPropertiesProvider) {}

std::unique_ptr<velox::connector::DataSource> SystemConnector::createDataSource(
    const velox::RowTypePtr& outputType,
    const velox::connector::ConnectorTableHandlePtr& tableHandle,
    const velox::connector::ColumnHandleMap& columnHandles,
    velox::connector::ConnectorQueryCtx* connectorQueryCtx) {
  auto* systemHandle =
      dynamic_cast<const SystemTableHandle*>(tableHandle.get());
  VELOX_CHECK_NOT_NULL(systemHandle, "Expected SystemTableHandle");

  // Dispatch based on which table is being scanned. Use the handle's name
  // (always available) rather than layout() which is null after
  // deserialization.
  const auto& name = systemHandle->name();

  static const auto kSessionPropertiesName =
      SchemaTableName{
          std::string(kMetadataSchema), std::string(kSessionPropertiesTable)}
          .toString();
  static const auto kQueriesName =
      SchemaTableName{std::string(kRuntimeSchema), std::string(kQueriesTable)}
          .toString();

  if (name == kSessionPropertiesName) {
    return std::make_unique<SessionPropertiesDataSource>(
        outputType,
        columnHandles,
        sessionPropertiesProvider_,
        connectorQueryCtx->memoryPool());
  }

  if (name == kQueriesName) {
    return std::make_unique<SystemDataSource>(
        outputType,
        columnHandles,
        queryInfoProvider_,
        connectorQueryCtx->memoryPool());
  }

  VELOX_FAIL("Unknown system table: {}", name);
}

} // namespace facebook::axiom::connector::system
