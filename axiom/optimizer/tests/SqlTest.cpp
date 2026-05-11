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

#include <folly/FileUtil.h>
#include <folly/init/Init.h>
#include <gtest/gtest.h>
#include <filesystem>
#include "axiom/optimizer/tests/SqlFile.h"
#include "axiom/optimizer/tests/SqlTestBase.h"
#include "axiom/optimizer/tests/TestDataPath.h"

namespace facebook::axiom::optimizer::test {
namespace {

// Test fixture that runs a single QueryEntry through SqlTestBase. Setup
// statements come from the .sql file's setup_file: / setup directives
// and are run against the per-test connector before TestBody.
class SqlTest : public SqlTestBase {
 public:
  SqlTest(QueryEntry entry, std::vector<std::string> setupStatements)
      : entry_(std::move(entry)),
        setupStatements_(std::move(setupStatements)) {}

 protected:
  void SetUp() override {
    SqlTestBase::SetUp();
    for (const auto& statement : setupStatements_) {
      runSetupStatement(statement);
    }
  }

  void TestBody() override {
    try {
      switch (entry_.type) {
        case QueryEntry::Type::kResults:
          assertResults(entry_.sql, entry_.checkColumnNames, entry_.duckDbSql);
          break;
        case QueryEntry::Type::kOrdered:
          assertOrderedResults(
              entry_.sql, entry_.checkColumnNames, entry_.duckDbSql);
          break;
        case QueryEntry::Type::kCount:
          assertResultCount(entry_.sql, entry_.expectedCount);
          break;
        case QueryEntry::Type::kError:
          assertFailure(entry_.sql, entry_.expectedError);
          break;
      }
    } catch (const std::exception& e) {
      FAIL() << "Unexpected exception: " << e.what();
    }
  }

 private:
  QueryEntry entry_;
  std::vector<std::string> setupStatements_;
};

// Registers all queries from a .sql file as individual gtest tests under
// fixture 'SqlTest'. Each registered test instance receives both its own
// query entry and the file's setup statements.
void registerQueryFile(const std::string& fileName) {
  auto path = getTestFilePath(fmt::format("sql/{}", fileName));

  std::string content;
  VELOX_CHECK(
      folly::readFile(path.c_str(), content), "Failed to read: {}", path);

  auto baseDir = std::filesystem::path(path).parent_path().string();
  auto file = SqlFile::parse(content, baseDir);

  // Strip the .sql extension to use as a test name prefix.
  auto baseName = fileName.substr(0, fileName.rfind('.'));

  for (const auto& entry : file.entries) {
    auto testName = fmt::format("{}_l{}", baseName, entry.lineNumber);
    auto capturedEntry = entry;
    auto capturedSetup = file.setupStatements;
    testing::RegisterTest(
        "SqlTest",
        testName.c_str(),
        /*type_param=*/nullptr,
        /*value_param=*/nullptr,
        path.c_str(),
        entry.lineNumber,
        [capturedEntry = std::move(capturedEntry),
         capturedSetup = std::move(capturedSetup)]() -> SqlTest* {
          return new SqlTest(capturedEntry, capturedSetup);
        });
  }
}

} // namespace
} // namespace facebook::axiom::optimizer::test

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  folly::Init init(&argc, &argv, false);

  using namespace facebook::axiom::optimizer::test;

  registerQueryFile("basic.sql");
  registerQueryFile("join.sql");
  registerQueryFile("subquery.sql");
  registerQueryFile("window.sql");
  registerQueryFile("set.sql");
  registerQueryFile("limit.sql");
  registerQueryFile("aggregation.sql");
  registerQueryFile("subfield.sql");
  registerQueryFile("nullif.sql");
  registerQueryFile("coercion.sql");
  registerQueryFile("distinctAggregation.sql");
  registerQueryFile("unionAll.sql");
  registerQueryFile("unionAllFlatten.sql");

  return RUN_ALL_TESTS();
}
