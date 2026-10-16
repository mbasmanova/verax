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

#include <folly/Function.h>
#include <folly/container/F14Set.h>

#include "axiom/common/Enums.h"
#include "axiom/logical_plan/Expr.h"
#include "axiom/logical_plan/PropertyGraph.h"

/// Path patterns matched by GraphMatchNode.
///
///   (a IS A WHERE a.x = 1) -[e IS B]->{1,3} (b)
///
/// is a path pattern of three terms: a vertex pattern, a repeated edge
/// pattern and a vertex pattern. A match is a path in the graph whose vertices
/// and edges satisfy the terms in order.
///
/// A predicate reads properties of the vertices and edges that patterns bind
/// through the pattern names: it reads input 'a' of type ROW(x BIGINT) and
/// dereferences field x. The ROW type lists the properties the predicate
/// reads.
namespace facebook::axiom::logical_plan {

class GraphLabelExpression;
using GraphLabelExpressionPtr = std::shared_ptr<const GraphLabelExpression>;

/// Label expression of a vertex or edge pattern. A label is the name of a
/// vertex or edge of the graph, and an element table has the labels of the
/// vertices or edges it backs. Written A, %, !A, A & B or A | B.
class GraphLabelExpression {
 public:
  enum class Kind { kName, kWildcard, kNegation, kConjunction, kDisjunction };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Kind);

  virtual ~GraphLabelExpression() = default;

  Kind kind() const {
    return kind_;
  }

  /// Returns true if an element with labels 'labels' matches.
  virtual bool matches(const std::vector<std::string>& labels) const = 0;

  /// Calls 'visit' once for each occurrence of a label name in the
  /// expression. For example, calls it with A, B and C for !A | (B & C), with
  /// A twice for A | !A, and with A only for A | %; a wildcard contains no
  /// name.
  virtual void forEachName(
      folly::FunctionRef<void(std::string_view)> visit) const = 0;

  virtual std::string toString() const = 0;

  bool operator==(const GraphLabelExpression& other) const;

  virtual folly::dynamic serialize() const;

  static GraphLabelExpressionPtr create(const folly::dynamic& obj);

 protected:
  explicit GraphLabelExpression(Kind kind) : kind_{kind} {}

  // Returns true if 'other', of the same kind, is equal.
  virtual bool equals(const GraphLabelExpression& other) const = 0;

 private:
  const Kind kind_;
};

/// Label 'name': matches elements that have it.
class GraphLabelName final : public GraphLabelExpression {
 public:
  explicit GraphLabelName(std::string name);

  const std::string& name() const {
    return name_;
  }

  bool matches(const std::vector<std::string>& labels) const override;

  void forEachName(
      folly::FunctionRef<void(std::string_view)> visit) const override;

  std::string toString() const override;

  folly::dynamic serialize() const override;

 private:
  bool equals(const GraphLabelExpression& other) const override;

  const std::string name_;
};

/// Any label ('%'): matches every element.
class GraphLabelWildcard final : public GraphLabelExpression {
 public:
  GraphLabelWildcard() : GraphLabelExpression{Kind::kWildcard} {}

  bool matches(const std::vector<std::string>& labels) const override;

  void forEachName(
      folly::FunctionRef<void(std::string_view)> visit) const override;

  std::string toString() const override;

 private:
  bool equals(const GraphLabelExpression& other) const override;
};

/// Negation ('!'): matches elements its operand does not match.
class GraphLabelNegation final : public GraphLabelExpression {
 public:
  explicit GraphLabelNegation(GraphLabelExpressionPtr operand);

  const GraphLabelExpressionPtr& operand() const {
    return operand_;
  }

  bool matches(const std::vector<std::string>& labels) const override;

  void forEachName(
      folly::FunctionRef<void(std::string_view)> visit) const override;

  std::string toString() const override;

  folly::dynamic serialize() const override;

 private:
  bool equals(const GraphLabelExpression& other) const override;

  const GraphLabelExpressionPtr operand_;
};

/// Conjunction ('&') of two or more operands: matches elements every operand
/// matches.
class GraphLabelConjunction final : public GraphLabelExpression {
 public:
  explicit GraphLabelConjunction(std::vector<GraphLabelExpressionPtr> operands);

  const std::vector<GraphLabelExpressionPtr>& operands() const {
    return operands_;
  }

  bool matches(const std::vector<std::string>& labels) const override;

  void forEachName(
      folly::FunctionRef<void(std::string_view)> visit) const override;

  std::string toString() const override;

  folly::dynamic serialize() const override;

 private:
  bool equals(const GraphLabelExpression& other) const override;

  const std::vector<GraphLabelExpressionPtr> operands_;
};

/// Disjunction ('|') of two or more operands: matches elements any operand
/// matches.
class GraphLabelDisjunction final : public GraphLabelExpression {
 public:
  explicit GraphLabelDisjunction(std::vector<GraphLabelExpressionPtr> operands);

  const std::vector<GraphLabelExpressionPtr>& operands() const {
    return operands_;
  }

  bool matches(const std::vector<std::string>& labels) const override;

  void forEachName(
      folly::FunctionRef<void(std::string_view)> visit) const override;

  std::string toString() const override;

  folly::dynamic serialize() const override;

 private:
  bool equals(const GraphLabelExpression& other) const override;

  const std::vector<GraphLabelExpressionPtr> operands_;
};

/// How many times an edge or subpath repeats: {min,max}. An unset 'max' means
/// no limit.
struct GraphRepetition {
  int64_t min{0};
  std::optional<int64_t> max;

  bool operator==(const GraphRepetition& other) const = default;
};

/// Restriction on the paths a pattern matches.
enum class GraphPathMode {
  /// Allows repeated vertices and edges.
  kWalk,
  /// Forbids repeated edges.
  kTrail,
  /// Forbids repeated vertices.
  kAcyclic,
  /// Forbids repeated vertices, except that the first and last may be the same.
  kSimple,
};

AXIOM_DECLARE_ENUM_NAME(GraphPathMode);

/// Selection of paths per pair of endpoints. 'count' is set only for kAny,
/// kShortest and kShortestGroups, where it is positive; kShortest requires
/// it. GraphMatchNode checks this.
struct GraphPathSelector {
  enum class Kind {
    /// Every path.
    kAll,
    /// 'count' arbitrary paths, 1 if unset.
    kAny,
    /// One shortest path.
    kAnyShortest,
    /// Every shortest path.
    kAllShortest,
    /// The 'count' shortest paths.
    kShortest,
    /// Every path in the 'count' shortest length groups, 1 if unset.
    kShortestGroups,
  };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Kind);

  Kind kind{Kind::kAll};
  std::optional<int64_t> count;

  static GraphPathSelector all() {
    return {.kind = Kind::kAll};
  }

  static GraphPathSelector any(std::optional<int64_t> count) {
    return {.kind = Kind::kAny, .count = count};
  }

  static GraphPathSelector anyShortest() {
    return {.kind = Kind::kAnyShortest};
  }

  static GraphPathSelector allShortest() {
    return {.kind = Kind::kAllShortest};
  }

  static GraphPathSelector shortest(int64_t count) {
    return {.kind = Kind::kShortest, .count = count};
  }

  static GraphPathSelector shortestGroups(std::optional<int64_t> count) {
    return {.kind = Kind::kShortestGroups, .count = count};
  }

  bool operator==(const GraphPathSelector& other) const = default;
};

class GraphPatternTerm;
using GraphPatternTermPtr = std::shared_ptr<const GraphPatternTerm>;

/// Term of a path pattern: a vertex pattern, an edge pattern or a subpath.
/// Each term may have a name and a predicate. The predicate is a BOOLEAN
/// condition the match must satisfy. Its inputs are names of vertex and edge
/// patterns, each of ROW type with the properties the predicate reads.
class GraphPatternTerm {
 public:
  enum class Kind { kVertex, kEdge, kSubpath };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Kind);

  virtual ~GraphPatternTerm() = default;

  Kind kind() const {
    return kind_;
  }

  bool is(Kind kind) const {
    return kind_ == kind;
  }

  /// Name the term gives to the vertex, edge or subpath it matches, like a
  /// table alias; 'a' in (a IS Person). Every vertex or edge pattern with the
  /// same name binds the same element. Empty if the term has no name.
  const std::string& name() const {
    return name_;
  }

  /// Null if the term has no predicate.
  const ExprPtr& predicate() const {
    return predicate_;
  }

  /// How many times the term repeats. Unset for a vertex pattern, and for an
  /// edge pattern or a subpath that matches once.
  virtual const std::optional<GraphRepetition>& repetition() const;

  /// Adds the names of the vertex and edge patterns in 'terms', including
  /// those inside subpaths, to 'names'.
  static void collectElementNames(
      const std::vector<GraphPatternTermPtr>& terms,
      folly::F14FastSet<std::string>& names);

  /// Caller must ensure this kind is correct.
  template <typename T>
  const T* as() const {
    static_assert(std::is_base_of_v<GraphPatternTerm, T>);
    VELOX_DCHECK_NOT_NULL(dynamic_cast<const T*>(this));
    return static_cast<const T*>(this);
  }

  bool operator==(const GraphPatternTerm& other) const;

  virtual folly::dynamic serialize() const;

  static GraphPatternTermPtr create(const folly::dynamic& obj, void* context);

 protected:
  GraphPatternTerm(Kind kind, std::string name, ExprPtr predicate);

  // Returns true if 'other', of the same kind, is equal apart from 'name' and
  // 'predicate'.
  virtual bool equals(const GraphPatternTerm& other) const = 0;

 private:
  const Kind kind_;
  const std::string name_;
  const ExprPtr predicate_;
};

/// Vertex or edge pattern: matches one element of the tables its label
/// expression selects.
///
/// Invariants:
/// - 'predicate' reads only this pattern's name, which is not empty if
///   'predicate' is set.
class GraphElementPattern : public GraphPatternTerm {
 public:
  /// Null matches any label.
  const GraphLabelExpressionPtr& label() const {
    return label_;
  }

  /// Returns the tables of 'graph' the pattern can match: the vertex tables
  /// for a vertex pattern, or the edge tables for an edge pattern, whose names
  /// satisfy its label.
  std::vector<const PropertyGraph::ElementTable*> matchingTables(
      const PropertyGraph& graph) const;

  folly::dynamic serialize() const override;

 protected:
  GraphElementPattern(
      Kind kind,
      std::string name,
      GraphLabelExpressionPtr label,
      ExprPtr predicate);

  bool equals(const GraphPatternTerm& other) const override;

 private:
  const GraphLabelExpressionPtr label_;
};

/// Vertex pattern: (name IS label WHERE predicate).
class GraphVertexPattern final : public GraphElementPattern {
 public:
  GraphVertexPattern(
      std::string name,
      GraphLabelExpressionPtr label,
      ExprPtr predicate);
};

/// Edge pattern: -[name IS label WHERE predicate]->{repetition}.
///
/// Invariants:
/// - A repetition's 'min' is not negative and does not exceed its 'max'.
class GraphEdgePattern final : public GraphElementPattern {
 public:
  enum class Direction {
    /// From the vertex on the left to the vertex on the right: -[]->.
    kRight,
    /// From the vertex on the right to the vertex on the left: <-[]-.
    kLeft,
    /// Either way: -[]-.
    kAnyDirection,
  };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Direction);

  GraphEdgePattern(
      std::string name,
      GraphLabelExpressionPtr label,
      ExprPtr predicate,
      Direction direction,
      std::optional<GraphRepetition> repetition);

  Direction direction() const {
    return direction_;
  }

  const std::optional<GraphRepetition>& repetition() const override {
    return repetition_;
  }

  folly::dynamic serialize() const override;

 private:
  bool equals(const GraphPatternTerm& other) const override;

  const Direction direction_;
  const std::optional<GraphRepetition> repetition_;
};

/// Subpath: (name = mode terms WHERE predicate){repetition}, or with '?' in
/// place of the repetition.
///
/// Invariants:
/// - 'terms' is not empty.
/// - 'predicate' reads only names of the vertex and edge patterns inside the
///   subpath.
/// - 'repetition' and 'optional' are not both set.
/// - A repetition's 'min' is not negative and does not exceed its 'max'.
/// - A repeated subpath contains no repeated term.
class GraphSubpathPattern final : public GraphPatternTerm {
 public:
  GraphSubpathPattern(
      std::string name,
      GraphPathMode mode,
      std::vector<GraphPatternTermPtr> terms,
      ExprPtr predicate,
      std::optional<GraphRepetition> repetition,
      bool optional);

  GraphPathMode mode() const {
    return mode_;
  }

  const std::vector<GraphPatternTermPtr>& terms() const {
    return terms_;
  }

  const std::optional<GraphRepetition>& repetition() const override {
    return repetition_;
  }

  /// True if the subpath matches once or not at all ('?').
  bool optional() const {
    return optional_;
  }

  folly::dynamic serialize() const override;

 private:
  bool equals(const GraphPatternTerm& other) const override;

  const GraphPathMode mode_;
  const std::vector<GraphPatternTermPtr> terms_;
  const std::optional<GraphRepetition> repetition_;
  const bool optional_;
};

/// Path pattern: name = selector mode terms. A path written without a
/// selector or mode has ALL and WALK.
struct GraphPathPattern {
  /// Name the pattern gives to the path it matches; 'p' in p = (a)-[e]->(b).
  /// Empty if the pattern has no name.
  std::string name;

  GraphPathSelector selector;
  GraphPathMode mode{GraphPathMode::kWalk};
  std::vector<GraphPatternTermPtr> terms;

  bool operator==(const GraphPathPattern& other) const;

  folly::dynamic serialize() const;

  static GraphPathPattern create(const folly::dynamic& obj, void* context);
};

} // namespace facebook::axiom::logical_plan

AXIOM_ENUM_FORMATTER(facebook::axiom::logical_plan::GraphPathMode);
