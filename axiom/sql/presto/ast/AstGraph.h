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

#include "axiom/sql/presto/ast/AstRelations.h"

/// AST nodes for graph queries: GRAPH_TABLE (SQL/PGQ) and query-scoped graph
/// definitions (WITH GRAPH name AS (...)).
///
///   WITH GRAPH social AS (
///     VERTEX TABLES (person KEY (id) LABEL Person)
///     EDGE TABLES (knows KEY (src, dst)
///       SOURCE KEY (src) REFERENCES person (id)
///       DESTINATION KEY (dst) REFERENCES person (id)
///       LABEL Knows))
///   SELECT * FROM GRAPH_TABLE (social
///     MATCH (a IS Person WHERE a.name = 'Alice') -[k IS Knows]-> (b)
///     COLUMNS (b.name AS friend, k.since))
namespace axiom::sql::presto {

/// Label expression of a graph element pattern: a label name, the wildcard
/// '%', or a negation, conjunction or disjunction of label expressions.
///
/// Invariants:
/// - kName has a name and no operands.
/// - kWildcard has neither.
/// - kNegation has one operand.
/// - kConjunction and kDisjunction have two or more operands.
class LabelExpression : public Node {
 public:
  enum class Kind { kName, kWildcard, kNegation, kConjunction, kDisjunction };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Kind);

  LabelExpression(
      NodeLocation location,
      Kind kind,
      IdentifierPtr name,
      std::vector<std::shared_ptr<LabelExpression>> operands);

  Kind kind() const {
    return kind_;
  }

  /// Label name. Set only for kName.
  const IdentifierPtr& name() const {
    return name_;
  }

  const std::vector<std::shared_ptr<LabelExpression>>& operands() const {
    return operands_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  Kind kind_;
  IdentifierPtr name_;
  std::vector<std::shared_ptr<LabelExpression>> operands_;
};

using LabelExpressionPtr = std::shared_ptr<LabelExpression>;

/// Repetition bounds of a quantified edge or parenthesized path. '*' is
/// {0, unbounded}, '+' is {1, unbounded}, '{n}' is {n, n} and '{m,n}' is
/// {m, n}, where an omitted lower bound is 0.
struct GraphQuantifier {
  int64_t lower{0};

  /// Maximum number of repetitions. Unset means unbounded.
  std::optional<int64_t> upper;

  bool operator==(const GraphQuantifier& other) const {
    return lower == other.lower && upper == other.upper;
  }

  size_t hash() const;
};

/// Restriction on the paths a pattern matches. kWalk allows repeated nodes
/// and edges, kTrail forbids repeated edges, kAcyclic forbids repeated nodes,
/// and kSimple forbids repeated nodes except that the first and last may be
/// the same.
enum class PathMode { kWalk, kTrail, kAcyclic, kSimple };

AXIOM_DECLARE_ENUM_NAME(PathMode);

/// Selection of paths per pair of endpoints, at the head of a path pattern.
struct PathSelector {
  enum class Kind {
    /// ALL: every path.
    kAll,
    /// ANY [k]: k arbitrary paths, 1 when 'count' is unset.
    kAny,
    /// ANY SHORTEST: one shortest path.
    kAnyShortest,
    /// ALL SHORTEST: every shortest path.
    kAllShortest,
    /// SHORTEST k: the k shortest paths.
    kShortest,
    /// SHORTEST [k] GROUP: every path in the k shortest length groups, 1 when
    /// 'count' is unset.
    kShortestGroups,
  };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Kind);

  Kind kind{Kind::kAll};

  /// Positive when set.
  std::optional<int64_t> count;

  bool operator==(const PathSelector& other) const {
    return kind == other.kind && count == other.count;
  }

  size_t hash() const;
};

/// Element of a path pattern: a node pattern, an edge pattern or a
/// parenthesized path pattern.
class PathElement : public Node {
 public:
  PathElement(NodeType type, NodeLocation location) : Node(type, location) {}
};

using PathElementPtr = std::shared_ptr<PathElement>;

/// Node pattern: (variable IS label WHERE predicate). Each part is optional.
class NodePattern : public PathElement {
 public:
  NodePattern(
      NodeLocation location,
      IdentifierPtr variable,
      LabelExpressionPtr label,
      ExpressionPtr where)
      : PathElement(NodeType::kNodePattern, location),
        variable_(std::move(variable)),
        label_(std::move(label)),
        where_(std::move(where)) {}

  const IdentifierPtr& variable() const {
    return variable_;
  }

  const LabelExpressionPtr& label() const {
    return label_;
  }

  const ExpressionPtr& where() const {
    return where_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  IdentifierPtr variable_;
  LabelExpressionPtr label_;
  ExpressionPtr where_;
};

/// Edge pattern: -[variable IS label WHERE predicate]-> and its left and
/// any-direction forms, or the abbreviations ->, <- and -, which have no
/// variable, label or predicate. An optional quantifier repeats the edge.
class EdgePattern : public PathElement {
 public:
  enum class Direction { kRight, kLeft, kAnyDirection };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Direction);

  EdgePattern(
      NodeLocation location,
      Direction direction,
      IdentifierPtr variable,
      LabelExpressionPtr label,
      ExpressionPtr where,
      std::optional<GraphQuantifier> quantifier)
      : PathElement(NodeType::kEdgePattern, location),
        direction_(direction),
        variable_(std::move(variable)),
        label_(std::move(label)),
        where_(std::move(where)),
        quantifier_(quantifier) {}

  Direction direction() const {
    return direction_;
  }

  const IdentifierPtr& variable() const {
    return variable_;
  }

  const LabelExpressionPtr& label() const {
    return label_;
  }

  const ExpressionPtr& where() const {
    return where_;
  }

  const std::optional<GraphQuantifier>& quantifier() const {
    return quantifier_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  Direction direction_;
  IdentifierPtr variable_;
  LabelExpressionPtr label_;
  ExpressionPtr where_;
  std::optional<GraphQuantifier> quantifier_;
};

/// Parenthesized path pattern: (variable = mode elements WHERE predicate),
/// followed by an optional quantifier or '?'. Variables under a quantifier
/// bind once per repetition; variables under '?' bind to one element or to
/// none.
///
/// Invariants:
/// - 'elements' is not empty.
/// - 'quantifier' and 'optional' are not both set.
class ParenthesizedPathPattern : public PathElement {
 public:
  ParenthesizedPathPattern(
      NodeLocation location,
      IdentifierPtr variable,
      std::optional<PathMode> mode,
      std::vector<PathElementPtr> elements,
      ExpressionPtr where,
      std::optional<GraphQuantifier> quantifier,
      bool optional);

  /// Subpath variable.
  const IdentifierPtr& variable() const {
    return variable_;
  }

  const std::optional<PathMode>& mode() const {
    return mode_;
  }

  const std::vector<PathElementPtr>& elements() const {
    return elements_;
  }

  const ExpressionPtr& where() const {
    return where_;
  }

  const std::optional<GraphQuantifier>& quantifier() const {
    return quantifier_;
  }

  /// True for a subpath followed by '?'.
  bool isOptional() const {
    return optional_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  IdentifierPtr variable_;
  std::optional<PathMode> mode_;
  std::vector<PathElementPtr> elements_;
  ExpressionPtr where_;
  std::optional<GraphQuantifier> quantifier_;
  bool optional_;
};

/// Path pattern: variable = selector mode elements. The variable, selector
/// and mode are optional.
///
/// Elements need not alternate between node and edge patterns. Adjacent node
/// patterns bind the same node, as when a quantified subpath that starts and
/// ends with a node repeats. An edge pattern with no node pattern next to it
/// has an implicit node pattern with no variable, label or predicate there.
///
/// Invariants:
/// - 'elements' is not empty.
class PathPattern : public Node {
 public:
  PathPattern(
      NodeLocation location,
      IdentifierPtr variable,
      std::optional<PathSelector> selector,
      std::optional<PathMode> mode,
      std::vector<PathElementPtr> elements);

  /// Path variable.
  const IdentifierPtr& variable() const {
    return variable_;
  }

  const std::optional<PathSelector>& selector() const {
    return selector_;
  }

  const std::optional<PathMode>& mode() const {
    return mode_;
  }

  const std::vector<PathElementPtr>& elements() const {
    return elements_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  IdentifierPtr variable_;
  std::optional<PathSelector> selector_;
  std::optional<PathMode> mode_;
  std::vector<PathElementPtr> elements_;
};

using PathPatternPtr = std::shared_ptr<PathPattern>;

/// GRAPH_TABLE (graph MATCH paths WHERE predicate COLUMNS (...)): matches one
/// or more path patterns against a property graph and returns one row per
/// match, with one column per COLUMNS entry. 'where' is optional.
///
/// Invariants:
/// - 'graph' is set.
/// - 'paths' is not empty.
/// - 'columns' is not empty.
class GraphTable : public Relation {
 public:
  GraphTable(
      NodeLocation location,
      std::shared_ptr<QualifiedName> graph,
      std::vector<PathPatternPtr> paths,
      ExpressionPtr where,
      std::vector<std::shared_ptr<SingleColumn>> columns);

  /// Name of the property graph.
  const std::shared_ptr<QualifiedName>& graph() const {
    return graph_;
  }

  const std::vector<PathPatternPtr>& paths() const {
    return paths_;
  }

  /// Predicate of MATCH ... WHERE.
  const ExpressionPtr& where() const {
    return where_;
  }

  const std::vector<std::shared_ptr<SingleColumn>>& columns() const {
    return columns_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  std::shared_ptr<QualifiedName> graph_;
  std::vector<PathPatternPtr> paths_;
  ExpressionPtr where_;
  std::vector<std::shared_ptr<SingleColumn>> columns_;
};

/// Property of a graph label: an expression over the element table's columns
/// and its name. 'name' is unset for a plain column reference, whose name is
/// the column's.
struct GraphProperty {
  ExpressionPtr expression;
  IdentifierPtr name;

  bool operator==(const GraphProperty& other) const {
    return Node::deepEqual(expression, other.expression) &&
        Node::deepEqual(name, other.name);
  }

  size_t hash() const {
    return folly::hash::hash_combine(
        Node::deepHash(expression), Node::deepHash(name));
  }
};

/// Label of a graph element table with its properties. 'name' is unset for
/// the default label, named after the table. 'properties' is unset when the
/// label exposes all columns.
struct GraphLabel {
  IdentifierPtr name;
  std::optional<std::vector<GraphProperty>> properties;

  bool operator==(const GraphLabel& other) const;

  size_t hash() const;
};

/// Endpoint of an edge table: SOURCE or DESTINATION KEY (keyColumns)
/// REFERENCES vertexTable (referencedColumns).
struct EdgeEndpoint {
  std::vector<IdentifierPtr> keyColumns;

  /// Name or alias of the vertex table.
  IdentifierPtr vertexTable;

  std::vector<IdentifierPtr> referencedColumns;

  bool operator==(const EdgeEndpoint& other) const {
    return Node::deepEqualAll(keyColumns, other.keyColumns) &&
        Node::deepEqual(vertexTable, other.vertexTable) &&
        Node::deepEqualAll(referencedColumns, other.referencedColumns);
  }

  size_t hash() const;
};

/// Vertex or edge table of a graph definition. An edge table has a source and
/// a destination; a vertex table has neither. An empty 'labels' means one
/// default label exposing all columns.
///
/// Invariants:
/// - 'table' is set.
/// - 'keyColumns' is not empty.
/// - 'source' and 'destination' are both set or both unset.
class GraphElementTable : public Node {
 public:
  GraphElementTable(
      NodeLocation location,
      std::shared_ptr<QualifiedName> table,
      IdentifierPtr alias,
      std::vector<IdentifierPtr> keyColumns,
      std::optional<EdgeEndpoint> source,
      std::optional<EdgeEndpoint> destination,
      std::vector<GraphLabel> labels);

  const std::shared_ptr<QualifiedName>& table() const {
    return table_;
  }

  const IdentifierPtr& alias() const {
    return alias_;
  }

  const std::vector<IdentifierPtr>& keyColumns() const {
    return keyColumns_;
  }

  const std::optional<EdgeEndpoint>& source() const {
    return source_;
  }

  const std::optional<EdgeEndpoint>& destination() const {
    return destination_;
  }

  bool isEdge() const {
    return source_.has_value();
  }

  const std::vector<GraphLabel>& labels() const {
    return labels_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  std::shared_ptr<QualifiedName> table_;
  IdentifierPtr alias_;
  std::vector<IdentifierPtr> keyColumns_;
  std::optional<EdgeEndpoint> source_;
  std::optional<EdgeEndpoint> destination_;
  std::vector<GraphLabel> labels_;
};

using GraphElementTablePtr = std::shared_ptr<GraphElementTable>;

/// Query-scoped graph definition: WITH GRAPH name AS (VERTEX TABLES (...)
/// EDGE TABLES (...)).
///
/// Invariants:
/// - 'name' is set.
/// - 'vertexTables' is not empty; 'edgeTables' may be.
class WithGraph : public Node {
 public:
  WithGraph(
      NodeLocation location,
      IdentifierPtr name,
      std::vector<GraphElementTablePtr> vertexTables,
      std::vector<GraphElementTablePtr> edgeTables);

  const IdentifierPtr& name() const {
    return name_;
  }

  const std::vector<GraphElementTablePtr>& vertexTables() const {
    return vertexTables_;
  }

  const std::vector<GraphElementTablePtr>& edgeTables() const {
    return edgeTables_;
  }

  void accept(AstVisitor* visitor) override;

  size_t hash() const override;

 protected:
  bool equals(const Node& other) const override;

 private:
  IdentifierPtr name_;
  std::vector<GraphElementTablePtr> vertexTables_;
  std::vector<GraphElementTablePtr> edgeTables_;
};

} // namespace axiom::sql::presto

AXIOM_ENUM_FORMATTER(axiom::sql::presto::PathMode);
AXIOM_EMBEDDED_ENUM_FORMATTER(
    axiom::sql::presto::LabelExpression,
    LabelExpression::Kind);
AXIOM_EMBEDDED_ENUM_FORMATTER(
    axiom::sql::presto::EdgePattern,
    EdgePattern::Direction);
AXIOM_EMBEDDED_ENUM_FORMATTER(
    axiom::sql::presto::PathSelector,
    PathSelector::Kind);
