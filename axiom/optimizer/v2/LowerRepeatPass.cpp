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

#include "axiom/optimizer/v2/LowerRepeatPass.h"

#include "axiom/optimizer/v2/AppendAll.h"
#include "axiom/optimizer/v2/EstimateProvider.h"
#include "axiom/optimizer/v2/ExprFactory.h"
#include "axiom/optimizer/v2/ExprSimplifier.h"
#include "axiom/optimizer/v2/NodeRewriter.h"
#include "axiom/optimizer/v2/NodeSimplifier.h"
#include "axiom/optimizer/v2/PlanSubstitutions.h"

namespace facebook::axiom::optimizer::v2 {
namespace {

// A Repeat as seen from the side its walks leave from.
struct Walk {
  NodeCP from;
  ExprVector fromKeys;
  // Hop keys of the vertex a hop leaves from and the vertex it reaches, in
  // the direction of the walk.
  ExprVector hopFrom;
  ExprVector hopTo;
  // Null when the walk ends at a row of 'from'.
  NodeCP to;
  ExprVector toKeys;
};

// The FixedPoint's state columns: the carried columns, the current vertex,
// and the hop count, in that order.
struct WalkState {
  ColumnVector columns;
  ColumnVector carried;
  ColumnVector vertex;
  ColumnCP hops;
};

// Appends the columns 'exprs' read that 'columns' does not hold yet.
void appendColumnsRead(const ExprVector& exprs, ColumnVector& columns) {
  PlanObjectSet read;
  read.unionColumns(exprs);
  read.eraseAll(columns);
  read.forEach<Column>([&](ColumnCP column) { columns.push_back(column); });
}

// Returns a new column with an unknown value for each of 'columns'.
ColumnVector unknownValueCopies(const ColumnVector& columns) {
  ColumnVector copies;
  copies.reserve(columns.size());
  for (ColumnCP column : columns) {
    copies.push_back(Column::createWithUnknownValue(column));
  }
  return copies;
}

ExprVector toExprs(const ColumnVector& columns) {
  return ExprVector(columns.begin(), columns.end());
}

class Lowering : public NodeRewriter<NoContext> {
 public:
  Lowering(Builder& builder, velox::core::ExpressionEvaluator& evaluator)
      : NodeRewriter(builder),
        exprs_(builder),
        simplifier_(builder, evaluator),
        nodeSimplifier_(builder, simplifier_) {}

  using NodeRewriter::rewrite;

 protected:
  NodeCP rewriteRepeat(const Repeat* node, NoContext& context) override {
    // Lowers the Repeats inside the inputs first.
    const auto* repeat =
        NodeRewriter::rewriteRepeat(node, context)->as<Repeat>();
    return lower(*repeat, walkOf(*repeat));
  }

 private:
  // Walks from the end when it is present and has fewer estimated rows.
  Walk walkOf(const Repeat& repeat) {
    bool fromEnd{false};
    if (repeat.end() != nullptr) {
      const auto startRows = estimates_.estimate(repeat.start()).cardinality;
      const auto endRows = estimates_.estimate(repeat.end()).cardinality;
      fromEnd =
          startRows.has_value() && endRows.has_value() && *endRows < *startRows;
    }
    if (fromEnd) {
      return {
          .from = repeat.end(),
          .fromKeys = repeat.endKeys(),
          .hopFrom = repeat.hopDestinationKeys(),
          .hopTo = repeat.hopSourceKeys(),
          .to = repeat.start(),
          .toKeys = repeat.startKeys(),
      };
    }
    return {
        .from = repeat.start(),
        .fromKeys = repeat.startKeys(),
        .hopFrom = repeat.hopSourceKeys(),
        .hopTo = repeat.hopDestinationKeys(),
        .to = repeat.end(),
        .toKeys = repeat.endKeys(),
    };
  }

  ExprCP bigint(int64_t value) {
    return builder().makeLiteral(
        velox::Variant(value), toType(velox::BIGINT()));
  }

  // Returns the FixedPoint over 'walk' and the walks it accumulates, filtered
  // and shaped as 'repeat's output.
  NodeCP lower(const Repeat& repeat, const Walk& walk) {
    // The walk state: the columns of 'from' the result reads, the current
    // vertex, and the number of hops so far.
    ColumnVector carried = walk.from->outputsAmong(repeat.outputColumns());
    if (walk.to == nullptr) {
      appendColumnsRead(walk.toKeys, carried);
    }
    const size_t numCarried = carried.size();
    const size_t numKeys = walk.fromKeys.size();

    ExprVector anchorExprs = toExprs(carried);
    ColumnVector anchorColumns = carried;
    for (ExprCP key : walk.fromKeys) {
      anchorExprs.push_back(key);
      anchorColumns.push_back(Column::create("walk_vertex", key->value()));
    }
    anchorExprs.push_back(bigint(0));
    anchorColumns.push_back(
        Column::create("walk_hops", Value(toType(velox::BIGINT()))));
    NodeCP anchor = builder().make<Project>(
        {walk.from, std::move(anchorExprs), anchorColumns});

    WalkState state;
    state.columns = unknownValueCopies(anchorColumns);
    const auto& stateColumns = state.columns;
    state.carried.assign(
        stateColumns.begin(), stateColumns.begin() + numCarried);
    state.vertex.assign(
        stateColumns.begin() + numCarried,
        stateColumns.begin() + numCarried + numKeys);
    state.hops = stateColumns.back();

    const Name name = queryCtx()->newName("walk");
    NodeCP step = makeStep(repeat, walk, name, state, anchorColumns);
    NodeCP fixedPoint = builder().make<FixedPoint>({
        .anchor = anchor,
        .step = step,
        .convergence =
            nodeSimplifier_.makeEmptyDeltaConvergence(name, stateColumns),
        .name = name,
        .outputColumns = stateColumns,
        .sourceColumns = anchorColumns,
        // The step adds no rows once every walk has 'maxHops' hops, which
        // the loop sees one iteration later.
        .maxIterations = repeat.maxHops() + 1,
        .recursiveNumDrivers = std::nullopt,
    });

    ExprVector predicates{
        exprs_.makeGreaterThanOrEqual(state.hops, bigint(repeat.minHops()))};
    PlanSubstitutions toState;
    for (size_t i = 0; i < numCarried; ++i) {
      toState.add(carried[i], state.carried[i]);
    }
    if (walk.to == nullptr) {
      for (size_t i = 0; i < numKeys; ++i) {
        predicates.push_back(exprs_.makeEq(
            state.vertex[i], toState.apply(walk.toKeys[i], exprs_)));
      }
    }
    NodeCP walks = builder().make<Filter>({fixedPoint, std::move(predicates)});

    if (walk.to != nullptr) {
      ColumnVector joined = state.carried;
      appendAll(joined, walk.to->outputsAmong(repeat.outputColumns()));
      walks = builder().make<Join>({
          .left = walks,
          .right = walk.to,
          .joinType = velox::core::JoinType::kInner,
          .leftKeys = toExprs(state.vertex),
          .rightKeys = walk.toKeys,
          .outputColumns = std::move(joined),
      });
    }

    ExprVector outputExprs;
    outputExprs.reserve(repeat.outputColumns().size());
    for (ColumnCP column : repeat.outputColumns()) {
      outputExprs.push_back(toState.apply(column, exprs_));
    }
    return builder().make<Project>(
        {walks, std::move(outputExprs), repeat.outputColumns()});
  }

  // Extends the latest walks that have fewer than 'maxHops' hops by one hop.
  NodeCP makeStep(
      const Repeat& repeat,
      const Walk& walk,
      Name name,
      const WalkState& state,
      const ColumnVector& anchorColumns) {
    NodeCP latest = builder().make<WorkingTable>({
        .name = name,
        .outputColumns = state.columns,
        .readMode = WorkingTableReadMode::kLatestDelta,
    });
    NodeCP extensible = builder().make<Filter>(
        {latest, {exprs_.makeLessThan(state.hops, bigint(repeat.maxHops()))}});

    ColumnVector joined = state.columns;
    appendColumnsRead(walk.hopTo, joined);
    NodeCP extended = builder().make<Join>({
        .left = extensible,
        .right = repeat.hop(),
        .joinType = velox::core::JoinType::kInner,
        .leftKeys = toExprs(state.vertex),
        .rightKeys = walk.hopFrom,
        .outputColumns = std::move(joined),
    });

    ExprVector stepExprs = toExprs(state.carried);
    stepExprs.insert(stepExprs.end(), walk.hopTo.begin(), walk.hopTo.end());
    stepExprs.push_back(exprs_.makeBigintAddition(state.hops, bigint(1)));
    return builder().make<Project>(
        {extended, std::move(stepExprs), unknownValueCopies(anchorColumns)});
  }

  ExprFactory exprs_;
  ExprSimplifier simplifier_;
  NodeSimplifier nodeSimplifier_;
  EstimateProvider estimates_;
};

} // namespace

NodeCP LowerRepeatPass::run(
    NodeCP root,
    Builder& builder,
    velox::core::ExpressionEvaluator& evaluator) {
  return Lowering(builder, evaluator).rewrite(root);
}

} // namespace facebook::axiom::optimizer::v2
