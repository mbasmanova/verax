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
#pragma once

#include <gtest/gtest.h>
#include "velox/core/ITypedExpr.h"
#include "velox/parse/IExpr.h"

namespace facebook::velox::core {

/// Structurally compares a typed expression tree (from a Velox plan) against
/// an untyped expression tree. Sets gtest failures with descriptive messages
/// on mismatch.
class ExprMatcher {
 public:
  /// Function name used as a wildcard in expected expressions. A CallExpr
  /// with this name and zero inputs matches any typed subtree.
  static constexpr std::string_view kWildcard = "any";

  /// Returns true if the trees match. On mismatch, sets gtest failures
  /// with SCOPED_TRACE context showing the path through the tree.
  static bool match(const TypedExprPtr& actual, const core::ExprPtr& expected);
};

} // namespace facebook::velox::core
