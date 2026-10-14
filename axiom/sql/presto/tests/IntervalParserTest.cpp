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

#include <initializer_list>
#include <utility>

#include "axiom/sql/presto/tests/PrestoParserTestBase.h"

namespace axiom::sql::presto::test {

using namespace facebook::velox;
namespace lp = facebook::axiom::logical_plan;

namespace {

class IntervalParserTest : public PrestoParserTestBase {
 protected:
  lp::ExprPtr parseExpr(std::string_view sql) {
    return makeParser().parseExpression(sql, true);
  }

  void testDayTime(std::string_view sql, int64_t expectedMillis) {
    testInterval(sql, expectedMillis, INTERVAL_DAY_TIME());
  }

  void testYearMonth(std::string_view sql, int32_t expectedMonths) {
    testInterval(sql, expectedMonths, INTERVAL_YEAR_MONTH());
  }

  void testErrors(
      std::initializer_list<std::pair<std::string_view, std::string_view>>
          cases) {
    for (const auto& [sql, expectedMessage] : cases) {
      SCOPED_TRACE(sql);
      AXIOM_EXPECT_PRESTO_SEMANTIC_ERROR(parseExpr(sql), expectedMessage);
    }
  }

 private:
  template <typename T>
  void
  testInterval(std::string_view sql, T expected, const TypePtr& expectedType) {
    SCOPED_TRACE(sql);
    const auto expr = parseExpr(sql);
    ASSERT_TRUE(expr->isConstant());
    ASSERT_EQ(*expr->type(), *expectedType);
    const auto value = expr->as<lp::ConstantExpr>()->value();
    ASSERT_FALSE(value->isNull());
    EXPECT_EQ(value->value<T>(), expected);
  }
};

TEST_F(IntervalParserTest, dayTime) {
  constexpr int64_t kSecond = 1'000;
  constexpr int64_t kMinute = 60 * kSecond;
  constexpr int64_t kHour = 60 * kMinute;
  constexpr int64_t kDay = 24 * kHour;

  testDayTime("INTERVAL '2' DAY", 2 * kDay);
  testDayTime("INTERVAL '3' HOUR", 3 * kHour);
  testDayTime("INTERVAL '4' MINUTE", 4 * kMinute);
  testDayTime("INTERVAL '5' SECOND", 5 * kSecond);

  testDayTime("INTERVAL '' DAY", 0);
  testDayTime("INTERVAL '0' HOUR", 0);

  testDayTime("INTERVAL '-2' DAY", -2 * kDay);
  testDayTime("INTERVAL '-3' HOUR", -3 * kHour);
  testDayTime("INTERVAL '-4' MINUTE", -4 * kMinute);
  testDayTime("INTERVAL '-5' SECOND", -5 * kSecond);

  // A fraction of a second keeps its milliseconds.
  testDayTime("INTERVAL '1.5' SECOND", kSecond + 500);
  testDayTime("INTERVAL '0.001' SECOND", 1);
  testDayTime("INTERVAL '0.00049' SECOND", 0);
  testDayTime("INTERVAL '.001' SECOND", 1);
  testDayTime("INTERVAL '-.001' SECOND", -1);
  testDayTime("INTERVAL '+.5' SECOND", 500);

  // Fields follow the qualifier order; omitted trailing fields are zero.
  testDayTime("INTERVAL '0 00:01:30' DAY TO SECOND", 90 * kSecond);
  testDayTime(
      "INTERVAL '1 02:03:04.5' DAY TO SECOND",
      kDay + 2 * kHour + 3 * kMinute + 4 * kSecond + 500);
  testDayTime(
      "INTERVAL '1 02:03' DAY TO MINUTE", kDay + 2 * kHour + 3 * kMinute);
  testDayTime("INTERVAL '1 02' DAY TO HOUR", kDay + 2 * kHour);
  testDayTime(
      "INTERVAL '02:03:04' HOUR TO SECOND",
      2 * kHour + 3 * kMinute + 4 * kSecond);
  testDayTime("INTERVAL '02:03' HOUR TO MINUTE", 2 * kHour + 3 * kMinute);
  testDayTime("INTERVAL '03:04' MINUTE TO SECOND", 3 * kMinute + 4 * kSecond);
  testDayTime("INTERVAL '03:.004' MINUTE TO SECOND", 3 * kMinute + 4);
  testDayTime(
      "INTERVAL '-1 02:03:04' DAY TO SECOND",
      -(kDay + 2 * kHour + 3 * kMinute + 4 * kSecond));

  // The sign before the quoted value applies to the whole duration.
  testDayTime("INTERVAL -'1 00:00:01' DAY TO SECOND", -(kDay + kSecond));

  testDayTime("INTERVAL '12' DAY TO SECOND", 12 * kDay);
  testDayTime("INTERVAL '1 02' DAY TO SECOND", kDay + 2 * kHour);
  testDayTime("INTERVAL '10:45' HOUR TO SECOND", 10 * kHour + 45 * kMinute);
  testDayTime("INTERVAL '45' MINUTE TO SECOND", 45 * kMinute);
  testDayTime("INTERVAL '' DAY TO SECOND", 0);
  testDayTime("INTERVAL '' HOUR TO MINUTE", 0);
  testDayTime("INTERVAL '1.' SECOND", kSecond);
  testDayTime("INTERVAL '03:04.' MINUTE TO SECOND", 3 * kMinute + 4 * kSecond);
  testDayTime("INTERVAL '1:+2' HOUR TO MINUTE", kHour + 2 * kMinute);

  // Fields contribute their duration even beyond the clock ranges.
  testDayTime("INTERVAL '100' HOUR", 100 * kHour);
  testDayTime("INTERVAL '1 24:00:00' DAY TO SECOND", 2 * kDay);
  testDayTime("INTERVAL '1 00:60:00' DAY TO SECOND", kDay + kHour);
  testDayTime("INTERVAL '1 00:00:60' DAY TO SECOND", kDay + kMinute);
  testDayTime("INTERVAL '2147483647' SECOND", 2'147'483'647 * kSecond);
  testDayTime("INTERVAL '123456789.9' SECOND", 123'456'789 * kSecond + 900);
  testDayTime("INTERVAL '.1234567890' SECOND", 123);

  testDayTime("INTERVAL '-' DAY TO SECOND", 0);
  testDayTime("INTERVAL '-+1' SECOND", -kSecond);
}

TEST_F(IntervalParserTest, dayTimeErrors) {
  testErrors({
      {
          "INTERVAL '1 ' DAY TO SECOND",
          "Expected digits in the HOUR field",
      },
      {
          "INTERVAL '1:' HOUR TO SECOND",
          "Expected digits in the MINUTE field",
      },
      {
          "INTERVAL '+' SECOND",
          "Expected digits in the SECOND field",
      },
      {
          "INTERVAL '2147483647.999' SECOND",
          "A decimal point requires fewer than 10 integer digits",
      },
      {
          "INTERVAL '2147483647.' SECOND",
          "A decimal point requires fewer than 10 integer digits",
      },
      {
          "INTERVAL '.12345678901' SECOND",
          "SECOND field must contain at most 10 digits, including the fraction",
      },
      {
          "INTERVAL '000000000001' SECOND",
          "SECOND field must contain at most 10 digits",
      },
      {
          "INTERVAL '1:02:03' DAY TO SECOND",
          "Invalid INTERVAL DAY TO SECOND value: 1:02:03; Expected a space between DAY and HOUR",
      },
      {
          "INTERVAL '1 02:03:04' SECOND",
          "Unexpected characters:  02:03:04",
      },
      {
          "INTERVAL '1,5' SECOND",
          "Invalid INTERVAL SECOND value: 1,5; Unexpected characters: ,5",
      },
      {
          "INTERVAL 'abc' SECOND",
          "Expected digits in the SECOND field",
      },
      {
          "INTERVAL '.' SECOND",
          "Expected digits in the SECOND field",
      },
      {
          "INTERVAL '1:-2' HOUR TO MINUTE",
          "Invalid INTERVAL HOUR TO MINUTE value: 1:-2; The MINUTE field must be non-negative",
      },
      {
          "INTERVAL '++1' SECOND",
          "Expected digits in the SECOND field",
      },
      {
          "INTERVAL '1' DAY TO YEAR",
          "Invalid INTERVAL qualifier: DAY TO YEAR; fields must belong to the same group",
      },
      {
          "INTERVAL '1' SECOND TO DAY",
          "Invalid INTERVAL qualifier: SECOND TO DAY; fields must go from largest to smallest: SECOND vs DAY",
      },
      {
          "INTERVAL '2147483648' SECOND",
          "Invalid INTERVAL SECOND value: 2147483648; The SECOND field exceeds 2147483647",
      },
      {
          "INTERVAL '9223372036854775.808' SECOND",
          "SECOND field must contain at most 10 digits",
      },
      {
          "INTERVAL '99999999999999999999' SECOND",
          "SECOND field must contain at most 10 digits",
      },
      {
          "INTERVAL '999999999999999999' DAY",
          "DAY field must contain at most 10 digits",
      },
  });
}

TEST_F(IntervalParserTest, yearMonth) {
  testYearMonth("INTERVAL '2' YEAR", 2 * 12);
  testYearMonth("INTERVAL '3' MONTH", 3);

  testYearMonth("INTERVAL '' YEAR", 0);
  testYearMonth("INTERVAL '0' MONTH", 0);

  testYearMonth("INTERVAL '-2' YEAR", -2 * 12);
  testYearMonth("INTERVAL '-3' MONTH", -3);

  // A missing month field is zero; larger month fields add their duration.
  testYearMonth("INTERVAL '1-6' YEAR TO MONTH", 12 + 6);
  testYearMonth("INTERVAL '0-11' YEAR TO MONTH", 11);
  testYearMonth("INTERVAL '-1-6' YEAR TO MONTH", -(12 + 6));

  testYearMonth("INTERVAL '124' YEAR TO MONTH", 124 * 12);
  testYearMonth("INTERVAL '' YEAR TO MONTH", 0);
  testYearMonth("INTERVAL '124-30' YEAR TO MONTH", 124 * 12 + 30);
  testYearMonth("INTERVAL '1-12' YEAR TO MONTH", 24);
  testYearMonth("INTERVAL '1-+2' YEAR TO MONTH", 14);
  testYearMonth("INTERVAL '178956970-7' YEAR TO MONTH", 2'147'483'647);
}

TEST_F(IntervalParserTest, yearMonthErrors) {
  testErrors({
      {
          "INTERVAL '1-6' MONTH TO YEAR",
          "Invalid INTERVAL qualifier: MONTH TO YEAR; fields must go from largest to smallest: MONTH vs YEAR",
      },
      {
          "INTERVAL '1-2' YEAR TO DAY",
          "Invalid INTERVAL qualifier: YEAR TO DAY; fields must belong to the same group",
      },
      {
          "INTERVAL '1-6-9' YEAR TO MONTH",
          "Unexpected characters: -9",
      },
      {
          "INTERVAL '1:2' YEAR TO MONTH",
          "Expected '-' between YEAR and MONTH",
      },
      {
          "INTERVAL '1-' YEAR TO MONTH",
          "Expected digits in the MONTH field",
      },
      {
          "INTERVAL '178956970-8' YEAR TO MONTH",
          "Invalid INTERVAL YEAR TO MONTH value: 178956970-8; Total exceeds 2147483647 months",
      },
      {
          "INTERVAL '999999999' YEAR",
          "Total exceeds 2147483647 months",
      },
  });
}

} // namespace
} // namespace axiom::sql::presto::test
