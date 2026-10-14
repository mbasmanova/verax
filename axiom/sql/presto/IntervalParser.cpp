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

#include "axiom/sql/presto/IntervalParser.h"

#include <folly/Expected.h>
#include <folly/Unit.h>

#include <limits>
#include <string_view>
#include <utility>

#include "axiom/sql/presto/PrestoSqlError.h"
#include "velox/type/Type.h"

namespace axiom::sql::presto {

using namespace facebook::velox;
namespace lp = facebook::axiom::logical_plan;

namespace {

using IntervalField = IntervalLiteral::IntervalField;

template <typename T>
using ParseResult = folly::Expected<T, std::string>;

// Order fields from largest to smallest unit.
enum DayTimeField : int32_t {
  kDay = 0,
  kHour = 1,
  kMinute = 2,
  kSecond = 3,
};

DayTimeField dayTimeField(IntervalLiteral::IntervalField field) {
  switch (field) {
    case IntervalLiteral::IntervalField::kDay:
      return kDay;
    case IntervalLiteral::IntervalField::kHour:
      return kHour;
    case IntervalLiteral::IntervalField::kMinute:
      return kMinute;
    case IntervalLiteral::IntervalField::kSecond:
      return kSecond;
    default:
      VELOX_UNREACHABLE();
  }
}

constexpr size_t kMaxDigits = 10;

bool isDigit(char character) {
  return character >= '0' && character <= '9';
}

// Reads a non-negative int32_t field. Seconds may omit their integer part.
ParseResult<int64_t>
readNumber(const std::string& value, size_t& pos, IntervalField field) {
  const size_t start = pos;
  int64_t number = 0;
  while (pos < value.size() && isDigit(value[pos])) {
    if (pos - start == kMaxDigits) {
      return folly::makeUnexpected(
          fmt::format(
              "The {} field must contain at most {} digits",
              field,
              kMaxDigits));
    }
    number = number * 10 + (value[pos++] - '0');
  }
  if (pos == start &&
      !(field == IntervalField::kSecond && pos < value.size() &&
        value[pos] == '.')) {
    return folly::makeUnexpected(
        fmt::format("Expected digits in the {} field", field));
  }
  if (number > std::numeric_limits<int32_t>::max()) {
    return folly::makeUnexpected(
        fmt::format(
            "The {} field exceeds {}",
            field,
            std::numeric_limits<int32_t>::max()));
  }
  return number;
}

// Reads fractional seconds, keeping the first three digits as milliseconds.
ParseResult<int64_t>
readMillis(const std::string& value, size_t& pos, size_t integerDigits) {
  if (pos == value.size() || value[pos] != '.') {
    return 0;
  }
  if (integerDigits >= kMaxDigits) {
    return folly::makeUnexpected(
        fmt::format(
            "A decimal point requires fewer than {} integer digits in the SECOND field",
            kMaxDigits));
  }
  ++pos;
  const size_t start = pos;
  int64_t millis = 0;
  while (pos < value.size() && isDigit(value[pos])) {
    const size_t fractionDigits = pos - start;
    if (integerDigits + fractionDigits == kMaxDigits) {
      return folly::makeUnexpected(
          fmt::format(
              "The SECOND field must contain at most {} digits, including the fraction",
              kMaxDigits));
    }
    if (fractionDigits < 3) {
      millis = millis * 10 + (value[pos] - '0');
    }
    ++pos;
  }
  if (integerDigits == 0 && pos == start) {
    return folly::makeUnexpected(
        std::string("Expected digits in the SECOND field"));
  }
  for (size_t digits = pos - start; digits < 3; ++digits) {
    millis *= 10;
  }
  return millis;
}

// Reads a non-negative field with an optional plus sign. Returns milliseconds
// for seconds and the integer value for other fields.
ParseResult<int64_t>
readField(const std::string& value, size_t& pos, IntervalField field) {
  if (pos < value.size() && value[pos] == '+') {
    ++pos;
  }
  if (pos < value.size() && value[pos] == '-') {
    return folly::makeUnexpected(
        fmt::format("The {} field must be non-negative", field));
  }
  const size_t start = pos;
  auto number = readNumber(value, pos, field);
  if (!number.hasValue()) {
    return number;
  }
  if (field == IntervalField::kSecond) {
    auto millis = readMillis(value, pos, pos - start);
    if (!millis.hasValue()) {
      return millis;
    }
    return number.value() * 1'000 + millis.value();
  }
  return number;
}

enum class Separator { kSpace, kColon, kHyphen };

ParseResult<folly::Unit> readSeparator(
    const std::string& value,
    size_t& pos,
    Separator separator,
    IntervalField previous,
    IntervalField next) {
  char expected;
  std::string_view description;
  switch (separator) {
    case Separator::kSpace:
      expected = ' ';
      description = "a space";
      break;
    case Separator::kColon:
      expected = ':';
      description = "':'";
      break;
    case Separator::kHyphen:
      expected = '-';
      description = "'-'";
      break;
    default:
      VELOX_UNREACHABLE();
  }
  if (value[pos] != expected) {
    return folly::makeUnexpected(
        fmt::format(
            "Expected {} between {} and {}", description, previous, next));
  }
  ++pos;
  return folly::unit;
}

ParseResult<folly::Unit> checkEnd(const std::string& value, size_t pos) {
  if (pos < value.size()) {
    return folly::makeUnexpected(
        fmt::format("Unexpected characters: {}", value.substr(pos)));
  }
  return folly::unit;
}

ParseResult<int64_t> parseDayTime(
    const std::string& value,
    size_t pos,
    IntervalField start,
    IntervalField end) {
  const DayTimeField first = dayTimeField(start);
  const DayTimeField last = dayTimeField(end);
  // Seconds are already expressed in milliseconds by readField.
  static constexpr std::pair<IntervalField, int64_t> kUnits[] = {
      {IntervalField::kDay, 24 * 60 * 60 * 1'000},
      {IntervalField::kHour, 60 * 60 * 1'000},
      {IntervalField::kMinute, 60 * 1'000},
      {IntervalField::kSecond, 1},
  };
  int64_t millis = 0;
  for (int32_t index = first; index <= last && pos < value.size(); ++index) {
    const auto [field, unitMillis] = kUnits[index];
    if (index > first) {
      auto separator = readSeparator(
          value,
          pos,
          index == kHour ? Separator::kSpace : Separator::kColon,
          kUnits[index - 1].first,
          field);
      if (!separator.hasValue()) {
        return folly::makeUnexpected(std::move(separator.error()));
      }
    }
    auto fieldValue = readField(value, pos, field);
    if (!fieldValue.hasValue()) {
      return fieldValue;
    }
    // Bounded integer fields and fractions fit together in int64_t
    // milliseconds.
    millis += fieldValue.value() * unitMillis;
  }
  auto endOfValue = checkEnd(value, pos);
  if (!endOfValue.hasValue()) {
    return folly::makeUnexpected(std::move(endOfValue.error()));
  }
  return millis;
}

ParseResult<int64_t> parseYearMonth(
    const std::string& value,
    size_t pos,
    IntervalField start,
    IntervalField end) {
  if (pos == value.size()) {
    return 0;
  }
  auto firstField = readField(value, pos, start);
  if (!firstField.hasValue()) {
    return firstField;
  }
  int64_t months = firstField.value();
  if (start == IntervalField::kYear) {
    months *= 12;
  }
  if (start != end && pos < value.size()) {
    auto separator = readSeparator(value, pos, Separator::kHyphen, start, end);
    if (!separator.hasValue()) {
      return folly::makeUnexpected(std::move(separator.error()));
    }
    auto lastField = readField(value, pos, end);
    if (!lastField.hasValue()) {
      return lastField;
    }
    months += lastField.value();
  }
  if (months > std::numeric_limits<int32_t>::max()) {
    return folly::makeUnexpected(
        fmt::format(
            "Total exceeds {} months", std::numeric_limits<int32_t>::max()));
  }
  auto endOfValue = checkEnd(value, pos);
  if (!endOfValue.hasValue()) {
    return folly::makeUnexpected(std::move(endOfValue.error()));
  }
  return months;
}

} // namespace

lp::ExprApi IntervalParser::parse(const IntervalLiteral& literal) {
  const auto start = literal.startField();
  const auto end = literal.endField().value_or(start);
  const auto& value = literal.value();
  const auto location = literal.location();
  const auto qualifier = start == end ? fmt::format("{}", start)
                                      : fmt::format("{} TO {}", start, end);
  const bool yearMonth = literal.isYearToMonth();
  const bool endYearMonth =
      end == IntervalField::kYear || end == IntervalField::kMonth;
  AXIOM_PRESTO_SEMANTIC_CHECK_EQ(
      yearMonth,
      endYearMonth,
      location,
      value,
      "Invalid INTERVAL qualifier: {}; fields must belong to the same group",
      qualifier);
  AXIOM_PRESTO_SEMANTIC_CHECK_LE(
      start,
      end,
      location,
      value,
      "Invalid INTERVAL qualifier: {}; fields must go from largest to smallest",
      qualifier);

  size_t pos = 0;
  int32_t sign = literal.sign() == IntervalLiteral::Sign::kPositive ? 1 : -1;
  if (!value.empty() && value[0] == '-') {
    sign = -sign;
    ++pos;
  }
  const auto parsed = yearMonth ? parseYearMonth(value, pos, start, end)
                                : parseDayTime(value, pos, start, end);
  AXIOM_PRESTO_SEMANTIC_CHECK(
      parsed.hasValue(),
      location,
      value,
      "Invalid INTERVAL {} value: {}; {}",
      qualifier,
      value,
      parsed.error());

  if (yearMonth) {
    return lp::Lit(
        static_cast<int32_t>(sign * parsed.value()), INTERVAL_YEAR_MONTH());
  }
  return lp::Lit(sign * parsed.value(), INTERVAL_DAY_TIME());
}

} // namespace axiom::sql::presto
