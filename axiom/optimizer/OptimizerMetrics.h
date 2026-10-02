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

#include <string_view>

namespace facebook::axiom {

/// The names of the metrics the optimizer records into its session's stat
/// writer.
struct OptimizerMetrics {
  /// Covers waiting for the connector statistics requests the optimizer issues
  /// per table, and stops when the last one returns. Nests inside the optimize
  /// phase timing.
  static constexpr std::string_view kEstimateStatsWallNanos{
      "estimateStatsWallNanos"};

  /// One sample per table resolved from the connector. Repeat references
  /// within an optimization run hit the Schema's cache and are not sampled, so
  /// count is below the number of table references in the query. Nests inside
  /// the optimize phase timing.
  static constexpr std::string_view kFindTableWallNanos{"findTableWallNanos"};

  /// Number of plan objects the query created, the count that
  /// OptimizerOptions::maxPlanObjects caps. One sample per planned query.
  static constexpr std::string_view kPlanObjects{"planObjects"};

  /// Bytes the planning arena holds when planning ends, including freed
  /// allocations it keeps for reuse. One sample per planned query.
  static constexpr std::string_view kArenaBytes{"arenaBytes"};
};

} // namespace facebook::axiom
