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

#include "axiom/sql/presto/grammar/SyntaxParser.h"

#include "axiom/sql/presto/PrestoSqlError.h"
#include "axiom/sql/presto/grammar/PrestoSqlLexer.h"
#include "axiom/sql/presto/grammar/UpperCaseInputStream.h"

namespace axiom::sql::presto {

namespace {

// Captures the first syntax error reported by the lexer or the parser.
class SyntaxErrorListener : public antlr4::BaseErrorListener {
 public:
  void reset() {
    firstError_.reset();
  }

  const std::string& firstError() const {
    return firstError_.value();
  }

  size_t line() const {
    return line_;
  }

  size_t column() const {
    return column_;
  }

  const std::string& token() const {
    return token_;
  }

  void syntaxError(
      antlr4::Recognizer* /*recognizer*/,
      antlr4::Token* offendingSymbol,
      size_t line,
      size_t charPositionInLine,
      const std::string& msg,
      std::exception_ptr /*e*/) override {
    if (firstError_.has_value()) {
      return; // only capture first error
    }

    line_ = line - 1; // 0-based
    column_ = charPositionInLine; // 0-based
    firstError_ = msg;
    token_ =
        offendingSymbol != nullptr ? offendingSymbol->getText() : std::string();
  }

 private:
  std::optional<std::string> firstError_;
  size_t line_{};
  size_t column_{};
  std::string token_;
};

// Bounds grammar-rule nesting to prevent a parser-stack overflow.
class DepthLimitListener : public antlr4::tree::ParseTreeListener {
 public:
  explicit DepthLimitListener(uint32_t maxDepth) : maxDepth_{maxDepth} {}

  void enterEveryRule(antlr4::ParserRuleContext* ctx) override {
    if (++depth_ > maxDepth_) {
      static const std::string kMessage{
          "Expression exceeds maximum nesting depth"};
      auto* token = ctx->getStart();
      throw PrestoSqlError(
          kMessage,
          token->getLine() - 1, // 0-based
          token->getCharPositionInLine(),
          /*token=*/std::nullopt,
          PrestoSqlErrorKind::kSemantic,
          kMessage);
    }
  }

  void exitEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {
    if (depth_ > 0) {
      --depth_;
    }
  }

  void visitTerminal(antlr4::tree::TerminalNode* /*node*/) override {}
  void visitErrorNode(antlr4::tree::ErrorNode* /*node*/) override {}

  void reset() {
    depth_ = 0;
  }

 private:
  uint32_t maxDepth_;
  uint32_t depth_{0};
};

} // namespace

struct SyntaxParser::Impl {
  Impl(std::string_view sql, uint32_t maxDepth)
      : input{sql},
        lexer{&input},
        tokens{&lexer},
        parser{&tokens},
        depthListener{maxDepth} {
    lexer.removeErrorListeners();
    lexer.addErrorListener(&errorListener);

    parser.removeErrorListeners();
    parser.addErrorListener(&errorListener);
    parser.addParseListener(&depthListener);

    // Use SLL prediction mode for faster parsing. SLL is much faster than LL
    // mode and works for most SQL queries. If SLL fails, we fall back to LL.
    parser.getInterpreter<antlr4::atn::ParserATNSimulator>()->setPredictionMode(
        antlr4::atn::PredictionMode::SLL);
  }

  // Each member reads from the one declared before it.
  UpperCaseInputStream input;
  PrestoSqlLexer lexer;
  antlr4::CommonTokenStream tokens;
  PrestoSqlParser parser;
  SyntaxErrorListener errorListener;
  DepthLimitListener depthListener;
};

SyntaxParser::SyntaxParser(std::string_view sql, uint32_t maxDepth)
    : impl_{std::make_unique<Impl>(sql, maxDepth)} {}

SyntaxParser::~SyntaxParser() = default;

PrestoSqlParser::StatementContext* SyntaxParser::parse() {
  // Try SLL mode first (fast path).
  try {
    auto ctx = impl_->parser.singleStatement();
    if (impl_->parser.getNumberOfSyntaxErrors() == 0) {
      return ctx->statement();
    }
  } catch (const PrestoSqlError&) {
    // Don't re-parse in LL, it would re-hit this semantic error.
    throw;
  } catch (const std::exception&) {
    // SLL mode failed, fall through to LL mode.
  }

  // Fall back to LL mode (slower but handles all valid SQL).
  impl_->tokens.seek(0);
  // Reset both the parser and errorListener so that errors from the SLL
  // attempt are discarded. Either the LL path succeeds and we return a
  // valid AST, or it fails and we capture fresh LL error info.
  impl_->parser.reset();
  impl_->errorListener.reset();
  impl_->depthListener.reset();
  impl_->parser.getInterpreter<antlr4::atn::ParserATNSimulator>()
      ->setPredictionMode(antlr4::atn::PredictionMode::LL);

  auto ctx = impl_->parser.singleStatement();
  if (impl_->parser.getNumberOfSyntaxErrors() > 0) {
    throw PrestoSqlError(
        impl_->errorListener.firstError(),
        impl_->errorListener.line(),
        impl_->errorListener.column(),
        impl_->errorListener.token(),
        PrestoSqlErrorKind::kSyntax,
        impl_->errorListener.firstError());
  }

  return ctx->statement();
}

} // namespace axiom::sql::presto
