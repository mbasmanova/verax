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

#include <gtest/gtest.h>

#include "axiom/optimizer/tests/QueryTestBase.h"
#include "velox/common/base/tests/GTestUtils.h"

namespace facebook::axiom::optimizer::test {
namespace {

using namespace facebook::velox;

// A table that can only be read by key is reachable only through an index
// lookup. These tests cover the planning and lowering of that shape.
class IndexLookupJoinTest : public QueryTestBase,
                            public testing::WithParamInterface<bool> {
 protected:
  void SetUp() override {
    useV2_ = GetParam();
    QueryTestBase::SetUp();
    testConnector_->addTable("t", ROW({"a", "b"}, BIGINT()));
    testConnector_->metadata()->addLookupTable(
        "lookup", ROW({"id", "v"}, BIGINT()), {"id"});
  }
};

// V1 plans the required index lookup; v2 rejects its attempted full scan.
TEST_P(IndexLookupJoinTest, indexLookup) {
  const auto logicalPlan = parseSelect(
      "SELECT * FROM t JOIN lookup ON t.a = lookup.id", kTestConnectorId);

  if (useV2_) {
    VELOX_ASSERT_THROW(
        toSingleNodePlan(logicalPlan),
        "Lookup-only table layout requires lookup keys");
    return;
  }

  AXIOM_ASSERT_PLAN(
      toSingleNodePlan(logicalPlan),
      matchScan("t")
          .indexLookupJoin(
              matchScan("lookup"), core::JoinType::kInner, {"a = id"})
          .build());
}

AXIOM_INSTANTIATE_V1_V2(IndexLookupJoinTest);

} // namespace
} // namespace facebook::axiom::optimizer::test
