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

#include "axiom/optimizer/tests/HiveQueriesTestBase.h"
#include "axiom/optimizer/tests/PlanMatcher.h"
#include "axiom/optimizer/tests/QueryTestBase.h"

namespace facebook::axiom::optimizer {
namespace {

using namespace velox;
namespace lp = facebook::axiom::logical_plan;

class SubqueryTest : public test::HiveQueriesTestBase {};

TEST_F(SubqueryTest, scalar) {
  // = <subquery>
  {
    auto query =
        "select * from nation where n_regionkey "
        "= (select r_regionkey from region where r_name like 'AF%')";

    SCOPED_TRACE(query);
    auto plan = toSingleNodePlan(query);
    auto matcher = core::PlanMatcherBuilder()
                       .tableScan("nation")
                       .hashJoin(
                           core::PlanMatcherBuilder()
                               .hiveScan("region", {}, "r_name like 'AF%'")
                               .build(),
                           velox::core::JoinType::kInner)
                       .build();

    AXIOM_ASSERT_PLAN(plan, matcher);
  }

  // IN <subquery>
  {
    auto query =
        "select * from nation where n_regionkey "
        "IN (select r_regionkey from region where r_name > 'ASIA')";

    SCOPED_TRACE(query);
    auto plan = toSingleNodePlan(query);
    auto matcher = core::PlanMatcherBuilder()
                       .tableScan("nation")
                       .hashJoin(
                           core::PlanMatcherBuilder()
                               .hiveScan("region", test::gt("r_name", "ASIA"))
                               .build(),
                           velox::core::JoinType::kLeftSemiFilter)
                       .build();

    AXIOM_ASSERT_PLAN(plan, matcher);
  }

  // NOT IN <subquery>
  {
    auto query =
        "select * from nation where n_regionkey "
        "NOT IN (select r_regionkey from region where r_name > 'ASIA')";

    SCOPED_TRACE(query);
    auto plan = toSingleNodePlan(query);
    auto matcher = core::PlanMatcherBuilder()
                       .tableScan("nation")
                       .hashJoin(
                           core::PlanMatcherBuilder()
                               .hiveScan("region", test::gt("r_name", "ASIA"))
                               .build(),
                           velox::core::JoinType::kAnti)
                       .build();

    AXIOM_ASSERT_PLAN(plan, matcher);
  }
}

} // namespace
} // namespace facebook::axiom::optimizer
