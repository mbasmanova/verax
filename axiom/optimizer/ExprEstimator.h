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

#include "axiom/optimizer/Filters.h"

namespace facebook::axiom::optimizer {

/// Estimates the statistics of an expression from the statistics of what it
/// reads: the current estimates of the columns in 'constraints', and the rules
/// for each kind of subexpression.
///
/// Records the estimate of every expression it visits in 'constraints', keyed
/// by the expression's id.
///
/// Usage: `Value value = ExprEstimator(constraints).estimate(expr);`
class ExprEstimator {
 public:
  explicit ExprEstimator(ConstraintMap& constraints)
      : constraints_{constraints} {}

  /// Returns the estimate of 'expr'. With 'update', re-estimates a call or
  /// field access already in 'constraints'; a column or literal keeps its
  /// recorded estimate.
  Value estimate(ExprCP expr, bool update = false);

  /// Returns the estimate of 'aggregate's output, one value per group, given
  /// the number of groups. The arguments are estimated over the aggregation's
  /// input. For example, max(x) returns one of x's values, so its NDV, min and
  /// max are x's (see FunctionMetadata::DrawnFrom).
  Value estimateAggregate(
      const Aggregate& aggregate,
      std::optional<float> numGroups);

 private:
  // Returns the estimate of 'call' from its arguments' estimates.
  Value estimateCall(const Call& call, bool update);

  ConstraintMap& constraints_;
};

} // namespace facebook::axiom::optimizer
