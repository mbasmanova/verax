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

// Projects an OR onto caller-defined groups. A group produces a necessary
// filter only when every disjunct has at least one conjunct in that group.
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

  struct Candidate {
    Group key;
    std::vector<ExprVector> conjunctsByDisjunct;
    bool matchesOriginal;
  };

  std::vector<Candidate> groups;
  const ExprVector disjuncts = ExprFactory::flattenOr(orExpr);
  for (size_t i = 0; i < disjuncts.size(); ++i) {
    const ExprVector conjuncts = ExprFactory::flattenAnd(disjuncts[i]);
    folly::F14FastMap<Group, ExprVector> conjunctsByGroup;
    std::vector<Group> groupOrder;
    for (ExprCP conjunct : conjuncts) {
      const auto group = groupFor(conjunct->columns());
      if (!group.has_value()) {
        continue;
      }
      auto [it, inserted] = conjunctsByGroup.try_emplace(*group);
      if (inserted && i == 0) {
        groupOrder.push_back(*group);
      }
      it->second.push_back(conjunct);
    }

    if (i == 0) {
      groups.reserve(groupOrder.size());
      for (const Group group : groupOrder) {
        auto& groupedConjuncts = conjunctsByGroup.at(group);
        const bool matchesOriginal =
            groupedConjuncts.size() == conjuncts.size();
        groups.push_back(
            {group, {std::move(groupedConjuncts)}, matchesOriginal});
      }
      continue;
    }

    std::erase_if(groups, [&](Candidate& candidate) {
      const auto groupedConjuncts = conjunctsByGroup.find(candidate.key);
      if (groupedConjuncts == conjunctsByGroup.end()) {
        return true;
      }
      const bool matchesOriginal =
          groupedConjuncts->second.size() == conjuncts.size();
      candidate.conjunctsByDisjunct.push_back(
          std::move(groupedConjuncts->second));
      candidate.matchesOriginal &= matchesOriginal;
      return false;
    });
    if (groups.empty()) {
      return {};
    }
  }

  std::vector<std::pair<Group, ExprCP>> result;
  result.reserve(groups.size());
  for (auto& group : groups) {
    if (group.matchesOriginal) {
      result.emplace_back(group.key, orExpr);
      continue;
    }
    ExprVector groupedDisjuncts;
    groupedDisjuncts.reserve(group.conjunctsByDisjunct.size());
    for (auto& conjuncts : group.conjunctsByDisjunct) {
      groupedDisjuncts.push_back(combineBalanced(
          std::move(conjuncts),
          [&](ExprCP lhs, ExprCP rhs) { return factory.makeAnd(lhs, rhs); }));
    }
    result.emplace_back(
        group.key,
        combineBalanced(
            std::move(groupedDisjuncts),
            [&](ExprCP lhs, ExprCP rhs) { return factory.makeOr(lhs, rhs); }));
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
