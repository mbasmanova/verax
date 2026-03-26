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

namespace axiom::sql::presto {

/// Options controlling SQL parsing behavior.
struct ParserOptions {
  /// Enables Friendly SQL extensions inspired by DuckDB: named ROW
  /// constructors, trailing commas, FROM-first syntax, etc.
  bool friendlySql{true};

  /// When true, decimal literals (e.g., 1.5) are parsed as DOUBLE. When
  /// false, they are parsed as DECIMAL with precision and scale inferred
  /// from the literal. Matches Presto's decimal_literal_result_type session
  /// property.
  bool parseDecimalLiteralAsDouble{true};
};

} // namespace axiom::sql::presto
