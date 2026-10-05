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

#include <optional>
#include <string>

#include <folly/container/F14Map.h>
#include "velox/core/PlanNode.h"

namespace facebook::axiom::optimizer {

/// Record the history data for a tracked PlanNode.
struct NodePrediction {
  /// Estimated result cardinality. An optimizer operator may lower to several
  /// Velox nodes; the entry is keyed by the outermost one, whose output is the
  /// operator's result.
  float cardinality{0};

  /// For a table scan, the estimated rows it reads, as reported by the
  /// connector; see `connector::FilteredTableStats::numRawInputRows`. Unset for
  /// every other node, and for a connector that does not report it.
  std::optional<uint64_t> numRawInputRows;

  /// For a table scan, the estimated size in bytes of a row it reads, as
  /// reported by the connector; see
  /// `connector::FilteredTableStats::numRawInputBytesPerRow`. Unset for every
  /// other node, and for a connector that does not report it.
  std::optional<float> numRawInputBytesPerRow;

  /// For a table scan, the estimated number of splits it produces. Unset for
  /// every other node, and for a connector that does not report it.
  std::optional<uint64_t> numSplits;

  /// Estimated size of an output row in bytes. Unset when the size of a
  /// variable-width output column is unknown.
  std::optional<float> numOutputBytesPerRow;

  /// Returns a human-readable summary of the estimate for annotating plan
  /// output.
  std::string toString() const;
};

using NodePredictionMap =
    folly::F14FastMap<velox::core::PlanNodeId, NodePrediction>;

} // namespace facebook::axiom::optimizer
