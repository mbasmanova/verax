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
#include <gtest/gtest.h>
#include "axiom/connectors/tests/TestConnector.h"
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

  void TearDown() override {
    for (const auto& id : connectorIds_) {
      facebook::velox::connector::unregisterConnector(id);
    }
  }

  std::unique_ptr<SqlQueryRunner> makeRunner() {
    auto runner = std::make_unique<SqlQueryRunner>();

    runner->initialize([&](auto&) {
      static int32_t kCounter = 0;

      auto testConnector =
          std::make_shared<facebook::axiom::connector::TestConnector>(
              fmt::format("test{}", kCounter++));
      facebook::velox::connector::registerConnector(testConnector);

      connectorIds_.emplace_back(testConnector->connectorId());

      return std::make_pair(testConnector->connectorId(), std::nullopt);
    });

    return runner;
  }

 private:
  std::vector<std::string> connectorIds_;
};

TEST_F(SqlQueryRunnerTest, basic) {
  auto runner = makeRunner();

  SqlQueryRunner::RunOptions options;
  auto result = runner->run("SELECT 1", options);

  ASSERT_FALSE(result.message.has_value());
  ASSERT_EQ(1, result.results.size());

  test::assertEqualVectors(
      result.results[0], makeRowVector({makeFlatVector<int32_t>({1})}));
}

TEST_F(SqlQueryRunnerTest, multipleInstances) {
  auto a = makeRunner();
  auto b = makeRunner();

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

} // namespace
} // namespace axiom::sql
