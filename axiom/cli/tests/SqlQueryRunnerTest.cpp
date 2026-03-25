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

#include "axiom/cli/SqlQueryRunner.h"
#include <folly/init/Init.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "axiom/connectors/tests/TestConnector.h"
#include "velox/common/base/tests/GTestUtils.h"
#include "velox/common/time/Timer.h"
#include "velox/functions/prestosql/types/TimestampWithTimeZoneType.h"
#include "velox/vector/tests/utils/VectorTestBase.h"

using namespace facebook::velox;

namespace axiom::sql {
namespace {

class SqlQueryRunnerTest : public ::testing::Test, public test::VectorTestBase {
 protected:
  static void SetUpTestCase() {
    facebook::velox::memory::MemoryManager::testingSetInstance(
        facebook::velox::memory::MemoryManager::Options{});
  }

  void SetUp() override {
    runner_ = makeRunner();
  }

  void TearDown() override {
    runner_.reset();
    for (const auto& id : connectorIds_) {
      facebook::velox::connector::unregisterConnector(id);
    }
  }

  inline static const std::string kDefaultSchema{
      facebook::axiom::connector::TestConnector::kDefaultSchema};

  std::unique_ptr<SqlQueryRunner> makeRunner(
      const std::string& connectorId = "test") {
    auto runner = std::make_unique<SqlQueryRunner>();

    runner->initialize([&]() {
      auto testConnector =
          std::make_shared<facebook::axiom::connector::TestConnector>(
              connectorId);
      facebook::velox::connector::registerConnector(testConnector);

      connectorIds_.emplace_back(testConnector->connectorId());

      return std::make_pair(testConnector->connectorId(), kDefaultSchema);
    });

    return runner;
  }

  SqlQueryRunner::SqlResult run(std::string_view sql) {
    return runner_->run(sql, {});
  }

  RowVectorPtr fetchSingleRow(std::string_view sql) {
    auto result = run(sql);
    VELOX_CHECK(
        !result.message.has_value(), "Query failed: {}", *result.message);
    VELOX_CHECK_EQ(1, result.results.size());
    VELOX_CHECK_EQ(1, result.results[0]->size());
    return result.results[0];
  }

  void assertSchemas(const std::vector<std::string>& expected) {
    auto result = run("SHOW SCHEMAS");
    ASSERT_FALSE(result.message.has_value());
    ASSERT_EQ(1, result.results.size());
    test::assertEqualVectors(
        result.results[0],
        makeRowVector({"Schema"}, {makeFlatVector(expected)}));
  }

  std::unique_ptr<SqlQueryRunner> runner_;

 private:
  std::vector<std::string> connectorIds_;
};

TEST_F(SqlQueryRunnerTest, runSingleStatement) {
  test::assertEqualVectors(
      fetchSingleRow("SELECT 1"),
      makeRowVector({makeFlatVector<int32_t>({1})}));
}

TEST_F(SqlQueryRunnerTest, runRejectsMultipleStatements) {
  VELOX_ASSERT_THROW(run("SELECT 1; SELECT 2"), "Expected a single statement");
}

TEST_F(SqlQueryRunnerTest, parseAndRunMixedStatementTypes) {
  auto statements = runner_->parseMultiple(
      "SELECT 42; EXPLAIN (TYPE LOGICAL) SELECT 1; select 7", {});
  ASSERT_EQ(3, statements.size());

  auto selectResult = runner_->run(*statements[0], {});
  ASSERT_FALSE(selectResult.message.has_value());
  test::assertEqualVectors(
      selectResult.results[0], makeRowVector({makeFlatVector<int32_t>({42})}));

  auto explainResult = runner_->run(*statements[1], {});
  ASSERT_TRUE(explainResult.message.has_value());
  ASSERT_FALSE(explainResult.message.value().empty());

  auto lastResult = runner_->run(*statements[2], {});
  ASSERT_FALSE(lastResult.message.has_value());
  test::assertEqualVectors(
      lastResult.results[0], makeRowVector({makeFlatVector<int32_t>({7})}));
}

TEST_F(SqlQueryRunnerTest, multipleRunnerInstances) {
  auto a = makeRunner("test_a");
  auto b = makeRunner("test_b");

  auto resultA = a->run("SELECT 1", {});
  auto resultB = b->run("SELECT 1 + 2, 'foo'", {});

  ASSERT_FALSE(resultA.message.has_value());
  ASSERT_EQ(1, resultA.results.size());

  test::assertEqualVectors(
      resultA.results[0], makeRowVector({makeFlatVector<int32_t>({1})}));

  ASSERT_FALSE(resultB.message.has_value());
  ASSERT_EQ(1, resultB.results.size());

  test::assertEqualVectors(
      resultB.results[0],
      makeRowVector({
          makeFlatVector<int32_t>({3}),
          makeFlatVector<std::string>({"foo"}),
      }));
}

TEST_F(SqlQueryRunnerTest, invalidStatementThrows) {
  EXPECT_THROW(run("INVALID SYNTAX HERE"), std::exception);
}

TEST_F(SqlQueryRunnerTest, parseMultipleWithInvalidStatement) {
  EXPECT_THROW(
      runner_->parseMultiple("SELECT 1; INVALID; SELECT 2", {}),
      std::exception);
}

TEST_F(SqlQueryRunnerTest, explainCtas) {
  {
    auto result = run("EXPLAIN (TYPE LOGICAL) CREATE TABLE t AS SELECT 1 AS x");
    ASSERT_TRUE(result.message.has_value());
    EXPECT_THAT(
        result.message.value(),
        ::testing::HasSubstr("- TableWrite CREATE: -> ROW<rows:BIGINT>"));
  }

  {
    auto result =
        run("EXPLAIN (TYPE OPTIMIZED) CREATE TABLE t AS SELECT 1 AS x");
    ASSERT_TRUE(result.message.has_value());
    EXPECT_THAT(
        result.message.value(),
        ::testing::HasSubstr("TableWrite [1.00 rows] ->"));
  }

  {
    auto result = run("EXPLAIN CREATE TABLE t AS SELECT 1 AS x");
    ASSERT_TRUE(result.message.has_value());
    EXPECT_THAT(result.message.value(), ::testing::HasSubstr("-- TableWrite"));
  }

  // EXPLAIN is side-effect-free.
  VELOX_ASSERT_THROW(run("SELECT * FROM t"), "Table not found: t");

  // EXPLAIN ANALYZE runs the query and creates the table.
  {
    auto result = run("EXPLAIN ANALYZE CREATE TABLE t AS SELECT 1 AS x");
    ASSERT_TRUE(result.message.has_value());
    EXPECT_THAT(result.message.value(), ::testing::HasSubstr("-- TableWrite"));
  }

  {
    auto result = run("SELECT * FROM t");
    ASSERT_FALSE(result.message.has_value());
    ASSERT_EQ(1, result.results.size());
    test::assertEqualVectors(
        result.results[0], makeRowVector({makeFlatVector<int32_t>({1})}));
  }
}

TEST_F(SqlQueryRunnerTest, explainCreateTable) {
  auto result = run("EXPLAIN CREATE TABLE t(x int)");
  EXPECT_EQ(result.message, R"(CREATE TABLE test."default"."t")");

  // EXPLAIN is side-effect-free.
  VELOX_ASSERT_THROW(run("SELECT * FROM t"), "Table not found: t");

  // Fails if the table already exists.
  run("CREATE TABLE t(x int)");
  VELOX_ASSERT_THROW(
      run("EXPLAIN CREATE TABLE t(x int)"), "Table already exists");

  // IF NOT EXISTS succeeds even if the table exists.
  result = run("EXPLAIN CREATE TABLE IF NOT EXISTS t(x int)");
  EXPECT_EQ(result.message, R"(CREATE TABLE IF NOT EXISTS test."default"."t")");
}

TEST_F(SqlQueryRunnerTest, explainDropTable) {
  // Fails if the table doesn't exist.
  VELOX_ASSERT_THROW(run("EXPLAIN DROP TABLE t"), "Table does not exist");

  // IF EXISTS succeeds even if the table doesn't exist.
  auto result = run("EXPLAIN DROP TABLE IF EXISTS t");
  EXPECT_EQ(result.message, R"(DROP TABLE IF EXISTS test."default"."t")");

  run("CREATE TABLE t(x int)");

  result = run("EXPLAIN DROP TABLE t");
  EXPECT_EQ(result.message, R"(DROP TABLE test."default"."t")");

  // EXPLAIN is side-effect-free.
  run("DROP TABLE t");
}

TEST_F(SqlQueryRunnerTest, showStats) {
  // Create a table with 100 rows and 4 columns: x has 100 distinct values,
  // y has 7 distinct values, z is an array column, w is NULL for every 4th row.
  run("CREATE TABLE t AS "
      "SELECT x, x % 7 AS y, sequence(1, x % 7 + 1) AS z, "
      "if(x % 4 <> 0, x + x % 7) AS w "
      "FROM unnest(sequence(1, 100)) AS _(x)");

  {
    // SHOW STATS FOR <table>: reports raw connector stats.
    auto expected = makeRowVector({
        // row_count.
        makeNullableFlatVector<int64_t>(
            {100, std::nullopt, std::nullopt, std::nullopt, std::nullopt}),
        // column_name.
        makeNullableFlatVector<std::string>({std::nullopt, "x", "y", "z", "w"}),
        // nulls_fraction: 0.25 for w; 0 for the rest.
        makeNullableFlatVector<double>({std::nullopt, 0.0, 0.0, 0.0, 0.25}),
        // distinct_values_count: NULL for z (array).
        makeNullableFlatVector<int64_t>(
            {std::nullopt, 100, 7, std::nullopt, 75}),
        // avg_length: 3 for z (array); NULL for the rest.
        makeNullableFlatVector<int64_t>(
            {std::nullopt, std::nullopt, std::nullopt, 3, std::nullopt}),
        // low_value.
        makeNullableFlatVector<std::string>(
            {std::nullopt, "1", "0", std::nullopt, "2"}),
        // high_value.
        makeNullableFlatVector<std::string>(
            {std::nullopt, "100", "6", std::nullopt, "103"}),
    });

    auto result = run("SHOW STATS FOR t");
    ASSERT_FALSE(result.message.has_value());
    ASSERT_EQ(1, result.results.size());
    test::assertEqualVectors(expected, result.results[0]);

    // SHOW STATS FOR (SELECT * FROM <table>): reports optimizer estimates. The
    // optimizer always estimates NDV (defaults to numRows when unknown) and
    // doesn't track avgLength.
    expected = makeRowVector({
        expected->childAt(0), // row_count.
        expected->childAt(1), // column_name.
        expected->childAt(2), // nulls_fraction.
        // distinct_values_count: 100 for z (optimizer defaults to numRows).
        makeNullableFlatVector<int64_t>({std::nullopt, 100, 7, 100, 75}),
        // avg_length: not tracked by the optimizer.
        makeNullConstant(TypeKind::BIGINT, 5),
        expected->childAt(5), // low_value.
        expected->childAt(6), // high_value.
    });

    result = run("SHOW STATS FOR (SELECT * FROM t)");
    ASSERT_FALSE(result.message.has_value());
    ASSERT_EQ(1, result.results.size());
    test::assertEqualVectors(expected, result.results[0]);
  }
}

// Verifies that SHOW STATS FOR (<query>) reflects optimizer estimates after
// filter pushdown: reduced row count, tightened min/max, capped NDV.
TEST_F(SqlQueryRunnerTest, showStatsForQueryWithFilter) {
  run("CREATE TABLE t AS "
      "SELECT x, x % 7 AS y, sequence(1, x % 7 + 1) AS z, "
      "if(x % 4 <> 0, x + x % 7) AS w "
      "FROM unnest(sequence(1, 100)) AS _(x)");

  auto expected = makeRowVector({
      // row_count: 50 (filter x > 50 keeps half the rows).
      makeNullableFlatVector<int64_t>(
          {50, std::nullopt, std::nullopt, std::nullopt, std::nullopt}),
      // column_name.
      makeNullableFlatVector<std::string>({std::nullopt, "x", "y", "z", "w"}),
      // nulls_fraction.
      makeNullableFlatVector<double>({std::nullopt, 0.0, 0.0, 0.0, 0.25}),
      // distinct_values_count: reduced for x and w; y stays at 7 because the
      // optimizer assumes column independence — the filter on x doesn't reduce
      // y's domain (and 7 < 50 filtered rows, so NDV is not capped).
      makeNullableFlatVector<int64_t>({std::nullopt, 50, 7, 50, 50}),
      // avg_length: not tracked by the optimizer.
      makeNullConstant(TypeKind::BIGINT, 5),
      // low_value: x tightened to 51.
      makeNullableFlatVector<std::string>(
          {std::nullopt, "51", "0", std::nullopt, "2"}),
      // high_value.
      makeNullableFlatVector<std::string>(
          {std::nullopt, "100", "6", std::nullopt, "103"}),
  });

  auto result = run("SHOW STATS FOR (SELECT * FROM t WHERE x > 50)");
  ASSERT_FALSE(result.message.has_value());
  ASSERT_EQ(1, result.results.size());
  test::assertEqualVectors(expected, result.results[0]);
}

TEST_F(SqlQueryRunnerTest, createAndDropSchema) {
  assertSchemas({kDefaultSchema});

  auto createResult = run("CREATE SCHEMA foo");
  EXPECT_EQ("Created schema: foo", createResult.message);
  assertSchemas({kDefaultSchema, "foo"});

  auto dropResult = run("DROP SCHEMA foo");
  EXPECT_EQ("Dropped schema: foo", dropResult.message);
  assertSchemas({kDefaultSchema});
}

TEST_F(SqlQueryRunnerTest, createSchemaErrors) {
  VELOX_ASSERT_THROW(run("CREATE SCHEMA default"), "Schema already exists");

  auto result = run("CREATE SCHEMA IF NOT EXISTS default");
  EXPECT_EQ("Created schema: default", result.message);
}

TEST_F(SqlQueryRunnerTest, dropSchemaErrors) {
  VELOX_ASSERT_THROW(run("DROP SCHEMA nonexistent"), "Schema does not exist");

  auto result = run("DROP SCHEMA IF EXISTS nonexistent");
  EXPECT_EQ("Dropped schema: nonexistent", result.message);

  VELOX_ASSERT_THROW(run("DROP SCHEMA default"), "Cannot drop the default");
  assertSchemas({kDefaultSchema});

  VELOX_ASSERT_THROW(
      run("DROP SCHEMA default CASCADE"), "CASCADE is not supported");
}

TEST_F(SqlQueryRunnerTest, createTableInNonExistentSchema) {
  VELOX_ASSERT_THROW(
      run("CREATE TABLE nonexistent.t AS SELECT 1 AS x"),
      "Schema does not exist: nonexistent");
}

// Verifies that current_timestamp returns a value close to the actual wall
// clock time. Captures wall clock before and after the query to bound the
// expected result without relying on an exact match.
TEST_F(SqlQueryRunnerTest, currentTimestamp) {
  auto before = getCurrentTimeMs();
  auto row = fetchSingleRow("SELECT current_timestamp");
  auto after = getCurrentTimeMs();

  auto packed = row->childAt(0)->as<SimpleVector<int64_t>>()->valueAt(0);
  auto millis = unpackMillisUtc(packed);

  EXPECT_GE(millis, before);
  EXPECT_LE(millis, after);
}

TEST_F(SqlQueryRunnerTest, explainFormatGraphviz) {
  for (const auto& type : {"LOGICAL", "GRAPH"}) {
    SCOPED_TRACE(type);

    // FORMAT GRAPHVIZ produces DOT output.
    auto graphviz = run(
        fmt::format("EXPLAIN (TYPE {}, FORMAT GRAPHVIZ) SELECT 1 AS x", type));
    ASSERT_TRUE(graphviz.message.has_value());
    EXPECT_THAT(graphviz.message.value(), ::testing::HasSubstr("digraph"));

    // Without FORMAT, produces text (no "digraph").
    auto text = run(fmt::format("EXPLAIN (TYPE {}) SELECT 1 AS x", type));
    ASSERT_TRUE(text.message.has_value());
    EXPECT_THAT(
        text.message.value(), ::testing::Not(::testing::HasSubstr("digraph")));
  }

  // FORMAT GRAPHVIZ with unsupported TYPE fails.
  VELOX_ASSERT_USER_THROW(
      run("EXPLAIN (TYPE OPTIMIZED, FORMAT GRAPHVIZ) SELECT 1 AS x"),
      "EXPLAIN FORMAT GRAPHVIZ is supported for TYPE LOGICAL and TYPE GRAPH only");

  VELOX_ASSERT_USER_THROW(
      run("EXPLAIN (FORMAT GRAPHVIZ) SELECT 1 AS x"),
      "EXPLAIN FORMAT GRAPHVIZ is supported for TYPE LOGICAL and TYPE GRAPH only");

  // FORMAT JSON is rejected.
  VELOX_ASSERT_USER_THROW(
      run("EXPLAIN (FORMAT JSON) SELECT 1 AS x"),
      "Unsupported EXPLAIN format: JSON");
}

TEST_F(SqlQueryRunnerTest, showSchemasWithLike) {
  run("CREATE SCHEMA dev");
  run("CREATE SCHEMA staging");
  SCOPE_EXIT {
    run("DROP SCHEMA IF EXISTS dev");
    run("DROP SCHEMA IF EXISTS staging");
  };

  auto result = run("SHOW SCHEMAS LIKE 'd%'");
  ASSERT_EQ(1, result.results.size());
  test::assertEqualVectors(
      result.results[0],
      makeRowVector(
          {"Schema"}, {makeFlatVector<std::string>({kDefaultSchema, "dev"})}));
}

TEST_F(SqlQueryRunnerTest, showCreateTable) {
  {
    run("CREATE TABLE t1 (id INTEGER, name VARCHAR)");
    auto row = fetchSingleRow("SHOW CREATE TABLE t1");
    auto ddl = row->childAt(0)->variantAt(0).value<std::string>();
    EXPECT_EQ(
        ddl,
        "CREATE TABLE test.\"default\".\"t1\" (\n"
        "   id INTEGER,\n"
        "   name VARCHAR\n"
        ")");
  }

  {
    // Hidden columns are not part of the schema and should not appear
    // in the DDL. The output should be equivalent to the original
    // CREATE TABLE statement.
    run("CREATE TABLE t2 (a INTEGER, b VARCHAR) "
        "WITH (hidden = ARRAY['h1', 'h2'])");
    auto row = fetchSingleRow("SHOW CREATE TABLE t2");
    auto ddl = row->childAt(0)->variantAt(0).value<std::string>();
    EXPECT_EQ(
        ddl,
        "CREATE TABLE test.\"default\".\"t2\" (\n"
        "   a INTEGER,\n"
        "   b VARCHAR\n"
        ")\n"
        "WITH (\n"
        "   hidden = ARRAY['h1', 'h2']\n"
        ")");
  }

  // Non-existent table.
  VELOX_ASSERT_USER_THROW(
      run("SHOW CREATE TABLE no_such_table"), "Table not found");
}

} // namespace
} // namespace axiom::sql

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  folly::Init init(&argc, &argv, false);
  return RUN_ALL_TESTS();
}
