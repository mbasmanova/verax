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

#include "axiom/optimizer/ToSubfield.h"

namespace facebook::axiom::optimizer {

namespace {
using PathElementPtr = std::unique_ptr<velox::common::Subfield::PathElement>;

PathElementPtr toSubscript(const Step& step, bool asField) {
  if (step.allFields) {
    return std::make_unique<velox::common::Subfield::AllSubscripts>();
  }
  if (asField) {
    return std::make_unique<velox::common::Subfield::NestedField>(
        step.field ? std::string(step.field) : fmt::format("{}", step.id));
  }
  if (step.field) {
    return std::make_unique<velox::common::Subfield::StringSubscript>(
        step.field);
  }
  return std::make_unique<velox::common::Subfield::LongSubscript>(step.id);
}
} // namespace

std::vector<velox::common::Subfield> toSubfields(
    std::string_view columnName,
    const PathSet& paths,
    bool mapKeysAsFields) {
  std::vector<velox::common::Subfield> subfields;
  paths.forEachPath([&](PathCP path) {
    std::vector<PathElementPtr> elements;
    elements.push_back(
        std::make_unique<velox::common::Subfield::NestedField>(
            std::string(columnName)));

    bool first = true;
    for (const auto& step : path->steps()) {
      switch (step.kind) {
        case StepKind::kField:
          VELOX_CHECK_NOT_NULL(
              step.field, "Index subfield not suitable for pruning");
          elements.push_back(
              std::make_unique<velox::common::Subfield::NestedField>(
                  step.field));
          break;
        case StepKind::kSubscript:
        case StepKind::kElementAt:
          elements.push_back(toSubscript(step, mapKeysAsFields && first));
          break;
      }
      first = false;
    }

    subfields.emplace_back(std::move(elements));
  });

  return subfields;
}

} // namespace facebook::axiom::optimizer
