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

#include "axiom/sql/presto/ast/AstGraph.h"
#include "axiom/sql/presto/ast/AstVisitor.h"

namespace axiom::sql::presto {

namespace {

const auto& labelExpressionKindNames() {
  static const folly::F14FastMap<LabelExpression::Kind, std::string_view>
      kNames = {
          {LabelExpression::Kind::kName, "NAME"},
          {LabelExpression::Kind::kWildcard, "WILDCARD"},
          {LabelExpression::Kind::kNegation, "NEGATION"},
          {LabelExpression::Kind::kConjunction, "CONJUNCTION"},
          {LabelExpression::Kind::kDisjunction, "DISJUNCTION"},
      };
  return kNames;
}

const auto& pathModeNames() {
  static const folly::F14FastMap<PathMode, std::string_view> kNames = {
      {PathMode::kWalk, "WALK"},
      {PathMode::kTrail, "TRAIL"},
      {PathMode::kAcyclic, "ACYCLIC"},
      {PathMode::kSimple, "SIMPLE"},
  };
  return kNames;
}

const auto& pathSelectorKindNames() {
  static const folly::F14FastMap<PathSelector::Kind, std::string_view> kNames =
      {
          {PathSelector::Kind::kAll, "ALL"},
          {PathSelector::Kind::kAny, "ANY"},
          {PathSelector::Kind::kAnyShortest, "ANY SHORTEST"},
          {PathSelector::Kind::kAllShortest, "ALL SHORTEST"},
          {PathSelector::Kind::kShortest, "SHORTEST"},
          {PathSelector::Kind::kShortestGroups, "SHORTEST GROUP"},
      };
  return kNames;
}

const auto& edgeDirectionNames() {
  static const folly::F14FastMap<EdgePattern::Direction, std::string_view>
      kNames = {
          {EdgePattern::Direction::kRight, "RIGHT"},
          {EdgePattern::Direction::kLeft, "LEFT"},
          {EdgePattern::Direction::kAnyDirection, "ANY_DIRECTION"},
      };
  return kNames;
}

template <typename T>
size_t hashOptional(const std::optional<T>& value) {
  return value.has_value() ? value->hash() : 0;
}

size_t hashOptionalCount(const std::optional<int64_t>& count) {
  return folly::hash::hash_combine(count.has_value(), count.value_or(0));
}

template <typename T>
size_t hashOptionalEnum(const std::optional<T>& value) {
  return value.has_value()
      ? std::hash<int>{}(static_cast<int>(value.value())) + 1
      : 0;
}

template <typename T>
size_t hashAll(const std::vector<T>& values) {
  size_t hash = values.size();
  for (const auto& value : values) {
    hash = folly::hash::hash_combine(hash, value.hash());
  }
  return hash;
}

} // namespace

AXIOM_DEFINE_EMBEDDED_ENUM_NAME(
    LabelExpression,
    Kind,
    labelExpressionKindNames);
AXIOM_DEFINE_ENUM_NAME(PathMode, pathModeNames);
AXIOM_DEFINE_EMBEDDED_ENUM_NAME(PathSelector, Kind, pathSelectorKindNames);
AXIOM_DEFINE_EMBEDDED_ENUM_NAME(EdgePattern, Direction, edgeDirectionNames);

LabelExpression::LabelExpression(
    NodeLocation location,
    Kind kind,
    IdentifierPtr name,
    std::vector<std::shared_ptr<LabelExpression>> operands)
    : Node(NodeType::kLabelExpression, location),
      kind_(kind),
      name_(std::move(name)),
      operands_(std::move(operands)) {
  VELOX_CHECK_EQ(kind_ == Kind::kName, name_ != nullptr);
  switch (kind_) {
    case Kind::kName:
    case Kind::kWildcard:
      VELOX_CHECK(operands_.empty());
      break;
    case Kind::kNegation:
      VELOX_CHECK_EQ(1, operands_.size());
      break;
    case Kind::kConjunction:
    case Kind::kDisjunction:
      VELOX_CHECK_GE(operands_.size(), 2);
      break;
  }
}

void LabelExpression::accept(AstVisitor* visitor) {
  visitor->visitLabelExpression(this);
}

size_t LabelExpression::hash() const {
  return folly::hash::hash_combine(
      std::hash<int>{}(static_cast<int>(kind_)),
      Node::deepHash(name_),
      Node::deepHashAll(operands_));
}

bool LabelExpression::equals(const Node& other) const {
  const auto& o = *other.as<LabelExpression>();
  return kind_ == o.kind_ && Node::deepEqual(name_, o.name_) &&
      Node::deepEqualAll(operands_, o.operands_);
}

size_t GraphQuantifier::hash() const {
  return folly::hash::hash_combine(lower, hashOptionalCount(upper));
}

size_t PathSelector::hash() const {
  return folly::hash::hash_combine(
      static_cast<int>(kind), hashOptionalCount(count));
}

void NodePattern::accept(AstVisitor* visitor) {
  visitor->visitNodePattern(this);
}

size_t NodePattern::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(variable_),
      Node::deepHash(label_),
      Node::deepHash(where_));
}

bool NodePattern::equals(const Node& other) const {
  const auto& o = *other.as<NodePattern>();
  return Node::deepEqual(variable_, o.variable_) &&
      Node::deepEqual(label_, o.label_) && Node::deepEqual(where_, o.where_);
}

void EdgePattern::accept(AstVisitor* visitor) {
  visitor->visitEdgePattern(this);
}

size_t EdgePattern::hash() const {
  return folly::hash::hash_combine(
      static_cast<int>(direction_),
      Node::deepHash(variable_),
      Node::deepHash(label_),
      Node::deepHash(where_),
      hashOptional(quantifier_));
}

bool EdgePattern::equals(const Node& other) const {
  const auto& o = *other.as<EdgePattern>();
  return direction_ == o.direction_ &&
      Node::deepEqual(variable_, o.variable_) &&
      Node::deepEqual(label_, o.label_) && Node::deepEqual(where_, o.where_) &&
      quantifier_ == o.quantifier_;
}

ParenthesizedPathPattern::ParenthesizedPathPattern(
    NodeLocation location,
    IdentifierPtr variable,
    std::optional<PathMode> mode,
    std::vector<PathElementPtr> elements,
    ExpressionPtr where,
    std::optional<GraphQuantifier> quantifier,
    bool optional)
    : PathElement(NodeType::kParenthesizedPathPattern, location),
      variable_(std::move(variable)),
      mode_(mode),
      elements_(std::move(elements)),
      where_(std::move(where)),
      quantifier_(quantifier),
      optional_(optional) {
  VELOX_CHECK(!elements_.empty());
  VELOX_CHECK(!(quantifier_.has_value() && optional_));
}

void ParenthesizedPathPattern::accept(AstVisitor* visitor) {
  visitor->visitParenthesizedPathPattern(this);
}

size_t ParenthesizedPathPattern::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(variable_),
      hashOptionalEnum(mode_),
      Node::deepHashAll(elements_),
      Node::deepHash(where_),
      hashOptional(quantifier_),
      optional_);
}

bool ParenthesizedPathPattern::equals(const Node& other) const {
  const auto& o = *other.as<ParenthesizedPathPattern>();
  return Node::deepEqual(variable_, o.variable_) && mode_ == o.mode_ &&
      Node::deepEqualAll(elements_, o.elements_) &&
      Node::deepEqual(where_, o.where_) && quantifier_ == o.quantifier_ &&
      optional_ == o.optional_;
}

PathPattern::PathPattern(
    NodeLocation location,
    IdentifierPtr variable,
    std::optional<PathSelector> selector,
    std::optional<PathMode> mode,
    std::vector<PathElementPtr> elements)
    : Node(NodeType::kPathPattern, location),
      variable_(std::move(variable)),
      selector_(selector),
      mode_(mode),
      elements_(std::move(elements)) {
  VELOX_CHECK(!elements_.empty());
}

void PathPattern::accept(AstVisitor* visitor) {
  visitor->visitPathPattern(this);
}

size_t PathPattern::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(variable_),
      hashOptional(selector_),
      hashOptionalEnum(mode_),
      Node::deepHashAll(elements_));
}

bool PathPattern::equals(const Node& other) const {
  const auto& o = *other.as<PathPattern>();
  return Node::deepEqual(variable_, o.variable_) && selector_ == o.selector_ &&
      mode_ == o.mode_ && Node::deepEqualAll(elements_, o.elements_);
}

GraphTable::GraphTable(
    NodeLocation location,
    std::shared_ptr<QualifiedName> graph,
    std::vector<PathPatternPtr> paths,
    ExpressionPtr where,
    std::vector<std::shared_ptr<SingleColumn>> columns)
    : Relation(NodeType::kGraphTable, location),
      graph_(std::move(graph)),
      paths_(std::move(paths)),
      where_(std::move(where)),
      columns_(std::move(columns)) {
  VELOX_CHECK_NOT_NULL(graph_);
  VELOX_CHECK(!paths_.empty());
  VELOX_CHECK(!columns_.empty());
}

void GraphTable::accept(AstVisitor* visitor) {
  visitor->visitGraphTable(this);
}

size_t GraphTable::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(graph_),
      Node::deepHashAll(paths_),
      Node::deepHash(where_),
      Node::deepHashAll(columns_));
}

bool GraphTable::equals(const Node& other) const {
  const auto& o = *other.as<GraphTable>();
  return Node::deepEqual(graph_, o.graph_) &&
      Node::deepEqualAll(paths_, o.paths_) &&
      Node::deepEqual(where_, o.where_) &&
      Node::deepEqualAll(columns_, o.columns_);
}

bool GraphLabel::operator==(const GraphLabel& other) const {
  return Node::deepEqual(name, other.name) && properties == other.properties;
}

size_t GraphLabel::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(name),
      properties.has_value() ? hashAll(properties.value()) + 1 : 0);
}

size_t EdgeEndpoint::hash() const {
  return folly::hash::hash_combine(
      Node::deepHashAll(keyColumns),
      Node::deepHash(vertexTable),
      Node::deepHashAll(referencedColumns));
}

GraphElementTable::GraphElementTable(
    NodeLocation location,
    std::shared_ptr<QualifiedName> table,
    IdentifierPtr alias,
    std::vector<IdentifierPtr> keyColumns,
    std::optional<EdgeEndpoint> source,
    std::optional<EdgeEndpoint> destination,
    std::vector<GraphLabel> labels)
    : Node(NodeType::kGraphElementTable, location),
      table_(std::move(table)),
      alias_(std::move(alias)),
      keyColumns_(std::move(keyColumns)),
      source_(std::move(source)),
      destination_(std::move(destination)),
      labels_(std::move(labels)) {
  VELOX_CHECK_NOT_NULL(table_);
  VELOX_CHECK(!keyColumns_.empty());
  VELOX_CHECK_EQ(source_.has_value(), destination_.has_value());
}

void GraphElementTable::accept(AstVisitor* visitor) {
  visitor->visitGraphElementTable(this);
}

size_t GraphElementTable::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(table_),
      Node::deepHash(alias_),
      Node::deepHashAll(keyColumns_),
      hashOptional(source_),
      hashOptional(destination_),
      hashAll(labels_));
}

bool GraphElementTable::equals(const Node& other) const {
  const auto& o = *other.as<GraphElementTable>();
  return Node::deepEqual(table_, o.table_) &&
      Node::deepEqual(alias_, o.alias_) &&
      Node::deepEqualAll(keyColumns_, o.keyColumns_) && source_ == o.source_ &&
      destination_ == o.destination_ && labels_ == o.labels_;
}

WithGraph::WithGraph(
    NodeLocation location,
    IdentifierPtr name,
    std::vector<GraphElementTablePtr> vertexTables,
    std::vector<GraphElementTablePtr> edgeTables)
    : Node(NodeType::kWithGraph, location),
      name_(std::move(name)),
      vertexTables_(std::move(vertexTables)),
      edgeTables_(std::move(edgeTables)) {
  VELOX_CHECK_NOT_NULL(name_);
  VELOX_CHECK(!vertexTables_.empty());
}

void WithGraph::accept(AstVisitor* visitor) {
  visitor->visitWithGraph(this);
}

size_t WithGraph::hash() const {
  return folly::hash::hash_combine(
      Node::deepHash(name_),
      Node::deepHashAll(vertexTables_),
      Node::deepHashAll(edgeTables_));
}

bool WithGraph::equals(const Node& other) const {
  const auto& o = *other.as<WithGraph>();
  return Node::deepEqual(name_, o.name_) &&
      Node::deepEqualAll(vertexTables_, o.vertexTables_) &&
      Node::deepEqualAll(edgeTables_, o.edgeTables_);
}

} // namespace axiom::sql::presto
