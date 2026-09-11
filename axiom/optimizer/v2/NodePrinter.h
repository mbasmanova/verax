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

#include <functional>
#include <string>
#include "axiom/optimizer/v2/EstimateProvider.h"
#include "axiom/optimizer/v2/Node.h"

namespace facebook::axiom::optimizer::v2 {

/// Renders an IR tree as indented text.
class NodePrinter {
 public:
  struct Options {
    /// Supplies the estimate to print under each node. Unset prints none, and
    /// a node whose cardinality is unknown prints none either way.
    std::function<Estimate(NodeCP)> estimates;
  };

  /// Returns 'root' as indented text. Columns are shown by their `name()`
  /// (the unique synthetic), not `outputName()`, so identity is visible.
  static std::string toText(NodeCP root, const Options& options = {});
};

} // namespace facebook::axiom::optimizer::v2
