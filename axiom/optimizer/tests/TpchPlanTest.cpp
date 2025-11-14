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

#include <folly/init/Init.h>
#include <gtest/gtest.h>
#include "axiom/logical_plan/PlanBuilder.h"
#include "axiom/optimizer/tests/HiveQueriesTestBase.h"
#include "velox/dwio/common/tests/utils/DataFiles.h"
#include "velox/exec/tests/utils/TpchQueryBuilder.h"

DEFINE_int32(num_repeats, 1, "Number of repeats for optimization timing");

DECLARE_uint32(optimizer_trace);
DECLARE_string(history_save_path);

namespace facebook::axiom::optimizer {
namespace {

using namespace facebook::velox;
namespace lp = facebook::axiom::logical_plan;

class TpchPlanTest : public virtual test::HiveQueriesTestBase {
 protected:
  static void SetUpTestCase() {
    test::HiveQueriesTestBase::SetUpTestCase();
  }

  static void TearDownTestCase() {
    if (!FLAGS_history_save_path.empty()) {
      suiteHistory().saveToFile(FLAGS_history_save_path);
    }
    test::HiveQueriesTestBase::TearDownTestCase();
  }

  void SetUp() override {
    HiveQueriesTestBase::SetUp();

    referenceBuilder_ = std::make_unique<exec::test::TpchQueryBuilder>(
        LocalRunnerTestBase::localFileFormat_);
    referenceBuilder_->initialize(LocalRunnerTestBase::localDataPath_);
  }

  void TearDown() override {
    HiveQueriesTestBase::TearDown();
  }

  static std::string readSqlFromFile(const std::string& filePath) {
    auto path = velox::test::getDataFilePath("axiom/optimizer/tests", filePath);
    std::ifstream inputFile(path, std::ifstream::binary);

    VELOX_CHECK(inputFile, "Failed to open SQL file: {}", path);

    // Find out file size.
    auto begin = inputFile.tellg();
    inputFile.seekg(0, std::ios::end);
    auto end = inputFile.tellg();

    const auto fileSize = end - begin;
    VELOX_CHECK_GT(fileSize, 0, "SQL file is empty: {}", path);

    // Read the file.
    std::string sql;
    sql.resize(fileSize);

    inputFile.seekg(begin);
    inputFile.read(sql.data(), fileSize);
    inputFile.close();

    return sql;
  }

  std::string readTpchSql(int32_t query) {
    return readSqlFromFile(fmt::format("tpch.queries/q{}.sql", query));
  }

  lp::LogicalPlanNodePtr parseTpchSql(int32_t query) {
    auto sql = readTpchSql(query);

    ::axiom::sql::presto::PrestoParser prestoParser(
        exec::test::kHiveConnectorId, std::nullopt, pool());
    auto statement = prestoParser.parse(sql);

    VELOX_CHECK(statement->isSelect());

    auto logicalPlan =
        statement->as<::axiom::sql::presto::SelectStatement>()->plan();
    VELOX_CHECK_NOT_NULL(logicalPlan);

    return logicalPlan;
  }

  void checkTpchSql(int32_t query) {
    auto sql = readTpchSql(query);
    auto referencePlan = referenceBuilder_->getQueryPlan(query).plan;
    checkResults(sql, referencePlan);
  }

  std::unique_ptr<exec::test::TpchQueryBuilder> referenceBuilder_;
};

TEST_F(TpchPlanTest, stats) {
  auto verifyStats = [&](const auto& tableName, auto cardinality) {
    SCOPED_TRACE(tableName);

    auto logicalPlan = lp::PlanBuilder()
                           .tableScan(exec::test::kHiveConnectorId, tableName)
                           .build();

    auto planAndStats = planVelox(logicalPlan);
    auto stats = planAndStats.prediction;
    ASSERT_EQ(stats.size(), 1);

    ASSERT_EQ(stats.begin()->first, logicalPlan->id());
    ASSERT_EQ(stats.begin()->second.cardinality, cardinality);
  };

  verifyStats("region", 5);
  verifyStats("nation", 25);
  verifyStats("orders", 150'000);
  verifyStats("lineitem", 600'572);
}

TEST_F(TpchPlanTest, q01) {
  checkTpchSql(1);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q02) {
  checkTpchSql(2);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q03) {
  checkTpchSql(3);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q04) {
  checkTpchSql(4);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q05) {
  checkTpchSql(5);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q06) {
  checkTpchSql(6);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q07) {
  checkTpchSql(7);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q08) {
  checkTpchSql(8);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q09) {
  checkTpchSql(9);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q10) {
  checkTpchSql(10);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q11) {
  checkTpchSql(11);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q12) {
  checkTpchSql(12);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q13) {
  checkTpchSql(13);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q14) {
  checkTpchSql(14);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q15) {
  checkTpchSql(15);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q16) {
  checkTpchSql(16);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q17) {
  checkTpchSql(17);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q18) {
  checkTpchSql(18);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q19) {
  checkTpchSql(19);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q20) {
  // TODO Fix the plan when 'enableReducingExistences' is true.
  const bool originalEnableReducingExistences =
      optimizerOptions_.enableReducingExistences;
  optimizerOptions_.enableReducingExistences = false;
  SCOPE_EXIT {
    optimizerOptions_.enableReducingExistences =
        originalEnableReducingExistences;
  };
  checkTpchSql(20);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q21) {
  checkTpchSql(21);

  // TODO Verify the plan.
}

TEST_F(TpchPlanTest, q22) {
  checkTpchSql(22);

  // TODO Verify the plan.
}

// Use to re-generate the plans stored in tpch.plans directory.
TEST_F(TpchPlanTest, DISABLED_makePlans) {
  const auto path =
      velox::test::getDataFilePath("axiom/optimizer/tests", "tpch.plans");

  const runner::MultiFragmentPlan::Options options{
      .numWorkers = 1, .numDrivers = 1};

  for (auto q = 1; q <= 22; ++q) {
    LOG(ERROR) << "q" << q;
    const bool originalEnableReducingExistences =
        optimizerOptions_.enableReducingExistences;
    optimizerOptions_.enableReducingExistences = (q != 20);
    SCOPE_EXIT {
      optimizerOptions_.enableReducingExistences =
          originalEnableReducingExistences;
    };

    auto logicalPlan = parseTpchSql(q);
    planVelox(logicalPlan, options, fmt::format("{}/q{}", path, q));
  }
}

} // namespace
} // namespace facebook::axiom::optimizer

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  folly::Init init(&argc, &argv, false);
  return RUN_ALL_TESTS();
}
