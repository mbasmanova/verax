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
#include "axiom/optimizer/v2/NodeRewriter.h"
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

// The walks' columns: the carried columns, the current vertex, the values of
// the hop columns the result reads, and the hop count, in that order. Walks of
// at most one hop have no hop count; walks that loop read no hop columns.
struct WalkState {
  ColumnVector columns;
  ColumnVector carried;
  ColumnVector vertex;
  ColumnVector hopValues;
  ColumnCP hops{nullptr};

  static WalkState of(
      ColumnVector columns,
      size_t numCarried,
      size_t numKeys,
      size_t numHopValues) {
    WalkState state;
    auto it = columns.begin();
    state.carried.assign(it, it + numCarried);
    it += numCarried;
    state.vertex.assign(it, it + numKeys);
    it += numKeys;
    state.hopValues.assign(it, it + numHopValues);
    it += numHopValues;
    if (it != columns.end()) {
      state.hops = *it;
    }
    state.columns = std::move(columns);
    return state;
  }
};

// Appends the columns 'exprs' read that 'columns' does not hold yet.
void appendColumnsRead(const ExprVector& exprs, ColumnVector& columns) {
  PlanObjectSet read;
  read.unionColumns(exprs);
  read.eraseAll(columns);
  read.forEach<Column>([&](ColumnCP column) { columns.push_back(column); });
}

// Returns a new column with an unknown value for each of 'columns'.
ColumnVector createWithUnknownValues(const ColumnVector& columns) {
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
  explicit Lowering(Builder& builder)
      : NodeRewriter(builder), exprs_(builder) {}

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
    // The walks carry the columns of 'from' the result reads, the current
    // vertex, the hop columns the result reads, and, when they loop, the
    // number of hops so far.
    ColumnVector carried =
        walk.from->outputsAmong(repeat.effectiveSourceColumns());
    if (walk.to == nullptr) {
      appendColumnsRead(walk.toKeys, carried);
    }
    const ColumnVector hopColumns =
        repeat.hop()->outputsAmong(repeat.effectiveSourceColumns());
    const size_t numKeys = walk.fromKeys.size();
    const bool loops = repeat.maxHops() > 1;
    NodeCP anchor = makeAnchor(walk, carried, hopColumns, loops);
    const auto& anchorColumns = anchor->outputColumns();

    WalkState state;
    NodeCP walks{nullptr};
    if (loops) {
      state = WalkState::of(
          createWithUnknownValues(anchorColumns),
          carried.size(),
          numKeys,
          /*numHopValues=*/0);
      walks = makeFixedPoint(repeat, walk, anchor, anchorColumns, state);
    } else {
      auto [node, columns] = makeShortWalks(
          repeat, walk, anchor, anchorColumns, carried, hopColumns);
      walks = node;
      state = WalkState::of(
          std::move(columns), carried.size(), numKeys, hopColumns.size());
    }
    return makeResult(repeat, walk, walks, state, carried, hopColumns);
  }

  // Returns the walks of zero hops: 'carried', the vertex 'from' leaves from,
  // NULL for each of 'hopColumns', and, when the walks loop, a hop count of 0.
  NodeCP makeAnchor(
      const Walk& walk,
      const ColumnVector& carried,
      const ColumnVector& hopColumns,
      bool loops) {
    ExprVector exprs = toExprs(carried);
    ColumnVector columns = carried;
    for (ExprCP key : walk.fromKeys) {
      exprs.push_back(key);
      columns.push_back(Column::create("walk_vertex", key->value()));
    }
    for (ColumnCP column : hopColumns) {
      exprs.push_back(builder().makeNull(column->value().type));
      columns.push_back(Column::create("walk_hop", column->value()));
    }
    if (loops) {
      exprs.push_back(bigint(0));
      columns.push_back(
          Column::create("walk_hops", Value(toType(velox::BIGINT()))));
    }
    return builder().make<Project>(
        {walk.from, std::move(exprs), std::move(columns)});
  }

  // Returns 'walks' with at least 'minHops' hops, joined with 'to' or ending
  // at 'from' when 'to' is null, shaped as 'repeat's output. 'carried' are the
  // columns of 'from' and 'hopColumns' those of the hop that 'state' carries.
  NodeCP makeResult(
      const Repeat& repeat,
      const Walk& walk,
      NodeCP walks,
      const WalkState& state,
      const ColumnVector& carried,
      const ColumnVector& hopColumns) {
    ExprVector predicates;
    if (repeat.minHops() > 0) {
      predicates.push_back(
          exprs_.makeGreaterThanOrEqual(state.hops, bigint(repeat.minHops())));
    }
    PlanSubstitutions toState;
    for (size_t i = 0; i < carried.size(); ++i) {
      toState.add(carried[i], state.carried[i]);
    }
    for (size_t i = 0; i < hopColumns.size(); ++i) {
      toState.add(hopColumns[i], state.hopValues[i]);
    }
    if (walk.to == nullptr) {
      for (size_t i = 0; i < state.vertex.size(); ++i) {
        predicates.push_back(exprs_.makeEq(
            state.vertex[i], toState.apply(walk.toKeys[i], exprs_)));
      }
    }
    if (!predicates.empty()) {
      walks = builder().make<Filter>({walks, std::move(predicates)});
    }

    if (walk.to != nullptr) {
      ColumnVector joined = state.carried;
      appendAll(joined, state.hopValues);
      appendAll(joined, walk.to->outputsAmong(repeat.effectiveSourceColumns()));
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
    for (ColumnCP source : repeat.effectiveSourceColumns()) {
      outputExprs.push_back(toState.apply(source, exprs_));
    }
    return builder().make<Project>(
        {walks, std::move(outputExprs), repeat.outputColumns()});
  }

  // Returns the FixedPoint that accumulates the walks from 'anchor' into
  // 'state'.
  NodeCP makeFixedPoint(
      const Repeat& repeat,
      const Walk& walk,
      NodeCP anchor,
      const ColumnVector& anchorColumns,
      const WalkState& state) {
    const Name name = queryCtx()->newName("walk");
    return builder().make<FixedPoint>({
        .anchor = anchor,
        .step = makeStep(repeat, walk, name, state, anchorColumns),
        .name = name,
        .outputColumns = state.columns,
        .sourceColumns = anchorColumns,
        // The step adds no rows once every walk has 'maxHops' hops, which
        // the loop sees one iteration later.
        .maxIterations = repeat.maxHops() + 1,
        .recursiveNumDrivers = std::nullopt,
    });
  }

  // Returns the walks of at most one hop and their columns: 'anchor' for zero
  // hops, and 'from' joined with the hop for one. 'minHops' is 0: one hop
  // exactly is a join.
  std::pair<NodeCP, ColumnVector> makeShortWalks(
      const Repeat& repeat,
      const Walk& walk,
      NodeCP anchor,
      const ColumnVector& anchorColumns,
      const ColumnVector& carried,
      const ColumnVector& hopColumns) {
    NodeVector legs{anchor};
    QGVector<ColumnVector> legColumns{anchorColumns};
    if (repeat.maxHops() == 1) {
      NodeCP hopped = extendByOneHop(
          repeat,
          walk,
          walk.from,
          walk.fromKeys,
          carried,
          hopColumns,
          /*hops=*/nullptr,
          anchorColumns);
      legs.push_back(hopped);
      legColumns.push_back(hopped->outputColumns());
    }
    if (legs.size() == 1) {
      return {legs.front(), std::move(legColumns.front())};
    }
    ColumnVector columns = createWithUnknownValues(anchorColumns);
    return {
        builder().make<UnionAll>(
            {std::move(legs), std::move(legColumns), columns}),
        columns};
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
    return extendByOneHop(
        repeat,
        walk,
        extensible,
        toExprs(state.vertex),
        state.carried,
        /*hopColumns=*/{},
        state.hops,
        anchorColumns);
  }

  // Joins 'walks' with the hop on 'vertex' and the hop's source, keeping all of
  // the walks' columns so the join's input needs no projection. Returns the
  // walks' 'carried' columns, the hop's destination as the current vertex,
  // 'hopColumns', and 'hops' plus one when set, as new columns named like
  // 'anchorColumns'.
  NodeCP extendByOneHop(
      const Repeat& repeat,
      const Walk& walk,
      NodeCP walks,
      ExprVector vertex,
      const ColumnVector& carried,
      const ColumnVector& hopColumns,
      ColumnCP hops,
      const ColumnVector& anchorColumns) {
    ColumnVector joined = walks->outputColumns();
    appendColumnsRead(walk.hopTo, joined);
    appendColumnsRead(toExprs(hopColumns), joined);
    NodeCP extended = builder().make<Join>({
        .left = walks,
        .right = repeat.hop(),
        .joinType = velox::core::JoinType::kInner,
        .leftKeys = std::move(vertex),
        .rightKeys = walk.hopFrom,
        .outputColumns = std::move(joined),
    });

    ExprVector exprs = toExprs(carried);
    appendAll(exprs, walk.hopTo);
    appendAll(exprs, toExprs(hopColumns));
    if (hops != nullptr) {
      exprs.push_back(exprs_.makeBigintIncrement(hops));
    }
    return builder().make<Project>(
        {extended, std::move(exprs), createWithUnknownValues(anchorColumns)});
  }

  ExprFactory exprs_;
  EstimateProvider estimates_;
};

} // namespace

NodeCP LowerRepeatPass::run(NodeCP root, Builder& builder) {
  return Lowering(builder).rewrite(root);
}

} // namespace facebook::axiom::optimizer::v2
