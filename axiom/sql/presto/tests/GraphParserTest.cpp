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

#include "axiom/sql/presto/tests/ExpectPrestoSqlError.h"
#include "axiom/sql/presto/tests/PrestoParserTestBase.h"
#include "velox/common/base/tests/GTestUtils.h"

namespace axiom::sql::presto::test {

using namespace facebook::velox;

namespace {

class GraphParserTest : public PrestoParserTestBase {
 protected:
  GraphParserTest() {
    parserOptions_.graphQueries = true;
  }

  // Prefixes 'query' with graph g: vertices N (nation) and R (region), and
  // edge InRegion from N to R, backed by nation's region key.
  static std::string withGraph(std::string_view query) {
    return fmt::format(
        "WITH GRAPH g AS ("
        "  VERTEX TABLES ("
        "    nation KEY (n_nationkey) LABEL N,"
        "    region KEY (r_regionkey) LABEL R)"
        "  EDGE TABLES ("
        "    nation AS in_region KEY (n_nationkey)"
        "      SOURCE KEY (n_nationkey) REFERENCES nation (n_nationkey)"
        "      DESTINATION KEY (n_regionkey) REFERENCES region (r_regionkey)"
        "      LABEL InRegion)) "
        "{}",
        query);
  }
};

// COLUMNS that read a property or a path length are outputs of the graph
// match. Any other expression is computed above it.
TEST_F(GraphParserTest, columns) {
  testSelect(
      withGraph(
          "SELECT * FROM GRAPH_TABLE (g "
          "MATCH p = (a IS N) -[e IS InRegion]-> (b IS R) "
          "COLUMNS (a.n_name, b.r_name, path_length(p)))"),
      matchGraph({"a.n_name", "b.r_name", "path_length(p)"}).output());

  testSelect(
      withGraph(
          "SELECT * FROM GRAPH_TABLE (g "
          "MATCH (a IS N) -[e IS InRegion]-> (b IS R) "
          "COLUMNS (length(a.n_name) AS len, b.r_name))"),
      matchGraph({"a.n_name AS name", "b.r_name AS region"})
          .project({"length(name)", "region"})
          .output());

  // Repeated reads and repeated names are each their own column.
  testSelect(
      withGraph(
          "SELECT * FROM GRAPH_TABLE (g "
          "MATCH (a IS N), (c IS N) "
          "COLUMNS (a.n_name, c.n_name, a.n_name))"),
      matchGraph({"a.n_name AS a_name", "c.n_name AS c_name"})
          .project({"a_name", "c_name", "a_name"})
          .output());

  // A property of a pattern under a repetition is an array with one entry per
  // repetition.
  const auto plan = parseSelect(withGraph(
      "SELECT * FROM GRAPH_TABLE (g "
      "MATCH (a IS N) -[e IS InRegion]->{1,3} (b IS R) "
      "COLUMNS (e.n_name))"));
  EXPECT_EQ(*plan->outputType()->childAt(0), *ARRAY(VARCHAR()));
}

// Path patterns that share a pattern name match the same element.
TEST_F(GraphParserTest, paths) {
  testSelect(
      withGraph(
          "SELECT * FROM GRAPH_TABLE (g "
          "MATCH (a IS N) -[e IS InRegion]-> (b IS R), "
          "(c IS N) -[f IS InRegion]-> (b) "
          "COLUMNS (a.n_name AS a_name, c.n_name AS c_name, b.r_name))"),
      matchGraph({"a.n_name", "c.n_name", "b.r_name"}).output());
}

// A label on several tables reads the properties they all define.
TEST_F(GraphParserTest, sharedLabel) {
  testSelect(
      "WITH GRAPH g AS ("
      "  VERTEX TABLES ("
      "    nation KEY (n_nationkey) LABEL Place PROPERTIES (n_name AS name),"
      "    region KEY (r_regionkey) LABEL Place PROPERTIES (r_name AS name))) "
      "SELECT * FROM GRAPH_TABLE (g MATCH (a IS Place) COLUMNS (a.name))",
      matchGraph({"a.name"}).output());

  // An edge label may connect different pairs of vertices on different
  // tables, and an edge endpoint may reference a table with several labels.
  testSelect(
      "WITH GRAPH g AS ("
      "  VERTEX TABLES ("
      "    nation KEY (n_nationkey) LABEL N,"
      "    region KEY (r_regionkey) LABEL R LABEL Place)"
      "  EDGE TABLES ("
      "    nation AS u KEY (n_nationkey)"
      "      SOURCE KEY (n_nationkey) REFERENCES nation (n_nationkey)"
      "      DESTINATION KEY (n_regionkey) REFERENCES region (r_regionkey)"
      "      LABEL Link PROPERTIES (n_name AS name),"
      "    region AS v KEY (r_regionkey)"
      "      SOURCE KEY (r_regionkey) REFERENCES region (r_regionkey)"
      "      DESTINATION KEY (r_regionkey) REFERENCES region (r_regionkey)"
      "      LABEL Link PROPERTIES (r_name AS name))) "
      "SELECT * FROM GRAPH_TABLE (g MATCH (a) -[e IS Link]-> (b) "
      "COLUMNS (e.name))",
      matchGraph({"e.name"}).output());
}

// Predicates read properties of the patterns they can see.
TEST_F(GraphParserTest, predicates) {
  for (const auto* match : {
           "(a IS N WHERE a.n_name = 'x') -[e IS InRegion]-> (b IS R)",
           "((a IS N) -[e IS InRegion]-> (b IS R) WHERE a.n_name = b.r_name)",
           "(a IS N) -[e IS InRegion]-> (b IS R) WHERE a.n_name = b.r_name",
       }) {
    SCOPED_TRACE(match);
    testSelect(
        withGraph(
            fmt::format(
                "SELECT * FROM GRAPH_TABLE (g MATCH {} COLUMNS (b.r_name))",
                match)),
        matchGraph({"b.r_name"}).output());
  }
}

TEST_F(GraphParserTest, graphErrors) {
  const auto query =
      "SELECT * FROM GRAPH_TABLE (g MATCH (a) COLUMNS (a.n_name))";
  const std::vector<std::pair<std::string, std::string>> cases = {
      {
          "VERTEX TABLES (nation KEY (n_nationkey)) "
          "EDGE TABLES (region KEY (r_regionkey) "
          "SOURCE KEY (r_regionkey) REFERENCES missing (n_nationkey) "
          "DESTINATION KEY (r_regionkey) REFERENCES nation (n_nationkey))",
          "Edge table references an unknown vertex table: region, missing",
      },
      {
          "VERTEX TABLES (nation KEY (n_nationkey)) "
          "EDGE TABLES (region KEY (r_regionkey) "
          "SOURCE KEY (r_name) REFERENCES nation (n_name) "
          "DESTINATION KEY (r_regionkey) REFERENCES nation (n_nationkey))",
          "Edge endpoint must reference the key of its vertex table: region, "
          "nation",
      },
      {
          "VERTEX TABLES ("
          "nation KEY (n_nationkey) LABEL X PROPERTIES (n_name), "
          "region KEY (r_regionkey) LABEL X PROPERTIES (r_name))",
          "Graph vertex or edge is defined twice differently: x",
      },
      {
          "VERTEX TABLES (nation KEY (n_nationkey) "
          "LABEL A PROPERTIES (n_name AS x) "
          "LABEL B PROPERTIES (n_comment AS x))",
          "Graph element table gives a property two expressions: nation.x",
      },
  };
  for (const auto& [definition, error] : cases) {
    SCOPED_TRACE(definition);
    VELOX_ASSERT_USER_THROW(
        parseSql(fmt::format("WITH GRAPH g AS ({}) {}", definition, query)),
        error);
  }

  AXIOM_EXPECT_PRESTO_SEMANTIC_ERROR(
      parseSql(
          "WITH GRAPH g AS (VERTEX TABLES (nation KEY (n_nationkey))),"
          " GRAPH g AS (VERTEX TABLES (region KEY (r_regionkey))) "
          "SELECT 1"),
      "WITH graph name specified more than once: g");
}

TEST_F(GraphParserTest, matchErrors) {
  const std::vector<std::pair<std::string, std::string>> cases = {
      {
          "(a IS X) COLUMNS (a.n_name)",
          "Vertex not found in graph: x",
      },
      {
          "(a IS N WHERE b.n_name = 'x') COLUMNS (a.n_name)",
          "Pattern predicate reads a name it cannot see: b",
      },
      {
          "(a IS N) COLUMNS (c.n_name)",
          "Graph match output references an unknown pattern name: c",
      },
      {
          "(a IS N) COLUMNS (a.r_name)",
          "Property is not defined by any table the element can match: r_name",
      },
      {
          "(a IS N) -[e IS InRegion]->{1,3} (b IS R) "
          "WHERE e.n_name = 'x' "
          "COLUMNS (a.n_name)",
          "Graph match predicate reads a pattern under a repetition: e",
      },
  };
  for (const auto& [match, error] : cases) {
    SCOPED_TRACE(match);
    VELOX_ASSERT_USER_THROW(
        parseSql(withGraph(
            fmt::format("SELECT * FROM GRAPH_TABLE (g MATCH {})", match))),
        error);
  }

  AXIOM_EXPECT_PRESTO_SEMANTIC_ERROR(
      parseSql("SELECT * FROM GRAPH_TABLE (missing MATCH (a) COLUMNS (a.x))"),
      "Property graph not found: missing");
}

// A graph is visible in the query that defines it and in queries nested in
// it.
TEST_F(GraphParserTest, scope) {
  testSelect(
      withGraph(
          "SELECT * FROM (SELECT * FROM GRAPH_TABLE (g "
          "MATCH (a IS N) COLUMNS (a.n_name)))"),
      matchGraph({"a.n_name"}).output());

  AXIOM_EXPECT_PRESTO_SEMANTIC_ERROR(
      parseSql(
          "SELECT * FROM (" + withGraph("SELECT 1") +
          ") CROSS JOIN GRAPH_TABLE (g MATCH (a) COLUMNS (a.n_name))"),
      "Property graph not found: g");
}

} // namespace
} // namespace axiom::sql::presto::test
