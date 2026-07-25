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

// Registers, in the query arena, a Variant of 'kind' built from a numeric
// bound; nullptr for kinds without a numeric bound. Registration gives stable
// storage for the detail:: range math.
VariantCP registerNumericBound(velox::TypeKind kind, double value) {
  switch (kind) {
    case velox::TypeKind::TINYINT:
      return registerVariant(
          velox::Variant::create<velox::TypeKind::TINYINT>(
              static_cast<int8_t>(value)));
    case velox::TypeKind::SMALLINT:
      return registerVariant(
          velox::Variant::create<velox::TypeKind::SMALLINT>(
              static_cast<int16_t>(value)));
    case velox::TypeKind::INTEGER:
      return registerVariant(
          velox::Variant::create<velox::TypeKind::INTEGER>(
              static_cast<int32_t>(value)));
    case velox::TypeKind::BIGINT:
      return registerVariant(
          velox::Variant::create<velox::TypeKind::BIGINT>(
              static_cast<int64_t>(value)));
    case velox::TypeKind::REAL:
      return registerVariant(
          velox::Variant::create<velox::TypeKind::REAL>(
              static_cast<float>(value)));
    case velox::TypeKind::DOUBLE:
      return registerVariant(
          velox::Variant::create<velox::TypeKind::DOUBLE>(value));
    default:
      return nullptr;
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

// Selectivity and refined Value of an IN list of 'listSize' distinct values.
std::optional<Selectivity>
inListFilter(const Value& value, double listSize, Value& refined) {
  auto selectivity = detail::inListSelectivity(value, listSize);
  refined = detail::refineRange(value, nullptr, nullptr, listSize);
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
      VariantCP lower = range.lower() == std::numeric_limits<int64_t>::min()
          ? nullptr
          : registerNumericBound(kind, static_cast<double>(range.lower()));
      VariantCP upper = range.upper() == std::numeric_limits<int64_t>::max()
          ? nullptr
          : registerNumericBound(kind, static_cast<double>(range.upper()));
      return rangeFilter(value, lower, upper, refined);
    }

    case FilterKind::kDoubleRange: {
      const auto& range = static_cast<const DoubleRange&>(filter);
      VariantCP lower = range.lowerUnbounded()
          ? nullptr
          : registerNumericBound(kind, range.lower());
      VariantCP upper = range.upperUnbounded()
          ? nullptr
          : registerNumericBound(kind, range.upper());
      return rangeFilter(value, lower, upper, refined);
    }

    case FilterKind::kFloatRange: {
      const auto& range = static_cast<const FloatRange&>(filter);
      VariantCP lower = range.lowerUnbounded()
          ? nullptr
          : registerNumericBound(kind, range.lower());
      VariantCP upper = range.upperUnbounded()
          ? nullptr
          : registerNumericBound(kind, range.upper());
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
      return inListFilter(
          value,
          static_cast<const BigintValuesUsingHashTable&>(filter)
              .values()
              .size(),
          refined);

    case FilterKind::kBigintValuesUsingBitmask:
      return inListFilter(
          value,
          static_cast<const BigintValuesUsingBitmask&>(filter).values().size(),
          refined);

    case FilterKind::kBytesValues:
      return inListFilter(
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
