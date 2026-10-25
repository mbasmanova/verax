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

#include "axiom/optimizer/UnionConstraints.h"

#include <algorithm>
#include <functional>
#include <vector>

#include "axiom/optimizer/EstimateMath.h"

namespace facebook::axiom::optimizer {

namespace {
// The widest of the inputs' 'field' bounds, where 'widens(candidate, bound)'
// is true when 'candidate' lies outside 'bound'. An all-null input adds no
// bound; any other input with an unknown bound leaves the result unknown.
template <typename Widens>
VariantCP widestBound(
    std::span<const Value* const> inputs,
    VariantCP Value::* field,
    Widens widens) {
  VariantCP result = nullptr;
  for (const Value* input : inputs) {
    if (input->nullFraction == 1.0f) {
      continue;
    }
    VariantCP candidate = input->*field;
    if (candidate == nullptr) {
      return nullptr;
    }
    if (result == nullptr || widens(*candidate, *result)) {
      result = candidate;
    }
  }
  return result;
}
// Distinct values of an integer range covered by union inputs.
struct CoveredRange {
  VariantCP min;
  VariantCP max;
  float ndv;
};

// The NDV of 'range' per value of its span, at most one.
float density(TypeCP type, VariantCP min, VariantCP max, float ndv) {
  const std::optional<float> span = rangeCardinality(type, min, max);
  return span.has_value() && *span > 0 ? std::min(1.0f, ndv / *span) : 1.0f;
}

// The NDV of a union's output column; see `UnionConstraints::combine`.
std::optional<float> unionNdv(
    TypeCP type,
    std::span<const Value* const> inputs) {
  std::vector<CoveredRange> covered;
  float rangeless = 0;
  bool contributed = false;
  for (const Value* input : inputs) {
    if (input->nullFraction == 1.0f) {
      continue;
    }
    if (!input->cardinality.has_value()) {
      return std::nullopt;
    }
    contributed = true;
    const float ndv = *input->cardinality;
    if (!rangeCardinality(type, input->min, input->max).has_value()) {
      rangeless += ndv;
      continue;
    }
    const float inputDensity = density(type, input->min, input->max, ndv);
    CoveredRange merged{input->min, input->max, ndv};
    float largest = ndv;
    float sum = ndv;
    float shared = 0;
    std::vector<CoveredRange> rest;
    for (const CoveredRange& range : covered) {
      if (*range.max < *input->min || *input->max < *range.min) {
        rest.push_back(range);
        continue;
      }
      VariantCP overlapMin = *range.min < *input->min ? input->min : range.min;
      VariantCP overlapMax = *input->max < *range.max ? input->max : range.max;
      shared += rangeCardinality(type, overlapMin, overlapMax).value_or(0) *
          density(type, range.min, range.max, range.ndv) * inputDensity;
      merged.min = *range.min < *merged.min ? range.min : merged.min;
      merged.max = *merged.max < *range.max ? range.max : merged.max;
      largest = std::max(largest, range.ndv);
      sum += range.ndv;
    }
    merged.ndv = std::clamp(sum - shared, largest, sum);
    rest.push_back(merged);
    covered = std::move(rest);
  }
  if (!contributed) {
    return inputs[0]->cardinality;
  }
  float total = rangeless;
  for (const CoveredRange& range : covered) {
    total += range.ndv;
  }
  return total;
}

} // namespace

Value UnionConstraints::combine(
    std::span<const Value* const> inputs,
    std::span<const std::optional<float>> cardinalities) {
  VELOX_CHECK_GT(inputs.size(), 0);
  VELOX_CHECK_EQ(inputs.size(), cardinalities.size());

  Value combined = *inputs[0];

  combined.min = widestBound(inputs, &Value::min, std::less<>());
  // std::greater needs operator>, which Variant lacks, so the max swaps the
  // arguments of operator<.
  combined.max = widestBound(
      inputs, &Value::max, [](const auto& a, const auto& b) { return b < a; });

  std::optional<float> totalRows = cardinalities[0];
  std::optional<float> weightedNullFraction =
      mul(combined.nullFraction, totalRows);
  std::optional<float> weightedTrueFraction =
      mul(combined.trueFraction, totalRows);
  for (size_t i = 1; i < inputs.size(); ++i) {
    totalRows = add(totalRows, cardinalities[i]);
    weightedNullFraction = add(
        weightedNullFraction, mul(inputs[i]->nullFraction, cardinalities[i]));
    weightedTrueFraction = add(
        weightedTrueFraction, mul(inputs[i]->trueFraction, cardinalities[i]));
    combined.nullable = combined.nullable || inputs[i]->nullable;
  }
  combined.nullFraction = divide(weightedNullFraction, totalRows);
  combined.trueFraction = divide(weightedTrueFraction, totalRows);

  combined.cardinality = unionNdv(combined.type, inputs);
  return combined;
}

} // namespace facebook::axiom::optimizer
