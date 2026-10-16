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

#include <array>
#include <limits>
#include <numeric>

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

// Returns the repetition of 'term' if it is an edge pattern that repeats other
// than exactly once, or null. An edge pattern repeated exactly once joins as a
// plain edge.
const lp::GraphRepetition* walksRepetition(const lp::GraphPatternTerm& term) {
  if (term.kind() != lp::GraphPatternTerm::Kind::kEdge) {
    return nullptr;
  }
  const auto& repetition = term.as<lp::GraphEdgePattern>()->repetition();
  if (!repetition.has_value() ||
      (repetition->min == 1 && repetition->max == 1)) {
    return nullptr;
  }
  return &*repetition;
}

[[noreturn]] void failGroupRead(std::string_view name) {
  VELOX_NYI(
      "Reading a repeated graph pattern outside its own pattern is not "
      "supported yet: {}",
      name);
}

// Fails if 'expr' reads a pattern name in 'names'.
void checkNoGroupReads(
    const lp::Expr& expr,
    const folly::F14FastSet<std::string>& names) {
  if (expr.isInputReference() &&
      names.contains(expr.as<lp::InputReferenceExpr>()->name())) {
    failGroupRead(expr.as<lp::InputReferenceExpr>()->name());
  }
  for (const auto& input : expr.inputs()) {
    checkNoGroupReads(*input, names);
  }
  if (expr.isLambda()) {
    checkNoGroupReads(*expr.as<lp::LambdaExpr>()->body(), names);
  }
}

// Returns the number of matches per pair of endpoints a selector keeps, or
// nullopt for all. ANY, ANY SHORTEST and SHORTEST k keep up to k. In a path
// without repetition every match has the same length, so the others keep
// every match.
std::optional<int32_t> selectorLimit(const lp::GraphPathSelector& selector) {
  using Kind = lp::GraphPathSelector::Kind;
  switch (selector.kind) {
    case Kind::kAny:
    case Kind::kAnyShortest:
    case Kind::kShortest:
      return static_cast<int32_t>(std::min<int64_t>(
          selector.count.value_or(1), std::numeric_limits<int32_t>::max()));
    case Kind::kAll:
    case Kind::kAllShortest:
    case Kind::kShortestGroups:
      return std::nullopt;
  }
  VELOX_UNREACHABLE();
}

} // namespace

std::optional<Translated> Translator::GraphMatchLowering::lower(
    const LpNameSet& required) {
  const auto& paths = match_.paths();
  for (size_t i = 0; i < paths.size(); ++i) {
    addPath(paths[i], i);
  }
  for (auto& element : elements_) {
    element.properties = lp::PropertyGraph::properties(element.labelTables);
  }
  if (match_.predicate() != nullptr) {
    checkPropertyReads(*match_.predicate());
  }
  checkGroupReads();
  if (!narrow()) {
    return std::nullopt;
  }

  copySharedElements();
  const auto foldedEnds = fold();
  for (size_t i = 0; i < elements_.size(); ++i) {
    if (elements_[i].isVertex() && !elements_[i].folds()) {
      buildVertex(elements_[i]);
    }
  }
  for (size_t i = 0; i < elements_.size(); ++i) {
    if (elements_[i].isEdge()) {
      buildEdge(i, foldedEnds[i]);
    }
  }
  bindPatternNames();
  filterHops();
  connect();
  walked_.assign(repeatedEdges_.size(), false);

  // Paths that share no name join with a cross product: no connection links
  // two components.
  const auto groups = components();
  std::vector<NodeCP> nodes;
  for (const auto& component : groups) {
    nodes.push_back(lowerComponent(component));
  }
  NodeCP node = join(groups, std::move(nodes));

  ExprVector conjuncts;
  if (match_.predicate() != nullptr) {
    conjuncts =
        translatePredicates({match_.predicate().get()}, /*path=*/std::nullopt);
  }
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

void Translator::GraphMatchLowering::checkGroupReads() const {
  folly::F14FastSet<std::string> names;
  for (const auto& path : match_.paths()) {
    for (const auto& term : path.terms) {
      if (term->kind() == lp::GraphPatternTerm::Kind::kEdge &&
          term->as<lp::GraphEdgePattern>()->repetition().has_value() &&
          !term->name().empty()) {
        names.insert(term->name());
      }
    }
  }
  if (names.empty()) {
    return;
  }
  if (match_.predicate() != nullptr) {
    checkNoGroupReads(*match_.predicate(), names);
  }
  for (const auto& path : match_.paths()) {
    for (const auto& term : path.terms) {
      if (term->predicate() != nullptr && !names.contains(term->name())) {
        checkNoGroupReads(*term->predicate(), names);
      }
    }
  }
  for (const auto& output : match_.outputs()) {
    if (output->kind() == lp::GraphMatchOutput::Kind::kProperty &&
        names.contains(output->pattern())) {
      failGroupRead(output->pattern());
    }
  }
}

void Translator::GraphMatchLowering::copySharedElements() {
  const auto numElements = elements_.size();
  for (size_t original = 0; original < numElements; ++original) {
    bool limited = false;
    // Copy the set: the loop moves paths from the original to its copies.
    const auto paths = elements_[original].paths;
    for (const auto path : paths) {
      if (!paths_[path].limit.has_value()) {
        continue;
      }
      if (!limited) {
        limited = true;
        continue;
      }
      Element copy = elements_[original];
      copy.paths = {path};
      elements_[original].paths.erase(path);
      const auto index = elements_.size();
      elements_.push_back(std::move(copy));
      elements_[original].needsIdentity = true;
      elements_[index].needsIdentity = true;
      copies_.push_back({original, index, path});

      for (auto& occurrence : occurrences_) {
        if (occurrence.path != path) {
          continue;
        }
        for (auto* element :
             {&occurrence.edge, &occurrence.from, &occurrence.to}) {
          if (*element == original) {
            *element = index;
          }
        }
      }
      for (auto& repeated : repeatedEdges_) {
        if (repeated.path != path) {
          continue;
        }
        for (auto* element : {&repeated.edge, &repeated.from, &repeated.to}) {
          if (*element == original) {
            *element = index;
          }
        }
      }
      auto& pathInfo = paths_[path];
      if (pathInfo.first == original) {
        pathInfo.first = index;
      }
      if (pathInfo.last == original) {
        pathInfo.last = index;
      }
    }
  }
}

std::vector<std::vector<Translator::GraphMatchLowering::EdgeEnd>>
Translator::GraphMatchLowering::fold() {
  // A selector partitions a path's matches by its endpoints' identities.
  for (const auto& path : paths_) {
    if (path.limit.has_value()) {
      elements_[path.first].needsIdentity = true;
      elements_[path.last].needsIdentity = true;
    }
  }
  // A walk joins its ends on their identities.
  for (const auto& repeated : repeatedEdges_) {
    elements_[repeated.from].needsIdentity = true;
    elements_[repeated.to].needsIdentity = true;
  }
  for (const auto& occurrence : occurrences_) {
    for (const auto& end : occurrence.ends()) {
      ++vertexAt(end.vertex).numEdgeEnds;
    }
  }
  std::vector<std::vector<EdgeEnd>> foldedEnds(elements_.size());
  for (const auto& occurrence : occurrences_) {
    for (const auto& end : occurrence.ends()) {
      if (elements_[end.vertex].folds()) {
        auto& vertex = vertexAt(end.vertex);
        vertex.foldedEdge = occurrence.edge;
        vertex.foldedAtSource = end.source;
        foldedEnds[occurrence.edge].push_back(end);
      }
    }
  }
  return foldedEnds;
}

size_t Translator::GraphMatchLowering::bind(
    const lp::GraphElementPattern& pattern,
    bool edge) {
  const auto tables = graph_.matchingTables(pattern.label().get(), edge);
  const auto& name = pattern.name();

  // A name bound before matches only the tables every pattern with the name
  // matches.
  if (const auto it = elementByName_.find(name); it != elementByName_.end()) {
    auto& labelTables = elements_[it->second].labelTables;
    std::erase_if(labelTables, [&](const auto* table) {
      return std::find(tables.begin(), tables.end(), table) == tables.end();
    });
    return it->second;
  }

  if (!name.empty()) {
    elementByName_.emplace(name, elements_.size());
  }
  using State = decltype(Element::state);
  elements_.push_back(
      {.name = name,
       .labelTables = tables,
       .state = edge ? State{EdgeState{}} : State{VertexState{}}});
  return elements_.size() - 1;
}

void Translator::GraphMatchLowering::addPath(
    const lp::GraphPathPattern& path,
    size_t pathIndex) {
  using Direction = lp::GraphEdgePattern::Direction;

  Path& pathInfo = paths_.emplace_back();
  pathInfo.limit = selectorLimit(path.selector);
  const bool repeats =
      std::any_of(path.terms.begin(), path.terms.end(), [](const auto& term) {
        return walksRepetition(*term) != nullptr;
      });
  if (repeats && path.selector.kind != lp::GraphPathSelector::Kind::kAny &&
      path.selector.kind != lp::GraphPathSelector::Kind::kAll) {
    VELOX_NYI(
        "Shortest-path selector on a path with repetition is not supported "
        "yet");
  }
  if (path.mode != lp::GraphPathMode::kWalk) {
    VELOX_NYI(
        "Graph path mode is not supported yet: {}",
        lp::GraphPathModeName::toName(path.mode));
  }

  // The vertex the next edge leaves from, and the edge waiting for the vertex
  // it reaches.
  std::optional<size_t> vertex;
  std::optional<EdgeOccurrence> pendingEdge;
  std::optional<RepeatedEdge> pendingRepeat;
  int64_t numEdges{0};
  for (const auto& term : path.terms) {
    if (term->predicate() != nullptr) {
      checkPropertyReads(*term->predicate());
      // A repeated edge pattern's predicate applies to each hop.
      if (walksRepetition(*term) == nullptr) {
        pathInfo.predicates.push_back(term->predicate().get());
      }
    }
    switch (term->kind()) {
      case lp::GraphPatternTerm::Kind::kSubpath:
        VELOX_NYI("Graph subpath patterns are not supported yet");
      case lp::GraphPatternTerm::Kind::kEdge: {
        const auto* edge = term->as<lp::GraphEdgePattern>();
        if (!vertex.has_value() || pendingEdge.has_value() ||
            pendingRepeat.has_value()) {
          VELOX_NYI(
              "Graph edge pattern without a vertex pattern before it is not "
              "supported yet");
        }
        const bool undirected = edge->direction() == Direction::kAnyDirection;
        const bool reused = elementByName_.contains(edge->name());
        const auto index = bind(*edge, /*edge=*/true);
        elements_[index].paths.insert(pathIndex);
        if (reused && (undirected || edgeAt(index).undirected)) {
          VELOX_NYI(
              "Undirected graph edge pattern with a reused name is not "
              "supported yet: {}",
              edge->name());
        }
        edgeAt(index).undirected = undirected;
        if (const auto* repetition = walksRepetition(*term)) {
          if (!repetition->max.has_value()) {
            VELOX_NYI(
                "Graph edge repetition without an upper bound is not "
                "supported yet");
          }
          if (repetition->min == 0) {
            VELOX_NYI(
                "Graph edge repetition with a lower bound of 0 is not "
                "supported yet");
          }
          edgeAt(index).repeated = true;
          pendingRepeat = RepeatedEdge{
              .edge = index,
              .from = *vertex,
              .pointsRight = edge->direction() != Direction::kLeft,
              .minHops = static_cast<int32_t>(repetition->min),
              .maxHops = static_cast<int32_t>(*repetition->max),
              .path = pathIndex};
          if (term->predicate() != nullptr) {
            pendingRepeat->predicates.push_back(term->predicate().get());
          }
          break;
        }
        pendingEdge = EdgeOccurrence{
            .edge = index,
            .from = *vertex,
            .pointsRight = edge->direction() != Direction::kLeft,
            .path = pathIndex};
        ++numEdges;
        break;
      }
      case lp::GraphPatternTerm::Kind::kVertex: {
        if (vertex.has_value() && !pendingEdge.has_value() &&
            !pendingRepeat.has_value()) {
          VELOX_NYI(
              "Adjacent graph vertex patterns are not supported yet: {}",
              term->name());
        }
        const auto index =
            bind(*term->as<lp::GraphVertexPattern>(), /*edge=*/false);
        elements_[index].paths.insert(pathIndex);
        if (!vertex.has_value()) {
          pathInfo.first = index;
        }
        if (pendingEdge.has_value()) {
          pendingEdge->to = index;
          occurrences_.push_back(*pendingEdge);
          pendingEdge.reset();
        }
        if (pendingRepeat.has_value()) {
          pendingRepeat->to = index;
          repeatedEdges_.push_back(std::move(*pendingRepeat));
          pendingRepeat.reset();
        }
        vertex = index;
        break;
      }
    }
  }
  if (pendingEdge.has_value() || pendingRepeat.has_value()) {
    VELOX_NYI(
        "Graph edge pattern without a vertex pattern after it is not "
        "supported yet");
  }
  pathInfo.last = vertex.value();
  if (!path.name.empty() && !repeats) {
    pathLengths_.emplace(path.name, numEdges);
  }
}

bool Translator::GraphMatchLowering::narrow() {
  for (auto& element : elements_) {
    for (const auto* table : element.labelTables) {
      element.legs.push_back({table});
      if (const auto* edge = std::get_if<EdgeState>(&element.state);
          edge != nullptr && edge->undirected) {
        element.legs.push_back({table, /*reversed=*/true});
      }
    }
  }

  auto tableIds = [](const Element& vertex) {
    folly::F14FastSet<int32_t> ids;
    for (const auto& leg : vertex.legs) {
      ids.insert(leg.table->id);
    }
    return ids;
  };

  // Drops the legs of 'vertex' whose table is not in 'referenced'. Returns true
  // if it dropped any.
  auto keepReferenced = [](Element& vertex,
                           const folly::F14FastSet<int32_t>& referenced) {
    const auto numLegs = vertex.legs.size();
    std::erase_if(vertex.legs, [&](const Leg& leg) {
      return !referenced.contains(leg.table->id);
    });
    return vertex.legs.size() != numLegs;
  };

  bool changed{true};
  while (changed) {
    changed = false;
    for (const auto& occurrence : occurrences_) {
      auto& edge = elements_[occurrence.edge];
      auto& from = elements_[occurrence.from];
      auto& to = elements_[occurrence.to];
      const auto fromIds = tableIds(from);
      const auto toIds = tableIds(to);

      // The vertex tables the remaining edge legs leave from and reach.
      folly::F14FastSet<int32_t> fromReferenced;
      folly::F14FastSet<int32_t> toReferenced;
      const auto numEdgeLegs = edge.legs.size();
      std::erase_if(edge.legs, [&](const Leg& leg) {
        const auto fromId = leg.tableId(occurrence.pointsRight);
        const auto toId = leg.tableId(!occurrence.pointsRight);
        if (!fromIds.contains(fromId) || !toIds.contains(toId)) {
          return true;
        }
        fromReferenced.insert(fromId);
        toReferenced.insert(toId);
        return false;
      });

      const bool fromChanged = keepReferenced(from, fromReferenced);
      const bool toChanged = keepReferenced(to, toReferenced);
      changed = changed || edge.legs.size() != numEdgeLegs || fromChanged ||
          toChanged;
    }

    // A walk leaves from a table a hop leaves from and reaches a table a hop
    // reaches. The hops between visit any table.
    for (const auto& repeated : repeatedEdges_) {
      const auto& edge = elements_[repeated.edge];
      folly::F14FastSet<int32_t> fromReferenced;
      folly::F14FastSet<int32_t> toReferenced;
      for (const auto& leg : edge.legs) {
        fromReferenced.insert(leg.tableId(repeated.pointsRight));
        toReferenced.insert(leg.tableId(!repeated.pointsRight));
      }
      const bool fromChanged =
          keepReferenced(elements_[repeated.from], fromReferenced);
      const bool toChanged =
          keepReferenced(elements_[repeated.to], toReferenced);
      changed = changed || fromChanged || toChanged;
    }
  }

  return std::none_of(
      elements_.begin(), elements_.end(), [](const Element& element) {
        return element.legs.empty();
      });
}

namespace {

// Names of the columns of an element's relation other than its properties.
// Each starts with '$', which no property name does.
class ColumnNames {
 public:
  // Table ID and key column 'i' of the identity 'end' selects (see
  // Leg::tableId).
  static std::string tableId(std::optional<bool> end) {
    if (!end.has_value()) {
      return "$table";
    }
    return *end ? "$source_table" : "$destination_table";
  }

  static std::string key(std::optional<bool> end, size_t i) {
    if (!end.has_value()) {
      return fmt::format("$key{}", i);
    }
    return fmt::format("{}{}", *end ? "$source" : "$destination", i);
  }

  // Property 'property' of the vertex at index 'vertex', which joins inside an
  // edge's legs.
  static std::string foldedProperty(size_t vertex, std::string_view property) {
    return fmt::format("${}.{}", vertex, property);
  }
};

// Returns the data type of column 'name' of the plan of 'table'.
velox::TypePtr columnType(
    const lp::PropertyGraph::ElementTable& table,
    std::string_view name) {
  return table.plan->outputType()->findChild(name);
}

} // namespace

int32_t Translator::GraphMatchLowering::Leg::tableId(
    std::optional<bool> end) const {
  if (!end.has_value()) {
    return table->id;
  }
  const auto* edgeTable = static_cast<const EdgeTable*>(table);
  return *end != reversed ? edgeTable->sourceTableId
                          : edgeTable->destinationTableId;
}

const std::vector<std::string>& Translator::GraphMatchLowering::Leg::keyColumns(
    std::optional<bool> end) const {
  if (!end.has_value()) {
    return table->keyColumns;
  }
  const auto* edgeTable = static_cast<const EdgeTable*>(table);
  return *end != reversed ? edgeTable->sourceColumns
                          : edgeTable->destinationColumns;
}

bool Translator::GraphMatchLowering::Element::tableIdVaries(
    std::optional<bool> end) const {
  return std::any_of(legs.begin(), legs.end(), [&](const Leg& leg) {
    return leg.tableId(end) != legs[0].tableId(end);
  });
}

ExprVector Translator::GraphMatchLowering::Element::identity(
    std::optional<bool> end) const {
  ExprVector exprs;
  if (auto it = scope.find(ColumnNames::tableId(end)); it != scope.end()) {
    exprs.push_back(it->second);
  }
  for (size_t i = 0; i < legs[0].keyColumns(end).size(); ++i) {
    exprs.push_back(scope.at(ColumnNames::key(end, i)));
  }
  return exprs;
}

namespace {

// Appends the names and types of the columns that hold the identity 'end'
// selects (see Leg::tableId): the table ID when it varies, then the key.
template <typename Element>
void appendIdentitySchema(
    const Element& element,
    std::optional<bool> end,
    std::vector<std::string>& names,
    std::vector<velox::TypePtr>& types) {
  if (element.tableIdVaries(end)) {
    names.push_back(ColumnNames::tableId(end));
    types.push_back(velox::INTEGER());
  }
  const auto& first = element.legs[0];
  const auto& firstColumns = first.keyColumns(end);
  for (size_t i = 0; i < firstColumns.size(); ++i) {
    const auto type = columnType(*first.table, firstColumns[i]);
    for (const auto& leg : element.legs) {
      const auto& columns = leg.keyColumns(end);
      if (columns.size() != firstColumns.size() ||
          !columnType(*leg.table, columns[i])->equivalent(*type)) {
        VELOX_NYI(
            "Graph pattern whose identity is compared and that matches tables "
            "with keys of different types is not supported yet: {}",
            element.name);
      }
    }
    names.push_back(ColumnNames::key(end, i));
    types.push_back(type);
  }
}

// Appends the values of the identity 'end' selects for a row of 'leg' of
// 'element', whose table columns 'scope' holds.
template <typename Element, typename Leg>
void appendIdentityValues(
    const Element& element,
    std::optional<bool> end,
    const Leg& leg,
    const Scope& scope,
    ExprFactory& factory,
    ExprVector& exprs) {
  if (element.tableIdVaries(end)) {
    exprs.push_back(factory.makeLiteral(
        velox::Variant(leg.tableId(end)), toType(velox::INTEGER())));
  }
  for (const auto& name : leg.keyColumns(end)) {
    exprs.push_back(scope.at(name));
  }
}

} // namespace

namespace {

// An element table whose plan is a Project directly over a TableScan, which
// lets the lowering read the element table as columns of the scanned table.
class ScannedTable {
 public:
  // Returns nullopt when the plan of 'table' has another shape.
  static std::optional<ScannedTable> of(
      const lp::PropertyGraph::ElementTable& table) {
    const auto& plan = table.plan;
    if (!plan->is(lp::NodeKind::kProject) ||
        !plan->onlyInput()->is(lp::NodeKind::kTableScan)) {
      return std::nullopt;
    }
    return ScannedTable{
        *plan->as<lp::ProjectNode>(),
        *plan->onlyInput()->as<lp::TableScanNode>()};
  }

  const lp::ProjectNode& project() const {
    return *project_;
  }

  const lp::TableScanNode& scan() const {
    return *scan_;
  }

  // True if 'other' scans the same table.
  bool sameTable(const ScannedTable& other) const {
    return scan_->connectorId() == other.scan_->connectorId() &&
        scan_->tableName() == other.scan_->tableName();
  }

  // Returns the schema name of the column the element table outputs unchanged
  // as 'name', or nullopt when the Project computes 'name' from an expression.
  std::optional<std::string> schemaName(std::string_view name) const {
    const auto& names = project_->names();
    const auto it = std::find(names.begin(), names.end(), name);
    VELOX_CHECK(it != names.end());
    const auto& expr = *project_->expressions()[it - names.begin()];
    if (!expr.isInputReference()) {
      return std::nullopt;
    }
    return scan_->columnNames()[scan_->outputType()->getChildIdx(
        expr.as<lp::InputReferenceExpr>()->name())];
  }

 private:
  ScannedTable(const lp::ProjectNode& project, const lp::TableScanNode& scan)
      : project_{&project}, scan_{&scan} {}

  const lp::ProjectNode* project_;
  const lp::TableScanNode* scan_;
};

// True if each row of 'edge' is the row of 'vertex' that the edge's
// 'endColumns' reference: the two scan one table, and the end columns are the
// columns of 'vertexKey'. The key is unique, so the referenced row is the
// edge's own.
bool sameRow(
    const ScannedTable& edge,
    const std::vector<std::string>& endColumns,
    const ScannedTable& vertex,
    const std::vector<std::string>& vertexKey) {
  if (!edge.sameTable(vertex)) {
    return false;
  }
  for (size_t i = 0; i < endColumns.size(); ++i) {
    const auto column = edge.schemaName(endColumns[i]);
    if (!column.has_value() || column != vertex.schemaName(vertexKey[i])) {
      return false;
    }
  }
  return true;
}

} // namespace

Translated Translator::GraphMatchLowering::translateTable(
    const ElementTable& table) {
  auto planGuard = translator_.translatingPlan(*table.plan);
  return translator_.translateNode(*table.plan);
}

void Translator::GraphMatchLowering::buildVertex(Element& vertex) {
  const auto& properties = vertex.properties;

  // Edges join a shared vertex on its identity. A vertex at no edge end is
  // compared with nothing unless it needs its identity.
  const bool shared = std::get<VertexState>(vertex.state).numEdgeEnds > 1 ||
      vertex.needsIdentity;

  std::vector<std::string> names;
  std::vector<velox::TypePtr> types;
  if (shared) {
    appendIdentitySchema(vertex, /*end=*/std::nullopt, names, types);
  }
  appendAll(names, properties->names());
  appendAll(types, properties->children());

  std::vector<NodeCP> legNodes;
  std::vector<ExprVector> legExprs;
  for (const auto& leg : vertex.legs) {
    Translated translated = translateTable(*leg.table);
    ExprVector exprs;
    if (shared) {
      appendIdentityValues(
          vertex,
          /*end=*/std::nullopt,
          leg,
          translated.scope,
          translator_.exprFactory_,
          exprs);
    }
    appendProperties(*properties, *leg.table, translated.scope, exprs);
    legNodes.push_back(translated.node);
    legExprs.push_back(std::move(exprs));
  }
  unionLegs(vertex, std::move(legNodes), legExprs, names, types);
}

void Translator::GraphMatchLowering::buildEdge(
    size_t edgeIndex,
    const std::vector<EdgeEnd>& foldedEnds) {
  auto& edge = elements_[edgeIndex];
  const auto& properties = edge.properties;

  // The ends a shared vertex joins on, which the relation outputs, by source.
  // A walk's hops join on both.
  const bool repeated = std::get<EdgeState>(edge.state).repeated;
  std::array<bool, 2> keepEnd{repeated, repeated};
  for (const auto& occurrence : occurrences_) {
    if (occurrence.edge != edgeIndex) {
      continue;
    }
    for (const auto& end : occurrence.ends()) {
      const auto& vertex = elements_[end.vertex];
      if (!vertex.folds() || vertex.needsIdentity) {
        keepEnd[end.source] = true;
      }
    }
  }

  std::vector<std::string> names;
  std::vector<velox::TypePtr> types;
  if (edge.needsIdentity) {
    appendIdentitySchema(edge, /*end=*/std::nullopt, names, types);
  }
  for (const bool source : {true, false}) {
    if (keepEnd[source]) {
      appendIdentitySchema(edge, source, names, types);
    }
  }
  appendAll(names, properties->names());
  appendAll(types, properties->children());

  // Properties of the vertices that join inside the legs.
  for (const auto& end : foldedEnds) {
    const auto& vertexProperties = *elements_[end.vertex].properties;
    for (size_t i = 0; i < vertexProperties.size(); ++i) {
      names.push_back(
          ColumnNames::foldedProperty(end.vertex, vertexProperties.nameOf(i)));
      types.push_back(vertexProperties.childAt(i));
    }
  }

  std::vector<NodeCP> legNodes;
  std::vector<ExprVector> legExprs;
  for (const auto& leg : edge.legs) {
    auto rows = translateLeg(leg, foldedEnds);
    const Scope& edgeScope = rows.edgeScope;

    ExprVector exprs;
    if (edge.needsIdentity) {
      appendIdentityValues(
          edge,
          /*end=*/std::nullopt,
          leg,
          edgeScope,
          translator_.exprFactory_,
          exprs);
    }
    for (const bool source : {true, false}) {
      if (keepEnd[source]) {
        appendIdentityValues(
            edge, source, leg, edgeScope, translator_.exprFactory_, exprs);
      }
    }
    appendProperties(*properties, *leg.table, edgeScope, exprs);
    for (size_t k = 0; k < foldedEnds.size(); ++k) {
      appendProperties(
          *elements_[foldedEnds[k].vertex].properties,
          *rows.foldedVertices[k].table,
          rows.foldedVertices[k].scope,
          exprs);
    }
    legNodes.push_back(rows.node);
    legExprs.push_back(std::move(exprs));
  }
  unionLegs(edge, std::move(legNodes), legExprs, names, types);

  // A folded vertex reads its properties from the edge's relation.
  for (const auto& end : foldedEnds) {
    auto& vertex = elements_[end.vertex];
    for (const auto& name : vertex.properties->names()) {
      vertex.scope[name] =
          edge.scope.at(ColumnNames::foldedProperty(end.vertex, name));
    }
  }
}

Translated Translator::GraphMatchLowering::dropSelfLoops(
    Translated translated,
    const EdgeTable& table) {
  // The other orientation reads each self-loop.
  ExprVector equalities;
  for (size_t i = 0; i < table.sourceColumns.size(); ++i) {
    equalities.push_back(translator_.exprFactory_.makeEq(
        translated.scope.at(table.sourceColumns[i]),
        translated.scope.at(table.destinationColumns[i])));
  }
  return translator_.simplifyFilter(
      translated.node,
      {translator_.exprFactory_.makeNot(
          translator_.exprFactory_.andAll(equalities))},
      std::move(translated.scope),
      /*propagateConstants=*/false);
}

Translator::GraphMatchLowering::LegRows
Translator::GraphMatchLowering::translateLeg(
    const Leg& leg,
    const std::vector<EdgeEnd>& foldedEnds) {
  const auto& table = *static_cast<const EdgeTable*>(leg.table);
  const auto edgeScanned = ScannedTable::of(table);

  // The vertex table at each folded end, and whether its row is the edge's.
  std::vector<const ElementTable*> vertexTables;
  std::vector<bool> sameRowEnds;
  for (const auto& end : foldedEnds) {
    const auto vertexTableId = leg.tableId(end.source);
    const auto& vertexLegs = elements_[end.vertex].legs;
    const auto it = std::find_if(
        vertexLegs.begin(), vertexLegs.end(), [&](const Leg& vertexLeg) {
          return vertexLeg.table->id == vertexTableId;
        });
    VELOX_CHECK(it != vertexLegs.end());
    vertexTables.push_back(it->table);
    const auto vertexScanned = ScannedTable::of(*it->table);
    sameRowEnds.push_back(
        edgeScanned.has_value() && vertexScanned.has_value() &&
        sameRow(
            *edgeScanned,
            leg.keyColumns(end.source),
            *vertexScanned,
            it->table->keyColumns));
  }

  LegRows rows;
  rows.foldedVertices.resize(foldedEnds.size());
  Translated translated;
  if (std::find(sameRowEnds.begin(), sameRowEnds.end(), true) !=
      sameRowEnds.end()) {
    std::vector<const ElementTable*> tables{&table};
    for (size_t k = 0; k < foldedEnds.size(); ++k) {
      if (sameRowEnds[k]) {
        tables.push_back(vertexTables[k]);
      }
    }
    auto translations = translateOverOneScan(tables);
    translated = std::move(translations[0]);
    size_t next = 1;
    for (size_t k = 0; k < foldedEnds.size(); ++k) {
      if (sameRowEnds[k]) {
        rows.foldedVertices[k] = {
            vertexTables[k], std::move(translations[next++].scope)};
      }
    }
  } else {
    translated = translateTable(table);
  }
  if (leg.reversed && table.sourceTableId == table.destinationTableId) {
    translated = dropSelfLoops(std::move(translated), table);
  }
  rows.node = translated.node;
  rows.edgeScope = std::move(translated.scope);

  for (size_t k = 0; k < foldedEnds.size(); ++k) {
    if (!sameRowEnds[k]) {
      rows.foldedVertices[k] = {
          vertexTables[k],
          joinVertexTable(
              rows, leg.keyColumns(foldedEnds[k].source), *vertexTables[k])};
    }
  }
  return rows;
}

std::vector<Translator::Translated>
Translator::GraphMatchLowering::translateOverOneScan(
    const std::vector<const ElementTable*>& tables) {
  std::vector<ScannedTable> scanned;
  for (const auto* table : tables) {
    scanned.push_back(ScannedTable::of(*table).value());
  }

  // Each column of the table the tables read, under the output name of the
  // first table's scan that reads it.
  std::vector<ScanColumn> columns;
  folly::F14FastMap<std::string, std::string> outputNames;
  for (const auto& table : scanned) {
    const auto& scanNode = table.scan();
    for (size_t i = 0; i < scanNode.columnNames().size(); ++i) {
      const auto& column = scanNode.columnNames()[i];
      const auto& name = scanNode.outputType()->nameOf(i);
      if (outputNames.emplace(column, name).second) {
        columns.push_back({.schemaName = column, .outputName = name});
      }
    }
  }
  Translated scan = [&] {
    auto planGuard = translator_.translatingPlan(*tables[0]->plan);
    return translator_.translateScan(
        scanned[0].scan().connectorId(),
        scanned[0].scan().tableName(),
        columns);
  }();

  std::vector<Translated> translations;
  for (const auto& table : scanned) {
    Translated input{.node = scan.node};
    const auto& scanNode = table.scan();
    for (size_t i = 0; i < scanNode.columnNames().size(); ++i) {
      input.scope[scanNode.outputType()->nameOf(i)] =
          scan.scope.at(outputNames.at(scanNode.columnNames()[i]));
    }
    const auto& names = table.project().names();
    translations.push_back(translator_.translateProject(
        table.project(),
        LpNameSet(names.begin(), names.end()),
        std::move(input)));
  }
  return translations;
}

Translator::Scope Translator::GraphMatchLowering::joinVertexTable(
    LegRows& rows,
    const std::vector<std::string>& endColumns,
    const ElementTable& vertexTable) {
  auto columns = [](const Scope& scope,
                    const std::vector<std::string>& columnNames) {
    ExprVector exprs;
    for (const auto& name : columnNames) {
      exprs.push_back(scope.at(name));
    }
    return exprs;
  };
  Translated vertex = translateTable(vertexTable);
  auto joined = translator_.innerJoin(
      rows.node,
      vertex.node,
      columns(rows.edgeScope, endColumns),
      columns(vertex.scope, vertexTable.keyColumns));
  rows.node = translator_.nodeSimplifier_.materialize(joined);
  translator_.applySubstitutions(joined.substitutions, rows.edgeScope);
  translator_.applySubstitutions(joined.substitutions, vertex.scope);
  for (auto& folded : rows.foldedVertices) {
    translator_.applySubstitutions(joined.substitutions, folded.scope);
  }
  return std::move(vertex.scope);
}

void Translator::GraphMatchLowering::appendProperties(
    const velox::RowType& properties,
    const ElementTable& table,
    const Scope& scope,
    ExprVector& exprs) {
  for (size_t i = 0; i < properties.size(); ++i) {
    const auto it = table.properties.find(properties.nameOf(i));
    exprs.push_back(
        it != table.properties.end()
            ? translator_.translateExpr(
                  *it->second, scope, /*liftTarget=*/nullptr)
            : translator_.builder_.makeNull(toType(properties.childAt(i))));
  }
}

void Translator::GraphMatchLowering::unionLegs(
    Element& element,
    std::vector<NodeCP> legNodes,
    const std::vector<ExprVector>& legExprs,
    const std::vector<std::string>& names,
    const std::vector<velox::TypePtr>& types) {
  for (const auto& exprs : legExprs) {
    VELOX_CHECK_EQ(exprs.size(), names.size());
  }
  if (legNodes.size() == 1) {
    element.node = legNodes[0];
    for (size_t i = 0; i < names.size(); ++i) {
      element.scope[names[i]] = legExprs[0][i];
    }
    return;
  }
  // Every leg names its columns as the relation does.
  const std::vector<std::vector<std::string>> legNames(legNodes.size(), names);
  auto relation = translator_.makeUnionAll(
      std::move(legNodes),
      legExprs,
      legNames,
      names,
      types,
      [](std::string_view name, const Value& value) {
        return Column::create(name, value);
      });
  element.node = relation.node;
  element.scope = std::move(relation.scope);
}

void Translator::GraphMatchLowering::bindPatternNames() {
  for (auto& element : elements_) {
    const auto& properties = element.properties;
    if (element.name.empty() || properties->size() == 0) {
      continue;
    }
    ExprVector fields;
    for (size_t i = 0; i < properties->size(); ++i) {
      fields.push_back(element.scope.at(properties->nameOf(i)));
    }
    element.row = translator_.exprFactory_.makeRowConstructor(
        std::move(fields), toType(properties));
  }
}

void Translator::GraphMatchLowering::connect() {
  // A table ID column is on both sides of a connection or on neither: after
  // narrowing, a shared vertex has several legs exactly when the edge end
  // references several vertex tables.
  for (const auto& occurrence : occurrences_) {
    const auto& edge = elements_[occurrence.edge];
    for (const auto& end : occurrence.ends()) {
      if (elements_[end.vertex].folds()) {
        continue;
      }
      connections_.push_back(
          {end.vertex,
           identityOf(end.vertex, /*withTableId=*/false),
           occurrence.edge,
           edge.identity(end.source)});
    }
  }
  for (const auto& copy : copies_) {
    connections_.push_back(
        {holderOf(copy.original),
         identityOf(copy.original, /*withTableId=*/false),
         holderOf(copy.copy),
         identityOf(copy.copy, /*withTableId=*/false)});
  }
  for (const auto& connection : connections_) {
    VELOX_CHECK_EQ(connection.leftKeys.size(), connection.rightKeys.size());
  }
}

size_t Translator::GraphMatchLowering::holderOf(size_t element) const {
  return elements_[element].folds()
      ? std::get<VertexState>(elements_[element].state).foldedEdge
      : element;
}

std::vector<std::vector<size_t>> Translator::GraphMatchLowering::components()
    const {
  // Union-find over the connections.
  std::vector<size_t> parent(elements_.size());
  std::iota(parent.begin(), parent.end(), 0);
  std::function<size_t(size_t)> root = [&](size_t i) {
    return parent[i] == i ? i : parent[i] = root(parent[i]);
  };
  for (const auto& connection : connections_) {
    parent[root(connection.leftElement)] = root(connection.rightElement);
  }
  for (const auto& repeated : repeatedEdges_) {
    parent[root(holderOf(repeated.from))] = root(holderOf(repeated.to));
  }

  // A walk's hops join inside the walk.
  std::vector<std::vector<size_t>> components;
  folly::F14FastMap<size_t, size_t> componentByRoot;
  for (size_t i = 0; i < elements_.size(); ++i) {
    if (elements_[i].node == nullptr ||
        (elements_[i].isEdge() &&
         std::get<EdgeState>(elements_[i].state).repeated)) {
      continue;
    }
    const auto [it, inserted] =
        componentByRoot.emplace(root(i), components.size());
    if (inserted) {
      components.emplace_back();
    }
    components[it->second].push_back(i);
  }
  return components;
}

ExprVector Translator::GraphMatchLowering::identityOf(
    size_t element,
    bool withTableId) const {
  const auto& target = elements_[element];
  if (target.folds()) {
    const auto& vertex = std::get<VertexState>(target.state);
    return identity(
        elements_[vertex.foldedEdge], vertex.foldedAtSource, withTableId);
  }
  return identity(target, /*end=*/std::nullopt, withTableId);
}

ExprVector Translator::GraphMatchLowering::identity(
    const Element& element,
    std::optional<bool> end,
    bool withTableId) const {
  ExprVector exprs = element.identity(end);
  if (withTableId && !element.tableIdVaries(end)) {
    exprs.insert(
        exprs.begin(),
        translator_.exprFactory_.makeLiteral(
            velox::Variant(element.legs[0].tableId(end)),
            toType(velox::INTEGER())));
  }
  return exprs;
}

std::set<size_t> Translator::GraphMatchLowering::componentPaths(
    const std::vector<size_t>& component) const {
  std::set<size_t> paths;
  auto addPaths = [&](size_t element) {
    paths.insert(
        elements_[element].paths.begin(), elements_[element].paths.end());
  };
  for (const auto element : component) {
    addPaths(element);
  }
  for (const auto& occurrence : occurrences_) {
    if (std::find(component.begin(), component.end(), occurrence.edge) ==
        component.end()) {
      continue;
    }
    for (const auto& end : occurrence.ends()) {
      if (elements_[end.vertex].folds()) {
        addPaths(end.vertex);
      }
    }
  }
  return paths;
}

NodeCP Translator::GraphMatchLowering::limitMatches(
    NodeCP node,
    const Path& path) {
  // row_number() OVER (PARTITION BY first, last) <= limit.
  ExprVector partitionKeys = identityOf(path.first, /*withTableId=*/false);
  appendAll(partitionKeys, identityOf(path.last, /*withTableId=*/false));
  ColumnCP rank = Column::create("$rank", Value(toType(velox::BIGINT())));
  ColumnVector outputColumns = node->outputColumns();
  outputColumns.push_back(rank);
  auto ranked = translator_.nodeSimplifier_.make(
      Window::Key{
          .input = node,
          .functions = {WindowFunction{
              translator_.exprFactory_.makeRowNumber(),
              Frame::toCurrentRow(),
              /*ignoreNulls=*/false}},
          .partitionKeys = std::move(partitionKeys),
          .orderKeys = {},
          .orderTypes = {},
          .outputColumns = std::move(outputColumns),
      },
      {node, {}});
  node = translator_.nodeSimplifier_.materialize(ranked);
  substitute(ranked.substitutions);
  return filter(
      node,
      {translator_.exprFactory_.makeLessThanOrEqual(
          rank,
          translator_.exprFactory_.makeLiteral(
              velox::Variant(static_cast<int64_t>(path.limit.value())),
              toType(velox::BIGINT())))});
}

NodeCP Translator::GraphMatchLowering::lowerComponent(
    const std::vector<size_t>& component) {
  auto pathPredicates = [&](size_t path) {
    return translatePredicates(paths_[path].predicates, path);
  };

  // Each path with a selector joins, filters and limits its own elements.
  // After copying, no element is in two of them.
  std::vector<std::vector<size_t>> groups;
  std::vector<NodeCP> nodes;
  std::vector<bool> grouped(elements_.size(), false);
  std::vector<size_t> unlimitedPaths;
  for (const auto path : componentPaths(component)) {
    if (!paths_[path].limit.has_value()) {
      unlimitedPaths.push_back(path);
      continue;
    }
    std::vector<size_t> members;
    std::vector<std::vector<size_t>> singletons;
    std::vector<NodeCP> memberNodes;
    for (const auto element : component) {
      if (elements_[element].paths.contains(path)) {
        members.push_back(element);
        singletons.push_back({element});
        memberNodes.push_back(elements_[element].node);
        VELOX_CHECK(!grouped[element]);
        grouped[element] = true;
      }
    }
    NodeCP node = join(singletons, std::move(memberNodes));
    if (!paths_[path].predicates.empty()) {
      node = filter(node, pathPredicates(path));
    }
    groups.push_back(std::move(members));
    nodes.push_back(limitMatches(node, paths_[path]));
  }
  for (const auto element : component) {
    if (!grouped[element]) {
      groups.push_back({element});
      nodes.push_back(elements_[element].node);
    }
  }

  NodeCP node = join(groups, std::move(nodes));
  ExprVector conjuncts;
  for (const auto path : unlimitedPaths) {
    appendAll(conjuncts, pathPredicates(path));
  }
  return conjuncts.empty() ? node : filter(node, std::move(conjuncts));
}

NodeCP Translator::GraphMatchLowering::join(
    const std::vector<std::vector<size_t>>& groups,
    std::vector<NodeCP> nodes) {
  // The group of each element, or nullopt for one in no group.
  std::vector<std::optional<size_t>> groupOf(elements_.size());
  for (size_t i = 0; i < groups.size(); ++i) {
    for (const auto element : groups[i]) {
      groupOf[element] = i;
    }
  }
  std::vector<bool> joined(groups.size(), false);
  // True if the connection links a joined group to one not joined yet.
  auto crosses = [&](const Connection& connection) {
    const auto left = groupOf[connection.leftElement];
    const auto right = groupOf[connection.rightElement];
    return left.has_value() && right.has_value() &&
        joined[*left] != joined[*right];
  };

  NodeCP node = nodes[0];
  joined[0] = true;
  node = walkWithin(node, groupOf, joined);
  for (size_t step = 1; step < groups.size(); ++step) {
    // The first group not joined yet, preferring one connected to the groups
    // joined so far, then one a walk reaches.
    std::optional<size_t> next;
    for (const auto& connection : connections_) {
      if (crosses(connection)) {
        const auto left = *groupOf[connection.leftElement];
        next = joined[left] ? *groupOf[connection.rightElement] : left;
        break;
      }
    }
    if (!next.has_value()) {
      for (size_t i = 0; i < repeatedEdges_.size(); ++i) {
        const auto& repeated = repeatedEdges_[i];
        const auto from = groupOf[holderOf(repeated.from)];
        const auto to = groupOf[holderOf(repeated.to)];
        if (walked_[i] || !from.has_value() || !to.has_value() ||
            joined[*from] == joined[*to]) {
          continue;
        }
        node = joined[*from] ? walk(repeated, node, nodes[*to])
                             : walk(repeated, nodes[*from], node);
        walked_[i] = true;
        next = joined[*from] ? *to : *from;
        break;
      }
      if (next.has_value()) {
        joined[*next] = true;
        node = walkWithin(node, groupOf, joined);
        continue;
      }
    }
    if (!next.has_value()) {
      next = std::find(joined.begin(), joined.end(), false) - joined.begin();
    }

    ExprVector leftKeys;
    ExprVector rightKeys;
    for (const auto& connection : connections_) {
      if (!crosses(connection)) {
        continue;
      }
      if (groupOf[connection.rightElement] == next) {
        appendAll(leftKeys, connection.leftKeys);
        appendAll(rightKeys, connection.rightKeys);
      } else if (groupOf[connection.leftElement] == next) {
        appendAll(leftKeys, connection.rightKeys);
        appendAll(rightKeys, connection.leftKeys);
      }
    }
    auto simplified = translator_.innerJoin(
        node, nodes[*next], std::move(leftKeys), std::move(rightKeys));
    node = translator_.nodeSimplifier_.materialize(simplified);
    joined[*next] = true;

    // The join may replace columns of its inputs, such as a key with the key
    // it equals. Later joins and outputs read the replacements.
    substitute(simplified.substitutions);
    node = walkWithin(node, groupOf, joined);
  }
  return node;
}

NodeCP Translator::GraphMatchLowering::walkWithin(
    NodeCP node,
    const std::vector<std::optional<size_t>>& groupOf,
    const std::vector<bool>& joined) {
  for (size_t i = 0; i < repeatedEdges_.size(); ++i) {
    const auto& repeated = repeatedEdges_[i];
    const auto from = groupOf[holderOf(repeated.from)];
    const auto to = groupOf[holderOf(repeated.to)];
    if (!walked_[i] && from.has_value() && to.has_value() && joined[*from] &&
        joined[*to]) {
      node = walk(repeated, node, /*end=*/nullptr);
      walked_[i] = true;
    }
  }
  return node;
}

NodeCP Translator::GraphMatchLowering::walk(
    const RepeatedEdge& repeated,
    NodeCP start,
    NodeCP end) {
  const auto& hop = elements_[repeated.edge];

  // Two vertex tables can hold the same key, so the identity a walk follows
  // includes the table ID wherever a hop can leave from or reach more than one
  // table.
  folly::F14FastSet<int32_t> tableIds;
  for (const auto& leg : hop.legs) {
    tableIds.insert(leg.tableId(/*end=*/true));
    tableIds.insert(leg.tableId(/*end=*/false));
  }
  const bool withTableId = tableIds.size() > 1;
  ExprVector startKeys = identityOf(repeated.from, withTableId);
  ExprVector endKeys = identityOf(repeated.to, withTableId);
  ExprVector hopSourceKeys = identity(hop, repeated.pointsRight, withTableId);
  ExprVector hopDestinationKeys =
      identity(hop, !repeated.pointsRight, withTableId);
  VELOX_CHECK_EQ(startKeys.size(), hopSourceKeys.size());
  VELOX_CHECK_EQ(endKeys.size(), hopDestinationKeys.size());
  for (size_t i = 0; i < hopSourceKeys.size(); ++i) {
    if (!hopSourceKeys[i]->value().type->equivalent(
            *hopDestinationKeys[i]->value().type)) {
      VELOX_NYI(
          "Repeated graph edge pattern whose ends have keys of different "
          "types is not supported yet: {}",
          hop.name);
    }
  }

  ColumnVector outputColumns = start->outputColumns();
  if (end != nullptr) {
    appendAll(outputColumns, end->outputColumns());
  }
  translator_.hasRepeat_ = true;
  return translator_.builder_.make<Repeat>({
      .start = start,
      .hop = hop.node,
      .end = end,
      .startKeys = std::move(startKeys),
      .hopSourceKeys = std::move(hopSourceKeys),
      .hopDestinationKeys = std::move(hopDestinationKeys),
      .endKeys = std::move(endKeys),
      .minHops = repeated.minHops,
      .maxHops = repeated.maxHops,
      .outputColumns = std::move(outputColumns),
  });
}

void Translator::GraphMatchLowering::filterHops() {
  for (const auto& repeated : repeatedEdges_) {
    if (repeated.predicates.empty()) {
      continue;
    }
    auto& hop = elements_[repeated.edge];
    auto conjuncts = translatePredicates(repeated.predicates, repeated.path);
    const auto hopColumns =
        PlanObjectSet::fromObjects(hop.node->outputColumns());
    for (ExprCP conjunct : conjuncts) {
      if (!conjunct->columns().isSubset(hopColumns)) {
        VELOX_NYI(
            "Predicate of a repeated graph edge pattern that reads another "
            "pattern is not supported yet: {}",
            hop.name);
      }
    }
    hop.node = filter(hop.node, std::move(conjuncts));
  }
}

NodeCP Translator::GraphMatchLowering::filter(
    NodeCP node,
    ExprVector conjuncts) {
  auto simplified = translator_.nodeSimplifier_.make(
      Filter::Key{node, std::move(conjuncts)}, {node, {}});
  substitute(simplified.substitutions);
  if (simplified.empty()) {
    return translator_.builder_.makeEmptyValues(node->outputColumns());
  }
  return simplified.node;
}

void Translator::GraphMatchLowering::substitute(
    const PlanSubstitutions& substitutions) {
  for (auto& element : elements_) {
    translator_.applySubstitutions(substitutions, element.scope);
    if (element.row != nullptr) {
      element.row = translator_.substitute(substitutions, element.row);
    }
  }
  for (auto& connection : connections_) {
    translator_.applySubstitutions(substitutions, connection.leftKeys);
    translator_.applySubstitutions(substitutions, connection.rightKeys);
  }
}

ExprVector Translator::GraphMatchLowering::translatePredicates(
    const std::vector<const lp::Expr*>& predicates,
    std::optional<size_t> path) const {
  Scope scope;
  for (const auto& [name, index] : elementByName_) {
    auto element = index;
    for (const auto& copy : copies_) {
      if (copy.original == index && copy.path == path) {
        element = copy.copy;
      }
    }
    if (elements_[element].row != nullptr) {
      scope[name] = elements_[element].row;
    }
  }
  ExprVector conjuncts;
  conjuncts.reserve(predicates.size());
  for (const auto* predicate : predicates) {
    conjuncts.push_back(
        translator_.translateExpr(*predicate, scope, /*liftTarget=*/nullptr));
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
      const auto length = pathLengths_.find(output.pattern());
      if (length == pathLengths_.end()) {
        VELOX_NYI(
            "Path length of a path with repetition is not supported yet: {}",
            output.pattern());
      }
      scope[names[i]] = translator_.exprFactory_.makeLiteral(
          velox::Variant(length->second), toType(velox::BIGINT()));
      continue;
    }
    const auto& element = elements_[elementByName_.at(output.pattern())];
    scope[names[i]] =
        element.scope.at(output.as<lp::GraphPropertyOutput>()->property());
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
