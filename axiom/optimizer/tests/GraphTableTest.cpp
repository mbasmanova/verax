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
constexpr std::string_view kNationGraph =
    "GRAPH g AS ("
    "  VERTEX TABLES ("
    "    nation KEY (n_nationkey) LABEL Nation PROPERTIES (n_name),"
    "    region KEY (r_regionkey) LABEL Region PROPERTIES (r_name))"
    "  EDGE TABLES ("
    "    nation AS in_region KEY (n_nationkey)"
    "      SOURCE KEY (n_nationkey) REFERENCES nation (n_nationkey)"
    "      DESTINATION KEY (n_regionkey) REFERENCES region (r_regionkey)"
    "      LABEL InRegion))";

// People and who knows whom.
constexpr std::string_view kPeopleGraph =
    "GRAPH g AS ("
    "  VERTEX TABLES (person KEY (id) LABEL Person PROPERTIES (id, name))"
    "  EDGE TABLES (knows KEY (src, dst)"
    "    SOURCE KEY (src) REFERENCES person (id)"
    "    DESTINATION KEY (dst) REFERENCES person (id) LABEL Knows))";

class GraphTableTest : public test::QueryTestBase {
 protected:
  velox::core::PlanNodePtr toSingleNodePlan(
      std::string_view graph,
      std::string_view match) {
    return QueryTestBase::toSingleNodePlan(parseSelect(
        fmt::format("WITH {} SELECT * FROM GRAPH_TABLE (g {})", graph, match)));
  }

  // Adds the tables of kPeopleGraph next to TPC-H: 1'000 people, each knowing
  // ten others.
  void configureTestConnector() override {
    testConnector_->addTpchTables();
    testConnector_
        ->addTable(
            "person",
            velox::ROW({{"id", velox::BIGINT()}, {"name", velox::VARCHAR()}}))
        ->setStats(1'000, {{"name", {.numDistinct = 1'000}}});
    testConnector_
        ->addTable("knows", velox::ROW({"src", "dst"}, velox::BIGINT()))
        ->setStats(10'000, {});
  }
};

// ANY keeps one match per pair of endpoints: a RowNumber partitioned by both
// endpoints' keys with a limit of one. Each nation row is both a Nation vertex
// and its InRegion edge, so nation is read once.
TEST_F(GraphTableTest, selector) {
  auto plan = toSingleNodePlan(
      kNationGraph,
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

// A repeated edge walks from the start: the anchor reads the start's rows, and
// each step probes a hash table of the edges, built once for the loop. The
// walks with at least one hop then join the end.
TEST_F(GraphTableTest, repetition) {
  auto plan = toSingleNodePlan(
      kPeopleGraph,
      "MATCH (a IS Person) -[IS Knows]->{1,2} (b IS Person) "
      "COLUMNS (a.name AS a, b.name AS b)");
  auto matcher =
      velox::core::PlanMatcherBuilder()
          .fixedPoint(
              velox::core::FixedPointMatch("walk")
                  .outputState(
                      /*append=*/true,
                      matchScan("person").project({"name", "id", "0"}))
                  .hashTableState(matchScan("knows"))
                  .plan(
                      velox::core::PlanMatcherBuilder()
                          .stateSource("walk", /*delta=*/true)
                          .aliases({"name", "vertex", "hops"})
                          .filter("hops < 2")
                          .stateHashJoin({"vertex"})
                          .project({"name", "dst", "hops + 1"}))
                  .convergeOnEmpty({.maxIterations = 3}))
          .aliases({"name", "vertex", "hops"})
          .filter("hops >= 1")
          .hashJoinInner(
              matchScan("person").aliases({"id", "b_name"}),
              {.keys = {{"vertex = id"}}})
          .project({"name", "b_name"})
          .build();
  AXIOM_ASSERT_PLAN(plan, matcher);
}

// Walks of at most one hop need no loop: the start's rows for zero hops, and
// the start joined with the edges for one.
TEST_F(GraphTableTest, upToOneHop) {
  auto plan = toSingleNodePlan(
      kPeopleGraph,
      "MATCH (a IS Person) -[IS Knows]->{0,1} (b IS Person) "
      "COLUMNS (a.name AS a, b.name AS b)");
  auto matcher =
      matchScan("person")
          .project({"name", "id"})
          .localPartition(
              {matchScan("knows")
                   .hashJoinInner(matchScan("person"), {.keys = {{"src = id"}}})
                   .project({"name", "dst"})})
          .aliases({"name", "vertex"})
          .hashJoinInner(
              matchScan("person").aliases({"id", "b_name"}),
              {.keys = {{"vertex = id"}}})
          .project({"name", "b_name"})
          .build();
  AXIOM_ASSERT_PLAN(plan, matcher);
}

// The end has fewer rows than the start, so the walk leaves from the end and
// reads each hop from its destination to its source.
TEST_F(GraphTableTest, repetitionFromEnd) {
  auto plan = toSingleNodePlan(
      kPeopleGraph,
      "MATCH (a IS Person) -[IS Knows]->{1,2} (b IS Person WHERE b.name = 'Dave') "
      "COLUMNS (a.name AS a)");
  auto matcher =
      velox::core::PlanMatcherBuilder()
          .fixedPoint(
              velox::core::FixedPointMatch("walk")
                  .outputState(
                      /*append=*/true,
                      matchScan("person")
                          .aliases({"id", "name"})
                          .filter("name = 'Dave'")
                          .project({"id", "0"}))
                  .hashTableState(matchScan("knows").project({"dst", "src"}))
                  .plan(
                      velox::core::PlanMatcherBuilder()
                          .stateSource("walk", /*delta=*/true)
                          .aliases({"vertex", "hops"})
                          .filter("hops < 2")
                          .stateHashJoin({"vertex"})
                          .project({"src", "hops + 1"}))
                  .convergeOnEmpty({.maxIterations = 3}))
          .aliases({"vertex", "hops"})
          .filter("hops >= 1")
          .hashJoinInner(
              matchScan("person").aliases({"id", "a_name"}),
              {.keys = {{"vertex = id"}}})
          .project({"a_name"})
          .build();
  AXIOM_ASSERT_PLAN(plan, matcher);
}

// A vertex keeps only the tables that can connect to its edges. InRegion
// reaches only regions, so the vertex between the two edges reads region alone,
// with no union over nation and region and no table ID column.
TEST_F(GraphTableTest, narrowing) {
  auto plan = toSingleNodePlan(
      kNationGraph,
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
