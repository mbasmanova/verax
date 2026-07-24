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

#include <memory>
#include <vector>

#include "axiom/connectors/ConnectorMetadata.h"
#include "axiom/optimizer/QueryGraph.h"
#include "velox/core/PlanFragment.h"
#include "velox/core/QueryCtx.h"
#include "velox/type/Variant.h"

namespace facebook::axiom::optimizer {

// Shared building blocks for constant-folding a global aggregation over a base
// table's discrete-predicate (e.g. partition) columns. Used by both the v1
// (DerivedTable) and v2 (tree-IR) folds, which differ only in the enclosing IR;
// the connector-facing types (Column, BaseTable, TableLayout) are shared.

/// A table layout whose discrete-predicate columns cover a set of columns,
/// paired with the matching connector columns. 'layout' is nullptr if no layout
/// qualifies.
struct DiscreteLayout {
  const connector::TableLayout* layout{nullptr};
  std::vector<const connector::Column*> connectorColumns;
};

/// Finds the first layout of 'baseTable' whose discrete-predicate columns cover
/// every column in 'columns'.
DiscreteLayout findDiscreteLayout(
    const ColumnVector& columns,
    const BaseTable& baseTable);

/// Drains 'discretePredicates' into a flat list of row Variants.
std::vector<velox::Variant> toValues(
    connector::DiscretePredicates& discretePredicates);

/// Executes a single-node Velox plan to compute a constant, using the query's
/// velox QueryCtx directly (the plan runs serially in the caller's thread).
class ConstantPlanRunner {
 public:
  explicit ConstantPlanRunner(std::shared_ptr<velox::core::QueryCtx> queryCtx)
      : queryCtx_{std::move(queryCtx)} {}

  /// Runs 'fragment' serially in the caller's thread (velox Task in kSerial
  /// mode) and returns the single value of its result. 'fragment' must have no
  /// split-driven sources and must produce a single column and at most one row;
  /// no row yields a null of the column's type (a scalar over empty input).
  velox::Variant run(const velox::core::PlanFragment& fragment) const;

 private:
  const std::shared_ptr<velox::core::QueryCtx> queryCtx_;
};

} // namespace facebook::axiom::optimizer
