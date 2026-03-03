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

#include "axiom/optimizer/PlanObject.h"

namespace facebook::axiom::optimizer {

/// Key for memoization of partial plans. Identifies a subset of tables
/// with their required output columns and existence joins.
struct MemoKey {
  static MemoKey create(
      PlanObjectCP firstTable,
      PlanObjectSet columns,
      PlanObjectSet tables,
      std::vector<PlanObjectSet> existences = {}) {
    VELOX_CHECK_NOT_NULL(firstTable);
    VELOX_CHECK(tables.contains(firstTable));
    return MemoKey{
        firstTable,
        std::move(columns),
        std::move(tables),
        std::move(existences)};
  }

  bool operator==(const MemoKey& other) const;

  size_t hash() const;

  std::string toString() const;

  const PlanObjectCP firstTable;
  const PlanObjectSet columns;
  const PlanObjectSet tables;
  const std::vector<PlanObjectSet> existences;

 private:
  MemoKey(
      PlanObjectCP firstTable,
      PlanObjectSet columns,
      PlanObjectSet tables,
      std::vector<PlanObjectSet> existences)
      : firstTable(firstTable),
        columns(std::move(columns)),
        tables(std::move(tables)),
        existences(std::move(existences)) {}
};

} // namespace facebook::axiom::optimizer

namespace std {
template <>
struct hash<::facebook::axiom::optimizer::MemoKey> {
  size_t operator()(const ::facebook::axiom::optimizer::MemoKey& key) const {
    return key.hash();
  }
};
} // namespace std
