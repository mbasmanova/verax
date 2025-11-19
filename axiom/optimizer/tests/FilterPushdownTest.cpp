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
#include "axiom/logical_plan/PlanBuilder.h"
#include "axiom/optimizer/tests/HiveQueriesTestBase.h"
#include "axiom/optimizer/tests/PlanMatcher.h"
#include "axiom/optimizer/tests/QueryTestBase.h"
#include "velox/exec/tests/utils/PlanBuilder.h"

namespace facebook::axiom::optimizer::test {
namespace {

using namespace velox;
namespace lp = facebook::axiom::logical_plan;

class FilterPushdownTest : public HiveQueriesTestBase {};

TEST_F(FilterPushdownTest, throughAggregation) {
  auto logicalPlan = lp::PlanBuilder()
                         .tableScan(exec::test::kHiveConnectorId, "orders")
                         .aggregate({"o_custkey"}, {"sum(o_totalprice) as a0"})
                         .filter("o_custkey < 100 and a0 > 200.0")
                         .build();

  {
    auto plan = toSingleNodePlan(logicalPlan);
    auto matcher = core::PlanMatcherBuilder()
                       .hiveScan("orders", lt("o_custkey", 100L))
                       .singleAggregation()
                       .filter("a0 > 200.0")
                       .build();

    AXIOM_ASSERT_PLAN(plan, matcher);
  }

  auto referencePlan =
      exec::test::PlanBuilder()
          .tableScan("orders", getSchema("orders"))
          .singleAggregation({"o_custkey"}, {"sum(o_totalprice)"})
          .filter("o_custkey < 100 and a0 > 200.0")
          .planNode();

  checkSame(logicalPlan, referencePlan);
}

TEST_F(FilterPushdownTest, redundantCast) {
  auto logicalPlan = lp::PlanBuilder()
                         .tableScan(exec::test::kHiveConnectorId, "nation")
                         .filter("cast(n_nationkey as bigint) < 10")
                         .build();

  auto plan = toSingleNodePlan(logicalPlan);
  auto matcher = core::PlanMatcherBuilder()
                     .hiveScan("nation", lt("n_nationkey", 10L))
                     .build();

  AXIOM_ASSERT_PLAN(plan, matcher);
}

} // namespace
} // namespace facebook::axiom::optimizer::test
