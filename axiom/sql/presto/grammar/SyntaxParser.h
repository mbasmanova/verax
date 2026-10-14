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

#include <memory>
#include <string_view>

#include "axiom/sql/presto/grammar/PrestoSqlParser.h"

namespace axiom::sql::presto {

/// Parses the text of one SQL statement into an ANTLR parse tree. This is the
/// syntax stage of PrestoParser: it checks the grammar and nothing else.
///
///   SyntaxParser parser(sql, options.maxExpressionDepth);
///   auto* statement = parser.parse();
///   AstBuilder(options).visit(statement);
///
/// Keywords match regardless of letter case, using UpperCaseInputStream;
/// identifiers and string literals keep their original spelling in the tree.
///
/// The returned tree is owned by the SyntaxParser and is valid only while it
/// lives.
class SyntaxParser {
 public:
  /// @param maxDepth Maximum nesting depth of grammar rules; deeper input
  /// fails to avoid a stack overflow.
  SyntaxParser(std::string_view sql, uint32_t maxDepth);

  ~SyntaxParser();

  /// Returns the parse tree of the statement. Fails with a PrestoSqlError on
  /// a syntax error or on input nested deeper than 'maxDepth'.
  ///
  /// Tries ANTLR's fast SLL prediction first and falls back to full LL
  /// prediction, so a statement parses the same as with LL alone.
  PrestoSqlParser::StatementContext* parse();

 private:
  // The ANTLR input, lexer, token stream, parser and listeners.
  struct Impl;

  std::unique_ptr<Impl> impl_;
};

} // namespace axiom::sql::presto
