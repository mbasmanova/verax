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

#include "axiom/optimizer/v2/PrecomputeProjectionsPass.h"

#include "axiom/optimizer/v2/PrecomputeProjections.h"

#include "axiom/optimizer/v2/NodeRewriter.h"

namespace facebook::axiom::optimizer::v2 {
namespace {

// Lifts compound expressions at restricted operator positions into a Project
// below the consumer.
class Rewriter : public NodeRewriter<> {
 public:
  using NodeRewriter::NodeRewriter;

 protected:
  NodeCP rewriteUnionAll(const UnionAll* unionAll, NoContext& context) override;
  NodeCP rewriteFixedPoint(const FixedPoint* fixedPoint, NoContext& context)
      override;
  NodeCP rewriteApply(const Apply* /*apply*/, NoContext& /*context*/) override {
    VELOX_UNREACHABLE(
        "Apply must be removed by decorrelate before PrecomputeProjections");
  }
};

NodeCP Rewriter::rewriteFixedPoint(
    const FixedPoint* fixedPoint,
    NoContext& context) {
  auto restoreSchema = [&](NodeCP branch, const ColumnVector& columns) {
    if (branch->outputColumns() == columns) {
      return branch;
    }
    return PrecomputeProjections::makeProject(
        branch, ExprVector{columns.begin(), columns.end()}, columns, builder());
  };

  NodeCP anchor = restoreSchema(
      rewrite(fixedPoint->anchor(), context), fixedPoint->outputColumns());
  NodeCP step = restoreSchema(
      rewrite(fixedPoint->step(), context),
      fixedPoint->step()->outputColumns());
  NodeCP convergence = restoreSchema(
      rewrite(fixedPoint->convergence(), context),
      fixedPoint->convergence()->outputColumns());
  if (anchor == fixedPoint->anchor() && step == fixedPoint->step() &&
      convergence == fixedPoint->convergence()) {
    return fixedPoint;
  }
  return builder().make<FixedPoint>({
      .anchor = anchor,
      .step = step,
      .convergence = convergence,
      .name = fixedPoint->name(),
      .outputColumns = fixedPoint->outputColumns(),
      .maxIterations = fixedPoint->maxIterations(),
      .recursiveNumDrivers = fixedPoint->recursiveNumDrivers(),
  });
}

NodeCP Rewriter::rewriteUnionAll(const UnionAll* unionAll, NoContext& context) {
  // Velox's LocalPartition requires every source to share one output RowType,
  // so each leg must produce the union's output columns (same names, same
  // order). Emit that aligning projection here -- like the pre-projections for
  // aggregates/joins -- rather than at emit, folding it into a deterministic
  // child Project so a coercion leg (e.g. VALUES needing a cast) does not stack
  // two Projects. For a leg already isolated behind a remote exchange, the
  // rename lands on the exchange's consumer side; moving it below the exchange
  // is future work.
  const ColumnVector& outputColumns = unionAll->outputColumns();
  NodeVector newInputs;
  newInputs.reserve(unionAll->inputs().size());
  QGVector<ColumnVector> newLegColumns;
  newLegColumns.reserve(unionAll->inputs().size());
  bool changed = false;
  for (size_t i = 0; i < unionAll->inputs().size(); ++i) {
    NodeCP input = rewrite(unionAll->inputs()[i], context);
    const ColumnVector& legCols = unionAll->legColumns()[i];

    // Already aligned: the leg produces exactly legCols in order and each
    // carries the union's output name (so its type matches too).
    bool aligned = input->outputColumns().size() == legCols.size();
    for (size_t k = 0; aligned && k < legCols.size(); ++k) {
      aligned = input->outputColumns()[k] == legCols[k] &&
          legCols[k]->outputName() == outputColumns[k]->outputName();
    }
    if (aligned) {
      changed |= input != unionAll->inputs()[i];
      newInputs.push_back(input);
      newLegColumns.push_back(legCols);
      continue;
    }

    // Rename legCols to fresh columns carrying the union's output names.
    ExprVector exprs(legCols.begin(), legCols.end());
    ColumnVector projectColumns;
    projectColumns.reserve(outputColumns.size());
    for (ColumnCP column : outputColumns) {
      projectColumns.push_back(
          Column::createForSymbol(
              toName(column->outputName()), column->value()));
    }
    newInputs.push_back(
        PrecomputeProjections::makeProject(
            input, std::move(exprs), projectColumns, builder()));
    newLegColumns.push_back(std::move(projectColumns));
    changed = true;
  }
  if (!changed) {
    return unionAll;
  }
  return builder().make<UnionAll>(
      {std::move(newInputs), std::move(newLegColumns), outputColumns});
}

} // namespace

NodeCP PrecomputeProjectionsPass::run(NodeCP node, Builder& builder) {
  return Rewriter{builder}.rewrite(node);
}

} // namespace facebook::axiom::optimizer::v2
