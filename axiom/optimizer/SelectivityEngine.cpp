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

#include "axiom/optimizer/SelectivityEngine.h"

#include <limits>

#include "velox/type/Filter.h"

namespace facebook::axiom::optimizer {
namespace {

using velox::common::BigintRange;
using velox::common::BigintValuesUsingBitmask;
using velox::common::BigintValuesUsingHashTable;
using velox::common::BytesRange;
using velox::common::BytesValues;
using velox::common::DoubleRange;
using velox::common::FilterKind;
using velox::common::FloatRange;

template <typename T>
VariantCP registerIntegerBound(int64_t value) {
  VELOX_CHECK_GE(value, static_cast<int64_t>(std::numeric_limits<T>::min()));
  VELOX_CHECK_LE(value, static_cast<int64_t>(std::numeric_limits<T>::max()));
  return registerVariant(velox::Variant::create<T>(static_cast<T>(value)));
}

VariantCP registerIntegerBound(velox::TypeKind kind, int64_t value) {
  switch (kind) {
    case velox::TypeKind::TINYINT:
      return registerIntegerBound<int8_t>(value);
    case velox::TypeKind::SMALLINT:
      return registerIntegerBound<int16_t>(value);
    case velox::TypeKind::INTEGER:
      return registerIntegerBound<int32_t>(value);
    case velox::TypeKind::BIGINT:
      return registerIntegerBound<int64_t>(value);
    default:
      VELOX_UNREACHABLE();
  }
}

// Selectivity and refined Value of a range [lower, upper] (either bound nullptr
// for unbounded) over a column.
std::optional<Selectivity> rangeFilter(
    const Value& value,
    VariantCP lower,
    VariantCP upper,
    Value& refined) {
  auto selectivity = detail::rangeSelectivity(value, lower, upper);
  refined = value;
  if (selectivity.has_value() && value.cardinality.has_value()) {
    // Undo null scaling to get the fraction of distinct values retained.
    const double nullFraction = value.nullFraction.value_or(0);
    const double baseTrueFraction = (nullFraction < 1.0)
        ? selectivity->trueFraction / (1.0 - nullFraction)
        : selectivity->trueFraction;
    refined = detail::refineRange(
        value, lower, upper, *value.cardinality * baseTrueFraction);
  }
  return selectivity;
}

bool isWithinBounds(const Value& value, VariantCP candidate) {
  return (value.min == nullptr || !(*candidate < *value.min)) &&
      (value.max == nullptr || !(*value.max < *candidate));
}

// Estimates an integral point or IN-list filter from NDV after removing values
// outside the column's known range.
std::optional<Selectivity> integerValuesFilter(
    const Value& value,
    const std::vector<int64_t>& values,
    Value& refined) {
  VariantCP lower{nullptr};
  VariantCP upper{nullptr};
  double numValues{0};
  for (const auto integerValue : values) {
    auto* candidate = registerIntegerBound(value.type->kind(), integerValue);
    if (!isWithinBounds(value, candidate)) {
      continue;
    }
    lower = lower == nullptr || *candidate < *lower ? candidate : lower;
    upper = upper == nullptr || *upper < *candidate ? candidate : upper;
    ++numValues;
  }

  if (numValues == 0) {
    refined = Value(value.type, 0);
    refined.nullFraction = 0;
    refined.nullable = false;
    return Selectivity::likelyZero(value.nullFraction.value_or(0));
  }

  auto selectivity = detail::inListSelectivity(value, numValues);
  refined = detail::refineRange(value, lower, upper, numValues);
  return selectivity;
}

std::optional<Selectivity>
valuesFilter(const Value& value, double numValues, Value& refined) {
  auto selectivity = detail::inListSelectivity(value, numValues);
  refined = detail::refineRange(value, nullptr, nullptr, numValues);
  return selectivity;
}

} // namespace

std::optional<Selectivity> commonFilterSelectivity(
    const velox::common::Filter& filter,
    const Value& value,
    Value& refined) {
  refined = value;
  const double nullFraction = value.nullFraction.value_or(0);
  const auto kind = value.type->kind();

  if (!value.type->isPrimitiveType()) {
    switch (filter.kind()) {
      case FilterKind::kAlwaysTrue:
      case FilterKind::kAlwaysFalse:
      case FilterKind::kIsNull:
      case FilterKind::kIsNotNull:
        break;
      default:
        return Selectivity::noRange(nullFraction);
    }
  }

  switch (filter.kind()) {
    case FilterKind::kAlwaysTrue:
      return Selectivity{1.0, 0.0};

    case FilterKind::kAlwaysFalse: {
      refined = Value(value.type, 0);
      refined.nullFraction = 0;
      refined.nullable = false;
      return Selectivity{0.0, 0.0};
    }

    case FilterKind::kIsNull:
      refined.nullFraction = 1.0;
      return Selectivity{nullFraction, 0.0};

    case FilterKind::kIsNotNull:
      refined.nullFraction = 0;
      refined.nullable = false;
      return Selectivity{1.0 - nullFraction, 0.0};

    case FilterKind::kBigintRange: {
      const auto& range = static_cast<const BigintRange&>(filter);
      if (range.isSingleValue()) {
        return integerValuesFilter(value, {range.lower()}, refined);
      }

      VariantCP lower = range.lowerUnbounded()
          ? nullptr
          : registerIntegerBound(kind, range.lower());
      VariantCP upper = range.upperUnbounded()
          ? nullptr
          : registerIntegerBound(kind, range.upper());
      return rangeFilter(value, lower, upper, refined);
    }

    case FilterKind::kDoubleRange: {
      const auto& range = static_cast<const DoubleRange&>(filter);
      VariantCP lower = range.lowerUnbounded()
          ? nullptr
          : registerVariant(velox::Variant::create<double>(range.lower()));
      VariantCP upper = range.upperUnbounded()
          ? nullptr
          : registerVariant(velox::Variant::create<double>(range.upper()));
      return rangeFilter(value, lower, upper, refined);
    }

    case FilterKind::kFloatRange: {
      const auto& range = static_cast<const FloatRange&>(filter);
      VariantCP lower = range.lowerUnbounded()
          ? nullptr
          : registerVariant(velox::Variant::create<float>(range.lower()));
      VariantCP upper = range.upperUnbounded()
          ? nullptr
          : registerVariant(velox::Variant::create<float>(range.upper()));
      return rangeFilter(value, lower, upper, refined);
    }

    case FilterKind::kBytesRange: {
      const auto& range = static_cast<const BytesRange&>(filter);
      VariantCP lower = range.lowerUnbounded()
          ? nullptr
          : registerVariant(velox::Variant(range.lower()));
      VariantCP upper = range.upperUnbounded()
          ? nullptr
          : registerVariant(velox::Variant(range.upper()));
      return rangeFilter(value, lower, upper, refined);
    }

    case FilterKind::kBigintValuesUsingHashTable:
      return integerValuesFilter(
          value,
          static_cast<const BigintValuesUsingHashTable&>(filter).values(),
          refined);

    case FilterKind::kBigintValuesUsingBitmask:
      return integerValuesFilter(
          value,
          static_cast<const BigintValuesUsingBitmask&>(filter).values(),
          refined);

    case FilterKind::kBytesValues:
      return valuesFilter(
          value,
          static_cast<const BytesValues&>(filter).values().size(),
          refined);

    default:
      // Negated filters, multi-ranges, bloom filters, hugeint/timestamp ranges
      // and bool values are not modeled; use a neutral default.
      return Selectivity::unknown(nullFraction);
  }
}

} // namespace facebook::axiom::optimizer
