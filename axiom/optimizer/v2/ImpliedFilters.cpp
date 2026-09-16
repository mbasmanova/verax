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

#include "axiom/optimizer/v2/ImpliedFilters.h"

namespace facebook::axiom::optimizer::v2 {
namespace {

// Combines expressions into a balanced tree to bound recursive consumers to
// logarithmic depth.
template <typename Combine>
ExprCP combineBalanced(ExprVector expressions, Combine combine) {
  VELOX_CHECK(!expressions.empty());
  while (expressions.size() > 1) {
    size_t outputIndex{0};
    for (size_t i = 0; i + 1 < expressions.size(); i += 2) {
      expressions[outputIndex++] = combine(expressions[i], expressions[i + 1]);
    }
    if (expressions.size() % 2 != 0) {
      expressions[outputIndex++] = expressions.back();
    }
    expressions.resize(outputIndex);
  }
  return expressions.front();
}

template <typename Group>
struct GroupedProjection {
  Group group;
  ExprCP filter;
  bool matchesSource;
};

// Projects a boolean expression onto caller-defined groups. An AND combines
// every constraint available for a group. An OR retains a group only when
// every branch constrains it. Each node returns at most one projection per
// group, keeping construction linear in expression size times group count.
template <typename Group, typename GroupFor>
std::vector<GroupedProjection<Group>> projectLogicalExpression(
    ExprCP expression,
    ExprFactory& factory,
    const GroupFor& groupFor) {
  const auto* call =
      expression->is(PlanType::kCallExpr) ? expression->as<Call>() : nullptr;
  const bool isAnd =
      call != nullptr && call->name() == SpecialFormCallNames::kAnd;
  const bool isOr =
      call != nullptr && call->name() == SpecialFormCallNames::kOr;
  if (!isAnd && !isOr) {
    const auto group = groupFor(expression->columns());
    if (!group.has_value()) {
      return {};
    }
    return {{*group, expression, true}};
  }

  struct Accumulator {
    Group group;
    ExprVector filters;
    size_t numMatchedOperands{0};
    bool childrenMatchSource{true};
  };

  const ExprVector operands = isAnd ? ExprFactory::flattenAnd(expression)
                                    : ExprFactory::flattenOr(expression);
  std::vector<Accumulator> accumulators;
  folly::F14FastMap<Group, size_t> accumulatorByGroup;
  for (size_t operandIndex = 0; operandIndex < operands.size();
       ++operandIndex) {
    for (const auto& projection : projectLogicalExpression<Group>(
             operands[operandIndex], factory, groupFor)) {
      auto it = accumulatorByGroup.find(projection.group);
      if (it == accumulatorByGroup.end()) {
        if (isOr && operandIndex > 0) {
          continue;
        }
        it = accumulatorByGroup.emplace(projection.group, accumulators.size())
                 .first;
        accumulators.push_back({projection.group});
      }
      auto& accumulator = accumulators[it->second];
      accumulator.filters.push_back(projection.filter);
      ++accumulator.numMatchedOperands;
      accumulator.childrenMatchSource &= projection.matchesSource;
    }
  }

  std::vector<GroupedProjection<Group>> result;
  result.reserve(accumulators.size());
  for (auto& accumulator : accumulators) {
    if (isOr && accumulator.numMatchedOperands != operands.size()) {
      continue;
    }
    const bool matchesSource =
        accumulator.numMatchedOperands == operands.size() &&
        accumulator.childrenMatchSource;
    const ExprCP filter = isAnd
        ? combineBalanced(
              std::move(accumulator.filters),
              [&](ExprCP lhs, ExprCP rhs) { return factory.makeAnd(lhs, rhs); })
        : combineBalanced(
              std::move(accumulator.filters),
              [&](ExprCP lhs, ExprCP rhs) { return factory.makeOr(lhs, rhs); });
    result.push_back({accumulator.group, filter, matchesSource});
  }
  return result;
}

// Projects an OR onto caller-defined groups. A group produces a necessary
// filter only when every disjunct constrains that group.
template <typename Group, typename GroupFor>
std::vector<std::pair<Group, ExprCP>> deriveGroupedFiltersFromOr(
    ExprCP orExpr,
    ExprFactory& factory,
    GroupFor groupFor) {
  if (!orExpr->is(PlanType::kCallExpr) ||
      orExpr->as<Call>()->name() != SpecialFormCallNames::kOr ||
      orExpr->containsNonDeterministic()) {
    return {};
  }

  std::vector<std::pair<Group, ExprCP>> result;
  for (const auto& projection :
       projectLogicalExpression<Group>(orExpr, factory, groupFor)) {
    result.emplace_back(
        projection.group,
        projection.matchesSource ? orExpr : projection.filter);
  }
  return result;
}

enum class InputSide { kLeft, kRight };

// Compares AND and OR expressions after flattening nested calls of the same
// kind. Operand order remains significant.
bool equivalentModuloLogicalAssociativity(ExprCP lhs, ExprCP rhs) {
  if (lhs == rhs) {
    return true;
  }
  if (!lhs->is(PlanType::kCallExpr) || !rhs->is(PlanType::kCallExpr)) {
    return false;
  }

  const Name name = lhs->as<Call>()->name();
  if (name != rhs->as<Call>()->name()) {
    return false;
  }

  ExprVector lhsOperands;
  ExprVector rhsOperands;
  if (name == SpecialFormCallNames::kAnd) {
    ExprFactory::flattenAnd(lhs, lhsOperands);
    ExprFactory::flattenAnd(rhs, rhsOperands);
  } else if (name == SpecialFormCallNames::kOr) {
    ExprFactory::flattenOr(lhs, lhsOperands);
    ExprFactory::flattenOr(rhs, rhsOperands);
  } else {
    return false;
  }
  return std::ranges::equal(
      lhsOperands, rhsOperands, equivalentModuloLogicalAssociativity);
}

} // namespace

std::pair<ExprVector, ExprVector> ImpliedFilters::deriveForJoinInputs(
    const ExprVector& filters,
    const PlanObjectSet& leftColumns,
    const PlanObjectSet& rightColumns,
    ExprFactory& factory) {
  ExprVector leftFilters;
  ExprVector rightFilters;
  for (ExprCP conjunct : filters) {
    for (const auto& [side, filter] : deriveGroupedFiltersFromOr<InputSide>(
             conjunct,
             factory,
             [&](const PlanObjectSet& columns) -> std::optional<InputSide> {
               if (columns.empty()) {
                 return std::nullopt;
               }
               if (columns.isSubset(leftColumns)) {
                 return InputSide::kLeft;
               }
               if (columns.isSubset(rightColumns)) {
                 return InputSide::kRight;
               }
               return std::nullopt;
             })) {
      switch (side) {
        case InputSide::kLeft:
          leftFilters.push_back(filter);
          break;
        case InputSide::kRight:
          rightFilters.push_back(filter);
          break;
      }
    }
  }
  return {std::move(leftFilters), std::move(rightFilters)};
}

ExprVector ImpliedFilters::deriveForColumns(
    const ExprVector& filters,
    ExprFactory& factory) {
  folly::F14FastSet<ExprCP> uniqueFilters(filters.begin(), filters.end());
  folly::F14FastMap<ColumnCP, ExprVector> originalFiltersByColumn;
  for (ExprCP filter : filters) {
    const auto& columns = filter->columns();
    if (columns.size() == 1) {
      originalFiltersByColumn[columns.onlyObject<Column>()].push_back(filter);
    }
  }

  ExprVector result;
  for (ExprCP original : filters) {
    for (const auto& [column, filter] : deriveGroupedFiltersFromOr<ColumnCP>(
             original,
             factory,
             [](const PlanObjectSet& columns) -> std::optional<ColumnCP> {
               if (columns.size() != 1) {
                 return std::nullopt;
               }
               return columns.onlyObject<Column>();
             })) {
      if (!uniqueFilters.emplace(filter).second) {
        continue;
      }
      const auto originals = originalFiltersByColumn.find(column);
      if (originals == originalFiltersByColumn.end() ||
          std::ranges::none_of(originals->second, [&](ExprCP original) {
            return equivalentModuloLogicalAssociativity(original, filter);
          })) {
        result.push_back(filter);
      }
    }
  }
  return result;
}

} // namespace facebook::axiom::optimizer::v2
