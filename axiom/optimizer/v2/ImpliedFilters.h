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

#include "axiom/optimizer/v2/ExprFactory.h"

namespace facebook::axiom::optimizer::v2 {

/// Derives necessary filters by projecting every disjunct of an OR onto a
/// group of columns. For example, `(a = 1 AND b = 10) OR (a = 2 AND b = 20)`
/// implies both `a = 1 OR a = 2` and `b = 10 OR b = 20`.
class ImpliedFilters {
 public:
  /// Derives necessary filters for each join input from `filters`.
  static std::pair<ExprVector, ExprVector> deriveForJoinInputs(
      const ExprVector& filters,
      const PlanObjectSet& leftColumns,
      const PlanObjectSet& rightColumns,
      ExprFactory& factory);

  /// Derives new necessary single-column filters from ORs in `filters`.
  static ExprVector deriveForColumns(
      const ExprVector& filters,
      ExprFactory& factory);
};

} // namespace facebook::axiom::optimizer::v2
