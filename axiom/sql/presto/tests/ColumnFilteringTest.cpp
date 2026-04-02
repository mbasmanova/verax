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

#include "axiom/sql/presto/tests/PrestoParserTestBase.h"
#include "velox/common/base/tests/GTestUtils.h"

namespace axiom::sql::presto::test {

using namespace facebook::velox;

namespace {

class ColumnFilteringTest : public PrestoParserTestBase {};

TEST_F(ColumnFilteringTest, selectStarExclude) {
  // nation has: n_nationkey, n_name, n_regionkey, n_comment

  {
    auto matchOutput = [](const std::vector<std::string>& columns) {
      return matchScan("nation").project().output(columns);
    };

    // EXCLUDE single column.
    testSelect(
        "SELECT * EXCLUDE (n_comment) FROM nation",
        matchOutput({"n_nationkey", "n_name", "n_regionkey"}));

    // EXCLUDE multiple columns.
    testSelect(
        "SELECT * EXCLUDE (n_regionkey, n_comment) FROM nation",
        matchOutput({"n_nationkey", "n_name"}));

    // Qualified star with EXCLUDE.
    testSelect(
        "SELECT nation.* EXCLUDE (n_comment) FROM nation",
        matchOutput({"n_nationkey", "n_name", "n_regionkey"}));

    // EXCLUDE as identifier still works (backward compat).
    testSelect(
        "SELECT n_nationkey AS exclude FROM nation", matchOutput({"exclude"}));
  }

  // EXCLUDE in join.
  testSelect(
      "SELECT nation.* EXCLUDE (n_comment) FROM nation, region "
      "WHERE n_regionkey = r_regionkey",
      matchScan("nation")
          .join(matchScan("region").build())
          .filter()
          .project()
          .output({"n_nationkey", "n_name", "n_regionkey"}));

  // EXCLUDE non-existent column raises error.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT * EXCLUDE (no_such_column) FROM nation"),
      "Column not found for EXCLUDE: no_such_column");
}

TEST_F(ColumnFilteringTest, selectStarReplace) {
  // nation has: n_nationkey, n_name, n_regionkey, n_comment

  // REPLACE single column with expression.
  testSelect(
      "SELECT * REPLACE (upper(n_name) AS n_name) FROM nation",
      matchScan()
          .project(
              {"n_nationkey",
               "upper(n_name) AS n_name",
               "n_regionkey",
               "n_comment"})
          .output({"n_nationkey", "n_name", "n_regionkey", "n_comment"}));

  // REPLACE with constant.
  testSelect(
      "SELECT * REPLACE (0 AS n_regionkey) FROM nation",
      matchScan()
          .project({"n_nationkey", "n_name", "0 AS n_regionkey", "n_comment"})
          .output({"n_nationkey", "n_name", "n_regionkey", "n_comment"}));

  // Chained EXCLUDE + REPLACE.
  testSelect(
      "SELECT * EXCLUDE (n_comment) REPLACE (upper(n_name) AS n_name) FROM nation",
      matchScan()
          .project({"n_nationkey", "upper(n_name) AS n_name", "n_regionkey"})
          .output({"n_nationkey", "n_name", "n_regionkey"}));

  // REPLACE non-existent column raises error.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT * REPLACE (1 AS no_such_column) FROM nation"),
      "Column not found for REPLACE: no_such_column");

  // REPLACE column that was excluded raises error.
  VELOX_ASSERT_THROW(
      parseSelect(
          "SELECT * EXCLUDE (n_name) REPLACE (upper(n_name) AS n_name) FROM nation"),
      "Column not found for REPLACE: n_name");
}

TEST_F(ColumnFilteringTest, selectColumns) {
  // nation has: n_nationkey, n_name, n_regionkey, n_comment

  {
    auto matchOutput = [](const std::vector<std::string>& columns) {
      return matchScan("nation").project().output(columns);
    };

    // Match all columns starting with 'n_n'.
    testSelect(
        "SELECT COLUMNS('n_n.*') FROM nation",
        matchOutput({"n_nationkey", "n_name"}));

    // Match all columns.
    testSelect(
        "SELECT COLUMNS('.*') FROM nation",
        matchOutput({"n_nationkey", "n_name", "n_regionkey", "n_comment"}));

    // Qualified COLUMNS.
    testSelect(
        "SELECT nation.COLUMNS('n_n.*') FROM nation",
        matchOutput({"n_nationkey", "n_name"}));

    // COLUMNS with EXCLUDE.
    testSelect(
        "SELECT COLUMNS('n_n.*') EXCLUDE (n_name) FROM nation",
        matchOutput({"n_nationkey"}));

    // Mixed select items: star with EXCLUDE, multiple COLUMNS.
    testSelect(
        "SELECT * EXCLUDE (n_name, n_comment), COLUMNS('n_n.*') FROM nation",
        matchOutput({"n_nationkey", "n_regionkey", "n_nationkey", "n_name"}));
  }

  // COLUMNS with REPLACE.
  testSelect(
      "SELECT COLUMNS('n_n.*') REPLACE (upper(n_name) AS n_name) FROM nation",
      matchScan("nation")
          .project({"n_nationkey", "upper(n_name) AS n_name"})
          .output({"n_nationkey", "n_name"}));

  // No columns match -> error.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT COLUMNS('xyz.*') FROM nation"),
      "COLUMNS('xyz.*') matched no columns");
}

TEST_F(ColumnFilteringTest, selectStarModifiersErrors) {
  // Duplicate EXCLUDE clauses.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT * EXCLUDE (n_name) EXCLUDE (n_comment) FROM nation"),
      "Duplicate EXCLUDE clause");

  // Duplicate REPLACE clauses.
  VELOX_ASSERT_THROW(
      parseSelect(
          "SELECT * REPLACE (1 AS n_name) REPLACE (2 AS n_comment) FROM nation"),
      "Duplicate REPLACE clause");

  // EXCLUDE all columns → error.
  VELOX_ASSERT_THROW(
      parseSelect(
          "SELECT * EXCLUDE (n_nationkey, n_name, n_regionkey, n_comment) "
          "FROM nation"),
      "EXCLUDE removed all columns");

  // REPLACE same column twice → error.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT * REPLACE (1 AS n_name, 2 AS n_name) FROM nation"),
      "Duplicate column in REPLACE: n_name");

  // EXCLUDE same column twice → error.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT * EXCLUDE (n_name, n_name) FROM nation"),
      "Duplicate column in EXCLUDE: n_name");

  // Invalid regex pattern.
  VELOX_ASSERT_THROW(
      parseSelect("SELECT COLUMNS('[invalid') FROM nation"),
      "Invalid regex pattern: missing ]: [invalid");
}

TEST_F(ColumnFilteringTest, friendlySqlDisabled) {
  // EXCLUDE requires friendlySql.
  VELOX_ASSERT_THROW(
      makeStrictParser().parse("SELECT * EXCLUDE (n_name) FROM nation"),
      "EXCLUDE and REPLACE modifiers require Friendly SQL mode");

  // COLUMNS requires friendlySql.
  VELOX_ASSERT_THROW(
      makeStrictParser().parse("SELECT COLUMNS('.*') FROM nation"),
      "COLUMNS() requires Friendly SQL mode");
}

// Tests for EXCLUDE/REPLACE/COLUMNS behavior with duplicate column names
// (e.g., self-joins). EXCLUDE and COLUMNS match against original column names,
// not auto-generated disambiguated names.
TEST_F(ColumnFilteringTest, duplicateColumnNames) {
  // nation self-join: all column names are duplicated.
  // nation has: n_nationkey, n_name, n_regionkey, n_comment
  auto matchOutput = [](const std::vector<std::string>& columns) {
    return matchScan("nation")
        .join(matchScan("nation").build())
        .project()
        .output(columns);
  };

  // EXCLUDE removes all columns with the matching original name.
  testSelect(
      "SELECT * EXCLUDE (n_comment) FROM nation a, nation b",
      matchOutput(
          {"n_nationkey",
           "n_name",
           "n_regionkey",
           "n_nationkey",
           "n_name",
           "n_regionkey"}));

  // Qualified EXCLUDE only removes from the specified table.
  testSelect(
      "SELECT a.* EXCLUDE (n_comment), b.n_nationkey "
      "FROM nation a, nation b",
      matchOutput({"n_nationkey", "n_name", "n_regionkey", "n_nationkey"}));

  // COLUMNS matches against original column names.
  testSelect(
      "SELECT COLUMNS('n_name') FROM nation a, nation b",
      matchOutput({"n_name", "n_name"}));

  // Qualified COLUMNS restricts to one table.
  testSelect(
      "SELECT a.COLUMNS('n_n.*') FROM nation a, nation b",
      matchOutput({"n_nationkey", "n_name"}));

  // REPLACE with ambiguous column name fails.
  VELOX_ASSERT_THROW(
      parseSelect(
          "SELECT * REPLACE (upper(n_name) AS n_name) FROM nation a, nation b"),
      "Column is ambiguous for REPLACE");

  // Qualified REPLACE with qualified expression works.
  testSelect(
      "SELECT a.* REPLACE (upper(a.n_name) AS n_name) "
      "FROM nation a, nation b",
      matchOutput({"n_nationkey", "n_name", "n_regionkey", "n_comment"}));

  // Qualified name as REPLACE target is a syntax error.
  AXIOM_EXPECT_PARSE_ERROR(
      parseSelect("SELECT * REPLACE (1 AS a.n_name) FROM nation a, nation b"),
      "mismatched input '.'");
}

} // namespace
} // namespace axiom::sql::presto::test
