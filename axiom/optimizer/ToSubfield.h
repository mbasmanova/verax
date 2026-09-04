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

#include "axiom/optimizer/PathSet.h"
#include "velox/type/Subfield.h"

namespace facebook::axiom::optimizer {

/// Converts the accessed paths of one column into the subfields a connector
/// column handle takes. Each path becomes one subfield rooted at 'columnName'.
///
/// An empty 'paths' yields no subfields, which is how a caller says the whole
/// column is read.
///
/// @param mapKeysAsFields Renders the first subscript of a map column as a
/// struct field name rather than a subscript, for a layout that stores the map
/// as a struct. Applies only to the first step, since only the top-level map
/// is stored that way.
std::vector<velox::common::Subfield> toSubfields(
    std::string_view columnName,
    const PathSet& paths,
    bool mapKeysAsFields);

} // namespace facebook::axiom::optimizer
