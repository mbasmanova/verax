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

#include "axiom/logical_plan/PlanBuilder.h"
#include "axiom/logical_plan/PropertyGraph.h"

namespace facebook::axiom::logical_plan {

/// Builds a PropertyGraph: vertices and edges, each backed by tables.
///
///   auto graph = GraphBuilder(context, "g")
///       .vertex("Person", {"name"})
///       .backedBy("person", {"id"})
///       .backedBy("employee", {"emp_id"}, {"full_name AS name"})
///       .edge("Knows", {"since"})
///       .backedBy("knows", "person", {"a"}, "person", {"b"})
///       .build();
///
/// backedBy() adds a table to the vertex or edge defined last; an edge table
/// also names its source and destination endpoints. Each property reads the
/// table's column of the same name unless the table gives it an expression.
/// Tables are named; a named base table is scanned with the builder's
/// context.
///
/// build() assigns table IDs in definition order and checks:
/// - A table backing several vertices or edges is one table: one plan, one
///   key, the same endpoints, and one expression per property name.
/// - A table backs only vertices or only edges, and each edge table has both
///   endpoints.
/// - An endpoint references a vertex table.
class GraphBuilder {
 public:
  GraphBuilder(const PlanBuilder::Context& context, std::string name);

  /// Defines vertex 'name' with 'properties'. Defining a vertex again, with
  /// the same properties, continues it.
  GraphBuilder& vertex(std::string name, std::vector<std::string> properties);

  /// Defines edge 'name' with 'properties'. Defining an edge again, with the
  /// same properties, continues it.
  GraphBuilder& edge(std::string name, std::vector<std::string> properties);

  /// Endpoint of an edge table: edge 'columns' that hold the key of a row of
  /// vertex table 'table', aligned with that key.
  struct Endpoint {
    std::string table;
    std::vector<std::string> columns;

    /// The key columns 'columns' align with, in any order. Empty means the
    /// key in key order.
    std::vector<std::string> referencedColumns;

    bool operator==(const Endpoint& other) const = default;
  };

  /// Backs the vertex defined last with base table 'table', identified by
  /// 'keyColumns'.
  GraphBuilder& backedBy(
      std::string table,
      std::vector<std::string> keyColumns);

  /// @overload Takes expressions for some properties, as SQL "expr AS
  /// property".
  GraphBuilder& backedBy(
      std::string table,
      std::vector<std::string> keyColumns,
      const std::vector<std::string>& properties);

  /// Backs the edge defined last with base table 'table'. Edge columns
  /// 'sourceColumns' hold the key of a row of vertex table 'sourceTable',
  /// aligned with that key; likewise for the destination. The source columns,
  /// then the destination columns, identify an edge.
  GraphBuilder& backedBy(
      std::string table,
      std::string sourceTable,
      std::vector<std::string> sourceColumns,
      std::string destinationTable,
      std::vector<std::string> destinationColumns);

  /// @overload Takes expressions for some properties, as SQL "expr AS
  /// property".
  GraphBuilder& backedBy(
      std::string table,
      std::string sourceTable,
      std::vector<std::string> sourceColumns,
      std::string destinationTable,
      std::vector<std::string> destinationColumns,
      const std::vector<std::string>& properties);

  /// Backs the vertex defined last with the rows of 'plan' under name 'table'.
  /// Property expressions are aliased with the property name.
  GraphBuilder& backedBy(
      std::string table,
      PlanBuilder plan,
      std::vector<std::string> keyColumns,
      std::vector<ExprApi> properties);

  /// Backs the edge defined last with the rows of 'plan' under name 'table'.
  GraphBuilder& backedBy(
      std::string table,
      PlanBuilder plan,
      std::vector<std::string> keyColumns,
      Endpoint source,
      Endpoint destination,
      std::vector<ExprApi> properties);

  PropertyGraphPtr build();

 private:
  struct Label {
    std::string name;
    bool edge{false};
    std::vector<std::string> properties;

    // Names of the tables that back the label.
    std::vector<std::string> tables;
  };

  struct Table {
    std::string name;
    PlanBuilder plan;
    std::vector<std::string> keyColumns;
    bool edge{false};
    std::optional<Endpoint> source;
    std::optional<Endpoint> destination;

    // Expressions some backing gave properties, by property name.
    std::vector<std::pair<std::string, ExprApi>> properties;
  };

  GraphBuilder& defineLabel(Label label);

  // Adds 'table' to the label defined last, which is an edge if 'source'
  // and 'destination' are set.
  GraphBuilder& addBacking(
      std::string table,
      PlanBuilder plan,
      std::vector<std::string> keyColumns,
      std::optional<Endpoint> source,
      std::optional<Endpoint> destination,
      std::vector<ExprApi> properties);

  std::vector<ExprApi> parse(const std::vector<std::string>& sqls) const;

  // Returns the index of table 'name' in 'tables_', if any.
  std::optional<size_t> findTable(std::string_view name) const;

  // Returns every property each table defines, by table index: the
  // properties of the vertices or edges it backs, each an expression the
  // table gave or the column of the same name.
  std::vector<std::vector<std::pair<std::string, ExprApi>>> propertiesByTable()
      const;

  // Returns the columns of 'endpoint' aligned with the key of the vertex
  // table it references, and that table's index.
  std::pair<std::vector<std::string>, size_t> resolveEndpoint(
      const Table& edge,
      const Endpoint& endpoint) const;

  PlanBuilder::Context context_;
  const std::string name_;
  std::vector<Label> labels_;
  std::vector<Table> tables_;
  std::optional<size_t> lastLabel_;
};

} // namespace facebook::axiom::logical_plan
