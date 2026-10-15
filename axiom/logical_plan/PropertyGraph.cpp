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

#include "axiom/logical_plan/PropertyGraph.h"

#include <fmt/ranges.h>
#include <folly/container/F14Set.h>

#include "axiom/logical_plan/GraphPattern.h"
#include "axiom/logical_plan/LogicalPlanNode.h"

namespace facebook::axiom::logical_plan {

bool PropertyGraph::Label::operator==(const Label& other) const {
  return name == other.name && *properties == *other.properties &&
      tableIds == other.tableIds;
}

bool PropertyGraph::ElementTable::operator==(const ElementTable& other) const {
  return id == other.id && *plan == *other.plan &&
      keyColumns == other.keyColumns &&
      std::equal(
             properties.begin(),
             properties.end(),
             other.properties.begin(),
             other.properties.end(),
             [](const auto& left, const auto& right) {
               return left.first == right.first &&
                   *left.second == *right.second;
             });
}

namespace {

using ElementTable = PropertyGraph::ElementTable;

// Returns the data types of 'columns' in the output of 'table's plan. Fails
// if the plan lacks one of them.
std::vector<velox::TypePtr> columnTypes(
    const ElementTable& table,
    const std::vector<std::string>& columns) {
  const auto& outputType = table.plan->outputType();
  std::vector<velox::TypePtr> types;
  types.reserve(columns.size());
  for (const auto& column : columns) {
    const auto index = outputType->getChildIdxIfExists(column);
    VELOX_USER_CHECK(
        index.has_value(),
        "Column not found in the plan of graph element table: {}, {}",
        table.id,
        column);
    types.push_back(outputType->childAt(index.value()));
  }
  return types;
}

bool equivalentTypes(
    const std::vector<velox::TypePtr>& lhs,
    const std::vector<velox::TypePtr>& rhs) {
  return std::equal(
      lhs.begin(),
      lhs.end(),
      rhs.begin(),
      rhs.end(),
      [](const auto& left, const auto& right) {
        return left->equivalent(*right);
      });
}

std::string toString(const std::vector<velox::TypePtr>& types) {
  std::vector<std::string> names;
  names.reserve(types.size());
  for (const auto& type : types) {
    names.push_back(type->toString());
  }
  return fmt::format("({})", fmt::join(names, ", "));
}

void checkProperties(
    const std::string& name,
    const velox::RowTypePtr& properties) {
  VELOX_USER_CHECK_NOT_NULL(
      properties, "Graph vertex or edge has no properties type: {}", name);
  folly::F14FastSet<std::string_view> names;
  for (const auto& property : properties->names()) {
    VELOX_USER_CHECK(
        names.insert(property).second,
        "Duplicate property in graph vertex or edge: {}.{}",
        name,
        property);
  }
}

// Checks 'tables' and indexes them by ID. Fails on an ID already in 'ids'.
template <typename T>
folly::F14FastMap<int32_t, const T*> indexTables(
    const std::vector<T>& tables,
    folly::F14FastSet<int32_t>& ids) {
  folly::F14FastMap<int32_t, const T*> index;
  for (const auto& table : tables) {
    VELOX_USER_CHECK_GE(
        table.id, 0, "Graph element table ID is negative: {}", table.id);
    VELOX_USER_CHECK(
        ids.insert(table.id).second,
        "Duplicate graph element table ID: {}",
        table.id);
    VELOX_USER_CHECK_NOT_NULL(
        table.plan, "Graph element table has no plan: {}", table.id);
    VELOX_USER_CHECK(
        !table.keyColumns.empty(),
        "Graph element table has no key: {}",
        table.id);
    for (const auto& [property, expression] : table.properties) {
      VELOX_USER_CHECK_NOT_NULL(
          expression,
          "Graph property has no expression: {}, {}",
          table.id,
          property);
    }
    index.emplace(table.id, &table);
  }
  return index;
}

// Checks that 'columns' of 'edge' hold the key of a row in vertex table
// 'vertexTableId'.
void checkEndpoint(
    const PropertyGraph::EdgeTable& edge,
    const std::vector<std::string>& columns,
    int32_t vertexTableId,
    const folly::F14FastMap<int32_t, const PropertyGraph::VertexTable*>&
        vertexTables) {
  const auto it = vertexTables.find(vertexTableId);
  VELOX_USER_CHECK(
      it != vertexTables.end(),
      "Edge table references an unknown vertex table: {}, {}",
      edge.id,
      vertexTableId);
  const auto& vertex = *it->second;
  const auto endpointTypes = columnTypes(edge, columns);
  const auto keyTypes = columnTypes(vertex, vertex.keyColumns);
  VELOX_USER_CHECK(
      equivalentTypes(endpointTypes, keyTypes),
      "Edge endpoint columns do not match the vertex table's key: {} {}, {} {}",
      edge.id,
      toString(endpointTypes),
      vertex.id,
      toString(keyTypes));
}

// Checks the tables vertex or edge 'name' references by 'ids': they exist,
// have keys of one set of data types, and define its 'properties'. Adds 'name'
// to their 'tableNames' and its property names to their 'declared'
// properties.
template <typename T>
void checkReferences(
    std::string_view kind,
    const std::string& name,
    const velox::RowTypePtr& properties,
    const std::set<int32_t>& ids,
    const folly::F14FastMap<int32_t, const T*>& tables,
    folly::F14FastMap<int32_t, std::vector<std::string>>& tableNames,
    folly::F14FastMap<int32_t, folly::F14FastSet<std::string>>& declared) {
  VELOX_USER_CHECK(
      !ids.empty(), "Graph {} is not backed by any table: {}", kind, name);
  // Keys are not empty, so empty 'keyTypes' means no table was checked yet.
  std::vector<velox::TypePtr> keyTypes;
  for (const auto id : ids) {
    const auto it = tables.find(id);
    VELOX_USER_CHECK(
        it != tables.end(),
        "Graph {} references an unknown {} table: {}, {}",
        kind,
        kind,
        name,
        id);
    const auto& table = *it->second;

    tableNames[id].push_back(name);

    auto tableKeyTypes = columnTypes(table, table.keyColumns);
    VELOX_USER_CHECK(
        keyTypes.empty() || equivalentTypes(keyTypes, tableKeyTypes),
        "Tables that back a graph {} have keys of different data types: {}, "
        "{} and {}",
        kind,
        name,
        toString(keyTypes),
        toString(tableKeyTypes));
    keyTypes = std::move(tableKeyTypes);

    for (auto i = 0; i < properties->size(); ++i) {
      const auto& property = properties->nameOf(i);
      const auto& type = properties->childAt(i);
      const auto propertyIt = table.properties.find(property);
      VELOX_USER_CHECK(
          propertyIt != table.properties.end(),
          "Graph element table does not define a property: {}, {}.{}",
          id,
          name,
          property);
      const auto& expressionType = propertyIt->second->type();
      VELOX_USER_CHECK(
          expressionType->equivalent(*type),
          "Graph property expression does not match the property's data "
          "type: {}, {}.{}, {} and {}",
          id,
          name,
          property,
          expressionType->toString(),
          type->toString());
      declared[id].insert(property);
    }
  }
}

} // namespace

PropertyGraph::PropertyGraph(
    std::string name,
    std::vector<Label> vertices,
    std::vector<Label> edges,
    std::vector<VertexTable> vertexTables,
    std::vector<EdgeTable> edgeTables)
    : name_{std::move(name)},
      vertices_{std::move(vertices)},
      edges_{std::move(edges)},
      vertexTables_{std::move(vertexTables)},
      edgeTables_{std::move(edgeTables)} {
  VELOX_USER_CHECK(!name_.empty(), "Property graph name is empty");
  VELOX_USER_CHECK(
      !vertices_.empty(), "Property graph has no vertices: {}", name_);

  folly::F14FastSet<std::string_view> names;
  for (const auto* labels : {&vertices_, &edges_}) {
    for (const auto& label : *labels) {
      VELOX_USER_CHECK(
          names.insert(label.name).second,
          "Duplicate graph vertex or edge: {}",
          label.name);
      checkProperties(label.name, label.properties);
    }
  }

  folly::F14FastSet<int32_t> tableIds;
  const auto vertexTableById = indexTables(vertexTables_, tableIds);
  const auto edgeTableById = indexTables(edgeTables_, tableIds);
  for (const auto& table : edgeTables_) {
    checkEndpoint(
        table, table.sourceColumns, table.sourceTableId, vertexTableById);
    checkEndpoint(
        table,
        table.destinationColumns,
        table.destinationTableId,
        vertexTableById);
  }

  folly::F14FastMap<int32_t, folly::F14FastSet<std::string>> declared;
  for (const auto& vertex : vertices_) {
    checkReferences(
        "vertex",
        vertex.name,
        vertex.properties,
        vertex.tableIds,
        vertexTableById,
        tableNames_,
        declared);
  }
  for (const auto& edge : edges_) {
    checkReferences(
        "edge",
        edge.name,
        edge.properties,
        edge.tableIds,
        edgeTableById,
        tableNames_,
        declared);
  }

  auto checkDeclared = [&](const ElementTable& table) {
    VELOX_USER_CHECK(
        tableNames_.contains(table.id),
        "Graph element table is not referenced by any vertex or edge: {}",
        table.id);
    const auto& names = declared[table.id];
    for (const auto& [property, expression] : table.properties) {
      VELOX_USER_CHECK(
          names.contains(property),
          "Graph element table defines a property that no vertex or edge "
          "referencing it declares: {}, {}",
          table.id,
          property);
    }
  };
  for (const auto& table : vertexTables_) {
    checkDeclared(table);
  }
  for (const auto& table : edgeTables_) {
    checkDeclared(table);
  }
}

std::vector<const PropertyGraph::ElementTable*> PropertyGraph::matchingTables(
    const GraphLabelExpression* label,
    bool edges) const {
  std::vector<const ElementTable*> result;
  auto add = [&](const ElementTable& table) {
    if (label == nullptr || label->matches(tableNames_.at(table.id))) {
      result.push_back(&table);
    }
  };
  if (edges) {
    for (const auto& table : edgeTables_) {
      add(table);
    }
  } else {
    for (const auto& table : vertexTables_) {
      add(table);
    }
  }
  return result;
}

// static
velox::RowTypePtr PropertyGraph::properties(
    const std::vector<const ElementTable*>& tables) {
  std::map<std::string, velox::TypePtr> types;
  folly::F14FastSet<std::string> conflicting;
  for (const auto* table : tables) {
    for (const auto& [name, expression] : table->properties) {
      auto [it, inserted] = types.emplace(name, expression->type());
      if (!inserted && !it->second->equivalent(*expression->type())) {
        conflicting.insert(name);
      }
    }
  }
  std::vector<std::string> names;
  std::vector<velox::TypePtr> children;
  for (const auto& [name, type] : types) {
    if (!conflicting.contains(name)) {
      names.push_back(name);
      children.push_back(type);
    }
  }
  return velox::ROW(std::move(names), std::move(children));
}

// static
velox::TypePtr PropertyGraph::propertyType(
    const std::vector<const ElementTable*>& tables,
    const std::string& property) {
  const ElementTable* resultTable = nullptr;
  velox::TypePtr result;
  for (const auto* table : tables) {
    const auto it = table->properties.find(property);
    if (it == table->properties.end()) {
      continue;
    }
    const auto& type = it->second->type();
    VELOX_USER_CHECK(
        result == nullptr || result->equivalent(*type),
        "Tables an element can match give a property different data types: "
        "{}, {} {} and {} {}",
        property,
        resultTable != nullptr ? resultTable->id : 0,
        result != nullptr ? result->toString() : "",
        table->id,
        type->toString());
    result = type;
    resultTable = table;
  }
  return result;
}

bool PropertyGraph::isVertex(std::string_view name) const {
  return std::any_of(
      vertices_.begin(), vertices_.end(), [&](const auto& vertex) {
        return vertex.name == name;
      });
}

bool PropertyGraph::isEdge(std::string_view name) const {
  return std::any_of(edges_.begin(), edges_.end(), [&](const auto& edge) {
    return edge.name == name;
  });
}

bool PropertyGraph::operator==(const PropertyGraph& other) const {
  return name_ == other.name_ && vertices_ == other.vertices_ &&
      edges_ == other.edges_ && vertexTables_ == other.vertexTables_ &&
      edgeTables_ == other.edgeTables_;
}

namespace {

using velox::ISerializable;

folly::dynamic serializeLabel(const PropertyGraph::Label& label) {
  folly::dynamic obj = folly::dynamic::object;
  obj["name"] = label.name;
  obj["properties"] = label.properties->serialize();
  obj["tableIds"] =
      folly::dynamic::array_range(label.tableIds.begin(), label.tableIds.end());
  return obj;
}

PropertyGraph::Label deserializeLabel(const folly::dynamic& obj) {
  std::set<int32_t> tableIds;
  for (const auto& id : obj["tableIds"]) {
    tableIds.insert(static_cast<int32_t>(id.asInt()));
  }
  return {
      .name = obj["name"].asString(),
      .properties =
          ISerializable::deserialize<velox::RowType>(obj["properties"]),
      .tableIds = std::move(tableIds),
  };
}

folly::dynamic serializeTable(const ElementTable& table) {
  folly::dynamic obj = folly::dynamic::object;
  obj["id"] = table.id;
  obj["plan"] = table.plan->serialize();
  obj["keyColumns"] = ISerializable::serialize(table.keyColumns);

  folly::dynamic properties = folly::dynamic::array;
  for (const auto& [property, expression] : table.properties) {
    folly::dynamic propertyObj = folly::dynamic::object;
    propertyObj["property"] = property;
    propertyObj["expression"] = expression->serialize();
    properties.push_back(std::move(propertyObj));
  }
  obj["properties"] = std::move(properties);
  return obj;
}

ElementTable deserializeTable(const folly::dynamic& obj, void* context) {
  ElementTable table{
      .id = static_cast<int32_t>(obj["id"].asInt()),
      .plan = ISerializable::deserialize<LogicalPlanNode>(obj["plan"], context),
      .keyColumns = ISerializable::deserialize<std::vector<std::string>>(
          obj["keyColumns"]),
  };
  for (const auto& propertyObj : obj["properties"]) {
    table.properties.emplace(
        propertyObj["property"].asString(),
        ISerializable::deserialize<Expr>(propertyObj["expression"], context));
  }
  return table;
}

} // namespace

folly::dynamic PropertyGraph::serialize() const {
  folly::dynamic obj = folly::dynamic::object;
  obj["name"] = name_;

  folly::dynamic vertices = folly::dynamic::array;
  for (const auto& vertex : vertices_) {
    vertices.push_back(serializeLabel(vertex));
  }
  obj["vertices"] = std::move(vertices);

  folly::dynamic edges = folly::dynamic::array;
  for (const auto& edge : edges_) {
    edges.push_back(serializeLabel(edge));
  }
  obj["edges"] = std::move(edges);

  folly::dynamic vertexTables = folly::dynamic::array;
  for (const auto& table : vertexTables_) {
    vertexTables.push_back(serializeTable(table));
  }
  obj["vertexTables"] = std::move(vertexTables);

  folly::dynamic edgeTables = folly::dynamic::array;
  for (const auto& table : edgeTables_) {
    auto tableObj = serializeTable(table);
    tableObj["sourceColumns"] = ISerializable::serialize(table.sourceColumns);
    tableObj["sourceTableId"] = table.sourceTableId;
    tableObj["destinationColumns"] =
        ISerializable::serialize(table.destinationColumns);
    tableObj["destinationTableId"] = table.destinationTableId;
    edgeTables.push_back(std::move(tableObj));
  }
  obj["edgeTables"] = std::move(edgeTables);
  return obj;
}

// static
PropertyGraphPtr PropertyGraph::create(
    const folly::dynamic& obj,
    void* context) {
  std::vector<Label> vertices;
  for (const auto& vertexObj : obj["vertices"]) {
    vertices.push_back(deserializeLabel(vertexObj));
  }

  std::vector<Label> edges;
  for (const auto& edgeObj : obj["edges"]) {
    edges.push_back(deserializeLabel(edgeObj));
  }

  std::vector<VertexTable> vertexTables;
  for (const auto& tableObj : obj["vertexTables"]) {
    vertexTables.push_back({deserializeTable(tableObj, context)});
  }

  std::vector<EdgeTable> edgeTables;
  for (const auto& tableObj : obj["edgeTables"]) {
    edgeTables.push_back({
        deserializeTable(tableObj, context),
        ISerializable::deserialize<std::vector<std::string>>(
            tableObj["sourceColumns"]),
        static_cast<int32_t>(tableObj["sourceTableId"].asInt()),
        ISerializable::deserialize<std::vector<std::string>>(
            tableObj["destinationColumns"]),
        static_cast<int32_t>(tableObj["destinationTableId"].asInt()),
    });
  }

  return std::make_shared<PropertyGraph>(
      obj["name"].asString(),
      std::move(vertices),
      std::move(edges),
      std::move(vertexTables),
      std::move(edgeTables));
}

} // namespace facebook::axiom::logical_plan
