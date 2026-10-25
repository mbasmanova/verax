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

#include <span>

#include "axiom/optimizer/Filters.h"

namespace facebook::axiom::optimizer {

/// Combines column statistics across the inputs of a union.
struct UnionConstraints {
  /// Returns the statistics of a union's output column from the matching column
  /// of each input. 'inputs[i]' is that column's statistics in input i and
  /// 'cardinalities[i]' is input i's row count; both are non-empty and of
  /// equal size.
  ///   - min / max: the widest bounds. An all-null input adds no bound; an
  ///     input with an unknown bound leaves that bound unknown.
  ///   - null and true fractions: averages weighted by row count.
  ///   - NDV: the inputs' non-null distinct values, assuming uniform density
  ///     within each input's integer range and independence across inputs. Each
  ///     input is matched against the covered ranges it overlaps, and the
  ///     values expected in both are counted once; disjoint inputs sum in any
  ///     order. An input without an integer range counts as disjoint from the
  ///     rest, and an all-null input adds nothing.
  static Value combine(
      std::span<const Value* const> inputs,
      std::span<const std::optional<float>> cardinalities);
};

} // namespace facebook::axiom::optimizer
