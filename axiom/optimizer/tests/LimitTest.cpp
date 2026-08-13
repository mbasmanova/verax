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

#include <fmt/core.h>

#include <limits>

#include "axiom/optimizer/tests/QueryTestBase.h"

namespace facebook::axiom::optimizer {
namespace {

using namespace velox;

// A Limit's count when the query has OFFSET but no LIMIT.
constexpr int64_t kNoLimit = std::numeric_limits<int64_t>::max();

class LimitTest : public test::QueryTestBase,
                  public ::testing::WithParamInterface<bool> {
 protected:
  void SetUp() override {
    useV2_ = GetParam();
    test::QueryTestBase::SetUp();
  }

  core::PlanNodePtr toSingleNodePlan(
      std::string_view sql,
      int32_t numDrivers = 1) {
    auto logicalPlan = parseSelect(sql, kTestConnectorId);
    return QueryTestBase::toSingleNodePlan(logicalPlan, numDrivers);
  }

  MultiFragmentPlanPtr toDistributedPlan(std::string_view sql) {
    auto logicalPlan = parseSelect(sql, kTestConnectorId);
    return planVelox(logicalPlan).plan;
  }
};

TEST_P(LimitTest, limit) {
  constexpr auto sql = "SELECT * FROM nation LIMIT 10";

  // A single driver needs no partial limit.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql), matchScan("nation").finalLimit(0, 10).build());

  // Multiple drivers on one node: each driver limits, then the results are
  // merged and limited again.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql, /*numDrivers=*/4),
      matchScan("nation").localLimit(0, 10).build());

  AXIOM_ASSERT_DISTRIBUTED_PLAN(
      toDistributedPlan(sql),
      matchScan("nation").distributedLimit(0, 10).build());
}

TEST_P(LimitTest, offsetAndLimit) {
  constexpr auto sql = "SELECT * FROM nation OFFSET 5 LIMIT 10";

  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql), matchScan("nation").finalLimit(5, 10).build());

  // Partial limits must keep offset + count rows; only the final limit skips.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql, /*numDrivers=*/4),
      matchScan("nation").localLimit(5, 10).build());

  AXIOM_ASSERT_DISTRIBUTED_PLAN(
      toDistributedPlan(sql),
      matchScan("nation").distributedLimit(5, 10).build());
}

TEST_P(LimitTest, offsetOnly) {
  constexpr auto sql = "SELECT * FROM nation OFFSET 5";

  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql),
      matchScan("nation").finalLimit(5, kNoLimit).build());

  AXIOM_ASSERT_DISTRIBUTED_PLAN(
      toDistributedPlan(sql),
      matchScan("nation").gather().finalLimit(5, kNoLimit).build());
}

TEST_P(LimitTest, veryLargeOffset) {
  // offset + count exceeds the maximum int64, so the partial limit would keep
  // every row and is dropped instead of wrapping around.
  const auto sql =
      fmt::format("SELECT * FROM nation OFFSET {} LIMIT 100", kNoLimit - 5);

  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql),
      matchScan("nation").finalLimit(kNoLimit - 5, 100).build());

  AXIOM_ASSERT_DISTRIBUTED_PLAN(
      toDistributedPlan(sql),
      matchScan("nation").gather().finalLimit(kNoLimit - 5, 100).build());
}

TEST_P(LimitTest, orderByLimit) {
  constexpr auto sql = "SELECT * FROM nation ORDER BY n_name DESC LIMIT 10";

  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql), matchScan("nation").topN(10).build());

  // Each driver produces its own top 10; the merge preserves order and the
  // final limit trims to 10.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql, /*numDrivers=*/4),
      matchScan("nation").topN(10).localMerge().finalLimit(0, 10).build());

  // Each worker limits what it sends over the merge exchange, and the final
  // limit trims the merged output of all workers. v1 omits the per-worker
  // limit and ships each worker's full merged TopN output.
  AXIOM_ASSERT_DISTRIBUTED_PLAN(
      toDistributedPlan(sql),
      matchScan("nation")
          .topN(10)
          .localMerge()
          .finalLimitIf(useV2_, 0, 10)
          .shuffleMerge()
          .finalLimit(0, 10)
          .build());
}

TEST_P(LimitTest, orderByOffsetAndLimit) {
  constexpr auto sql =
      "SELECT * FROM nation ORDER BY n_name DESC OFFSET 5 LIMIT 10";

  // The TopN must keep offset + count rows before the offset drops any.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(sql),
      matchScan("nation").topN(15).finalLimit(5, 10).build());

  AXIOM_ASSERT_DISTRIBUTED_PLAN(
      toDistributedPlan(sql),
      matchScan("nation")
          .topN(15)
          .localMerge()
          .finalLimitIf(useV2_, 0, 15)
          .shuffleMerge()
          .finalLimit(5, 10)
          .build());
}

TEST_P(LimitTest, limitBeforeProject) {
  testConnector_->addTable("t", ROW({"a", "b"}, INTEGER()));

  // The limit goes below the projection, so no more than 'limit' rows are
  // projected.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan("SELECT a + b as c FROM (SELECT * FROM t LIMIT 10)"),
      matchScan("t").finalLimit(0, 10).project({"a + b as c"}).build());

  // v1 pushes the limit below the projection only when it is at most 8192
  // rows; v2 does so for any limit.
  //
  // TODO: The limit gathers into a single pipeline, so everything above it
  // runs single-threaded. Pushing the limit below the projection
  // unconditionally restricts parallelism and can slow the query down when the
  // limit is large.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan("SELECT a + b as c FROM (SELECT * FROM t LIMIT 10000)"),
      useV2_
          ? matchScan("t").finalLimit(0, 10'000).project({"a + b as c"}).build()
          : matchScan("t")
                .project({"a + b as c"})
                .finalLimit(0, 10'000)
                .build());
}

TEST_P(LimitTest, limitAfterOrderBy) {
  testConnector_->addTable("t", ROW({"a", "b"}, INTEGER()));

  for (auto limit : {10, 10'000}) {
    const auto sql = fmt::format(
        "SELECT c FROM (SELECT a + b as c FROM t) ORDER BY c LIMIT {}", limit);
    SCOPED_TRACE(sql);

    // v1 adds a rename-only projection over the TopN output.
    AXIOM_ASSERT_PLAN(
        toSingleNodePlan(sql),
        matchScan("t")
            .project({"a + b as c"})
            .topN(limit)
            .projectIf(!useV2_, {"c"})
            .build());
  }
}

TEST_P(LimitTest, zeroLimit) {
  testConnector_->addTable("t", ROW("a", BIGINT()));
  testConnector_->addTable("u", ROW("x", BIGINT()));

  // A zero-row limit collapses the subtree into an empty Values node.
  {
    const auto matcher = matchValues().build();

    for (const auto* sql : {
             "SELECT * FROM t LIMIT 0",
             "SELECT * FROM t ORDER BY a LIMIT 0",
             "SELECT * FROM t OFFSET 1 LIMIT 0",
             "SELECT * FROM t ORDER BY a OFFSET 1 LIMIT 0",
             "SELECT * FROM (SELECT * FROM t LIMIT 1) OFFSET 1",
             "SELECT * FROM (SELECT * FROM t ORDER BY a LIMIT 1) OFFSET 1",
         }) {
      SCOPED_TRACE(sql);
      AXIOM_ASSERT_PLAN(toSingleNodePlan(sql), matcher);
    }
  }

  // Operators above the empty Values node are preserved.
  AXIOM_ASSERT_PLAN(
      toSingleNodePlan("SELECT count(*) FROM (SELECT * FROM t LIMIT 0)"),
      matchValues().singleAggregation({}, {"count(*) as cnt"}).build());

  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(
          "SELECT * FROM t, (SELECT * FROM u LIMIT 0) s WHERE a = x"),
      matchScan("t")
          .hashJoin(matchValues().build(), core::JoinType::kInner)
          .build());
}

AXIOM_INSTANTIATE_V1_V2(LimitTest);

} // namespace
} // namespace facebook::axiom::optimizer
