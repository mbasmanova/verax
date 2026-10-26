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

#include "axiom/optimizer/ExprEstimator.h"

#include "axiom/optimizer/EstimateMath.h"
#include "axiom/optimizer/PlanUtils.h"

namespace facebook::axiom::optimizer {

Value ExprEstimator::estimate(ExprCP expr, bool update) {
  const bool isLeaf =
      expr->is(PlanType::kLiteralExpr) || expr->is(PlanType::kColumnExpr);
  if (!update || isLeaf) {
    if (const auto it = constraints_.find(expr->id());
        it != constraints_.end()) {
      return it->second;
    }
  }

  Value result = expr->value();
  if (expr->is(PlanType::kFieldExpr)) {
    const auto* field = expr->as<Field>();
    const Value base = estimate(field->base(), update);
    result = base.field(
        field->field() != nullptr
            ? base.type->asRow().getChildIdx(field->field())
            : field->index());
  } else if (expr->is(PlanType::kCallExpr)) {
    result = estimateCall(*expr->as<Call>(), update);
  }

  result = clampCardinality(result);
  constraints_.insert_or_assign(expr->id(), result);
  return result;
}

Value ExprEstimator::estimateCall(const Call& call, bool update) {
  VELOX_CHECK(
      !call.containsFunction(FunctionSet::kAggregate),
      "Expression cannot contain an aggregate function call: {}",
      call.toString());
  std::vector<Value> args;
  args.reserve(call.args().size());
  for (const auto* arg : call.args()) {
    args.push_back(estimate(arg, update));
  }

  // A row field's statistics are the row's child (see Value::field). The
  // index is an INTEGER literal.
  if (call.name() == SpecialFormCallNames::kDereference) {
    return args[0].field(
        static_cast<uint32_t>(integerValue(&call.literalAt(1))));
  }

  // The largest NDV among the arguments; unknown if any argument's is unknown.
  Value result = call.value();
  std::optional<float> maxCardinality = 1.0f;
  for (const Value& arg : args) {
    maxCardinality = maxOf(maxCardinality, arg.cardinality);
  }
  result.cardinality = maxCardinality;

  // Field i of a constructed row takes argument i's statistics.
  if (call.isRowConstructor()) {
    std::vector<const Value*> fields;
    fields.reserve(args.size());
    for (const Value& arg : args) {
      fields.push_back(&arg);
    }
    result.children = Value::makeChildren(result.type, fields);
  }
  return result;
}

} // namespace facebook::axiom::optimizer
