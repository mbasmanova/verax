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

#include "axiom/logical_plan/GraphPattern.h"

#include <fmt/ranges.h>
#include <folly/container/F14Map.h>
#include <folly/container/F14Set.h>

namespace facebook::axiom::logical_plan {

namespace {

const auto& labelExpressionKindNames() {
  static const folly::F14FastMap<GraphLabelExpression::Kind, std::string_view>
      kNames = {
          {GraphLabelExpression::Kind::kName, "NAME"},
          {GraphLabelExpression::Kind::kWildcard, "WILDCARD"},
          {GraphLabelExpression::Kind::kNegation, "NEGATION"},
          {GraphLabelExpression::Kind::kConjunction, "CONJUNCTION"},
          {GraphLabelExpression::Kind::kDisjunction, "DISJUNCTION"},
      };
  return kNames;
}

const auto& pathModeNames() {
  static const folly::F14FastMap<GraphPathMode, std::string_view> kNames = {
      {GraphPathMode::kWalk, "WALK"},
      {GraphPathMode::kTrail, "TRAIL"},
      {GraphPathMode::kAcyclic, "ACYCLIC"},
      {GraphPathMode::kSimple, "SIMPLE"},
  };
  return kNames;
}

const auto& pathSelectorKindNames() {
  static const folly::F14FastMap<GraphPathSelector::Kind, std::string_view>
      kNames = {
          {GraphPathSelector::Kind::kAll, "ALL"},
          {GraphPathSelector::Kind::kAny, "ANY"},
          {GraphPathSelector::Kind::kAnyShortest, "ANY_SHORTEST"},
          {GraphPathSelector::Kind::kAllShortest, "ALL_SHORTEST"},
          {GraphPathSelector::Kind::kShortest, "SHORTEST"},
          {GraphPathSelector::Kind::kShortestGroups, "SHORTEST_GROUPS"},
      };
  return kNames;
}

const auto& patternTermKindNames() {
  static const folly::F14FastMap<GraphPatternTerm::Kind, std::string_view>
      kNames = {
          {GraphPatternTerm::Kind::kVertex, "VERTEX"},
          {GraphPatternTerm::Kind::kEdge, "EDGE"},
          {GraphPatternTerm::Kind::kSubpath, "SUBPATH"},
      };
  return kNames;
}

const auto& edgeDirectionNames() {
  static const folly::F14FastMap<GraphEdgePattern::Direction, std::string_view>
      kNames = {
          {GraphEdgePattern::Direction::kRight, "RIGHT"},
          {GraphEdgePattern::Direction::kLeft, "LEFT"},
          {GraphEdgePattern::Direction::kAnyDirection, "ANY_DIRECTION"},
      };
  return kNames;
}

void checkOperands(const std::vector<GraphLabelExpressionPtr>& operands) {
  VELOX_USER_CHECK_GE(
      operands.size(), 2, "Label expression needs two or more operands");
  for (const auto& operand : operands) {
    VELOX_USER_CHECK_NOT_NULL(operand, "Label expression operand is null");
  }
}

void forEachOperandName(
    const std::vector<GraphLabelExpressionPtr>& operands,
    folly::FunctionRef<void(std::string_view)> visit) {
  for (const auto& operand : operands) {
    operand->forEachName(visit);
  }
}

bool equalOperands(
    const std::vector<GraphLabelExpressionPtr>& lhs,
    const std::vector<GraphLabelExpressionPtr>& rhs) {
  return std::equal(
      lhs.begin(),
      lhs.end(),
      rhs.begin(),
      rhs.end(),
      [](const auto& left, const auto& right) { return *left == *right; });
}

std::string joinOperands(
    const std::vector<GraphLabelExpressionPtr>& operands,
    std::string_view separator) {
  std::vector<std::string> texts;
  texts.reserve(operands.size());
  for (const auto& operand : operands) {
    texts.push_back(operand->toString());
  }
  return fmt::format("({})", fmt::join(texts, separator));
}

folly::dynamic serializeOperands(
    const std::vector<GraphLabelExpressionPtr>& operands) {
  folly::dynamic array = folly::dynamic::array;
  for (const auto& operand : operands) {
    array.push_back(operand->serialize());
  }
  return array;
}

std::vector<GraphLabelExpressionPtr> deserializeOperands(
    const folly::dynamic& array) {
  std::vector<GraphLabelExpressionPtr> operands;
  for (const auto& operand : array) {
    operands.push_back(GraphLabelExpression::create(operand));
  }
  return operands;
}

} // namespace

AXIOM_DEFINE_EMBEDDED_ENUM_NAME(
    GraphLabelExpression,
    Kind,
    labelExpressionKindNames);
AXIOM_DEFINE_ENUM_NAME(GraphPathMode, pathModeNames);
AXIOM_DEFINE_EMBEDDED_ENUM_NAME(GraphPathSelector, Kind, pathSelectorKindNames);
AXIOM_DEFINE_EMBEDDED_ENUM_NAME(GraphPatternTerm, Kind, patternTermKindNames);
AXIOM_DEFINE_EMBEDDED_ENUM_NAME(
    GraphEdgePattern,
    Direction,
    edgeDirectionNames);

bool GraphLabelExpression::operator==(const GraphLabelExpression& other) const {
  return kind_ == other.kind_ && equals(other);
}

folly::dynamic GraphLabelExpression::serialize() const {
  folly::dynamic obj = folly::dynamic::object;
  obj["kind"] = toName(kind_);
  return obj;
}

// static
GraphLabelExpressionPtr GraphLabelExpression::create(
    const folly::dynamic& obj) {
  switch (toKind(obj["kind"].asString())) {
    case Kind::kName:
      return std::make_shared<GraphLabelName>(obj["name"].asString());
    case Kind::kWildcard:
      return std::make_shared<GraphLabelWildcard>();
    case Kind::kNegation:
      return std::make_shared<GraphLabelNegation>(create(obj["operand"]));
    case Kind::kConjunction:
      return std::make_shared<GraphLabelConjunction>(
          deserializeOperands(obj["operands"]));
    case Kind::kDisjunction:
      return std::make_shared<GraphLabelDisjunction>(
          deserializeOperands(obj["operands"]));
  }
  VELOX_UNREACHABLE();
}

GraphLabelName::GraphLabelName(std::string name)
    : GraphLabelExpression{Kind::kName}, name_{std::move(name)} {
  VELOX_USER_CHECK(!name_.empty(), "Label name is empty");
}

bool GraphLabelName::matches(const std::vector<std::string>& labels) const {
  return std::find(labels.begin(), labels.end(), name_) != labels.end();
}

void GraphLabelName::forEachName(
    folly::FunctionRef<void(std::string_view)> visit) const {
  visit(name_);
}

std::string GraphLabelName::toString() const {
  return name_;
}

folly::dynamic GraphLabelName::serialize() const {
  auto obj = GraphLabelExpression::serialize();
  obj["name"] = name_;
  return obj;
}

bool GraphLabelName::equals(const GraphLabelExpression& other) const {
  return name_ == static_cast<const GraphLabelName&>(other).name_;
}

bool GraphLabelWildcard::matches(const std::vector<std::string>& labels) const {
  return !labels.empty();
}

void GraphLabelWildcard::forEachName(
    folly::FunctionRef<void(std::string_view)> /*visit*/) const {}

std::string GraphLabelWildcard::toString() const {
  return "%";
}

bool GraphLabelWildcard::equals(const GraphLabelExpression& /*other*/) const {
  return true;
}

GraphLabelNegation::GraphLabelNegation(GraphLabelExpressionPtr operand)
    : GraphLabelExpression{Kind::kNegation}, operand_{std::move(operand)} {
  VELOX_USER_CHECK_NOT_NULL(operand_, "Label expression operand is null");
}

bool GraphLabelNegation::matches(const std::vector<std::string>& labels) const {
  return !operand_->matches(labels);
}

void GraphLabelNegation::forEachName(
    folly::FunctionRef<void(std::string_view)> visit) const {
  operand_->forEachName(visit);
}

std::string GraphLabelNegation::toString() const {
  return fmt::format("!{}", operand_->toString());
}

folly::dynamic GraphLabelNegation::serialize() const {
  auto obj = GraphLabelExpression::serialize();
  obj["operand"] = operand_->serialize();
  return obj;
}

bool GraphLabelNegation::equals(const GraphLabelExpression& other) const {
  return *operand_ == *static_cast<const GraphLabelNegation&>(other).operand_;
}

GraphLabelConjunction::GraphLabelConjunction(
    std::vector<GraphLabelExpressionPtr> operands)
    : GraphLabelExpression{Kind::kConjunction}, operands_{std::move(operands)} {
  checkOperands(operands_);
}

bool GraphLabelConjunction::matches(
    const std::vector<std::string>& labels) const {
  return std::all_of(
      operands_.begin(), operands_.end(), [&](const auto& operand) {
        return operand->matches(labels);
      });
}

void GraphLabelConjunction::forEachName(
    folly::FunctionRef<void(std::string_view)> visit) const {
  forEachOperandName(operands_, visit);
}

std::string GraphLabelConjunction::toString() const {
  return joinOperands(operands_, " & ");
}

folly::dynamic GraphLabelConjunction::serialize() const {
  auto obj = GraphLabelExpression::serialize();
  obj["operands"] = serializeOperands(operands_);
  return obj;
}

bool GraphLabelConjunction::equals(const GraphLabelExpression& other) const {
  return equalOperands(
      operands_, static_cast<const GraphLabelConjunction&>(other).operands_);
}

GraphLabelDisjunction::GraphLabelDisjunction(
    std::vector<GraphLabelExpressionPtr> operands)
    : GraphLabelExpression{Kind::kDisjunction}, operands_{std::move(operands)} {
  checkOperands(operands_);
}

bool GraphLabelDisjunction::matches(
    const std::vector<std::string>& labels) const {
  return std::any_of(
      operands_.begin(), operands_.end(), [&](const auto& operand) {
        return operand->matches(labels);
      });
}

void GraphLabelDisjunction::forEachName(
    folly::FunctionRef<void(std::string_view)> visit) const {
  forEachOperandName(operands_, visit);
}

std::string GraphLabelDisjunction::toString() const {
  return joinOperands(operands_, " | ");
}

folly::dynamic GraphLabelDisjunction::serialize() const {
  auto obj = GraphLabelExpression::serialize();
  obj["operands"] = serializeOperands(operands_);
  return obj;
}

bool GraphLabelDisjunction::equals(const GraphLabelExpression& other) const {
  return equalOperands(
      operands_, static_cast<const GraphLabelDisjunction&>(other).operands_);
}

namespace {

bool equalNullableLabels(
    const GraphLabelExpressionPtr& lhs,
    const GraphLabelExpressionPtr& rhs) {
  if (lhs == nullptr || rhs == nullptr) {
    return lhs == rhs;
  }
  return *lhs == *rhs;
}

bool equalTerms(
    const std::vector<GraphPatternTermPtr>& lhs,
    const std::vector<GraphPatternTermPtr>& rhs) {
  return std::equal(
      lhs.begin(),
      lhs.end(),
      rhs.begin(),
      rhs.end(),
      [](const auto& left, const auto& right) { return *left == *right; });
}

void checkRepetition(const std::optional<GraphRepetition>& repetition) {
  if (!repetition.has_value()) {
    return;
  }
  VELOX_USER_CHECK_GE(repetition->min, 0, "Repetition minimum is negative");
  VELOX_USER_CHECK(
      !repetition->max.has_value() ||
          repetition->min <= repetition->max.value(),
      "Repetition minimum exceeds its maximum");
}

const std::optional<GraphRepetition>& repetitionOf(
    const GraphPatternTerm& term) {
  static const std::optional<GraphRepetition> kNone;
  switch (term.kind()) {
    case GraphPatternTerm::Kind::kVertex:
      return kNone;
    case GraphPatternTerm::Kind::kEdge:
      return term.as<GraphEdgePattern>()->repetition();
    case GraphPatternTerm::Kind::kSubpath:
      return term.as<GraphSubpathPattern>()->repetition();
  }
  VELOX_UNREACHABLE();
}

// Returns true if any term in 'terms', or inside a subpath among them, is
// repeated.
bool hasRepeatedTerm(const std::vector<GraphPatternTermPtr>& terms) {
  return std::any_of(terms.begin(), terms.end(), [](const auto& term) {
    return repetitionOf(*term).has_value() ||
        (term->isSubpath() &&
         hasRepeatedTerm(term->template as<GraphSubpathPattern>()->terms()));
  });
}

// Adds the names of the vertex and edge patterns in 'terms', including those
// inside subpaths, to 'names'.
void addElementNames(
    const std::vector<GraphPatternTermPtr>& terms,
    folly::F14FastSet<std::string>& names) {
  for (const auto& term : terms) {
    if (term->isSubpath()) {
      addElementNames(term->as<GraphSubpathPattern>()->terms(), names);
    } else if (!term->name().empty()) {
      names.insert(term->name());
    }
  }
}

// Checks that the inputs of 'predicate', if set, are ROWs named in 'names'.
void checkPredicateInputs(
    const ExprPtr& predicate,
    const folly::F14FastSet<std::string>& names) {
  if (predicate == nullptr) {
    return;
  }
  predicate->forEachInputReference([&](const InputReferenceExpr& input) {
    VELOX_USER_CHECK(
        names.contains(input.name()),
        "Pattern predicate reads a name it cannot see: {}",
        input.name());
    VELOX_USER_CHECK(
        input.type()->isRow(),
        "Pattern predicate reads a pattern name as a non-ROW: {}",
        input.name());
  });
}

folly::dynamic serializeRepetition(const GraphRepetition& repetition) {
  folly::dynamic obj = folly::dynamic::object;
  obj["min"] = repetition.min;
  if (repetition.max.has_value()) {
    obj["max"] = repetition.max.value();
  }
  return obj;
}

std::optional<GraphRepetition> deserializeRepetition(
    const folly::dynamic& obj) {
  if (!obj.count("repetition")) {
    return std::nullopt;
  }
  const auto& repetition = obj["repetition"];
  return GraphRepetition{
      .min = repetition["min"].asInt(),
      .max = repetition.count("max")
          ? std::optional<int64_t>(repetition["max"].asInt())
          : std::nullopt,
  };
}

GraphPathMode deserializeMode(const folly::dynamic& obj) {
  return GraphPathModeName::toGraphPathMode(obj["mode"].asString());
}

folly::dynamic serializeTerms(const std::vector<GraphPatternTermPtr>& terms) {
  folly::dynamic array = folly::dynamic::array;
  for (const auto& term : terms) {
    array.push_back(term->serialize());
  }
  return array;
}

std::vector<GraphPatternTermPtr> deserializeTerms(
    const folly::dynamic& array,
    void* context) {
  std::vector<GraphPatternTermPtr> terms;
  terms.reserve(array.size());
  for (const auto& term : array) {
    terms.push_back(GraphPatternTerm::create(term, context));
  }
  return terms;
}

} // namespace

GraphPatternTerm::GraphPatternTerm(
    Kind kind,
    std::string name,
    ExprPtr predicate)
    : kind_{kind}, name_{std::move(name)}, predicate_{std::move(predicate)} {
  if (predicate_ != nullptr) {
    VELOX_USER_CHECK_EQ(
        predicate_->type()->kind(),
        velox::TypeKind::BOOLEAN,
        "Pattern predicate is not BOOLEAN: {}",
        predicate_->type()->toString());
  }
}

bool GraphPatternTerm::operator==(const GraphPatternTerm& other) const {
  return kind_ == other.kind_ && name_ == other.name_ &&
      Expr::equalNullableExprs(predicate_, other.predicate_) && equals(other);
}

folly::dynamic GraphPatternTerm::serialize() const {
  folly::dynamic obj = folly::dynamic::object;
  obj["kind"] = toName(kind_);
  obj["name"] = name_;
  if (predicate_ != nullptr) {
    obj["predicate"] = predicate_->serialize();
  }
  return obj;
}

// static
GraphPatternTermPtr GraphPatternTerm::create(
    const folly::dynamic& obj,
    void* context) {
  auto name = obj["name"].asString();
  ExprPtr predicate = obj.count("predicate")
      ? velox::ISerializable::deserialize<Expr>(obj["predicate"], context)
      : nullptr;

  const auto kind = toKind(obj["kind"].asString());
  if (kind == Kind::kSubpath) {
    return std::make_shared<GraphSubpathPattern>(
        std::move(name),
        deserializeMode(obj),
        deserializeTerms(obj["terms"], context),
        std::move(predicate),
        deserializeRepetition(obj),
        obj["optional"].asBool());
  }

  GraphLabelExpressionPtr label =
      obj.count("label") ? GraphLabelExpression::create(obj["label"]) : nullptr;
  if (kind == Kind::kVertex) {
    return std::make_shared<GraphVertexPattern>(
        std::move(name), std::move(label), std::move(predicate));
  }
  return std::make_shared<GraphEdgePattern>(
      std::move(name),
      std::move(label),
      std::move(predicate),
      GraphEdgePattern::toDirection(obj["direction"].asString()),
      deserializeRepetition(obj));
}

GraphElementPattern::GraphElementPattern(
    Kind kind,
    std::string name,
    GraphLabelExpressionPtr label,
    ExprPtr predicate)
    : GraphPatternTerm{kind, std::move(name), std::move(predicate)},
      label_{std::move(label)} {
  VELOX_USER_CHECK(
      this->predicate() == nullptr || !this->name().empty(),
      "A pattern with a predicate must have a name");
  checkPredicateInputs(this->predicate(), {this->name()});
}

bool GraphElementPattern::equals(const GraphPatternTerm& other) const {
  return equalNullableLabels(
      label_, static_cast<const GraphElementPattern&>(other).label_);
}

folly::dynamic GraphElementPattern::serialize() const {
  auto obj = GraphPatternTerm::serialize();
  if (label_ != nullptr) {
    obj["label"] = label_->serialize();
  }
  return obj;
}

GraphVertexPattern::GraphVertexPattern(
    std::string name,
    GraphLabelExpressionPtr label,
    ExprPtr predicate)
    : GraphElementPattern{
          Kind::kVertex,
          std::move(name),
          std::move(label),
          std::move(predicate)} {}

GraphEdgePattern::GraphEdgePattern(
    std::string name,
    GraphLabelExpressionPtr label,
    ExprPtr predicate,
    Direction direction,
    std::optional<GraphRepetition> repetition)
    : GraphElementPattern{Kind::kEdge, std::move(name), std::move(label), std::move(predicate)},
      direction_{direction},
      repetition_{std::move(repetition)} {
  checkRepetition(repetition_);
}

bool GraphEdgePattern::equals(const GraphPatternTerm& other) const {
  const auto& rhs = static_cast<const GraphEdgePattern&>(other);
  return GraphElementPattern::equals(other) && direction_ == rhs.direction_ &&
      repetition_ == rhs.repetition_;
}

folly::dynamic GraphEdgePattern::serialize() const {
  auto obj = GraphElementPattern::serialize();
  obj["direction"] = toName(direction_);
  if (repetition_.has_value()) {
    obj["repetition"] = serializeRepetition(repetition_.value());
  }
  return obj;
}

GraphSubpathPattern::GraphSubpathPattern(
    std::string name,
    GraphPathMode mode,
    std::vector<GraphPatternTermPtr> terms,
    ExprPtr predicate,
    std::optional<GraphRepetition> repetition,
    bool optional)
    : GraphPatternTerm{Kind::kSubpath, std::move(name), std::move(predicate)},
      mode_{mode},
      terms_{std::move(terms)},
      repetition_{std::move(repetition)},
      optional_{optional} {
  VELOX_USER_CHECK(!terms_.empty(), "Subpath has no terms");
  for (const auto& term : terms_) {
    VELOX_USER_CHECK_NOT_NULL(term, "Subpath term is null");
  }
  VELOX_USER_CHECK(
      !(repetition_.has_value() && optional_),
      "A subpath cannot have both a repetition and '?'");
  checkRepetition(repetition_);
  VELOX_USER_CHECK(
      !repetition_.has_value() || !hasRepeatedTerm(terms_),
      "A repeated pattern term cannot be inside another");

  folly::F14FastSet<std::string> names;
  addElementNames(terms_, names);
  checkPredicateInputs(this->predicate(), names);
}

bool GraphSubpathPattern::equals(const GraphPatternTerm& other) const {
  const auto& rhs = static_cast<const GraphSubpathPattern&>(other);
  return mode_ == rhs.mode_ && equalTerms(terms_, rhs.terms_) &&
      repetition_ == rhs.repetition_ && optional_ == rhs.optional_;
}

folly::dynamic GraphSubpathPattern::serialize() const {
  auto obj = GraphPatternTerm::serialize();
  obj["mode"] = GraphPathModeName::toName(mode_);
  obj["terms"] = serializeTerms(terms_);
  if (repetition_.has_value()) {
    obj["repetition"] = serializeRepetition(repetition_.value());
  }
  obj["optional"] = optional_;
  return obj;
}

bool GraphPathPattern::operator==(const GraphPathPattern& other) const {
  return name == other.name && selector == other.selector &&
      mode == other.mode && equalTerms(terms, other.terms);
}

folly::dynamic GraphPathPattern::serialize() const {
  folly::dynamic obj = folly::dynamic::object;
  obj["name"] = name;
  folly::dynamic selectorObj = folly::dynamic::object;
  selectorObj["kind"] = GraphPathSelector::toName(selector.kind);
  if (selector.count.has_value()) {
    selectorObj["count"] = selector.count.value();
  }
  obj["selector"] = std::move(selectorObj);
  obj["mode"] = GraphPathModeName::toName(mode);
  obj["terms"] = serializeTerms(terms);
  return obj;
}

// static
GraphPathPattern GraphPathPattern::create(
    const folly::dynamic& obj,
    void* context) {
  const auto& selectorObj = obj["selector"];
  return GraphPathPattern{
      .name = obj["name"].asString(),
      .selector =
          GraphPathSelector{
              .kind = GraphPathSelector::toKind(selectorObj["kind"].asString()),
              .count = selectorObj.count("count")
                  ? std::optional<int64_t>(selectorObj["count"].asInt())
                  : std::nullopt,
          },
      .mode = deserializeMode(obj),
      .terms = deserializeTerms(obj["terms"], context),
  };
}

} // namespace facebook::axiom::logical_plan
