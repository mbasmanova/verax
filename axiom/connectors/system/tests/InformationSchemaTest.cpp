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
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "axiom/connectors/ConnectorMetadataRegistry.h"
#include "axiom/connectors/system/SystemConnectorMetadata.h"
#include "axiom/optimizer/tests/QueryTestBase.h"
#include "velox/connectors/ConnectorRegistry.h"
#include "velox/vector/tests/utils/VectorTestBase.h"

namespace facebook::axiom::connector::system {
namespace {

using namespace facebook::velox;

constexpr std::string_view kSystemConnectorId = "system";

/// Queries the information_schema relations of the test catalog. The .sql
/// tests cover the relations over tables; this covers what SQL cannot set up,
/// a view, since CREATE VIEW is not supported.
class InformationSchemaTest : public optimizer::test::QueryTestBase {
 protected:
  void SetUp() override {
    useV2_ = true;
    optimizer::test::QueryTestBase::SetUp();

    systemConnector_ = std::make_shared<SystemConnector>(
        std::string(kSystemConnectorId),
        /*queryInfoProvider=*/nullptr,
        /*sessionPropertiesProvider=*/nullptr);
    velox::connector::ConnectorRegistry::global().insert(
        std::string(kSystemConnectorId), systemConnector_);
    ConnectorMetadataRegistry::global().insert(
        std::string(kSystemConnectorId),
        std::make_shared<SystemConnectorMetadata>(systemConnector_.get()));

    testConnector_->createView(
        SchemaTableName{kDefaultSchema, "nation_names"},
        ROW("n_name", VARCHAR()),
        "SELECT n_name FROM nation");
  }

  void TearDown() override {
    ConnectorMetadataRegistry::global().erase(std::string(kSystemConnectorId));
    velox::connector::ConnectorRegistry::global().erase(
        std::string(kSystemConnectorId));
    systemConnector_.reset();

    optimizer::test::QueryTestBase::TearDown();
  }

  std::vector<RowVectorPtr> run(std::string_view sql) {
    return runVelox(parseSelect(sql, kTestConnectorId)).results;
  }

  std::shared_ptr<SystemConnector> systemConnector_;
};

TEST_F(InformationSchemaTest, view) {
  // A view reports the text it was defined with, and is not a base table.
  auto results =
      run("SELECT table_name, table_type FROM information_schema.tables "
          "WHERE table_schema = 'default' AND table_name = 'nation_names'");
  velox::test::assertEqualVectors(
      makeRowVector({
          makeFlatVector<std::string>({"nation_names"}),
          makeFlatVector<std::string>({"VIEW"}),
      }),
      results.at(0));

  results =
      run("SELECT view_definition, view_owner FROM information_schema.views "
          "WHERE table_schema = 'default' AND table_name = 'nation_names'");
  velox::test::assertEqualVectors(
      makeRowVector({
          makeFlatVector<std::string>({"SELECT n_name FROM nation"}),
          makeNullableFlatVector<std::string>({std::nullopt}),
      }),
      results.at(0));
}

TEST_F(InformationSchemaTest, viewColumns) {
  // A view's columns are described like a table's, but carry no role.
  auto results =
      run("SELECT column_name, data_type, extra_info "
          "FROM information_schema.columns "
          "WHERE table_schema = 'default' AND table_name = 'nation_names'");
  velox::test::assertEqualVectors(
      makeRowVector({
          makeFlatVector<std::string>({"n_name"}),
          makeFlatVector<std::string>({"varchar"}),
          makeNullableFlatVector<std::string>({std::nullopt}),
      }),
      results.at(0));
}

} // namespace
} // namespace facebook::axiom::connector::system

// Queries run here, and Velox execution reaches folly singletons that a
// gtest-provided main leaves uninitialized.
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  folly::Init init(&argc, &argv, false);
  return RUN_ALL_TESTS();
}
