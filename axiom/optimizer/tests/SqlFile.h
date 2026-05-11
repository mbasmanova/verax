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

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "axiom/common/Enums.h"

namespace facebook::axiom::optimizer::test {

/// Represents a single SQL query parsed from a test file, along with its
/// assertion type and any annotation parameters.
struct QueryEntry {
  enum class Type { kResults, kOrdered, kCount, kError };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Type)

  std::string sql;
  Type type{Type::kResults};
  std::optional<std::string> duckDbSql;
  uint64_t expectedCount{0};
  std::string expectedError;
  bool checkColumnNames{false};
  int32_t lineNumber{0};
};

/// Represents the contents of a parsed .sql test file: setup statements
/// to install reference tables, plus the query entries that test against
/// them.
struct SqlFile {
  /// DDL statements (CREATE TABLE / INSERT INTO …) collected from the
  /// file's setup directives in source order. Run before any query in the
  /// file executes.
  std::vector<std::string> setupStatements;

  /// Query entries parsed from the body of the file.
  std::vector<QueryEntry> entries;

  /// Parses 'content' into setup statements and queries.
  ///
  /// Setup directives recognized at the top of 'content' (before the first
  /// query):
  ///   -- setup_file: relative/path.sql
  ///       Splices in the contents of another .sql file, parsed as a
  ///       sequence of setup statements separated by '----'. Path is
  ///       resolved relative to 'baseDir'.
  ///   -- setup
  ///       Begins an inline setup block. Statements within the block are
  ///       separated by '----'.
  ///   -- end_setup
  ///       Ends an inline setup block.
  /// Both directive forms may appear any number of times in any order.
  /// Statements are collected in source order. The first non-directive
  /// line outside a setup block (including a plain '-- ' comment)
  /// switches the parser to query mode; everything from that line on is
  /// passed to the query parser.
  ///
  /// Queries are separated by '----'. Comment lines starting with '-- '
  /// before each query may carry annotations:
  ///   -- ordered         -> assertOrderedResults
  ///   -- count N         -> assertResultCount(sql, N)
  ///   -- error: message  -> assertFailure(sql, "message")
  ///   -- duckdb: sql     -> use alternate SQL for DuckDB comparison
  ///   -- columns         -> verify column names match DuckDB
  ///   -- disabled        -> skip this query
  /// Unrecognized '-- ' lines before SQL starts are treated as plain
  /// comments and ignored. '-- ' lines after SQL starts are part of the
  /// SQL body.
  ///
  /// @param baseDir Directory used to resolve setup_file paths. Pass an
  /// empty string when no setup_file directives are expected (e.g. unit
  /// tests of the parser).
  static SqlFile parse(std::string_view content, std::string_view baseDir);
};

} // namespace facebook::axiom::optimizer::test
