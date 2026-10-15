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

#include "axiom/optimizer/tests/QueryTestBase.h"

namespace facebook::axiom::optimizer {
namespace {

// Nations and regions, with an edge from each nation to its region.
constexpr std::string_view kGraph =
    "GRAPH g AS ("
    "  VERTEX TABLES ("
    "    nation KEY (n_nationkey) LABEL Nation PROPERTIES (n_name),"
    "    region KEY (r_regionkey) LABEL Region PROPERTIES (r_name))"
    "  EDGE TABLES ("
    "    nation AS in_region KEY (n_nationkey)"
    "      SOURCE KEY (n_nationkey) REFERENCES nation (n_nationkey)"
    "      DESTINATION KEY (n_regionkey) REFERENCES region (r_regionkey)"
    "      LABEL InRegion))";

class GraphTableTest : public test::QueryTestBase {
 protected:
  velox::core::PlanNodePtr toSingleNodePlan(std::string_view match) {
    return QueryTestBase::toSingleNodePlan(parseSelect(
        fmt::format(
            "WITH {} SELECT * FROM GRAPH_TABLE (g {})", kGraph, match)));
  }
};

// ANY keeps one match per pair of endpoints: a RowNumber partitioned by both
// endpoints' keys with a limit of one. Each nation row is both a Nation vertex
// and its InRegion edge, so nation is read once.
TEST_F(GraphTableTest, selector) {
  auto plan = toSingleNodePlan(
      "MATCH ANY (n IS Nation) -[IS InRegion]-> (r IS Region) "
      "COLUMNS (n.n_name AS nation, r.r_name AS region)");
  auto matcher =
      matchScan("nation")
          .aliases({"n_nationkey", "n_name", "n_regionkey"})
          .hashJoinInner(
              matchScan("region"), {.keys = {{"n_regionkey = r_regionkey"}}})
          .rowNumber({"n_nationkey", "n_regionkey"}, 1)
          .project({"n_name", "r_name"})
          .build();
  AXIOM_ASSERT_PLAN(plan, matcher);
}

// A vertex keeps only the tables that can connect to its edges. InRegion
// reaches only regions, so the vertex between the two edges reads region alone,
// with no union over nation and region and no table ID column.
TEST_F(GraphTableTest, narrowing) {
  auto plan = toSingleNodePlan(
      "MATCH (a IS Nation) -[IS InRegion]-> (y IS Nation | Region) <-[IS InRegion]- (b IS Nation) "
      "COLUMNS (a.n_name AS a, y.r_name AS y, b.n_name AS b)");
  auto matcher =
      matchScan("nation")
          .aliases({"a_name", "a_regionkey"})
          .hashJoinInner(
              matchScan("region"), {.keys = {{"a_regionkey = r_regionkey"}}})
          .hashJoinInner(
              matchScan("nation").aliases({"b_name", "b_regionkey"}),
              {.keys = {{"a_regionkey = b_regionkey"}}})
          .project({"a_name", "r_name", "b_name"})
          .build();
  AXIOM_ASSERT_PLAN(plan, matcher);
}

} // namespace
} // namespace facebook::axiom::optimizer
