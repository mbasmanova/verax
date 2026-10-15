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

#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>

#include "axiom/logical_plan/PlanBuilder.h"

namespace facebook::axiom::logical_plan {

/// Builds a GraphMatch node for PlanBuilder::startGraphMatch. Expressions are
/// untyped, as elsewhere in PlanBuilder. A predicate or output reads a property
/// of a vertex or edge pattern as name.property, and the length of a path or
/// subpath pattern as path_length(name).
///
/// Terms are added in path order: an edge connects the vertex pattern added
/// before it to the one added after it. This builds the plan for
///
///   SELECT * FROM GRAPH_TABLE (graph
///     MATCH p = ANY SHORTEST
///       (a IS Person WHERE a.age > 30) -[e IS Knows]->{1,3} (b IS Person)
///     WHERE a.city = b.city
///     COLUMNS (b.name AS friend, path_length(p) AS hops))
///   WHERE hops > 1
///   ORDER BY friend
///
/// as
///
///   PlanBuilder(context)
///       .startGraphMatch(graph)
///       .path("p", GraphPathSelector::anyShortest())
///       .vertex("a", "Person", "a.age > 30")
///       .rightEdge("e", "Knows")
///       .repeats(1, 3)
///       .vertex("b", "Person")
///       .filter("a.city = b.city")
///       .project({"b.name AS friend", "path_length(p) AS hops"})
///       .endGraphMatch()  // Returns the PlanBuilder.
///       .filter("hops > 1")
///       .orderBy({"friend"})
///       .build();
///
/// repeats() and optional() modify the edge or subpath added last. A projected
/// expression other than a single property or path length becomes a
/// projection above the node.
class PlanBuilder::GraphMatchBuilder {
 public:
  /// Function name that reads the length of a path or subpath pattern in
  /// projected expressions.
  static constexpr std::string_view kPathLengthFunctionName = "path_length";

  GraphMatchBuilder(PlanBuilder& builder, PropertyGraphPtr graph);

  /// Starts a path pattern with selector ALL and mode WALK. Patterns added
  /// before any path() call start an unnamed one implicitly.
  GraphMatchBuilder& path(std::string name);

  /// Starts a path pattern: name = selector mode. An empty 'name' leaves the
  /// path unnamed.
  GraphMatchBuilder&
  path(std::string name, GraphPathSelector selector, GraphPathMode mode);

  /// @overload Takes a selector, with mode WALK.
  GraphMatchBuilder& path(std::string name, GraphPathSelector selector);

  /// @overload Takes a mode, with selector ALL.
  GraphMatchBuilder& path(std::string name, GraphPathMode mode);

  /// Adds a vertex pattern to the current path or subpath. A null 'label'
  /// matches any label.
  GraphMatchBuilder& vertex(
      std::string name,
      GraphLabelExpressionPtr label,
      std::optional<ExprApi> predicate);

  /// @overload Takes a label name and a SQL predicate.
  GraphMatchBuilder&
  vertex(std::string name, std::string_view label, std::string_view predicate);

  /// @overload Matches label 'label', with no predicate.
  GraphMatchBuilder& vertex(std::string name, std::string_view label);

  /// @overload Matches 'label', with no predicate.
  GraphMatchBuilder& vertex(std::string name, GraphLabelExpressionPtr label);

  /// @overload Matches any label, with no predicate.
  GraphMatchBuilder& vertex(std::string name);

  /// Adds an edge pattern from the vertex on the left to the vertex on the
  /// right: -[]->.
  GraphMatchBuilder& rightEdge(
      std::string name,
      GraphLabelExpressionPtr label,
      std::optional<ExprApi> predicate);

  /// @overload Takes a label name and a SQL predicate.
  GraphMatchBuilder& rightEdge(
      std::string name,
      std::string_view label,
      std::string_view predicate);

  /// @overload Matches label 'label', with no predicate.
  GraphMatchBuilder& rightEdge(std::string name, std::string_view label);

  /// @overload Matches 'label', with no predicate.
  GraphMatchBuilder& rightEdge(std::string name, GraphLabelExpressionPtr label);

  /// @overload Matches any label, with no predicate.
  GraphMatchBuilder& rightEdge(std::string name);

  /// Adds an edge pattern from the vertex on the right to the vertex on the
  /// left: <-[]-.
  GraphMatchBuilder& leftEdge(
      std::string name,
      GraphLabelExpressionPtr label,
      std::optional<ExprApi> predicate);

  /// @overload Takes a label name and a SQL predicate.
  GraphMatchBuilder& leftEdge(
      std::string name,
      std::string_view label,
      std::string_view predicate);

  /// @overload Matches label 'label', with no predicate.
  GraphMatchBuilder& leftEdge(std::string name, std::string_view label);

  /// @overload Matches 'label', with no predicate.
  GraphMatchBuilder& leftEdge(std::string name, GraphLabelExpressionPtr label);

  /// @overload Matches any label, with no predicate.
  GraphMatchBuilder& leftEdge(std::string name);

  /// Adds an edge pattern in either direction: -[]-.
  GraphMatchBuilder& anyEdge(
      std::string name,
      GraphLabelExpressionPtr label,
      std::optional<ExprApi> predicate);

  /// @overload Takes a label name and a SQL predicate.
  GraphMatchBuilder&
  anyEdge(std::string name, std::string_view label, std::string_view predicate);

  /// @overload Matches label 'label', with no predicate.
  GraphMatchBuilder& anyEdge(std::string name, std::string_view label);

  /// @overload Matches 'label', with no predicate.
  GraphMatchBuilder& anyEdge(std::string name, GraphLabelExpressionPtr label);

  /// @overload Matches any label, with no predicate.
  GraphMatchBuilder& anyEdge(std::string name);

  /// Repeats the edge or subpath added last between 'min' and 'max' times. An
  /// unset 'max' means no limit.
  GraphMatchBuilder& repeats(int64_t min, std::optional<int64_t> max);

  /// Makes the subpath added last match once or not at all ('?').
  GraphMatchBuilder& optional();

  /// Starts a subpath in the current path or subpath.
  GraphMatchBuilder& startSubpath(std::string name, GraphPathMode mode);

  /// @overload Takes mode WALK.
  GraphMatchBuilder& startSubpath(std::string name);

  /// Ends the innermost subpath, with no predicate.
  GraphMatchBuilder& endSubpath();

  /// Ends the innermost subpath. 'predicate' reads the patterns inside it.
  GraphMatchBuilder& endSubpath(std::optional<ExprApi> predicate);

  /// @overload Takes a SQL predicate.
  GraphMatchBuilder& endSubpath(std::string_view predicate);

  /// Sets the condition on a whole match, across paths.
  GraphMatchBuilder& filter(const ExprApi& predicate);

  /// @overload Takes a SQL predicate.
  GraphMatchBuilder& filter(std::string_view predicate);

  /// Sets the output columns. Each one is named by its alias, or by the
  /// property name for a property.
  GraphMatchBuilder& project(const std::vector<ExprApi>& exprs);

  /// @overload Takes SQL expressions.
  GraphMatchBuilder& project(const std::vector<std::string>& exprs);

  /// @overload Takes SQL expressions.
  GraphMatchBuilder& project(std::initializer_list<std::string> exprs) {
    return project(std::vector<std::string>{exprs});
  }

  /// Adds the GraphMatch node, and a projection for computed expressions, to
  /// the PlanBuilder and returns it.
  PlanBuilder& endGraphMatch();

 private:
  // A vertex or edge pattern name, with the tables its patterns can match.
  struct ElementName {
    bool edge{false};
    std::vector<const PropertyGraph::ElementTable*> tables;
  };

  // A subpath started and not yet ended.
  struct OpenSubpath {
    std::string name;
    GraphPathMode mode{GraphPathMode::kWalk};
    std::vector<GraphPatternTermPtr> terms;

    // Vertex and edge pattern names inside the subpath.
    folly::F14FastSet<std::string> names;
  };

  // The term added last. repeats() and optional() may still change it.
  struct PendingTerm {
    GraphPatternTerm::Kind kind{GraphPatternTerm::Kind::kVertex};
    std::string name;
    GraphLabelExpressionPtr label;
    ExprPtr predicate;
    GraphEdgePattern::Direction direction{GraphEdgePattern::Direction::kRight};
    GraphPathMode mode{GraphPathMode::kWalk};
    std::vector<GraphPatternTermPtr> terms;
    std::optional<GraphRepetition> repetition;
    bool optional{false};
  };

  GraphMatchBuilder& addEdge(
      std::string name,
      GraphLabelExpressionPtr label,
      std::optional<ExprApi> predicate,
      GraphEdgePattern::Direction direction);

  void addElement(
      const std::string& name,
      const GraphLabelExpressionPtr& label,
      bool edge);

  // Builds the pending term, if any, and adds it to the current path or
  // subpath.
  void flush();

  // Resolves 'expr', in which each name in 'names' is a vertex or edge
  // pattern.
  ExprPtr resolve(
      const ExprApi& expr,
      const folly::F14FastSet<std::string>& names) const;

  std::optional<ExprApi> parse(std::string_view sql) const;

  PlanBuilder& builder_;
  const PropertyGraphPtr graph_;
  std::vector<GraphPathPattern> paths_;
  std::vector<OpenSubpath> subpaths_;
  std::optional<PendingTerm> pending_;
  folly::F14FastMap<std::string, ElementName> elementNames_;

  // Path and subpath pattern names.
  folly::F14FastSet<std::string> pathNames_;
  ExprPtr predicate_;
  std::vector<ExprApi> outputs_;
};

} // namespace facebook::axiom::logical_plan
