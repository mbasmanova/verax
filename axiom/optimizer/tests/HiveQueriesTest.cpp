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
#include "velox/exec/tests/utils/PlanBuilder.h"

namespace lp = facebook::velox::logical_plan;

namespace facebook::velox::optimizer {
namespace {

class HiveQueriesTest : public test::HiveQueriesTestBase {};

TEST_F(HiveQueriesTest, basic) {
  auto planNodeIdGenerator = std::make_shared<core::PlanNodeIdGenerator>();
  auto scan = [&](const std::string& tableName) {
    return exec::test::PlanBuilder(planNodeIdGenerator)
        .tableScan(tableName, getSchema(tableName));
  };

  checkResults("SELECT * FROM nation", scan("nation").planNode());

  checkResults(
      "SELECT * FROM nation LIMIT 5",
      scan("nation").limit(0, 5, false).planNode());

  checkResults(
      "SELECT * FROM nation OFFSET 7 LIMIT 5",
      scan("nation").limit(7, 5, false).planNode());

  checkResults(
      "SELECT count(*) FROM nation",
      scan("nation")
          .localPartition({})
          .singleAggregation({}, {"count(*)"})
          .planNode());

  checkResults(
      "SELECT DISTINCT n_regionkey FROM nation",
      scan("nation").singleAggregation({"n_regionkey"}, {}).planNode());

  checkResults(
      "SELECT r_name, count(*) FROM region, nation WHERE r_regionkey = n_regionkey GROUP BY 1",
      scan("region")
          .hashJoin(
              {"r_regionkey"},
              {"n_regionkey"},
              scan("nation").planNode(),
              "",
              {"r_name"})
          .localPartition({})
          .singleAggregation({"r_name"}, {"count(*)"})
          .planNode());
}

} // namespace
} // namespace facebook::velox::optimizer
