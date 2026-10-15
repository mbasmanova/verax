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

#include <map>
#include <set>

#include <folly/container/F14Map.h>

#include "axiom/logical_plan/Expr.h"

namespace facebook::axiom::logical_plan {

class GraphLabelExpression;

/// Property graph over relational data, in two parts.
///
/// - Schema, which patterns use: vertex labels and edge labels, each with a
///   name and properties. A label in a pattern names one of them.
/// - Backing, which maps the schema to relational data: vertex tables and
///   edge tables, each with a plan, a key, and one expression per
///   property. Each label references the tables that back it. An edge label
///   connects the vertex labels that its edge tables' endpoint tables back.
///
/// Fully resolved: nothing is left to defaults. For example, a graph of
/// people who know each other:
///
///   PropertyGraph graph(
///       "g",
///       {{.name = "Person",
///         .properties = ROW("name", VARCHAR()),
///         .tableIds = {0}}},
///       {{.name = "Knows",
///         .properties = ROW({}, {}),
///         .tableIds = {1}}},
///       {{{.id = 0,
///          .plan = personScan,
///          .keyColumns = {"id"},
///          .properties = {{"name", nameColumn}}}}},
///       {{{.id = 1, .plan = knowsScan, .keyColumns = {"a", "b"}},
///         {"a"},
///         0,
///         {"b"},
///         0}});
///
/// Invariants:
/// - 'name' is not empty, and there is at least one vertex.
/// - Names are unique across vertices and edges, and property names are
///   unique within a vertex or edge.
/// - Table IDs are unique across vertex and edge tables, and not negative.
/// - Each table has a plan and a non-empty key of plan columns.
/// - Each vertex references at least one vertex table, and each edge at least
///   one edge table. All tables a vertex or edge references have keys of the
///   same data types.
/// - Each table is referenced by at least one vertex or edge. It defines
///   exactly the properties of the vertices or edges that reference it, each
///   with an expression of the declared data type.
/// - An edge table's source and destination vertex tables exist, and its
///   source and destination columns match those tables' keys in data type.
///
/// A key identifies a row within its table. The graph's definer guarantees
/// this; the constructor cannot check it.
class PropertyGraph {
 public:
  /// Vertex label, such as Person, or edge label, such as Knows, with the IDs
  /// of the vertex or edge tables that back it.
  struct Label {
    std::string name;
    velox::RowTypePtr properties;
    std::set<int32_t> tableIds;

    bool operator==(const Label& other) const;
  };

  /// Table that backs vertices or edges. Each row of 'plan' is one element.
  struct ElementTable {
    /// Unique within the graph and part of the graph's definition. Element
    /// identity is this ID plus the key, so a query over the same graph
    /// produces the same identities.
    int32_t id{0};

    /// Plan that produces the table's rows.
    LogicalPlanNodePtr plan;

    /// Columns of 'plan' that identify a row: unique and never null, like a
    /// primary key.
    std::vector<std::string> keyColumns;

    /// Expressions over the columns of 'plan', by property name.
    std::map<std::string, ExprPtr> properties;

    bool operator==(const ElementTable& other) const;
  };

  /// Table that backs vertices.
  struct VertexTable : ElementTable {};

  /// Edge table. Each edge row connects a source vertex row to a destination
  /// vertex row. 'sourceColumns' are columns of this table that hold the key
  /// of the source row in vertex table 'sourceTableId', aligned with
  /// that table's 'keyColumns', like a foreign key; likewise for the
  /// destination. For example, in 'knows' (a, b) between rows of 'person' with
  /// key (id), 'sourceColumns' is (a) and 'destinationColumns' is (b).
  struct EdgeTable : ElementTable {
    std::vector<std::string> sourceColumns;
    int32_t sourceTableId{0};
    std::vector<std::string> destinationColumns;
    int32_t destinationTableId{0};

    bool operator==(const EdgeTable& other) const = default;
  };

  PropertyGraph(
      std::string name,
      std::vector<Label> vertices,
      std::vector<Label> edges,
      std::vector<VertexTable> vertexTables,
      std::vector<EdgeTable> edgeTables);

  const std::string& name() const {
    return name_;
  }

  const std::vector<Label>& vertices() const {
    return vertices_;
  }

  const std::vector<Label>& edges() const {
    return edges_;
  }

  const std::vector<VertexTable>& vertexTables() const {
    return vertexTables_;
  }

  const std::vector<EdgeTable>& edgeTables() const {
    return edgeTables_;
  }

  bool isVertex(std::string_view name) const;

  bool isEdge(std::string_view name) const;

  /// Returns the vertex tables, or the edge tables if 'edges' is true, whose
  /// vertex or edge names satisfy 'label'. A null 'label' matches every table.
  std::vector<const ElementTable*> matchingTables(
      const GraphLabelExpression* label,
      bool edges) const;

  /// Returns the data type of 'property' for an element of 'tables', or
  /// nullptr if none of them defines it. Fails if two of them define it with
  /// different data types.
  static velox::TypePtr propertyType(
      const std::vector<const ElementTable*>& tables,
      const std::string& property);

  /// Returns the properties an element of 'tables' has, sorted by name: those
  /// the tables that define them give one data type.
  static velox::RowTypePtr properties(
      const std::vector<const ElementTable*>& tables);

  bool operator==(const PropertyGraph& other) const;

  folly::dynamic serialize() const;

  static std::shared_ptr<const PropertyGraph> create(
      const folly::dynamic& obj,
      void* context);

 private:
  std::string name_;
  std::vector<Label> vertices_;
  std::vector<Label> edges_;
  std::vector<VertexTable> vertexTables_;
  std::vector<EdgeTable> edgeTables_;

  // Names of the vertices or edges each table backs, by table ID.
  folly::F14FastMap<int32_t, std::vector<std::string>> tableNames_;
};

using PropertyGraphPtr = std::shared_ptr<const PropertyGraph>;

} // namespace facebook::axiom::logical_plan
