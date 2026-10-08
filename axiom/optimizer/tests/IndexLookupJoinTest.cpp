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

#include <gtest/gtest.h>

#include "axiom/optimizer/tests/QueryTestBase.h"
#include "velox/common/base/tests/GTestUtils.h"

namespace facebook::axiom::optimizer::test {
namespace {

using namespace facebook::velox;

// A table that can only be read by key is reachable only through an index
// lookup. These tests cover the planning and lowering of that shape.
class IndexLookupJoinTest : public QueryTestBase,
                            public testing::WithParamInterface<bool> {
 protected:
  void SetUp() override {
    useV2_ = GetParam();
    QueryTestBase::SetUp();
  }

  void configureTestConnector() override {
    testConnector_->addTable("t", ROW({"a", "b"}, BIGINT()));
    testConnector_->addTable("u", ROW("x", BIGINT()));
    testConnector_->addLookupTable(
        "lookup", ROW({"k1", "k2", "v"}, BIGINT()), {"k1", "k2"});
    testConnector_->addLookupTable(
        "partitioned_lookup",
        ROW({"k", "v"}, BIGINT()),
        {"k"},
        connector::TestBucketSpec{{"k"}, 4});
  }
};

// A lookup-only table is joined by key rather than scanned and hash-joined.
TEST_P(IndexLookupJoinTest, indexLookup) {
  const auto sql = "SELECT * FROM t JOIN lookup ON t.a = lookup.k1";
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(parseSelect(sql)),
      matchScan("t")
          .indexLookupJoin(
              matchScan("lookup"), core::JoinType::kInner, {"a = k1"})
          .projectIf(useV2_, {"a", "b", "a as k1", "k2", "v"})
          .build());
}

TEST_P(IndexLookupJoinTest, lookupOnLeft) {
  if (!useV2_) {
    return;
  }

  const auto sql = "SELECT * FROM lookup JOIN t ON lookup.k1 = t.a";
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(parseSelect(sql)),
      matchScan("t")
          .indexLookupJoin(
              matchScan("lookup"), core::JoinType::kInner, {"a = k1"})
          .project({"k1", "k2", "v", "k1 as a", "b"})
          .build());
}

TEST_P(IndexLookupJoinTest, leftJoin) {
  if (!useV2_) {
    return;
  }

  const auto sql = "SELECT * FROM t LEFT JOIN lookup ON t.a = lookup.k1";
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(parseSelect(sql)),
      matchScan("t")
          .indexLookupJoin(
              matchScan("lookup"), core::JoinType::kLeft, {"a = k1"})
          .build());
}

TEST_P(IndexLookupJoinTest, multiKey) {
  if (!useV2_) {
    return;
  }

  const auto sql =
      "SELECT * FROM t JOIN lookup ON t.a = lookup.k2 AND t.b = lookup.k1";
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(parseSelect(sql)),
      matchScan("t")
          .indexLookupJoin(
              matchScan("lookup"), core::JoinType::kInner, {"b = k1", "a = k2"})
          .project({"a", "b", "b as k1", "a as k2", "v"})
          .build());
}

TEST_P(IndexLookupJoinTest, residualFilter) {
  if (!useV2_) {
    return;
  }

  {
    const auto sql =
        "SELECT * FROM t JOIN lookup ON t.a = lookup.k1 AND t.b < lookup.v";
    SCOPED_TRACE(sql);
    AXIOM_ASSERT_PLAN(
        toSingleNodePlan(parseSelect(sql)),
        matchScan("t")
            .indexLookupJoin(
                matchScan("lookup"), core::JoinType::kInner, {"a = k1"})
            .project({"a", "b", "a as k1", "k2", "v"})
            .build());
  }

  {
    const auto sql =
        "SELECT t.a FROM t JOIN lookup ON t.a = lookup.k1 AND t.b < lookup.v";
    SCOPED_TRACE(sql);
    VELOX_ASSERT_THROW(
        toSingleNodePlan(parseSelect(sql)),
        "Index lookup residual filters can reference only lookup columns in "
        "the join output");
  }
}

TEST_P(IndexLookupJoinTest, prefixCoverage) {
  if (!useV2_) {
    return;
  }

  const auto sql = "SELECT * FROM t JOIN lookup ON t.a = lookup.k2";
  VELOX_ASSERT_THROW(
      toSingleNodePlan(parseSelect(sql)),
      "Lookup equality keys must cover an index prefix");
}

TEST_P(IndexLookupJoinTest, duplicateLookupKey) {
  if (!useV2_) {
    return;
  }

  {
    const auto sql =
        "SELECT * FROM t JOIN lookup ON t.a = lookup.k1 AND t.b = lookup.k1";
    SCOPED_TRACE(sql);
    AXIOM_ASSERT_PLAN(
        toSingleNodePlan(parseSelect(sql)),
        matchScan("t")
            .filter("a = b")
            .indexLookupJoin(
                matchScan("lookup"), core::JoinType::kInner, {"a = k1"})
            .project({"a", "b", "a as k1", "k2", "v"})
            .build());
  }

  {
    const auto sql =
        "SELECT * FROM t LEFT JOIN lookup "
        "ON t.a = lookup.k1 AND t.b = lookup.k1";
    SCOPED_TRACE(sql);
    AXIOM_ASSERT_PLAN(
        toSingleNodePlan(parseSelect(sql)),
        matchScan("t")
            .indexLookupJoin(
                matchScan("lookup"), core::JoinType::kLeft, {"a = k1"}, "a = b")
            .build());
  }
}

TEST_P(IndexLookupJoinTest, partitionedLookupUnsupported) {
  if (!useV2_) {
    return;
  }

  const auto sql =
      "SELECT * FROM t JOIN partitioned_lookup ON t.a = "
      "partitioned_lookup.k";
  VELOX_ASSERT_THROW(
      toSingleNodePlan(parseSelect(sql)),
      "Partitioned index lookup is unsupported");
}

TEST_P(IndexLookupJoinTest, connectorRejectedFilter) {
  if (!useV2_) {
    return;
  }

  const auto sql =
      "SELECT * FROM t JOIN lookup ON t.a = lookup.k1 WHERE lookup.v > 0";
  VELOX_ASSERT_THROW(
      toSingleNodePlan(parseSelect(sql)),
      "Index lookup does not support connector-rejected filters");
}

TEST_P(IndexLookupJoinTest, downstreamJoin) {
  if (!useV2_) {
    return;
  }

  const auto sql =
      "SELECT * FROM (t JOIN lookup ON t.a = lookup.k1) JOIN u ON t.b = u.x";
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(parseSelect(sql)),
      matchScan("t")
          .indexLookupJoin(
              matchScan("lookup"), core::JoinType::kInner, {"a = k1"})
          .hashJoinInner(matchScan("u"), {.keys = {{"b = x"}}})
          .project({"a", "b", "a as k1", "k2", "v", "b as x"})
          .build());
}

AXIOM_INSTANTIATE_V1_V2(IndexLookupJoinTest);

} // namespace
} // namespace facebook::axiom::optimizer::test
