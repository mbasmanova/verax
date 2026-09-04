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

#include "axiom/optimizer/ConstantFold.h"

#include <atomic>

#include <fmt/format.h>
#include <folly/container/F14Map.h>

#include "velox/common/base/Exceptions.h"
#include "velox/exec/Task.h"
#include "velox/vector/BaseVector.h"

namespace facebook::axiom::optimizer {

DiscreteLayout findDiscreteLayout(
    const ColumnVector& columns,
    const BaseTable& baseTable) {
  VELOX_CHECK(!columns.empty());

  for (auto* layout : baseTable.schemaTable->connectorTable->layouts()) {
    const auto& discreteColumns = layout->discretePredicateColumns();
    if (discreteColumns.empty()) {
      continue;
    }

    folly::F14FastMap<std::string_view, const connector::Column*>
        discreteColumnMap;
    for (const auto* column : discreteColumns) {
      discreteColumnMap.emplace(column->name(), column);
    }

    std::vector<const connector::Column*> connectorColumns;
    connectorColumns.reserve(columns.size());
    bool covered{true};
    for (auto* column : columns) {
      auto it = discreteColumnMap.find(column->schemaColumn()->name());
      if (it == discreteColumnMap.end()) {
        covered = false;
        break;
      }
      connectorColumns.emplace_back(it->second);
    }

    if (covered) {
      return {layout, std::move(connectorColumns)};
    }
  }

  return {};
}

std::vector<velox::Variant> toValues(
    connector::DiscretePredicates& discretePredicates) {
  std::vector<velox::Variant> valueRows;
  for (;;) {
    auto rows = discretePredicates.next();
    if (rows.empty()) {
      break;
    }

    valueRows.reserve(valueRows.size() + rows.size());
    for (auto& row : rows) {
      valueRows.emplace_back(std::move(row));
    }
  }

  return valueRows;
}

namespace {

int64_t nextConstantFoldId() {
  static std::atomic<int64_t> counter{0};
  return ++counter;
}

} // namespace

std::optional<velox::Variant> ConstantPlanRunner::runScalar(
    const velox::core::PlanFragment& fragment) const {
  VELOX_CHECK_EQ(
      fragment.planNode->outputType()->size(),
      1,
      "runScalar needs a fragment of one column");
  auto row = run(fragment);
  if (!row.has_value()) {
    return std::nullopt;
  }
  return std::move((*row)[0]);
}

std::optional<std::vector<velox::Variant>> ConstantPlanRunner::run(
    const velox::core::PlanFragment& fragment) const {
  // Serial mode runs in the caller's thread, so the query's own QueryCtx works
  // directly -- no executor, cache, or config of its own is needed.
  auto task = velox::exec::Task::create(
      fmt::format("constant_fold:{}", nextConstantFoldId()),
      fragment,
      /*destination=*/0,
      queryCtx_,
      velox::exec::Task::ExecutionMode::kSerial);

  // Serial mode runs the whole pipeline in this thread. 'fragment' has no
  // split-driven source and at most one row, so next() yields at most one
  // non-empty single-row batch.
  velox::RowVectorPtr result;
  while (auto batch = task->next()) {
    if (batch->size() == 0) {
      continue;
    }
    VELOX_CHECK_NULL(result, "Constant-fold plan produced more than one row");
    VELOX_CHECK_EQ(
        batch->size(), 1, "Constant-fold plan produced more than one row");
    result = batch;
  }

  if (result == nullptr) {
    return std::nullopt;
  }
  return result->variantAt(0).row();
}

} // namespace facebook::axiom::optimizer
