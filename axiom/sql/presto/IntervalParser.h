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

#include "axiom/logical_plan/ExprApi.h"
#include "axiom/sql/presto/ast/AstNodesAll.h"

namespace axiom::sql::presto {

/// Parses Presto interval literals into typed constants.
/// For example, IntervalParser::parse(literal) converts INTERVAL '.001' SECOND
/// to an INTERVAL_DAY_TIME constant containing one millisecond.
/// See docs/IntervalParser.md for supported syntax and numeric limits.
class IntervalParser {
 public:
  /// Returns a year-month or day-time constant, including the literal's sign.
  /// Reports invalid values and qualifiers as Presto semantic errors.
  static facebook::axiom::logical_plan::ExprApi parse(
      const IntervalLiteral& literal);
};

} // namespace axiom::sql::presto
