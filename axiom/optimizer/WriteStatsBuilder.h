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

#include "axiom/connectors/ConnectorMetadata.h"
#include "axiom/optimizer/MultiFragmentPlan.h"
#include "velox/core/PlanNode.h"

namespace facebook::axiom::optimizer {

/// Builds ColumnStatsSpec instances for TableWrite and TableWriteMerge nodes.
/// Determines the topology (1, 2, or 3 specs) based on driver/worker counts:
///   - Single driver, single worker: writeSpec (kSingle)
///   - Multi driver, single worker: writeSpec (kPartial) + localMergeSpec
///     (kFinal)
///   - Multi worker: writeSpec (kPartial) + localMergeSpec (kIntermediate)
///     + finalMergeSpec (kFinal)
class WriteStatsBuilder {
 public:
  WriteStatsBuilder(
      const connector::Table& table,
      const velox::RowTypePtr& inputType,
      const connector::ConnectorWriteHandle& writeHandle,
      int32_t numDrivers,
      int32_t numWorkers);

  bool hasStats() const {
    return hasStats_;
  }

  bool needsMerge() const {
    return hasStats_ && needsMerge_;
  }

  bool needsFinalMerge() const {
    return hasStats_ && needsFinalMerge_;
  }

  WriteStatsMapping statsMapping() const {
    return statsMapping_;
  }

  /// Spec for the TableWriteNode. kSingle when no merge needed, kPartial
  /// with intermediate output types otherwise.
  velox::core::ColumnStatsSpec writeSpec() const;

  /// Spec for the local TableWriteMergeNode. kFinal (single worker) or
  /// kIntermediate (multi worker). Reads intermediate state from sourceType.
  velox::core::ColumnStatsSpec localMergeSpec(
      const velox::RowTypePtr& sourceType) const;

  /// Spec for the final TableWriteMergeNode in multi-worker writes. Always
  /// kFinal. Reads intermediate state from sourceType.
  velox::core::ColumnStatsSpec finalMergeSpec(
      const velox::RowTypePtr& sourceType) const;

 private:
  velox::core::ColumnStatsSpec buildMergeSpec(
      velox::core::AggregationNode::Step step,
      const velox::RowTypePtr& sourceType,
      const std::vector<velox::core::AggregationNode::Aggregate>&
          outputAggregates) const;

  bool hasStats_{false};
  bool needsMerge_{false};
  bool needsFinalMerge_{false};
  std::vector<velox::core::FieldAccessTypedExprPtr> groupingKeys_;
  std::vector<std::string> aggregateNames_;
  std::vector<velox::core::AggregationNode::Aggregate> aggregates_;
  WriteStatsMapping statsMapping_;
};

} // namespace facebook::axiom::optimizer
