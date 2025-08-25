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

#include "axiom/logical_plan/PlanBuilder.h"
#include "axiom/logical_plan/NameMappings.h"
#include "axiom/optimizer/connectors/ConnectorMetadata.h"
#include "velox/connectors/Connector.h"
#include "velox/exec/Aggregate.h"
#include "velox/exec/AggregateFunctionRegistry.h"
#include "velox/expression/Expr.h"
#include "velox/expression/SignatureBinder.h"
#include "velox/functions/FunctionRegistry.h"
#include "velox/parse/Expressions.h"
#include "velox/vector/VariantToVector.h"

namespace facebook::velox::logical_plan {

PlanBuilder& PlanBuilder::values(
    const RowTypePtr& rowType,
    std::vector<Variant> rows) {
  VELOX_USER_CHECK_NULL(node_, "Values node must be the leaf node");

  outputMapping_ = std::make_shared<NameMappings>();

  const auto numColumns = rowType->size();
  std::vector<std::string> outputNames;
  outputNames.reserve(numColumns);
  for (const auto& name : rowType->names()) {
    outputNames.push_back(newName(name));
    outputMapping_->add(name, outputNames.back());
  }

  node_ = std::make_shared<ValuesNode>(
      nextId(),
      ROW(std::move(outputNames), rowType->children()),
      std::move(rows));

  return *this;
}

PlanBuilder& PlanBuilder::values(const std::vector<RowVectorPtr>& values) {
  VELOX_USER_CHECK_NULL(node_, "Values node must be the leaf node");

  outputMapping_ = std::make_shared<NameMappings>();

  auto rowType = values.empty() ? ROW({}) : values.front()->rowType();
  const auto numColumns = rowType->size();
  std::vector<std::string> outputNames;
  outputNames.reserve(numColumns);
  for (const auto& name : rowType->names()) {
    outputNames.push_back(newName(name));
    outputMapping_->add(name, outputNames.back());
  }
  rowType = ROW(std::move(outputNames), rowType->children());

  std::vector<RowVectorPtr> newValues;
  newValues.reserve(values.size());
  for (const auto& value : values) {
    VELOX_USER_CHECK_NOT_NULL(value);
    VELOX_USER_CHECK(
        value->rowType()->equivalent(*rowType),
        "All values must have the equilent type: {} vs. {}",
        value->rowType()->toString(),
        rowType->toString());
    auto newValue = std::make_shared<RowVector>(
        value->pool(),
        rowType,
        value->nulls(),
        static_cast<size_t>(value->size()),
        value->children(),
        value->getNullCount());
    newValues.emplace_back(std::move(newValue));
  }

  node_ = std::make_shared<ValuesNode>(nextId(), std::move(newValues));

  return *this;
}

PlanBuilder& PlanBuilder::tableScan(const std::string& tableName) {
  VELOX_USER_CHECK(defaultConnectorId_.has_value());
  return tableScan(defaultConnectorId_.value(), tableName);
}

PlanBuilder& PlanBuilder::from(const std::vector<std::string>& tableNames) {
  VELOX_USER_CHECK_NULL(node_, "Table scan node must be the leaf node");
  VELOX_USER_CHECK(!tableNames.empty());

  tableScan(tableNames.front());

  Context context{defaultConnectorId_};
  context.planNodeIdGenerator = planNodeIdGenerator_;
  context.nameAllocator = nameAllocator_;

  for (auto i = 1; i < tableNames.size(); ++i) {
    crossJoin(PlanBuilder(context).tableScan(tableNames.at(i)));
  }

  return *this;
}

PlanBuilder& PlanBuilder::tableScan(
    const std::string& connectorId,
    const std::string& tableName) {
  VELOX_USER_CHECK_NULL(node_, "Table scan node must be the leaf node");

  auto* metadata = connector::getConnector(connectorId)->metadata();
  auto table = metadata->findTable(tableName);
  VELOX_USER_CHECK_NOT_NULL(table, "Table not found: {}", tableName);
  const auto& schema = table->rowType();

  const auto numColumns = schema->size();

  std::vector<TypePtr> columnTypes;
  columnTypes.reserve(numColumns);

  std::vector<std::string> outputNames;
  outputNames.reserve(numColumns);

  outputMapping_ = std::make_shared<NameMappings>();

  for (auto i = 0; i < schema->size(); ++i) {
    columnTypes.push_back(schema->childAt(i));

    outputNames.push_back(newName(schema->nameOf(i)));
    outputMapping_->add(schema->nameOf(i), outputNames.back());
  }

  node_ = std::make_shared<TableScanNode>(
      nextId(),
      ROW(outputNames, columnTypes),
      connectorId,
      tableName,
      schema->names());

  return *this;
}

PlanBuilder& PlanBuilder::tableScan(
    const std::string& tableName,
    const std::vector<std::string>& columnNames) {
  VELOX_USER_CHECK(defaultConnectorId_.has_value());
  return tableScan(defaultConnectorId_.value(), tableName, columnNames);
}

PlanBuilder& PlanBuilder::tableScan(
    const std::string& connectorId,
    const std::string& tableName,
    const std::vector<std::string>& columnNames) {
  VELOX_USER_CHECK_NULL(node_, "Table scan node must be the leaf node");

  auto* metadata = connector::getConnector(connectorId)->metadata();
  auto table = metadata->findTable(tableName);
  VELOX_USER_CHECK_NOT_NULL(table, "Table not found: {}", tableName);
  const auto& schema = table->rowType();

  const auto numColumns = columnNames.size();

  std::vector<TypePtr> columnTypes;
  columnTypes.reserve(numColumns);

  std::vector<std::string> outputNames;
  outputNames.reserve(numColumns);

  outputMapping_ = std::make_shared<NameMappings>();

  for (const auto& name : columnNames) {
    columnTypes.push_back(schema->findChild(name));

    outputNames.push_back(newName(name));
    outputMapping_->add(name, outputNames.back());
  }

  node_ = std::make_shared<TableScanNode>(
      nextId(),
      ROW(outputNames, columnTypes),
      connectorId,
      tableName,
      columnNames);

  return *this;
}

PlanBuilder& PlanBuilder::filter(const std::string& predicate) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Filter node cannot be a leaf node");

  auto untypedExpr = parse::parseExpr(predicate, parseOptions_);

  return filter(untypedExpr);
}

PlanBuilder& PlanBuilder::filter(const ExprApi& predicate) {
  auto expr = resolveScalarTypes(predicate.expr());

  node_ = std::make_shared<FilterNode>(nextId(), node_, expr);

  return *this;
}

namespace {
std::optional<std::string> tryGetRootName(const core::ExprPtr& expr) {
  if (const auto* fieldAccess =
          dynamic_cast<const core::FieldAccessExpr*>(expr.get())) {
    if (fieldAccess->isRootColumn()) {
      return fieldAccess->name();
    }
  }

  return std::nullopt;
}
} // namespace

std::vector<ExprApi> PlanBuilder::parse(const std::vector<std::string>& exprs) {
  std::vector<ExprApi> untypedExprs;
  untypedExprs.reserve(exprs.size());
  for (const auto& sql : exprs) {
    untypedExprs.emplace_back(parse::parseExpr(sql, parseOptions_));
  }

  return untypedExprs;
}

void PlanBuilder::resolveProjections(
    const std::vector<ExprApi>& projections,
    std::vector<std::string>& outputNames,
    std::vector<ExprPtr>& exprs,
    NameMappings& mappings) {
  for (const auto& untypedExpr : projections) {
    auto expr = resolveScalarTypes(untypedExpr.expr());

    const auto& alias = untypedExpr.name();

    if (expr->isInputReference()) {
      // Identity projection
      const auto& id = expr->asUnchecked<InputReferenceExpr>()->name();
      if (!alias.has_value() || id == alias.value()) {
        outputNames.push_back(id);

        const auto names = outputMapping_->reverseLookup(id);
        VELOX_USER_CHECK(!names.empty());

        for (const auto& name : names) {
          mappings.add(name, id);
        }
      } else {
        outputNames.push_back(newName(alias.value()));
        mappings.add(alias.value(), outputNames.back());
      }
    } else if (alias.has_value()) {
      outputNames.push_back(newName(alias.value()));
      mappings.add(alias.value(), outputNames.back());
    } else {
      outputNames.push_back(newName("expr"));
    }

    exprs.push_back(expr);
  }
}

PlanBuilder& PlanBuilder::project(const std::vector<std::string>& projections) {
  return project(parse(projections));
}

PlanBuilder& PlanBuilder::project(const std::vector<ExprApi>& projections) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Project node cannot be a leaf node");

  std::vector<std::string> outputNames;
  outputNames.reserve(projections.size());

  std::vector<ExprPtr> exprs;
  exprs.reserve(projections.size());

  auto newOutputMapping = std::make_shared<NameMappings>();

  resolveProjections(projections, outputNames, exprs, *newOutputMapping);

  node_ = std::make_shared<ProjectNode>(nextId(), node_, outputNames, exprs);
  outputMapping_ = newOutputMapping;

  return *this;
}

PlanBuilder& PlanBuilder::with(const std::vector<ExprApi>& projections) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Project node cannot be a leaf node");

  std::vector<std::string> outputNames;
  outputNames.reserve(projections.size());

  std::vector<ExprPtr> exprs;
  exprs.reserve(projections.size());

  auto newOutputMapping = std::make_shared<NameMappings>();

  const auto& inputType = node_->outputType();

  for (auto i = 0; i < inputType->size(); i++) {
    const auto& id = inputType->nameOf(i);

    outputNames.push_back(id);

    const auto names = outputMapping_->reverseLookup(id);
    for (const auto& name : names) {
      newOutputMapping->add(name, id);
    }

    exprs.push_back(
        std::make_shared<InputReferenceExpr>(inputType->childAt(i), id));
  }

  resolveProjections(projections, outputNames, exprs, *newOutputMapping);

  node_ = std::make_shared<ProjectNode>(nextId(), node_, outputNames, exprs);
  outputMapping_ = newOutputMapping;

  return *this;
}

PlanBuilder& PlanBuilder::aggregate(
    const std::vector<std::string>& groupingKeys,
    const std::vector<std::string>& aggregates) {
  return aggregate(parse(groupingKeys), parse(aggregates));
}

PlanBuilder& PlanBuilder::aggregate(
    const std::vector<ExprApi>& groupingKeys,
    const std::vector<ExprApi>& aggregates) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Aggregate node cannot be a leaf node");

  std::vector<std::string> outputNames;
  outputNames.reserve(groupingKeys.size() + aggregates.size());

  std::vector<ExprPtr> keyExprs;
  keyExprs.reserve(groupingKeys.size());

  auto newOutputMapping = std::make_shared<NameMappings>();

  resolveProjections(groupingKeys, outputNames, keyExprs, *newOutputMapping);

  std::vector<AggregateExprPtr> exprs;
  exprs.reserve(aggregates.size());

  for (const auto& aggregate : aggregates) {
    auto expr = resolveAggregateTypes(aggregate.expr());

    if (aggregate.name().has_value()) {
      const auto& alias = aggregate.name().value();
      outputNames.push_back(newName(alias));
      newOutputMapping->add(alias, outputNames.back());
    } else {
      outputNames.push_back(newName(expr->name()));
    }

    exprs.push_back(expr);
  }

  node_ = std::make_shared<AggregateNode>(
      nextId(),
      node_,
      keyExprs,
      std::vector<AggregateNode::GroupingSet>{},
      exprs,
      outputNames);

  outputMapping_ = newOutputMapping;

  return *this;
}

PlanBuilder& PlanBuilder::unnest(
    const std::vector<std::string>& unnestExprs,
    bool withOrdinality) {
  return unnest(parse(unnestExprs), withOrdinality);
}

PlanBuilder& PlanBuilder::unnest(
    const std::vector<ExprApi>& unnestExprs,
    bool withOrdinality,
    const std::optional<std::string>& alias,
    const std::vector<std::string>& unnestAliases) {
  auto newOutputMapping =
      node_ != nullptr ? outputMapping_ : std::make_shared<NameMappings>();

  size_t index = 0;

  auto addOutputMapping = [&](const std::string& name, const std::string& id) {
    if (!newOutputMapping->lookup(name)) {
      newOutputMapping->add(name, id);
    }
    newOutputMapping->add({.alias = alias, .name = name}, id);
    ++index;
  };

  std::vector<ExprPtr> exprs;
  std::vector<std::vector<std::string>> outputNames;
  for (const auto& unnestExpr : unnestExprs) {
    auto expr = resolveScalarTypes(unnestExpr.expr());
    exprs.push_back(expr);

    if (!unnestExpr.unnestedAliases().empty()) {
      outputNames.emplace_back();
      for (const std::string& alias : unnestExpr.unnestedAliases()) {
        outputNames.back().emplace_back(newName(alias));
        newOutputMapping->add(alias, outputNames.back().back());
      }
    } else {
      switch (expr->type()->kind()) {
        case TypeKind::ARRAY:
          if (!unnestAliases.empty()) {
            VELOX_USER_CHECK_LT(index, unnestAliases.size());

            const auto& outputName = unnestAliases.at(index);
            outputNames.emplace_back(
                std::vector<std::string>{newName(outputName)});

            addOutputMapping(outputName, outputNames.back().back());
          } else {
            outputNames.emplace_back(std::vector<std::string>{newName("e_")});
          }
          break;

        case TypeKind::MAP:
          if (!unnestAliases.empty()) {
            VELOX_USER_CHECK_LT(index, unnestAliases.size());

            const auto& keyName = unnestAliases.at(index);
            const auto& valueName = unnestAliases.at(index + 1);
            outputNames.emplace_back(
                std::vector<std::string>{newName(keyName), newName(valueName)});

            addOutputMapping(keyName, outputNames.back().at(0));
            addOutputMapping(valueName, outputNames.back().at(1));
          } else {
            outputNames.emplace_back(
                std::vector<std::string>{newName("k_"), newName("v_")});
          }
          break;

        default:
          VELOX_USER_FAIL(
              "Unsupported type to unnest: {}", expr->type()->toString());
      }
    }
  }

  std::optional<std::string> ordinalityName;
  if (withOrdinality) {
    ordinalityName = newName("orginality");
  }

  node_ = std::make_shared<UnnestNode>(
      nextId(), node_, exprs, outputNames, ordinalityName, withOrdinality);

  outputMapping_ = newOutputMapping;

  return *this;
}

namespace {

ExprPtr resolveJoinInputName(
    const std::optional<std::string>& alias,
    const std::string& name,
    const NameMappings& mapping,
    const RowTypePtr& inputRowType) {
  if (alias.has_value()) {
    if (auto id = mapping.lookup(alias.value(), name)) {
      return std::make_shared<InputReferenceExpr>(
          inputRowType->findChild(id.value()), id.value());
    }

    return nullptr;
  }

  if (auto id = mapping.lookup(name)) {
    return std::make_shared<InputReferenceExpr>(
        inputRowType->findChild(id.value()), id.value());
  }

  VELOX_USER_FAIL(
      "Cannot resolve column in join input: {} not found in [{}]",
      NameMappings::QualifiedName{alias, name}.toString(),
      mapping.toString());
}

std::string toString(
    const std::string& functionName,
    const std::vector<TypePtr>& argTypes) {
  std::ostringstream signature;
  signature << functionName << "(";
  for (auto i = 0; i < argTypes.size(); i++) {
    if (i > 0) {
      signature << ", ";
    }
    signature << argTypes[i]->toString();
  }
  signature << ")";
  return signature.str();
}

std::string toString(
    const std::vector<const exec::FunctionSignature*>& signatures) {
  std::stringstream out;
  for (auto i = 0; i < signatures.size(); ++i) {
    if (i > 0) {
      out << ", ";
    }
    out << signatures[i]->toString();
  }
  return out.str();
}

void applyCoersions(
    std::vector<ExprPtr>& inputs,
    const std::vector<TypePtr>& coersions) {
  if (coersions.empty()) {
    return;
  }

  for (auto i = 0; i < inputs.size(); ++i) {
    if (const auto& coersion = coersions.at(i)) {
      inputs[i] = std::make_shared<SpecialFormExpr>(
          coersion, SpecialForm::kCast, inputs[i]);
    }
  }
}

TypePtr resolveScalarFunction(
    const std::string& name,
    const std::vector<TypePtr>& argTypes,
    bool allowCoersions,
    std::vector<TypePtr>& coercions) {
  if (allowCoersions) {
    if (auto type = resolveFunctionWithCoercions(name, argTypes, coercions)) {
      return type;
    }
  } else {
    if (auto type = resolveFunction(name, argTypes)) {
      return type;
    }
  }

  auto allSignatures = getFunctionSignatures();
  auto it = allSignatures.find(name);
  if (it == allSignatures.end()) {
    VELOX_USER_FAIL("Scalar function doesn't exist: {}.", name);
  } else {
    const auto& functionSignatures = it->second;
    VELOX_USER_FAIL(
        "Scalar function signature is not supported: {}. Supported signatures: {}.",
        toString(name, argTypes),
        toString(functionSignatures));
  }
}

ExprPtr tryResolveSpecialForm(
    const std::string& name,
    const std::vector<ExprPtr>& resolvedInputs) {
  if (name == "and") {
    return std::make_shared<SpecialFormExpr>(
        BOOLEAN(), SpecialForm::kAnd, resolvedInputs);
  }

  if (name == "or") {
    return std::make_shared<SpecialFormExpr>(
        BOOLEAN(), SpecialForm::kOr, resolvedInputs);
  }

  if (name == "try") {
    return std::make_shared<SpecialFormExpr>(
        resolvedInputs.at(0)->type(), SpecialForm::kTry, resolvedInputs);
  }

  if (name == "coalesce") {
    return std::make_shared<SpecialFormExpr>(
        resolvedInputs.at(0)->type(), SpecialForm::kCoalesce, resolvedInputs);
  }

  if (name == "if") {
    return std::make_shared<SpecialFormExpr>(
        resolvedInputs.at(1)->type(), SpecialForm::kIf, resolvedInputs);
  }

  if (name == "switch") {
    return std::make_shared<SpecialFormExpr>(
        resolvedInputs.at(1)->type(), SpecialForm::kSwitch, resolvedInputs);
  }

  if (name == "subscript" && resolvedInputs.at(0)->type()->isRow()) {
    VELOX_USER_CHECK_EQ(2, resolvedInputs.size());

    const auto& rowType = resolvedInputs.at(0)->type()->asRow();

    const auto& fieldExpr = resolvedInputs.at(1);
    VELOX_USER_CHECK(fieldExpr->isConstant());
    VELOX_USER_CHECK_EQ(TypeKind::BIGINT, fieldExpr->type()->kind());

    const auto index =
        fieldExpr->asUnchecked<ConstantExpr>()->value()->value<int64_t>();

    VELOX_USER_CHECK_GE(index, 1);
    VELOX_USER_CHECK_LE(index, rowType.size());

    const int32_t zeroBasedIndex = index - 1;

    std::vector<ExprPtr> newInputs = {
        resolvedInputs.at(0),
        std::make_shared<ConstantExpr>(
            INTEGER(), std::make_shared<Variant>(zeroBasedIndex))};

    return std::make_shared<SpecialFormExpr>(
        rowType.childAt(zeroBasedIndex), SpecialForm::kDereference, newInputs);
  }

  if (name == "in") {
    return std::make_shared<SpecialFormExpr>(
        BOOLEAN(), SpecialForm::kIn, resolvedInputs);
  }

  if (name == "exists") {
    return std::make_shared<SpecialFormExpr>(
        BOOLEAN(), SpecialForm::kExists, resolvedInputs);
  }

  return nullptr;
}
} // namespace

ExprPtr ExprResolver::resolveLambdaExpr(
    const core::LambdaExpr* lambdaExpr,
    const std::vector<TypePtr>& lambdaInputTypes,
    const InputNameResolver& inputNameResolver) const {
  const auto& names = lambdaExpr->arguments();
  const auto& body = lambdaExpr->body();

  VELOX_CHECK_LE(names.size(), lambdaInputTypes.size());
  std::vector<TypePtr> types;
  types.reserve(names.size());
  for (auto i = 0; i < names.size(); ++i) {
    types.push_back(lambdaInputTypes[i]);
  }

  auto signature =
      ROW(std::vector<std::string>(names), std::vector<TypePtr>(types));
  auto lambdaResolver = [inputNameResolver, signature](
                            const std::optional<std::string>& alias,
                            const std::string& fieldName) -> ExprPtr {
    if (!alias.has_value()) {
      auto maybeIdx = signature->getChildIdxIfExists(fieldName);
      if (maybeIdx.has_value()) {
        return std::make_shared<InputReferenceExpr>(
            signature->childAt(maybeIdx.value()), fieldName);
      }
    }
    return inputNameResolver(alias, fieldName);
  };

  return std::make_shared<LambdaExpr>(
      signature, resolveScalarTypes(body, lambdaResolver));
}

namespace {
bool isLambdaArgument(const exec::TypeSignature& typeSignature) {
  return typeSignature.baseName() == "function";
}

bool hasLambdaArgument(const exec::FunctionSignature& signature) {
  for (const auto& type : signature.argumentTypes()) {
    if (isLambdaArgument(type)) {
      return true;
    }
  }

  return false;
}

bool isLambdaArgument(const exec::TypeSignature& typeSignature, int numInputs) {
  return isLambdaArgument(typeSignature) &&
      (typeSignature.parameters().size() == numInputs + 1);
}

bool isLambdaSignature(
    const exec::FunctionSignature* signature,
    const std::shared_ptr<const core::CallExpr>& callExpr) {
  if (!hasLambdaArgument(*signature)) {
    return false;
  }

  const auto numArguments = callExpr->inputs().size();

  if (numArguments != signature->argumentTypes().size()) {
    return false;
  }

  bool match = true;
  for (auto i = 0; i < numArguments; ++i) {
    if (auto lambda =
            dynamic_cast<const core::LambdaExpr*>(callExpr->inputAt(i).get())) {
      const auto numLambdaInputs = lambda->arguments().size();
      const auto& argumentType = signature->argumentTypes()[i];
      if (!isLambdaArgument(argumentType, numLambdaInputs)) {
        match = false;
        break;
      }
    }
  }

  return match;
}

const exec::FunctionSignature* FOLLY_NULLABLE findLambdaSignature(
    const std::vector<std::shared_ptr<exec::AggregateFunctionSignature>>&
        signatures,
    const std::shared_ptr<const core::CallExpr>& callExpr) {
  const exec::FunctionSignature* matchingSignature = nullptr;
  for (const auto& signature : signatures) {
    if (isLambdaSignature(signature.get(), callExpr)) {
      VELOX_CHECK_NULL(
          matchingSignature,
          "Cannot resolve ambiguous lambda function signatures for {}.",
          callExpr->name());
      matchingSignature = signature.get();
    }
  }

  return matchingSignature;
}

const exec::FunctionSignature* FOLLY_NULLABLE findLambdaSignature(
    const std::vector<const exec::FunctionSignature*>& signatures,
    const std::shared_ptr<const core::CallExpr>& callExpr) {
  const exec::FunctionSignature* matchingSignature = nullptr;
  for (const auto& signature : signatures) {
    if (isLambdaSignature(signature, callExpr)) {
      VELOX_CHECK_NULL(
          matchingSignature,
          "Cannot resolve ambiguous lambda function signatures for {}.",
          callExpr->name());
      matchingSignature = signature;
    }
  }

  return matchingSignature;
}

const exec::FunctionSignature* findLambdaSignature(
    const std::shared_ptr<const core::CallExpr>& callExpr) {
  // Look for a scalar lambda function.
  auto scalarSignatures = getFunctionSignatures(callExpr->name());
  if (!scalarSignatures.empty()) {
    return findLambdaSignature(scalarSignatures, callExpr);
  }

  // Look for an aggregate lambda function.
  if (auto signatures =
          exec::getAggregateFunctionSignatures(callExpr->name())) {
    return findLambdaSignature(signatures.value(), callExpr);
  }

  return nullptr;
}
} // namespace

ExprPtr ExprResolver::tryResolveCallWithLambdas(
    const std::shared_ptr<const core::CallExpr>& callExpr,
    const InputNameResolver& inputNameResolver) const {
  if (callExpr == nullptr) {
    return nullptr;
  }
  auto signature = findLambdaSignature(callExpr);

  if (signature == nullptr) {
    return nullptr;
  }

  // Resolve non-lambda arguments first.
  auto numArgs = callExpr->inputs().size();
  std::vector<ExprPtr> children(numArgs);
  std::vector<TypePtr> childTypes(numArgs);
  for (auto i = 0; i < numArgs; ++i) {
    if (!isLambdaArgument(signature->argumentTypes()[i])) {
      children[i] = resolveScalarTypes(callExpr->inputAt(i), inputNameResolver);
      childTypes[i] = children[i]->type();
    }
  }

  // Resolve lambda arguments.
  exec::SignatureBinder binder(*signature, childTypes);
  binder.tryBind();
  for (auto i = 0; i < numArgs; ++i) {
    auto argSignature = signature->argumentTypes()[i];
    if (isLambdaArgument(argSignature)) {
      std::vector<TypePtr> lambdaTypes;
      for (auto j = 0; j < argSignature.parameters().size() - 1; ++j) {
        auto type = binder.tryResolveType(argSignature.parameters()[j]);
        if (type == nullptr) {
          return nullptr;
        }
        lambdaTypes.push_back(type);
      }

      children[i] = resolveLambdaExpr(
          dynamic_cast<const core::LambdaExpr*>(callExpr->inputs()[i].get()),
          lambdaTypes,
          inputNameResolver);
    }
  }

  std::vector<TypePtr> types;
  types.reserve(children.size());
  for (auto& child : children) {
    types.push_back(child->type());
  }

  std::vector<TypePtr> coersions;
  auto returnType = resolveScalarFunction(
      callExpr->name(), types, enableCoersions_, coersions);
  applyCoersions(children, coersions);

  return std::make_shared<CallExpr>(returnType, callExpr->name(), children);
}

core::TypedExprPtr ExprResolver::makeConstantTypedExpr(
    const ExprPtr& expr) const {
  auto vector = variantToVector(
      expr->type(), *expr->asUnchecked<ConstantExpr>()->value(), pool_.get());
  return std::make_shared<core::ConstantTypedExpr>(vector);
}

ExprPtr ExprResolver::makeConstant(const VectorPtr& vector) const {
  auto variant = std::make_shared<Variant>(vector->variantAt(0));
  return std::make_shared<ConstantExpr>(vector->type(), std::move(variant));
}

ExprPtr ExprResolver::tryFoldCall(
    const TypePtr& type,
    const std::string& name,
    const std::vector<ExprPtr>& inputs) const {
  if (!queryCtx_) {
    return nullptr;
  }
  for (const auto& arg : inputs) {
    if (arg->kind() != ExprKind::kConstant) {
      return nullptr;
    }
  }
  std::vector<core::TypedExprPtr> args;
  args.reserve(inputs.size());
  for (const auto& arg : inputs) {
    args.push_back(makeConstantTypedExpr(arg));
  }
  auto vector = exec::tryEvaluateConstantExpression(
      std::make_shared<core::CallTypedExpr>(type, std::move(args), name),
      pool_.get(),
      queryCtx_,
      true);
  if (vector) {
    return makeConstant(vector);
  }
  return nullptr;
}

ExprPtr ExprResolver::tryFoldSpecialForm(
    const std::string& name,
    const std::vector<ExprPtr>& inputs) const {
  if (!queryCtx_) {
    return nullptr;
  }
  if (name == "in" && inputs.at(0)->isConstant() &&
      !inputs.at(1)->isSubquery()) {
    auto elementType = inputs[0]->type();

    std::vector<Variant> arrayElements;
    arrayElements.reserve(inputs.size() - 1);
    for (size_t i = 1; i < inputs.size(); i++) {
      VELOX_USER_CHECK(inputs.at(i)->isConstant());
      arrayElements.push_back(
          *inputs.at(i)->asUnchecked<ConstantExpr>()->value());
    }

    auto arrayConstant = std::make_shared<ConstantExpr>(
        ARRAY(elementType),
        std::make_shared<Variant>(Variant::array(arrayElements)));

    return tryFoldCall(BOOLEAN(), "in", {inputs[0], arrayConstant});
  }
  return nullptr;
}

ExprPtr ExprResolver::tryFoldCast(const TypePtr& type, const ExprPtr& input)
    const {
  if (!queryCtx_ || input->kind() != ExprKind::kConstant) {
    return nullptr;
  }
  auto vector = exec::tryEvaluateConstantExpression(
      std::make_shared<core::CastTypedExpr>(
          type, makeConstantTypedExpr(input), false),
      pool_.get(),
      queryCtx_,
      true);
  if (vector) {
    return makeConstant(vector);
  }
  return nullptr;
}

ExprPtr ExprResolver::resolveScalarTypes(
    const core::ExprPtr& expr,
    const InputNameResolver& inputNameResolver) const {
  if (const auto* fieldAccess =
          dynamic_cast<const core::FieldAccessExpr*>(expr.get())) {
    const auto& name = fieldAccess->name();

    if (fieldAccess->isRootColumn()) {
      return inputNameResolver(std::nullopt, name);
    }

    if (auto rootName = tryGetRootName(fieldAccess->input())) {
      if (auto resolved = inputNameResolver(rootName, name)) {
        return resolved;
      }
    }

    auto input = resolveScalarTypes(fieldAccess->input(), inputNameResolver);

    VELOX_USER_CHECK_EQ(
        input->type()->kind(),
        TypeKind::ROW,
        "Expected a struct, but got {}",
        input->type()->toString());

    return std::make_shared<SpecialFormExpr>(
        input->type()->asRow().findChild(name),
        SpecialForm::kDereference,
        std::vector<ExprPtr>{
            input,
            std::make_shared<ConstantExpr>(
                VARCHAR(), std::make_shared<Variant>(name))});
  }

  if (const auto& constant =
          dynamic_cast<const core::ConstantExpr*>(expr.get())) {
    return std::make_shared<ConstantExpr>(
        constant->type(), std::make_shared<Variant>(constant->value()));
  }

  if (auto lambdaCall = tryResolveCallWithLambdas(
          std::dynamic_pointer_cast<const core::CallExpr>(expr),
          inputNameResolver)) {
    return lambdaCall;
  }

  std::vector<ExprPtr> inputs;
  inputs.reserve(expr->inputs().size());
  for (const auto& input : expr->inputs()) {
    inputs.push_back(resolveScalarTypes(input, inputNameResolver));
  }

  if (const auto* call = dynamic_cast<const core::CallExpr*>(expr.get())) {
    const auto& name = call->name();

    if (hook_ != nullptr) {
      auto result = hook_(name, inputs);
      if (result != nullptr) {
        return result;
      }
    }

    if (auto specialForm = tryResolveSpecialForm(name, inputs)) {
      if (auto folded = tryFoldSpecialForm(name, inputs)) {
        return folded;
      }
      return specialForm;
    }

    std::vector<TypePtr> inputTypes;
    inputTypes.reserve(inputs.size());
    for (const auto& input : inputs) {
      inputTypes.push_back(input->type());
    }

    std::vector<TypePtr> coersions;
    auto type =
        resolveScalarFunction(name, inputTypes, enableCoersions_, coersions);

    applyCoersions(inputs, coersions);

    auto folded = tryFoldCall(type, name, inputs);
    if (folded != nullptr) {
      return folded;
    }

    return std::make_shared<CallExpr>(type, name, inputs);
  }

  if (const auto* cast = dynamic_cast<const core::CastExpr*>(expr.get())) {
    auto folded = tryFoldCast(cast->type(), inputs[0]);
    if (folded != nullptr) {
      return folded;
    }

    return std::make_shared<SpecialFormExpr>(
        cast->type(),
        cast->isTryCast() ? SpecialForm::kTryCast : SpecialForm::kCast,
        inputs);
  }

  if (const auto* subquery =
          dynamic_cast<const core::SubqueryExpr*>(expr.get())) {
    return std::make_shared<SubqueryExpr>(subquery->subquery());
  }

  VELOX_NYI("Can't resolve {}", expr->toString());
}

AggregateExprPtr ExprResolver::resolveAggregateTypes(
    const core::ExprPtr& expr,
    const InputNameResolver& inputNameResolver) const {
  const auto* call = dynamic_cast<const core::CallExpr*>(expr.get());
  VELOX_USER_CHECK_NOT_NULL(
      call, "Aggregate must be a call expression: {}", expr->toString());

  const auto& name = call->name();

  std::vector<ExprPtr> inputs;
  inputs.reserve(expr->inputs().size());
  for (const auto& input : expr->inputs()) {
    inputs.push_back(resolveScalarTypes(input, inputNameResolver));
  }

  std::vector<TypePtr> inputTypes;
  inputTypes.reserve(inputs.size());
  for (const auto& input : inputs) {
    inputTypes.push_back(input->type());
  }

  if (auto type = exec::resolveAggregateFunction(name, inputTypes).first) {
    return std::make_shared<AggregateExpr>(type, name, inputs);
  }

  auto allSignatures = exec::getAggregateFunctionSignatures();
  auto it = allSignatures.find(name);
  if (it == allSignatures.end()) {
    VELOX_USER_FAIL("Aggregate function doesn't exist: {}.", name);
  } else {
    const auto& functionSignatures = it->second;
    VELOX_USER_FAIL(
        "Aggregate function signature is not supported: {}. Supported signatures: {}.",
        toString(name, inputTypes),
        toString(functionSignatures));
  }
}

PlanBuilder& PlanBuilder::join(
    const PlanBuilder& right,
    const std::string& condition,
    JoinType joinType) {
  std::optional<ExprApi> conditionExpr;
  if (!condition.empty()) {
    conditionExpr = parse::parseExpr(condition, parseOptions_);
  }

  return join(right, conditionExpr, joinType);
}

PlanBuilder& PlanBuilder::join(
    const PlanBuilder& right,
    const std::optional<ExprApi>& condition,
    JoinType joinType) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Join node cannot be a leaf node");
  VELOX_USER_CHECK_NOT_NULL(right.node_);

  // User-facing column names may have duplicates between left and right side.
  // Columns that are unique can be referenced as is. Columns that are not
  // unique must be referenced using an alias.
  outputMapping_->merge(*right.outputMapping_);

  auto inputRowType = node_->outputType()->unionWith(right.node_->outputType());

  ExprPtr expr;
  if (condition.has_value()) {
    expr = resolver_.resolveScalarTypes(
        condition->expr(), [&](const auto& alias, const auto& name) {
          return resolveJoinInputName(
              alias, name, *outputMapping_, inputRowType);
        });
  }

  node_ =
      std::make_shared<JoinNode>(nextId(), node_, right.node_, joinType, expr);

  return *this;
}

PlanBuilder& PlanBuilder::unionAll(const PlanBuilder& other) {
  VELOX_USER_CHECK_NOT_NULL(node_, "UnionAll node cannot be a leaf node");
  VELOX_USER_CHECK_NOT_NULL(other.node_);

  node_ = std::make_shared<SetNode>(
      nextId(),
      std::vector<LogicalPlanNodePtr>{node_, other.node_},
      SetOperation::kUnionAll);

  return *this;
}

PlanBuilder& PlanBuilder::intersect(const PlanBuilder& other) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Intersect node cannot be a leaf node");
  VELOX_USER_CHECK_NOT_NULL(other.node_);

  node_ = std::make_shared<SetNode>(
      nextId(),
      std::vector<LogicalPlanNodePtr>{node_, other.node_},
      SetOperation::kIntersect);

  return *this;
}

PlanBuilder& PlanBuilder::except(const PlanBuilder& other) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Intersect node cannot be a leaf node");
  VELOX_USER_CHECK_NOT_NULL(other.node_);

  node_ = std::make_shared<SetNode>(
      nextId(),
      std::vector<LogicalPlanNodePtr>{node_, other.node_},
      SetOperation::kExcept);

  return *this;
}

PlanBuilder& PlanBuilder::setOperation(
    SetOperation op,
    const std::vector<PlanBuilder>& inputs) {
  VELOX_USER_CHECK_NULL(node_, "setOperation must be a leaf");
  outputMapping_ = inputs.front().outputMapping_;
  std::vector<LogicalPlanNodePtr> nodes;
  nodes.reserve(inputs.size());
  for (auto& builder : inputs) {
    VELOX_CHECK_NOT_NULL(builder.node_);
    nodes.push_back(builder.node_);
  }
  node_ = std::make_shared<SetNode>(nextId(), std::move(nodes), op);
  return *this;
}

PlanBuilder& PlanBuilder::sort(const std::vector<std::string>& sortingKeys) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Sort node cannot be a leaf node");

  std::vector<SortingField> sortingFields;
  sortingFields.reserve(sortingKeys.size());

  for (const auto& key : sortingKeys) {
    auto orderBy = parse::parseOrderByExpr(key);
    auto expr = resolveScalarTypes(orderBy.expr);

    sortingFields.push_back(
        SortingField{expr, SortOrder(orderBy.ascending, orderBy.nullsFirst)});
  }

  node_ = std::make_shared<SortNode>(nextId(), node_, sortingFields);

  return *this;
}

PlanBuilder& PlanBuilder::sort(const std::vector<SortKey>& sortingKeys) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Sort node cannot be a leaf node");

  std::vector<SortingField> sortingFields;
  sortingFields.reserve(sortingKeys.size());

  for (const auto& key : sortingKeys) {
    auto expr = resolveScalarTypes(key.expr.expr());

    sortingFields.push_back(
        SortingField{expr, SortOrder(key.ascending, key.nullsFirst)});
  }

  node_ = std::make_shared<SortNode>(nextId(), node_, sortingFields);

  return *this;
}

PlanBuilder& PlanBuilder::limit(int64_t offset, int64_t count) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Limit node cannot be a leaf node");

  node_ = std::make_shared<LimitNode>(nextId(), node_, offset, count);

  return *this;
}

PlanBuilder& PlanBuilder::offset(int64_t offset) {
  VELOX_USER_CHECK_NOT_NULL(node_, "Offset node cannot be a leaf node");

  node_ = std::make_shared<LimitNode>(
      nextId(), node_, offset, std::numeric_limits<int64_t>::max());

  return *this;
}

ExprPtr PlanBuilder::resolveInputName(
    const std::optional<std::string>& alias,
    const std::string& name) const {
  if (outputMapping_ == nullptr) {
    VELOX_CHECK_NOT_NULL(outerScope_);
    return outerScope_(alias, name);
  }

  if (alias.has_value()) {
    if (auto id = outputMapping_->lookup(alias.value(), name)) {
      return std::make_shared<InputReferenceExpr>(
          node_->outputType()->findChild(id.value()), id.value());
    }

    if (outerScope_ != nullptr) {
      // TODO Figure out how to handle dereference.
      return outerScope_(alias, name);
    }

    return nullptr;
  }

  if (auto id = outputMapping_->lookup(name)) {
    return std::make_shared<InputReferenceExpr>(
        node_->outputType()->findChild(id.value()), id.value());
  }

  if (outerScope_ != nullptr) {
    return outerScope_(alias, name);
  }

  VELOX_USER_FAIL(
      "Cannot resolve column: {} not in [{}]",
      NameMappings::QualifiedName{alias, name}.toString(),
      outputMapping_->toString());
}

ExprPtr PlanBuilder::resolveScalarTypes(const core::ExprPtr& expr) const {
  return resolver_.resolveScalarTypes(
      expr, [&](const auto& alias, const auto& name) {
        return resolveInputName(alias, name);
      });
}

AggregateExprPtr PlanBuilder::resolveAggregateTypes(
    const core::ExprPtr& expr) const {
  return resolver_.resolveAggregateTypes(
      expr, [&](const auto& alias, const auto& name) {
        return resolveInputName(alias, name);
      });
}

PlanBuilder& PlanBuilder::as(const std::string& alias) {
  outputMapping_->setAlias(alias);
  return *this;
}

std::string PlanBuilder::newName(const std::string& hint) {
  return nameAllocator_->newName(hint);
}

size_t PlanBuilder::numOutput() const {
  VELOX_CHECK_NOT_NULL(node_);
  return node_->outputType()->size();
}

std::vector<std::string> PlanBuilder::findOrAssignOutputNames() const {
  auto size = numOutput();

  std::vector<std::string> names;
  names.reserve(size);

  for (auto i = 0; i < size; i++) {
    names.push_back(findOrAssignOutputNameAt(i));
  }

  return names;
}

std::string PlanBuilder::findOrAssignOutputNameAt(size_t index) const {
  const auto size = numOutput();
  VELOX_CHECK_LT(index, size, "{}", node_->outputType()->toString());

  auto id = node_->outputType()->nameOf(index);

  auto names = outputMapping_->reverseLookup(id);
  if (names.empty()) {
    // Assign a name to the output column.
    outputMapping_->add(id, id);
    return id;
  }

  // Prefer non-aliased name.
  for (const auto& name : names) {
    if (!name.alias.has_value()) {
      return name.name;
    }
  }

  return names.front().name;
}

LogicalPlanNodePtr PlanBuilder::build() {
  VELOX_USER_CHECK_NOT_NULL(node_);
  VELOX_USER_CHECK_NOT_NULL(outputMapping_);

  // Use user-specified names for the output. Should we add an OutputNode?

  const auto names = outputMapping_->uniqueNames();

  bool needRename = false;

  const auto& rowType = node_->outputType();

  std::vector<std::string> outputNames;
  outputNames.reserve(rowType->size());

  std::vector<ExprPtr> exprs;
  exprs.reserve(rowType->size());

  for (auto i = 0; i < rowType->size(); i++) {
    const auto& id = rowType->nameOf(i);

    auto it = names.find(id);
    if (it != names.end()) {
      outputNames.push_back(it->second);
    } else {
      outputNames.push_back(id);
    }

    if (id != outputNames.back()) {
      needRename = true;
    }

    exprs.push_back(
        std::make_shared<InputReferenceExpr>(rowType->childAt(i), id));
  }

  if (needRename) {
    return std::make_shared<ProjectNode>(nextId(), node_, outputNames, exprs);
  }

  return node_;
}

} // namespace facebook::velox::logical_plan
