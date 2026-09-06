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

namespace facebook::axiom::optimizer {
namespace {

// The hidden columns addressing a row physically: $row_number, $row_group_id,
// and $row_id, which repeats both. A query names one explicitly; SELECT *
// leaves them out. File names carry generated ids, so the assertions relate
// the columns to each other rather than to a literal.
//
// TODO: Cover a filter on $row_number and on $row_id. Velox's makeScanSpec
// projects both columns but rejects a subfield filter on either, so a
// predicate the optimizer pushes into the scan fails there.
class HiveRowIdentityTest : public test::HiveQueriesTestBase {
 protected:
  static void SetUpTestCase() {
    test::HiveQueriesTestBase::SetUpTestCase();
    createTpchTables({velox::tpch::Table::TBL_REGION});
  }

  int64_t runCount(std::string_view fromClause) {
    const auto sql = fmt::format("SELECT count(*) {}", fromClause);
    SCOPED_TRACE(sql);
    return runVelox(parseSelect(sql)).getOnlyResult<int64_t>();
  }
};

TEST_F(HiveRowIdentityTest, rowIdentity) {
  // region is written as a single file of 5 rows, so the positions run 0..4
  // and every row shares one row group.
  checkSameSingleNode(
      parseSelect(R"(SELECT "$row_number" FROM region)"),
      {makeRowVector({makeFlatVector<int64_t>({0, 1, 2, 3, 4})})});

  auto files = runVelox(
      parseSelect(R"(SELECT DISTINCT "$path", "$row_group_id" FROM region)"));
  ASSERT_EQ(1, files.countRows());
  const auto& file = *files.results.at(0);
  const auto path = file.childAt(0)->variantAt(0).value<std::string>();
  const auto rowGroupId = file.childAt(1)->variantAt(0).value<std::string>();
  EXPECT_TRUE(path.ends_with("/" + rowGroupId)) << path << " vs " << rowGroupId;

  EXPECT_EQ(0, runCount(R"(FROM region
          WHERE "$row_number" <> "$row_id".rownumber
             OR "$row_group_id" <> "$row_id".rowgroupid)"));
}

} // namespace
} // namespace facebook::axiom::optimizer
