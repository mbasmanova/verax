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
#include "axiom/logical_plan/PlanPrinter.h"
#include "axiom/optimizer/tests/ParquetTpchTest.h"

namespace lp = facebook::velox::logical_plan;

namespace facebook::velox::optimizer::test {

// static
std::shared_ptr<exec::test::TempDirectoryPath>
    HiveQueriesTestBase::tempDirectory_ = nullptr;

// static
void HiveQueriesTestBase::SetUpTestCase() {
  tempDirectory_ = exec::test::TempDirectoryPath::create();
  test::ParquetTpchTest::createTables(tempDirectory_->getPath());

  LocalRunnerTestBase::testDataPath_ = tempDirectory_->getPath();
  LocalRunnerTestBase::localFileFormat_ = "parquet";
  LocalRunnerTestBase::SetUpTestCase();
}

// static
void HiveQueriesTestBase::TearDownTestCase() {
  LocalRunnerTestBase::TearDownTestCase();
  tempDirectory_.reset();
}

namespace {
std::unique_ptr<DuckParser> makeDuckParser(velox::memory::MemoryPool* pool) {
  auto parser =
      std::make_unique<DuckParser>(exec::test::kHiveConnectorId, pool);

  auto registerTable = [&](const std::string& name) {
    auto table = connector::getConnector(exec::test::kHiveConnectorId)
                     ->metadata()
                     ->findTable(name);
    parser->registerTable(name, table->rowType());
  };

  registerTable("region");
  registerTable("nation");
  registerTable("lineitem");
  registerTable("orders");
  registerTable("customer");
  registerTable("supplier");
  registerTable("part");
  registerTable("partsupp");

  return parser;
}
} // namespace

void HiveQueriesTestBase::SetUp() {
  test::QueryTestBase::SetUp();
  test::ParquetTpchTest::registerTpchConnector(kTpchConnectorId);
  duckParser_ = makeDuckParser(pool());
  prestoParser_ = std::make_unique<PrestoParser>(kTpchConnectorId, pool());
}

void HiveQueriesTestBase::TearDown() {
  connector::unregisterConnector(kTpchConnectorId);
  test::QueryTestBase::TearDown();
}

RowTypePtr HiveQueriesTestBase::getSchema(const std::string& tableName) {
  return connector::getConnector(exec::test::kHiveConnectorId)
      ->metadata()
      ->findTable(tableName)
      ->rowType();
}

void HiveQueriesTestBase::checkResults(
    const std::string& sql,
    const core::PlanNodePtr& referencePlan) {
  SCOPED_TRACE(sql);
  VELOX_CHECK_NOT_NULL(referencePlan);

  auto statement = prestoParser_->parse(sql);

  ASSERT_TRUE(statement->isSelect());
  auto logicalPlan = statement->asUnchecked<test::SelectStatement>()->plan();

  LOG(ERROR) << lp::PlanPrinter::toText(*logicalPlan);

  auto referenceResults = runVelox(referencePlan);

  // Distributed.
  {
    auto plan = planVelox(logicalPlan, {.numWorkers = 4, .numDrivers = 4});
    LOG(ERROR) << plan.plan->toString();
    checkResults(plan, referenceResults);
  }

  // Single node.
  for (auto numDrivers : {1, 4}) {
    SCOPED_TRACE(fmt::format("numWorkers: 1, numDrivers: {}", numDrivers));
    auto plan =
        planVelox(logicalPlan, {.numWorkers = 1, .numDrivers = numDrivers});
    checkResults(plan, referenceResults);
  }
}

void HiveQueriesTestBase::checkResults(
    const lp::LogicalPlanNodePtr& logicalPlan,
    const core::PlanNodePtr& referencePlan) {
  VELOX_CHECK_NOT_NULL(logicalPlan);
  VELOX_CHECK_NOT_NULL(referencePlan);

  auto referenceResults = runVelox(referencePlan);

  // Distributed.
  {
    auto plan = planVelox(logicalPlan, {.numWorkers = 4, .numDrivers = 4});
    checkResults(plan, referenceResults);
  }

  // Single node.
  for (auto numDrivers : {1, 4}) {
    SCOPED_TRACE(fmt::format("numWorkers: 1, numDrivers: {}", numDrivers));
    auto plan =
        planVelox(logicalPlan, {.numWorkers = 1, .numDrivers = numDrivers});
    checkResults(plan, referenceResults);
  }
}

void HiveQueriesTestBase::checkResults(
    const PlanAndStats& plan,
    const test::TestResult& expected) {
  auto results = runFragmentedPlan(plan);
  exec::test::assertEqualResults(expected.results, results.results);
}

void HiveQueriesTestBase::checkSingleNodePlan(
    const PlanAndStats& plan,
    const std::shared_ptr<core::PlanMatcher>& matcher) {
  SCOPED_TRACE(plan.plan->toString());

  const auto& fragments = plan.plan->fragments();
  ASSERT_EQ(1, fragments.size());

  ASSERT_TRUE(matcher->match(fragments.at(0).fragment.planNode));
}

} // namespace facebook::velox::optimizer::test
