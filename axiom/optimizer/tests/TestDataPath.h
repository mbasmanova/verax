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

#include <filesystem>
#include <string>
#include "velox/common/base/Exceptions.h"

namespace facebook::axiom::optimizer::test {

/// Returns the full path to a file relative to the optimizer test directory.
/// Works when run from the test source directory (ctest/Buck) and from the
/// repo root.
inline std::string getTestFilePath(const std::string& filePath) {
  if (std::filesystem::exists(filePath)) {
    return filePath;
  }
  auto withBase = "axiom/optimizer/tests/" + filePath;
  if (std::filesystem::exists(withBase)) {
    return withBase;
  }
  auto cwd = std::filesystem::current_path().string();
  VELOX_FAIL(
      "Test data file not found. Checked '{}' and '{}' relative to cwd '{}'",
      filePath,
      withBase,
      cwd);
}

} // namespace facebook::axiom::optimizer::test
