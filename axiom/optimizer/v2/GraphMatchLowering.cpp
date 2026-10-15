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

#include "axiom/optimizer/v2/GraphMatchLowering.h"

#include "axiom/optimizer/v2/AppendAll.h"

namespace facebook::axiom::optimizer::v2 {

namespace lp = logical_plan;

namespace {

using Scope = Translator::Scope;
using Translated = Translator::Translated;

// Fails for a pattern name used in a predicate other than to read a property,
// such as a = b, which compares elements, and for a subquery.
void checkPropertyReads(const lp::Expr& expr) {
  if (expr.isSpecialForm() &&
      expr.as<lp::SpecialFormExpr>()->form() == lp::SpecialForm::kDereference &&
      expr.inputAt(0)->isInputReference()) {
    return;
  }
  if (expr.isInputReference()) {
    VELOX_NYI(
        "Graph pattern name outside a property reference is not supported "
        "yet: {}",
        expr.as<lp::InputReferenceExpr>()->name());
  }
  if (expr.isSubquery()) {
    VELOX_NYI("Subquery in a graph pattern predicate is not supported yet");
  }
  if (expr.isLambda()) {
    checkPropertyReads(*expr.as<lp::LambdaExpr>()->body());
    return;
  }
  for (const auto& input : expr.inputs()) {
    checkPropertyReads(*input);
  }
}

} // namespace

ExprVector Translator::GraphMatchLowering::Element::columns(
    const std::vector<std::string>& names) const {
  ExprVector exprs;
  exprs.reserve(names.size());
  for (const auto& name : names) {
    exprs.push_back(scope.at(name));
  }
  return exprs;
}

std::optional<Translated> Translator::GraphMatchLowering::lower(
    const LpNameSet& required) {
  for (const auto& path : match_.paths()) {
    if (!addPath(path)) {
      return std::nullopt;
    }
  }
  if (match_.predicate() != nullptr) {
    checkPropertyReads(*match_.predicate());
    predicates_.push_back(match_.predicate().get());
  }

  NodeCP node = join();
  ExprVector conjuncts = translatePredicates();
  Scope scope = outputs(required);
  if (conjuncts.empty()) {
    return Translated{node, std::move(scope)};
  }
  return translator_.simplifyFilter(
      node,
      std::move(conjuncts),
      std::move(scope),
      /*propagateConstants=*/true);
}

std::optional<size_t> Translator::GraphMatchLowering::bind(
    const lp::GraphElementPattern& pattern,
    bool edge) {
  const auto tables = graph_.matchingTables(pattern.label().get(), edge);
  const auto& name = pattern.name();

  // A name bound before matches only its table.
  if (const auto it = elementByName_.find(name); it != elementByName_.end()) {
    if (std::find(tables.begin(), tables.end(), elements_[it->second].table) ==
        tables.end()) {
      return std::nullopt;
    }
    return it->second;
  }

  if (tables.size() > 1) {
    VELOX_NYI(
        "Graph label that matches several element tables is not supported "
        "yet: {}",
        pattern.label() != nullptr ? pattern.label()->toString() : "%");
  }
  if (tables.empty()) {
    return std::nullopt;
  }

  const auto* table = tables[0];
  Translated translated = [&] {
    auto planGuard = translator_.translatingPlan(*table->plan);
    return translator_.translateNode(*table->plan);
  }();
  if (!name.empty()) {
    if (!table->properties.empty()) {
      std::vector<std::string> names;
      std::vector<velox::TypePtr> types;
      std::vector<lp::ExprPtr> values;
      for (const auto& [property, expression] : table->properties) {
        names.push_back(property);
        types.push_back(expression->type());
        values.push_back(expression);
      }
      const lp::CallExpr row(
          velox::ROW(std::move(names), std::move(types)),
          "row_constructor",
          std::move(values));
      patternScope_[name] = translator_.translateExpr(
          row, translated.scope, /*liftTarget=*/nullptr);
    }
    elementByName_.emplace(name, elements_.size());
  }
  elements_.push_back({table, translated.node, std::move(translated.scope)});
  return elements_.size() - 1;
}

bool Translator::GraphMatchLowering::addPath(const lp::GraphPathPattern& path) {
  using Direction = lp::GraphEdgePattern::Direction;
  using EdgeTable = lp::PropertyGraph::EdgeTable;

  if (path.selector.has_value()) {
    VELOX_NYI("Graph path selectors are not supported yet");
  }
  if (path.mode.value_or(lp::GraphPathMode::kWalk) !=
      lp::GraphPathMode::kWalk) {
    VELOX_NYI(
        "Graph path mode is not supported yet: {}",
        lp::GraphPathModeName::toName(path.mode.value()));
  }

  // An edge waiting for the vertex it reaches: the edge, the edge columns
  // that hold that vertex's key, and the vertex table they reference.
  struct PendingEdge {
    size_t element;
    ExprVector columns;
    int32_t vertexTableId;
  };

  // The vertex the next edge leaves from.
  std::optional<size_t> vertex;
  std::optional<PendingEdge> pendingEdge;
  int64_t numEdges{0};
  for (const auto& term : path.terms) {
    if (term->predicate() != nullptr) {
      checkPropertyReads(*term->predicate());
      predicates_.push_back(term->predicate().get());
    }
    switch (term->kind()) {
      case lp::GraphPatternTerm::Kind::kSubpath:
        VELOX_NYI("Graph subpath patterns are not supported yet");
      case lp::GraphPatternTerm::Kind::kEdge: {
        const auto* edge = term->as<lp::GraphEdgePattern>();
        if (edge->repetition().has_value()) {
          VELOX_NYI("Repeated graph edge patterns are not supported yet");
        }
        if (edge->direction() == Direction::kAnyDirection) {
          VELOX_NYI("Undirected graph edge patterns are not supported yet");
        }
        if (!vertex.has_value() || pendingEdge.has_value()) {
          VELOX_NYI(
              "Graph edge pattern without a vertex pattern before it is not "
              "supported yet");
        }
        const auto index = bind(*edge, /*edge=*/true);
        if (!index.has_value()) {
          return false;
        }
        const auto& element = elements_[*index];
        const auto* table = static_cast<const EdgeTable*>(element.table);
        const bool pointsRight = edge->direction() == Direction::kRight;
        const auto& from = elements_[*vertex];
        const auto fromTableId =
            pointsRight ? table->sourceTableId : table->destinationTableId;
        if (fromTableId != from.table->id) {
          return false;
        }
        connections_.push_back(
            {*vertex,
             from.columns(from.table->keyColumns),
             *index,
             element.columns(
                 pointsRight ? table->sourceColumns
                             : table->destinationColumns)});
        pendingEdge = PendingEdge{
            *index,
            element.columns(
                pointsRight ? table->destinationColumns : table->sourceColumns),
            pointsRight ? table->destinationTableId : table->sourceTableId};
        ++numEdges;
        break;
      }
      case lp::GraphPatternTerm::Kind::kVertex: {
        if (vertex.has_value() && !pendingEdge.has_value()) {
          VELOX_NYI(
              "Adjacent graph vertex patterns are not supported yet: {}",
              term->name());
        }
        const auto index =
            bind(*term->as<lp::GraphVertexPattern>(), /*edge=*/false);
        if (!index.has_value()) {
          return false;
        }
        if (pendingEdge.has_value()) {
          const auto& to = elements_[*index];
          if (pendingEdge->vertexTableId != to.table->id) {
            return false;
          }
          connections_.push_back(
              {pendingEdge->element,
               std::move(pendingEdge->columns),
               *index,
               to.columns(to.table->keyColumns)});
          pendingEdge.reset();
        }
        vertex = index;
        break;
      }
    }
  }
  if (pendingEdge.has_value()) {
    VELOX_NYI(
        "Graph edge pattern without a vertex pattern after it is not "
        "supported yet");
  }
  if (!path.name.empty()) {
    pathLengths_.emplace(path.name, numEdges);
  }
  return true;
}

NodeCP Translator::GraphMatchLowering::join() {
  std::vector<bool> joined(elements_.size());
  joined[0] = true;
  NodeCP node = elements_[0].node;
  for (size_t step = 1; step < elements_.size(); ++step) {
    // The first element not joined yet, preferring one connected to the
    // elements joined so far.
    std::optional<size_t> next;
    for (const auto& connection : connections_) {
      const bool leftJoined = joined[connection.leftElement];
      if (leftJoined != joined[connection.rightElement]) {
        next = leftJoined ? connection.rightElement : connection.leftElement;
        break;
      }
    }
    if (!next.has_value()) {
      next = std::find(joined.begin(), joined.end(), false) - joined.begin();
    }

    ExprVector leftKeys;
    ExprVector rightKeys;
    for (const auto& connection : connections_) {
      if (connection.rightElement == *next && joined[connection.leftElement]) {
        appendAll(leftKeys, connection.leftKeys);
        appendAll(rightKeys, connection.rightKeys);
      } else if (
          connection.leftElement == *next && joined[connection.rightElement]) {
        appendAll(leftKeys, connection.rightKeys);
        appendAll(rightKeys, connection.leftKeys);
      }
    }
    auto simplified = translator_.innerJoin(
        node, elements_[*next].node, std::move(leftKeys), std::move(rightKeys));
    node = translator_.nodeSimplifier_.materialize(simplified);
    joined[*next] = true;

    // The join may replace columns of its inputs, such as a key with the key
    // it equals. Later joins and outputs read the replacements.
    const auto& substitutions = simplified.substitutions;
    for (auto& element : elements_) {
      translator_.applySubstitutions(substitutions, element.scope);
    }
    translator_.applySubstitutions(substitutions, patternScope_);
    for (auto& connection : connections_) {
      translator_.applySubstitutions(substitutions, connection.leftKeys);
      translator_.applySubstitutions(substitutions, connection.rightKeys);
    }
  }
  return node;
}

ExprVector Translator::GraphMatchLowering::translatePredicates() const {
  ExprVector conjuncts;
  conjuncts.reserve(predicates_.size());
  for (const auto* predicate : predicates_) {
    conjuncts.push_back(translator_.translateExpr(
        *predicate, patternScope_, /*liftTarget=*/nullptr));
  }
  return conjuncts;
}

Scope Translator::GraphMatchLowering::outputs(const LpNameSet& required) {
  Scope scope;
  const auto& outputs = match_.outputs();
  const auto& names = match_.outputNames();
  for (size_t i = 0; i < outputs.size(); ++i) {
    if (!required.contains(names[i])) {
      continue;
    }
    const auto& output = *outputs[i];
    if (output.kind() == lp::GraphMatchOutput::Kind::kPathLength) {
      scope[names[i]] = translator_.exprFactory_.makeLiteral(
          velox::Variant(pathLengths_.at(output.pattern())),
          toType(velox::BIGINT()));
      continue;
    }
    const auto& element = elements_[elementByName_.at(output.pattern())];
    const auto& property = output.as<lp::GraphPropertyOutput>()->property();
    scope[names[i]] = translator_.translateExpr(
        *element.table->properties.at(property),
        element.scope,
        /*liftTarget=*/nullptr);
  }
  return scope;
}

Translated Translator::translateGraphMatch(
    const lp::GraphMatchNode& match,
    const LpNameSet& required) {
  auto lowered = GraphMatchLowering(*this, match).lower(required);
  return lowered.has_value() ? std::move(*lowered)
                             : makeEmptyResult(*match.outputType());
}

} // namespace facebook::axiom::optimizer::v2
