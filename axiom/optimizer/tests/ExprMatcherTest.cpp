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

#include "axiom/optimizer/tests/ExprMatcher.h"
#include <gtest/gtest-spi.h>
#include <gtest/gtest.h>
#include "velox/core/Expressions.h"
#include "velox/parse/Expressions.h"
#include "velox/parse/ExpressionsParser.h"
#include "velox/type/Type.h"

namespace facebook::velox::core {
namespace {

TypedExprPtr field(const TypePtr& type, const std::string& name) {
  return std::make_shared<FieldAccessTypedExpr>(type, name);
}

TypedExprPtr
field(const TypePtr& type, const TypedExprPtr& input, const std::string& name) {
  return std::make_shared<FieldAccessTypedExpr>(type, input, name);
}

TypedExprPtr constant(const TypePtr& type, const Variant& value) {
  return std::make_shared<ConstantTypedExpr>(type, value);
}

TypedExprPtr constantNull(const TypePtr& type) {
  return ConstantTypedExpr::makeNull(type);
}

template <typename... Args>
TypedExprPtr
call(const TypePtr& type, const std::string& name, Args&&... args) {
  return std::make_shared<CallTypedExpr>(
      type, std::vector<TypedExprPtr>{std::forward<Args>(args)...}, name);
}

TypedExprPtr cast(const TypePtr& type, const TypedExprPtr& input, bool isTry) {
  return std::make_shared<CastTypedExpr>(type, input, isTry);
}

TypedExprPtr
deref(const TypePtr& type, const TypedExprPtr& input, uint32_t index) {
  return std::make_shared<DereferenceTypedExpr>(type, input, index);
}

TypedExprPtr concat(
    const std::vector<std::string>& names,
    const std::vector<TypedExprPtr>& inputs) {
  return std::make_shared<ConcatTypedExpr>(names, inputs);
}

TypedExprPtr lambda(const RowTypePtr& signature, const TypedExprPtr& body) {
  return std::make_shared<LambdaTypedExpr>(signature, body);
}

TypedExprPtr nullIf(
    const TypedExprPtr& value,
    const TypedExprPtr& comparand,
    const TypePtr& commonType) {
  return std::make_shared<NullIfTypedExpr>(value, comparand, commonType);
}

ExprPtr wildcard() {
  return std::make_shared<CallExpr>(
      std::string{ExprMatcher::kWildcard},
      std::vector<ExprPtr>{},
      std::nullopt);
}

class ExprMatcherTest : public testing::Test {
 protected:
  ExprPtr parseExpr(const std::string& sql) {
    return parser_.parseExpr(sql);
  }

  parse::DuckSqlExpressionsParser parser_;
};

TEST_F(ExprMatcherTest, rootColumn) {
  ExprMatcher::match(field(BIGINT(), "a"), parseExpr("a"));
}

TEST_F(ExprMatcherTest, rootColumnNameMismatch) {
  EXPECT_NONFATAL_FAILURE(
      ExprMatcher::match(field(BIGINT(), "a"), parseExpr("b")),
      R"(actual: '"a"', expected: '"b"')");
}

TEST_F(ExprMatcherTest, functionCall) {
  ExprMatcher::match(
      call(BIGINT(), "plus", field(BIGINT(), "a"), field(BIGINT(), "b")),
      parseExpr("a + b"));
}

TEST_F(ExprMatcherTest, nestedFunctionCall) {
  auto expr = call(
      BIGINT(),
      "mod",
      call(BIGINT(), "plus", field(BIGINT(), "a"), constant(BIGINT(), 1LL)),
      constant(BIGINT(), 3LL));
  ExprMatcher::match(expr, parseExpr("(a + 1) % 3"));
}

TEST_F(ExprMatcherTest, functionNameMismatch) {
  EXPECT_NONFATAL_FAILURE(
      ExprMatcher::match(
          call(BIGINT(), "minus", field(BIGINT(), "a"), field(BIGINT(), "b")),
          parseExpr("a + b")),
      R"(actual: 'minus("a","b")', expected: 'plus("a","b")')");
}

TEST_F(ExprMatcherTest, integerConstant) {
  ExprMatcher::match(constant(BIGINT(), 42LL), parseExpr("42"));
}

TEST_F(ExprMatcherTest, booleanConstant) {
  ExprMatcher::match(constant(BOOLEAN(), true), parseExpr("true"));
  ExprMatcher::match(constant(BOOLEAN(), false), parseExpr("false"));
}

TEST_F(ExprMatcherTest, nullConstant) {
  ExprMatcher::match(constantNull(BIGINT()), parseExpr("null"));
}

TEST_F(ExprMatcherTest, stringConstant) {
  ExprMatcher::match(
      constant(VARCHAR(), Variant::create<TypeKind::VARCHAR>("hello")),
      parseExpr("'hello'"));
}

TEST_F(ExprMatcherTest, doubleEpsilonMatch) {
  // 0.1 + 0.2 != 0.3 in double precision, but equalsWithEpsilon handles it.
  ExprMatcher::match(constant(DOUBLE(), Variant(0.1 + 0.2)), parseExpr("0.3"));
}

TEST_F(ExprMatcherTest, doubleEpsilonMismatch) {
  EXPECT_NONFATAL_FAILURE(
      ExprMatcher::match(constant(DOUBLE(), 1.0), parseExpr("2.0")),
      "actual: '1', expected: '2'");
}

TEST_F(ExprMatcherTest, cast) {
  ExprMatcher::match(
      cast(BIGINT(), field(INTEGER(), "a"), false),
      parseExpr("cast(a as bigint)"));
}

TEST_F(ExprMatcherTest, tryCast) {
  ExprMatcher::match(
      cast(VARCHAR(), field(BIGINT(), "a"), true),
      parseExpr("try_cast(a as varchar)"));
}

TEST_F(ExprMatcherTest, castTryCastMismatch) {
  EXPECT_NONFATAL_FAILURE(
      ExprMatcher::match(
          cast(BIGINT(), field(INTEGER(), "a"), false),
          parseExpr("try_cast(a as bigint)")),
      R"(actual: 'cast("a" as BIGINT)', expected: 'try_cast("a" as BIGINT)')");
}

TEST_F(ExprMatcherTest, dereferenceExpr) {
  auto structType = ROW({"x", "y"}, {BIGINT(), VARCHAR()});
  ExprMatcher::match(
      deref(BIGINT(), field(structType, "a"), 0), parseExpr("(a).x"));
}

TEST_F(ExprMatcherTest, fieldAccessStructField) {
  auto structType = ROW({"x", "y"}, {BIGINT(), VARCHAR()});
  ExprMatcher::match(
      field(BIGINT(), field(structType, "a"), "x"), parseExpr("(a).x"));
}

TEST_F(ExprMatcherTest, dereferenceFieldNameMismatch) {
  auto structType = ROW({"x", "y"}, {BIGINT(), VARCHAR()});
  EXPECT_NONFATAL_FAILURE(
      ExprMatcher::match(
          deref(BIGINT(), field(structType, "a"), 0), parseExpr("(a).y")),
      R"(actual: '"a"[x]', expected: 'dot("a","y")')");
}

TEST_F(ExprMatcherTest, concatTypedExpr) {
  ExprMatcher::match(
      concat({"c0", "c1"}, {constant(BIGINT(), 1LL), constant(BIGINT(), 2LL)}),
      parseExpr("row_constructor(1, 2)"));
}

TEST_F(ExprMatcherTest, lambda) {
  auto signature = ROW({"x", "y"}, {BIGINT(), BIGINT()});
  auto body =
      call(BIGINT(), "plus", field(BIGINT(), "x"), field(BIGINT(), "y"));
  ExprMatcher::match(lambda(signature, body), parseExpr("(x, y) -> x + y"));
}

TEST_F(ExprMatcherTest, nullIf) {
  ExprMatcher::match(
      nullIf(field(BIGINT(), "a"), field(BIGINT(), "b"), BIGINT()),
      parseExpr("nullif(a, b)"));
}

TEST_F(ExprMatcherTest, wildcardMatchesField) {
  ExprMatcher::match(field(BIGINT(), "a"), wildcard());
}

TEST_F(ExprMatcherTest, wildcardMatchesConstant) {
  ExprMatcher::match(constant(BIGINT(), 42LL), wildcard());
}

TEST_F(ExprMatcherTest, wildcardMatchesCall) {
  ExprMatcher::match(
      call(BIGINT(), "plus", field(BIGINT(), "a"), field(BIGINT(), "b")),
      wildcard());
}

TEST_F(ExprMatcherTest, wildcardInSubtree) {
  ExprMatcher::match(
      call(BIGINT(), "plus", field(BIGINT(), "a"), field(BIGINT(), "b")),
      std::make_shared<CallExpr>(
          "plus",
          std::vector<ExprPtr>{parseExpr("a"), wildcard()},
          std::nullopt));
}

} // namespace
} // namespace facebook::velox::core
