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

#include <array>
#include <set>
#include <variant>

#include "axiom/optimizer/v2/Translator.h"

namespace facebook::axiom::optimizer::v2 {

/// Lowers one graph match into a plan of joins over the element tables.
///
/// Runs in stages, each reading what the earlier ones settled:
///
/// 1. Bind: binds each pattern name to an element, and records the paths and
///    the edge occurrences between their vertices.
/// 2. Narrow: drops the tables an element cannot match given its neighbors.
///    An element is a union of the remaining legs; an undirected edge has a
///    leg per orientation.
/// 3. Copy: an element that several paths with a selector bind gets a copy
///    for each of them but the first, since each such path is limited on its
///    own before paths join. A copy matches its original on identity.
/// 4. Fold: a vertex at a single edge end joins inside the legs of that edge,
///    and reads its identity from that end. A vertex table that reads the
///    edge table's own rows is projected over the edge's scan. Other vertices
///    keep a relation of their own.
/// 5. Build: builds each element's relation.
/// 6. Connect: connects each edge to the unfolded vertices next to it, and
///    each copy to its original, on their identities.
/// 7. Join: joins each path with a selector on its own, filters it with its
///    term predicates, and limits it to the selector's matches per pair of
///    endpoints. Then joins the rest of the connected elements and filters
///    them with the other paths' term predicates. Unconnected groups join
///    with a cross product, and the match predicate filters the result.
///
///   Stage    Reads             Produces
///   -------  ----------------  ----------------------------
///   Bind     the logical plan  Element::name
///                              Element::labelTables
///                              Element::properties
///                              Element::paths
///                              EdgeState
///                              'elementByName_'
///                              'occurrences_'
///                              'paths_'
///                              'pathLengths_'
///
///   Narrow   'occurrences_'    Element::legs
///            Element::labelTables
///            EdgeState
///
///   Copy     Element::paths    'copies_'
///            'paths_'          'elements_', with the copies
///            'occurrences_'    'occurrences_', repointed
///                              'paths_', repointed
///                              Element::needsIdentity
///
///   Fold     'paths_'          VertexState
///            'occurrences_'    Element::needsIdentity
///                              folded EdgeEnds
///
///   Build    Element::legs     Element::node
///            VertexState       Element::scope
///            EdgeState         Element::row
///            folded EdgeEnds
///
///   Connect  'occurrences_'    'connections_'
///            'copies_'
///            Element::scope
///
///   Join     'connections_'    the plan
///            Element::node     Element::scope, substituted
///            'paths_'          Element::row, substituted
///            Element::row      'connections_', substituted
///            'copies_'
class Translator::GraphMatchLowering {
 public:
  GraphMatchLowering(
      Translator& translator,
      const logical_plan::GraphMatchNode& match)
      : translator_{translator}, match_{match}, graph_{*match.graph()} {}

  /// Returns the lowered match with its outputs in 'required', or nullopt when
  /// the match is empty because an element has no table left after narrowing.
  std::optional<Translated> lower(const LpNameSet& required);

 private:
  using ElementTable = logical_plan::PropertyGraph::ElementTable;
  using EdgeTable = logical_plan::PropertyGraph::EdgeTable;

  // A table an element can match. For an edge, 'reversed' reads its
  // destination as the end the pattern leaves from.
  struct Leg {
    const ElementTable* table{nullptr};
    bool reversed{false};

    // The table ID and the key columns of an identity of the leg's rows. With
    // 'end' unset, the leg's own table and key. For an edge leg with 'end'
    // set, the vertex table at its source (true) or destination (false) end,
    // and the edge columns that hold that vertex's key.
    int32_t tableId(std::optional<bool> end) const;
    const std::vector<std::string>& keyColumns(std::optional<bool> end) const;
  };

  // State only a vertex has.
  struct VertexState {
    // Number of edge ends it sits at.
    int32_t numEdgeEnds{0};

    // For a vertex that folds, the edge whose legs it joins inside, and
    // whether it sits at that edge's source end.
    size_t foldedEdge{0};
    bool foldedAtSource{false};
  };

  // State only an edge has.
  struct EdgeState {
    // True if an undirected pattern binds it.
    bool undirected{false};

    // True if a repeated pattern binds it. Its relation is the hop of the
    // walks, which no connection joins.
    bool repeated{false};
  };

  // A vertex or edge that patterns bind.
  struct Element {
    // Pattern name, empty for an unnamed pattern.
    std::string name;

    // Tables its label expressions match.
    std::vector<const ElementTable*> labelTables;

    // Properties of 'labelTables', which make the ROW its pattern name stands
    // for in predicates.
    velox::RowTypePtr properties;

    // Tables it can match: 'labelTables' less those that cannot connect to
    // the elements next to it. Each is one leg of its relation; an undirected
    // edge has a leg per orientation that connects.
    std::vector<Leg> legs;

    // Indices of the paths that bind the element. A path with a selector that
    // binds a copy of it is the copy's.
    std::set<size_t> paths;

    // The element's rows. Null for a vertex that joins inside an edge's legs.
    NodeCP node{nullptr};

    // Expressions over 'node' by name: the element's properties, and the
    // '$'-prefixed columns that joins and selectors read. For a vertex that
    // joins inside an edge's legs, its properties as expressions over the
    // edge's rows.
    Scope scope;

    // The ROW of its properties that its pattern name stands for in
    // predicates. Null for an unnamed element or one without properties.
    ExprCP row{nullptr};

    // True if its identity is read: a selector partitions on it, or it
    // matches a copy of it. A vertex that joins inside an edge's legs reads
    // its identity from that edge's end.
    bool needsIdentity{false};

    // Vertex or edge, with the state of that kind.
    std::variant<VertexState, EdgeState> state;

    bool isVertex() const {
      return std::holds_alternative<VertexState>(state);
    }

    bool isEdge() const {
      return std::holds_alternative<EdgeState>(state);
    }

    // True for a vertex that joins inside the legs of its one edge: it sits
    // at a single edge end. Any other vertex has a relation of its own that
    // the edges join on its identity.
    bool folds() const {
      return isVertex() && std::get<VertexState>(state).numEdgeEnds == 1;
    }

    // True if the legs give the identity 'end' selects (see Leg::tableId)
    // more than one table ID.
    bool tableIdVaries(std::optional<bool> end) const;

    // Returns the columns that hold the identity 'end' selects: the table ID
    // when it varies, then the key.
    ExprVector identity(std::optional<bool> end) const;
  };

  // A vertex at one end of an edge occurrence.
  struct EdgeEnd {
    size_t vertex{0};
    // True for the source end of the edge's relation.
    bool source{false};
  };

  // An edge pattern and the vertex patterns before and after it.
  struct EdgeOccurrence {
    size_t edge{0};
    size_t from{0};
    size_t to{0};
    // True if the edge leaves 'from' at the source end of its relation.
    bool pointsRight{false};
    // Index of the path the edge pattern is in.
    size_t path{0};

    // Returns 'from' and 'to' with the end of the edge's relation each sits
    // at.
    std::array<EdgeEnd, 2> ends() const {
      return {{{from, pointsRight}, {to, !pointsRight}}};
    }
  };

  // A repeated edge pattern: walks of between 'minHops' and 'maxHops' hops over
  // the edge's relation, from vertex 'from' to vertex 'to'.
  struct RepeatedEdge {
    size_t edge{0};
    size_t from{0};
    size_t to{0};
    // True if each hop leaves at the source end of the edge's relation.
    bool pointsRight{false};
    int32_t minHops{0};
    int32_t maxHops{0};
    // Index of the path the edge pattern is in.
    size_t path{0};
    // The edge pattern's own predicates, which each hop satisfies.
    std::vector<const logical_plan::Expr*> predicates;
  };

  // A path pattern: its selector's limit on matches per pair of endpoints,
  // its endpoint vertices, and its term predicates.
  struct Path {
    std::optional<int32_t> limit;
    size_t first{0};
    size_t last{0};
    std::vector<const logical_plan::Expr*> predicates;
  };

  // A vertex table joined inside an edge leg, and its columns by name.
  struct FoldedVertex {
    const ElementTable* table{nullptr};
    Scope scope;
  };

  // Elements 'leftElement' and 'rightElement' match where 'leftKeys' equal
  // 'rightKeys'.
  struct Connection {
    size_t leftElement;
    ExprVector leftKeys;
    size_t rightElement;
    ExprVector rightKeys;
  };

  // Returns the state of the vertex or edge at 'index' in 'elements_'.
  VertexState& vertexAt(size_t index) {
    return std::get<VertexState>(elements_[index].state);
  }

  EdgeState& edgeAt(size_t index) {
    return std::get<EdgeState>(elements_[index].state);
  }

  // Returns the element 'pattern' binds.
  size_t bind(const logical_plan::GraphElementPattern& pattern, bool edge);

  // Binds the patterns of 'path', the path at 'pathIndex', and records its
  // edge occurrences.
  void addPath(const logical_plan::GraphPathPattern& path, size_t pathIndex);

  // Fails if a predicate or an output reads a repeated edge pattern's name
  // outside the pattern: there it stands for one value per hop.
  void checkGroupReads() const;

  // Drops the legs that cannot connect to the elements next to them, until
  // no more can be dropped. After it, each vertex table an edge leg
  // references at an end is a leg of the vertex there. Returns false if an
  // element has no legs left.
  bool narrow();

  // Gives each path with a selector its own copy of each element that an
  // earlier path with a selector binds.
  void copySharedElements();

  // Sets each vertex's VertexState. Returns, for each edge, the ends whose
  // vertices join inside its legs.
  std::vector<std::vector<EdgeEnd>> fold();

  // Translates the plan of 'table'.
  Translated translateTable(const ElementTable& table);

  // Builds the relation of a vertex that does not join inside an edge.
  void buildVertex(Element& vertex);

  // Builds the relation of the edge at 'edgeIndex', joining each leg with the
  // vertices at 'foldedEnds'.
  void buildEdge(size_t edgeIndex, const std::vector<EdgeEnd>& foldedEnds);

  // Drops the self-loops of 'table' from 'translated', a reversed leg's rows.
  Translated dropSelfLoops(Translated translated, const EdgeTable& table);

  // The rows of one leg of an edge: the edge table's rows, and the vertex
  // table at each folded end.
  struct LegRows {
    NodeCP node{nullptr};

    // The edge table's columns by name.
    Scope edgeScope;

    // The vertex table at each folded end, and its columns by name.
    std::vector<FoldedVertex> foldedVertices;
  };

  // Returns the rows of 'leg' with the vertex tables at 'foldedEnds'. A vertex
  // table whose row is the edge's row is read from the same scan; any other
  // joins on its key.
  LegRows translateLeg(const Leg& leg, const std::vector<EdgeEnd>& foldedEnds);

  // Translates 'tables', whose plans are Projects over scans of one table,
  // over one scan that reads every column they read. Returns each table's
  // translation, in order.
  std::vector<Translated> translateOverOneScan(
      const std::vector<const ElementTable*>& tables);

  // Joins 'vertexTable' to 'rows' where its key equals the edge's
  // 'endColumns'. Returns the vertex table's columns by name, and applies the
  // join's substitutions to 'rows'.
  Scope joinVertexTable(
      LegRows& rows,
      const std::vector<std::string>& endColumns,
      const ElementTable& vertexTable);

  // Binds each named element's pattern name to a ROW of its properties.
  void bindPatternNames();

  // Appends to 'exprs' each of 'properties' as 'table' computes it over
  // 'scope', or a typed NULL where 'table' does not define it.
  void appendProperties(
      const velox::RowType& properties,
      const ElementTable& table,
      const Scope& scope,
      ExprVector& exprs);

  // Sets the relation of 'element' to the UNION ALL of its legs, or to its
  // one leg. 'legExprs[i]' holds leg i's expressions for 'names'.
  void unionLegs(
      Element& element,
      std::vector<NodeCP> legNodes,
      const std::vector<ExprVector>& legExprs,
      const std::vector<std::string>& names,
      const std::vector<velox::TypePtr>& types);

  // Connects each edge occurrence to the vertices next to it.
  void connect();

  // Returns the element whose rows hold 'element': the edge a folded vertex
  // joins inside, or the element itself.
  size_t holderOf(size_t element) const;

  // Returns the groups of elements that connections join, each in the order
  // patterns bind them. A vertex joined inside an edge's legs is in none.
  std::vector<std::vector<size_t>> components() const;

  // Returns the columns that identify 'element'. A vertex that folds reads
  // them from its edge's end. With 'withTableId', the table ID comes first
  // even where it does not vary.
  ExprVector identityOf(size_t element, bool withTableId) const;

  // Returns the identity 'end' selects of 'element' (see
  // Element::identity), with the table ID first even where it does not vary
  // if 'withTableId'.
  ExprVector identity(
      const Element& element,
      std::optional<bool> end,
      bool withTableId) const;

  // Filters each repeated edge's relation with the edge pattern's own
  // predicates.
  void filterHops();

  // Returns the walks of 'repeated' between the rows of 'start', which holds
  // its 'from' vertex, and 'end', which holds its 'to' vertex. A null 'end'
  // means 'start' holds both.
  NodeCP walk(const RepeatedEdge& repeated, NodeCP start, NodeCP end);

  // Returns 'node' joined with the walks whose ends are both in the groups
  // 'joined' marks. 'groupOf' maps an element to its group.
  NodeCP walkWithin(
      NodeCP node,
      const std::vector<std::optional<size_t>>& groupOf,
      const std::vector<bool>& joined);

  // Returns the paths that bind the elements of 'component', or the vertices
  // that join inside its edges.
  std::set<size_t> componentPaths(const std::vector<size_t>& component) const;

  // Returns 'node' with at most the selector's limit of matches of 'path'
  // per pair of endpoints.
  NodeCP limitMatches(NodeCP node, const Path& path);

  // Returns the matches of the paths in 'component': each path with a
  // selector joined, filtered and limited on its own, then joined with the
  // rest of the elements and filtered with the other paths' predicates.
  NodeCP lowerComponent(const std::vector<size_t>& component);

  // Joins 'groups', each a set of elements whose rows 'nodes' holds, on the
  // connections between groups. Joins next a group connected to those joined
  // before it, so paths that share names join without a cross product.
  NodeCP join(
      const std::vector<std::vector<size_t>>& groups,
      std::vector<NodeCP> nodes);

  // Returns 'node' filtered by 'conjuncts'.
  NodeCP filter(NodeCP node, ExprVector conjuncts);

  // Applies node simplification facts to every expression the lowering
  // holds: element columns and rows, and connection keys.
  void substitute(const PlanSubstitutions& substitutions);

  // Translates 'predicates' against the pattern names. In the predicates of
  // 'path', a name stands for the copy of its element that path binds.
  ExprVector translatePredicates(
      const std::vector<const logical_plan::Expr*>& predicates,
      std::optional<size_t> path) const;

  // Returns the outputs in 'required' by output name.
  Scope outputs(const LpNameSet& required);

  Translator& translator_;
  const logical_plan::GraphMatchNode& match_;
  const logical_plan::PropertyGraph& graph_;

  // Bound elements, in the order patterns first name them.
  std::vector<Element> elements_;

  // Index in 'elements_' of the element each pattern name binds.
  folly::F14FastMap<std::string, size_t> elementByName_;

  // Edge patterns, in the order paths list them. A repeated edge pattern is
  // in 'repeatedEdges_' instead.
  std::vector<EdgeOccurrence> occurrences_;

  // Repeated edge patterns, in the order paths list them.
  std::vector<RepeatedEdge> repeatedEdges_;

  // True for each repeated edge whose walks are joined.
  std::vector<bool> walked_;

  // Pairs of adjacent elements and the columns they match on.
  std::vector<Connection> connections_;

  // An element, its copy, and the path with a selector the copy is for.
  struct ElementCopy {
    size_t original{0};
    size_t copy{0};
    size_t path{0};
  };

  // Copies of elements that several paths with a selector bind.
  std::vector<ElementCopy> copies_;

  // Number of edges in each named path.
  folly::F14FastMap<std::string, int64_t> pathLengths_;

  // Path patterns, in the order the node lists them.
  std::vector<Path> paths_;
};

} // namespace facebook::axiom::optimizer::v2
