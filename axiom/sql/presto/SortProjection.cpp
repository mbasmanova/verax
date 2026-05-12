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
#include "axiom/sql/presto/SortProjection.h"

#include "folly/container/F14Map.h"
#include "velox/parse/Expressions.h"
#include "velox/parse/IExpr.h"

namespace axiom::sql::presto {

namespace lp = facebook::axiom::logical_plan;

namespace {
namespace core = facebook::velox::core;

// Indexes the SELECT-list projections by expression and by alias for
// matching ORDER BY sort keys. An alias whose ordinal is 0 is ambiguous
// (defined by more than one projection) and may only be used unambiguously.
struct ProjectionIndex {
  core::ExprMap<size_t> byExpr;
  folly::F14FastMap<std::string, size_t> byAlias;

  explicit ProjectionIndex(const std::vector<lp::ExprApi>& projections) {
    for (size_t i = 0; i < projections.size(); ++i) {
      byExpr.emplace(projections[i].expr(), i + 1);
      if (projections[i].alias().has_value()) {
        auto [iter, inserted] =
            byAlias.emplace(projections[i].alias().value(), i + 1);
        if (!inserted) {
          iter->second = 0;
        }
      }
    }
  }
};

// Recursively replaces root FieldAccessExpr nodes that match an output alias
// with the alias's underlying expression. Throws if the alias is ambiguous.
core::ExprPtr replaceAliases(
    const core::ExprPtr& expr,
    const folly::F14FastMap<std::string, size_t>& aliasMap,
    const std::vector<lp::ExprApi>& projections) {
  if (expr->is(core::IExpr::Kind::kFieldAccess)) {
    auto* field = expr->as<core::FieldAccessExpr>();
    if (field->isRootColumn()) {
      auto alias = aliasMap.find(field->name());
      if (alias != aliasMap.end()) {
        VELOX_USER_CHECK_NE(
            alias->second, 0, "Column is ambiguous: {}", field->name());
        return projections[alias->second - 1].expr();
      }
      return expr;
    }
  }

  const auto& inputs = expr->inputs();
  if (inputs.empty()) {
    return expr;
  }

  std::vector<core::ExprPtr> newInputs;
  bool changed = false;
  for (const auto& input : inputs) {
    auto newInput = replaceAliases(input, aliasMap, projections);
    if (newInput.get() != input.get()) {
      changed = true;
    }
    newInputs.push_back(std::move(newInput));
  }

  return changed ? expr->replaceInputs(std::move(newInputs)) : expr;
}

// Looks up a single sort key in 'index'. Returns the matching 1-based
// ordinal, or 0 if not present (caller decides whether to widen or fail).
// 'preResolvedOrdinal' short-circuits the lookup when the sort key was
// already resolved (e.g., from a positional ORDER BY ordinal).
size_t lookupSortKey(
    const lp::ExprApi& sortKey,
    size_t preResolvedOrdinal,
    const std::vector<lp::ExprApi>& projections,
    const ProjectionIndex& index) {
  if (preResolvedOrdinal != 0) {
    return preResolvedOrdinal;
  }
  if (sortKey.alias().has_value()) {
    auto it = index.byAlias.find(sortKey.alias().value());
    if (it != index.byAlias.end()) {
      VELOX_USER_CHECK_NE(it->second, 0, "Column is ambiguous: {}", it->first);
      return it->second;
    }
  }
  auto resolved = replaceAliases(sortKey.expr(), index.byAlias, projections);
  auto it = index.byExpr.find(resolved);
  return it != index.byExpr.end() ? it->second : 0;
}
} // namespace

std::vector<size_t> SortProjection::widenProjections(
    const std::vector<lp::ExprApi>& sortKeyExprs,
    const std::vector<size_t>& preResolvedOrdinals,
    std::vector<lp::ExprApi>& projections) {
  VELOX_CHECK_EQ(
      preResolvedOrdinals.size(),
      sortKeyExprs.size(),
      "Must be the same size as sortKeyExprs.");

  ProjectionIndex index{projections};
  std::vector<size_t> ordinals;
  ordinals.reserve(sortKeyExprs.size());

  for (size_t i = 0; i < sortKeyExprs.size(); ++i) {
    auto ordinal = lookupSortKey(
        sortKeyExprs[i], preResolvedOrdinals[i], projections, index);
    if (ordinal != 0) {
      ordinals.push_back(ordinal);
      continue;
    }
    // Sort key not present in the SELECT list; widen the projection.
    auto resolved =
        replaceAliases(sortKeyExprs[i].expr(), index.byAlias, projections);
    ordinal = projections.size() + 1;
    index.byExpr.emplace(resolved, ordinal);
    projections.emplace_back(std::move(resolved), sortKeyExprs[i].alias());
    ordinals.push_back(ordinal);
  }

  return ordinals;
}

std::vector<size_t> SortProjection::resolveSortKeys(
    const std::vector<lp::ExprApi>& sortKeyExprs,
    const std::vector<size_t>& preResolvedOrdinals,
    const std::vector<lp::ExprApi>& projections,
    const std::function<void(size_t)>& onUnresolved) {
  VELOX_CHECK_EQ(
      preResolvedOrdinals.size(),
      sortKeyExprs.size(),
      "Must be the same size as sortKeyExprs.");

  ProjectionIndex index{projections};
  std::vector<size_t> ordinals;
  ordinals.reserve(sortKeyExprs.size());

  for (size_t i = 0; i < sortKeyExprs.size(); ++i) {
    auto ordinal = lookupSortKey(
        sortKeyExprs[i], preResolvedOrdinals[i], projections, index);
    if (ordinal == 0) {
      onUnresolved(i);
      VELOX_FAIL("onUnresolved callback must throw");
    }
    ordinals.push_back(ordinal);
  }

  return ordinals;
}

void SortProjection::sortAndTrim(
    lp::PlanBuilder& builder,
    const std::vector<std::shared_ptr<SortItem>>& sortItems,
    const std::vector<size_t>& sortKeyOrdinals,
    size_t numOutputColumns) {
  VELOX_CHECK(!sortItems.empty());
  VELOX_CHECK_EQ(sortItems.size(), sortKeyOrdinals.size());

  std::vector<bool> ascending;
  std::vector<bool> nullsFirst;
  ascending.reserve(sortItems.size());
  nullsFirst.reserve(sortItems.size());
  for (const auto& item : sortItems) {
    ascending.push_back(item->isAscending());
    nullsFirst.push_back(item->isNullsFirst());
  }

  sortAndTrim(
      builder, sortKeyOrdinals, ascending, nullsFirst, numOutputColumns);
}

void SortProjection::sortAndTrim(
    lp::PlanBuilder& builder,
    const std::vector<size_t>& sortKeyOrdinals,
    const std::vector<bool>& ascending,
    const std::vector<bool>& nullsFirst,
    size_t numOutputColumns) {
  VELOX_CHECK(!sortKeyOrdinals.empty());
  VELOX_CHECK_EQ(ascending.size(), sortKeyOrdinals.size());
  VELOX_CHECK_EQ(nullsFirst.size(), sortKeyOrdinals.size());

  // Resolve sort key ordinals to output column names.
  std::vector<lp::SortKey> resolvedKeys;
  resolvedKeys.reserve(sortKeyOrdinals.size());
  for (size_t i = 0; i < sortKeyOrdinals.size(); ++i) {
    const auto column =
        builder.findOrAssignOutputNameAt(sortKeyOrdinals[i] - 1);
    resolvedKeys.emplace_back(column.toCol(), ascending[i], nullsFirst[i]);
  }

  builder.sort(resolvedKeys);

  // Only trim if extra columns were added for sorting.
  if (numOutputColumns < builder.numOutput()) {
    std::vector<lp::ExprApi> finalProjections;
    finalProjections.reserve(numOutputColumns);
    for (size_t i = 0; i < numOutputColumns; ++i) {
      finalProjections.emplace_back(
          builder.findOrAssignOutputNameAt(i).toCol());
    }
    builder.project(finalProjections);
  }
}

} // namespace axiom::sql::presto
