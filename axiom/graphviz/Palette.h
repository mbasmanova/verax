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

#include <string_view>

namespace facebook::axiom::graphviz {

/// Color palette shared by all dot printers so the rendered diagrams read
/// as one visual family.
struct ColorPalette {
  std::string_view text = "#1c2915"; // Dark green
  std::string_view lines = "#727a6b"; // Gray-green
  std::string_view header = "#ccd5c4"; // Light sage
  std::string_view highlight = "#ede3d9"; // Cream
  std::string_view circles = "#af9d89"; // Tan
  std::string_view subqueryEdge = "#8b4513"; // Saddle brown
};

inline constexpr ColorPalette kPalette;

} // namespace facebook::axiom::graphviz
