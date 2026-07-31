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

#include <mutex>

#include "axiom/connectors/ConnectorMetadata.h"

namespace facebook::axiom::optimizer {

class QueryGraphContext;

/// Default `FilterSelectivityEstimator`: estimates a filter's selectivity from
/// column statistics, relying only on the canonical conjunct form documented on
/// `TableLayout::createTableHandle` -- flattened conjuncts, column-first
/// comparisons (eq, lt, lte, gt, gte), and IN lists. Those canonical names are
/// dialect-independent (the optimizer normalizes filters to them before
/// pushdown), so the estimator makes no dialect assumption. Any conjunct
/// outside that documented form falls back to a default fraction, so the result
/// is always a usable selectivity.
///
/// Estimation uses the optimizer's QueryGraphContext (interned names, arena).
/// Construct on the optimizer thread; the active context is captured and
/// restored inside estimate() so a connector may call it from another thread
/// (e.g. its executor). A mutex serializes estimate() calls that share the
/// captured context.
class StatsFilterSelectivityEstimator
    : public connector::FilterSelectivityEstimator {
 public:
  StatsFilterSelectivityEstimator();

  connector::FilterEstimate estimate(
      const std::vector<velox::core::TypedExprPtr>& filters,
      const folly::F14FastMap<std::string, connector::TypedColumnStatistics>&
          columnStats) const override;

  connector::FilterEstimate estimate(
      const folly::F14FastMap<std::string, const velox::common::Filter*>&
          filters,
      const folly::F14FastMap<std::string, connector::TypedColumnStatistics>&
          columnStats) const override;

 private:
  QueryGraphContext* const context_;
  mutable std::mutex mutex_;
};

} // namespace facebook::axiom::optimizer
