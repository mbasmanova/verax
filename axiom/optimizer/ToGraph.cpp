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

#include "axiom/logical_plan/ExprPrinter.h"
#include "axiom/logical_plan/PlanPrinter.h"
#include "axiom/optimizer/FunctionRegistry.h"
#include "axiom/optimizer/Plan.h"
#include "axiom/optimizer/PlanUtils.h"
#include "velox/exec/AggregateFunctionRegistry.h"
#include "velox/expression/ConstantExpr.h"
#include "velox/expression/FunctionSignature.h"
#include "velox/functions/FunctionRegistry.h"
#include "velox/vector/VariantToVector.h"

#include <iostream>

namespace facebook::velox::optimizer {

namespace lp = facebook::velox::logical_plan;

/// Trace info to add to exception messages.
struct ToGraphContext {
  ToGraphContext(const lp::Expr* e) : expr(e), node(nullptr) {}

  ToGraphContext(const lp::LogicalPlanNode* n) : expr(nullptr), node(n) {}

  const lp::Expr* expr{nullptr};
  const lp::LogicalPlanNode* node{nullptr};
};

std::string toGraphMessage(VeloxException::Type exceptionType, void* arg) {
  auto ctx = reinterpret_cast<ToGraphContext*>(arg);
  if (ctx->expr != nullptr) {
    return fmt::format("Expr: {}", lp::ExprPrinter::toText(*ctx->expr));
  }
  if (ctx->node != nullptr) {
    return fmt::format(
        "Node: [{}] {}\n",
        ctx->node->id(),
        lp::PlanPrinter::summarizeToText(*ctx->node));
  }
  return "";
}

ExceptionContext makeExceptionContext(ToGraphContext* ctx) {
  ExceptionContext e;
  e.messageFunc = toGraphMessage;
  e.arg = ctx;
  return e;
}

void ToGraph::setDtOutput(
    DerivedTableP dt,
    const lp::LogicalPlanNode& logicalPlan) {
  const auto& outputType = logicalPlan.outputType();
  for (auto i = 0; i < outputType->size(); ++i) {
    const auto& type = outputType->childAt(i);
    const auto& name = outputType->nameOf(i);

    auto inner = translateColumn(name);
    dt->exprs.push_back(inner);

    Value value(toType(type), 0);
    auto* outer = make<Column>(toName(name), dt, value, toName(name));
    dt->columns.push_back(outer);
    renames_[name] = outer;
  }
}

void ToGraph::setDtUsedOutput(
    DerivedTableP dt,
    const lp::LogicalPlanNode& node) {
  const auto& type = node.outputType();
  for (auto i : usedChannels(node)) {
    const auto& name = type->nameOf(i);

    const auto* inner = translateColumn(name);
    dt->exprs.push_back(inner);

    const auto* outer =
        make<Column>(toName(name), dt, inner->value(), toName(name));
    dt->columns.push_back(outer);
    renames_[name] = outer;
  }
}

namespace {
bool isConstantTrue(ExprCP expr) {
  if (expr->type() != PlanType::kLiteralExpr) {
    return false;
  }
  const auto& variant = expr->as<Literal>()->literal();
  return variant.kind() == TypeKind::BOOLEAN && !variant.isNull() &&
      variant.value<bool>();
}
} // namespace

void ToGraph::translateConjuncts(const lp::ExprPtr& input, ExprVector& flat) {
  if (!input) {
    return;
  }
  if (isSpecialForm(input.get(), lp::SpecialForm::kAnd)) {
    for (auto& child : input->inputs()) {
      translateConjuncts(child, flat);
    }
  } else {
    auto translatedExpr = translateExpr(input);
    if (!isConstantTrue(translatedExpr)) {
      flat.push_back(translatedExpr);
    }
  }
}

ExprCP ToGraph::tryFoldConstant(
    const TypePtr& returnType,
    const std::string& callName,
    const ExprVector& literals) {
  try {
    Value value(toType(returnType), 1);
    auto* veraxExpr = make<Call>(
        PlanType::kCallExpr, toName(callName), value, literals, FunctionSet());
    auto typedExpr = queryCtx()->optimization()->toTypedExpr(veraxExpr);
    auto exprSet = evaluator_.compile(typedExpr);
    auto first = exprSet->exprs().front().get();
    if (auto constantExpr = dynamic_cast<const exec::ConstantExpr*>(first)) {
      auto typed = std::make_shared<lp::ConstantExpr>(
          constantExpr->type(),
          std::make_shared<Variant>(constantExpr->value()->variantAt(0)));

      return makeConstant(*typed);
    }
  } catch (const std::exception&) {
    // Swallow exception.
  }

  return nullptr;
}

bool ToGraph::isSubfield(const lp::Expr* expr, Step& step, lp::ExprPtr& input) {
  if (isSpecialForm(expr, lp::SpecialForm::kDereference)) {
    step.kind = StepKind::kField;
    auto maybeIndex =
        maybeIntegerLiteral(expr->inputAt(1)->asUnchecked<lp::ConstantExpr>());
    Name name = nullptr;
    int64_t id = 0;
    auto& rowType = expr->inputAt(0)->type()->as<TypeKind::ROW>();
    if (maybeIndex.has_value()) {
      id = maybeIndex.value();
      name = toName(rowType.nameOf(maybeIndex.value()));
    } else {
      auto& field = expr->inputAt(1)->asUnchecked<lp::ConstantExpr>()->value();
      name = toName(field->value<TypeKind::VARCHAR>());
      id = rowType.getChildIdx(name);
    }
    step.field = name;
    step.id = id;
    input = expr->inputAt(0);
    return true;
  }

  if (const auto* call = expr->asUnchecked<lp::CallExpr>()) {
    auto name = call->name();
    if (name == "subscript" || name == "element_at") {
      auto subscript = translateExpr(call->inputAt(1));
      if (subscript->is(PlanType::kLiteralExpr)) {
        step.kind = StepKind::kSubscript;
        auto& literal = subscript->as<Literal>()->literal();
        switch (subscript->value().type->kind()) {
          case TypeKind::VARCHAR:
            step.field = toName(literal.value<TypeKind::VARCHAR>());
            break;
          case TypeKind::BIGINT:
          case TypeKind::INTEGER:
          case TypeKind::SMALLINT:
          case TypeKind::TINYINT:
            step.id = integerValue(&literal);
            break;
          default:
            VELOX_UNREACHABLE();
        }
        input = expr->inputAt(0);
        return true;
      }
      return false;
    }
    if (name == "cardinality") {
      step.kind = StepKind::kCardinality;
      input = expr->inputAt(0);
      return true;
    }
  }
  return false;
}

void ToGraph::getExprForField(
    const lp::Expr* field,
    lp::ExprPtr& resultExpr,
    ColumnCP& resultColumn,
    const lp::LogicalPlanNode*& context) {
  for (;;) {
    auto& name = field->asUnchecked<lp::InputReferenceExpr>()->name();
    auto ordinal = context->outputType()->getChildIdx(name);
    if (const auto* project = context->asUnchecked<lp::ProjectNode>()) {
      auto& def = project->expressions()[ordinal];
      if (const auto* innerField = def->asUnchecked<lp::InputReferenceExpr>()) {
        context = context->inputAt(0).get();
        field = innerField;
        continue;
      }
      resultExpr = def;
      context = project->inputAt(0).get();
      return;
    }

    const auto& sources = context->inputs();
    if (sources.empty()) {
      auto leaf = findLeaf(context);
      auto it = renames_.find(name);
      VELOX_CHECK(it != renames_.end());
      auto maybeColumn = it->second;
      VELOX_CHECK(maybeColumn->is(PlanType::kColumnExpr));
      resultColumn = maybeColumn->as<Column>();
      resultExpr = nullptr;
      context = nullptr;
      const auto* relation = resultColumn->relation();
      VELOX_CHECK_NOT_NULL(relation);
      if (relation->is(PlanType::kTableNode) ||
          relation->is(PlanType::kValuesTableNode)) {
        VELOX_CHECK(leaf == relation);
      }
      return;
    }

    for (const auto& source : sources) {
      const auto& row = source->outputType();
      if (auto maybe = row->getChildIdxIfExists(name)) {
        context = source.get();
        break;
      }
    }
  }
}

std::optional<ExprCP> ToGraph::translateSubfield(const lp::ExprPtr& inputExpr) {
  std::vector<Step> steps;
  auto* source = exprSource_;
  auto expr = inputExpr;
  for (;;) {
    lp::ExprPtr input;
    Step step;
    VELOX_CHECK_NOT_NULL(expr);
    bool isStep = isSubfield(expr.get(), step, input);
    if (!isStep) {
      if (steps.empty()) {
        return std::nullopt;
      }
      // if this is a field we follow to the expr assigning the field if any.
      Step ignore;
      lp::ExprPtr ignore2;
      if (!isSubfield(expr.get(), ignore, ignore2)) {
        ColumnCP column = nullptr;
        if (expr->isInputReference()) {
          getExprForField(expr.get(), expr, column, source);
          if (expr) {
            continue;
          }
        }
        SubfieldProjections* skyline = nullptr;
        if (column) {
          auto it = allColumnSubfields_.find(column);
          if (it != allColumnSubfields_.end()) {
            skyline = &it->second;
          }
        } else {
          ensureFunctionSubfields(expr);
          auto call = expr->asUnchecked<lp::CallExpr>();
          auto it = functionSubfields_.find(call);
          if (it != functionSubfields_.end()) {
            skyline = &it->second;
          }
        }
        // 'steps is a path. 'skyline' is a map from path to Expr. If no prefix
        // of steps occurs in skyline, then the item referenced by steps is not
        // materialized. Otherwise, the prefix that matches one in skyline is
        // replaced by the Expr from skyline and the tail of 'steps' are tagged
        // on the Expr. If skyline is empty, then 'steps' simply becomes a
        // nested sequence of getters.
        if (steps.empty()) {
          return std::nullopt;
        }
        return makeGettersOverSkyline(steps, skyline, expr, column);
      }
    }
    steps.push_back(step);
    expr = input;
  }
}

namespace {
PathCP innerPath(const std::vector<Step>& steps, int32_t last) {
  std::vector<Step> reverse;
  for (int32_t i = steps.size() - 1; i >= last; --i) {
    reverse.push_back(steps[i]);
  }
  return toPath(std::move(reverse));
}

Variant* subscriptLiteral(TypeKind kind, const Step& step) {
  auto* ctx = queryCtx();
  switch (kind) {
    case TypeKind::VARCHAR:
      return ctx->registerVariant(
          std::make_unique<Variant>(std::string(step.field)));
    case TypeKind::BIGINT:
      return ctx->registerVariant(
          std::make_unique<Variant>(static_cast<int64_t>(step.id)));
    case TypeKind::INTEGER:
      return ctx->registerVariant(
          std::make_unique<Variant>(static_cast<int32_t>(step.id)));
    case TypeKind::SMALLINT:
      return ctx->registerVariant(
          std::make_unique<Variant>(static_cast<int16_t>(step.id)));
    case TypeKind::TINYINT:
      return ctx->registerVariant(
          std::make_unique<Variant>(static_cast<int8_t>(step.id)));
    default:
      VELOX_FAIL("Unsupported key type");
  }
}

} // namespace

ExprCP ToGraph::makeGettersOverSkyline(
    const std::vector<Step>& steps,
    const SubfieldProjections* skyline,
    const lp::ExprPtr& base,
    ColumnCP column) {
  int32_t last = steps.size() - 1;
  ExprCP expr = nullptr;
  if (skyline) {
    // We see how many trailing (inner) steps fall below skyline, i.e. address
    // enclosing containers that are not materialized.
    bool found = false;
    for (; last >= 0; --last) {
      auto inner = innerPath(steps, last);
      auto it = skyline->pathToExpr.find(inner);
      if (it != skyline->pathToExpr.end()) {
        expr = it->second;
        found = true;
        break;
      }
    }
    if (!found) {
      // The path is not materialized. Need a longer path. to intersect skyline.
      return nullptr;
    }
  } else {
    if (column) {
      expr = column;
    } else {
      trace(OptimizerOptions::kPreprocess, [&]() {
        std::cout << "Complex function with no skyline: steps="
                  << toPath(steps)->toString() << std::endl;
        std::cout << "base=" << lp::ExprPrinter::toText(*base) << std::endl;
        std::cout << "Columns=";
        for (auto& name : exprSource_->outputType()->names()) {
          std::cout << name << " ";
        }
        std::cout << std::endl;
      });
      expr = translateExpr(base);
    }
    last = steps.size();
  }

  std::vector<Step> reverse;
  for (int32_t i = last - 1; i >= 0; --i) {
    // We make a getter over expr made so far with 'steps[i]' as first.
    PathExpr pathExpr = {steps[i], nullptr, expr};
    auto it = deduppedGetters_.find(pathExpr);
    if (it != deduppedGetters_.end()) {
      expr = it->second;
    } else {
      auto& step = steps[i];
      switch (step.kind) {
        case StepKind::kField: {
          if (!step.field) {
            auto* type = toType(expr->value().type->childAt(step.id));
            expr = make<Field>(type, expr, step.id);
            break;
          }
          auto* type = toType(expr->value().type->childAt(
              expr->value().type->as<TypeKind::ROW>().getChildIdx(step.field)));
          expr = make<Field>(type, expr, step.field);
          break;
        }
        case StepKind::kSubscript: {
          auto inputType = expr->value().type;
          const Type* type = toType(
              inputType->childAt(inputType->kind() == TypeKind::ARRAY ? 0 : 1));
          auto subscriptType = toType(
              inputType->kind() == TypeKind::ARRAY
                  ? INTEGER()
                  : inputType->as<TypeKind::MAP>().childAt(0));
          auto subscriptKind = subscriptType->kind();
          ExprVector args;
          args.push_back(expr);
          args.push_back(make<Literal>(
              Value(subscriptType, 1), subscriptLiteral(subscriptKind, step)));
          expr = make<Call>(
              toName("subscript"),
              Value(type, 1),
              std::move(args),
              FunctionSet());
          break;
        }
        case StepKind::kCardinality: {
          expr = make<Call>(
              toName("cardinality"),
              Value(toType(INTEGER()), 1),
              ExprVector{expr},
              FunctionSet());
          break;
        }
        default:
          VELOX_NYI();
      }
      deduppedGetters_[pathExpr] = expr;
    }
  }
  return expr;
}

namespace {
std::optional<BitSet> findSubfields(
    const PlanSubfields& fields,
    const lp::CallExpr* call) {
  auto it = fields.argFields.find(call);
  if (it == fields.argFields.end()) {
    return std::nullopt;
  }
  auto& paths = it->second.resultPaths;
  auto it2 = paths.find(ResultAccess::kSelf);
  if (it2 == paths.end()) {
    return {};
  }
  return it2->second;
}
} // namespace

BitSet ToGraph::functionSubfields(
    const lp::CallExpr* call,
    bool controlOnly,
    bool payloadOnly) {
  BitSet subfields;
  if (!controlOnly) {
    auto maybe = findSubfields(payloadSubfields_, call);
    if (maybe.has_value()) {
      subfields = maybe.value();
    }
  }
  if (!payloadOnly) {
    auto maybe = findSubfields(controlSubfields_, call);
    if (maybe.has_value()) {
      subfields.unionSet(maybe.value());
    }
  }
  Path::subfieldSkyline(subfields);
  return subfields;
}

void ToGraph::ensureFunctionSubfields(const lp::ExprPtr& expr) {
  if (const auto* call = expr->asUnchecked<lp::CallExpr>()) {
    auto metadata = functionMetadata(exec::sanitizeName(call->name()));
    if (!metadata) {
      return;
    }
    if (!translatedSubfieldFuncs_.count(call)) {
      translateExpr(expr);
    }
  }
}

BuiltinNames::BuiltinNames()
    : eq(toName("eq")),
      lt(toName("lt")),
      lte(toName("lte")),
      gt(toName("gt")),
      gte(toName("gte")),
      plus(toName("plus")),
      multiply(toName("multiply")),
      _and(toName(SpecialFormCallNames::kAnd)),
      _or(toName(SpecialFormCallNames::kOr)),
      cast(toName(SpecialFormCallNames::kCast)),
      tryCast(toName(SpecialFormCallNames::kTryCast)),
      _try(toName(SpecialFormCallNames::kTry)),
      coalesce(toName(SpecialFormCallNames::kCoalesce)),
      _if(toName(SpecialFormCallNames::kIf)),
      _switch(toName(SpecialFormCallNames::kSwitch)),
      in(toName(SpecialFormCallNames::kIn)) {
  canonicalizable.insert(eq);
  canonicalizable.insert(lt);
  canonicalizable.insert(lte);
  canonicalizable.insert(gt);
  canonicalizable.insert(gte);
  canonicalizable.insert(plus);
  canonicalizable.insert(multiply);
  canonicalizable.insert(_and);
  canonicalizable.insert(_or);
}

Name BuiltinNames::reverse(Name name) const {
  if (name == lt) {
    return gt;
  }
  if (name == lte) {
    return gte;
  }
  if (name == gt) {
    return lt;
  }
  if (name == gte) {
    return lte;
  }
  return name;
}

BuiltinNames& ToGraph::builtinNames() {
  if (!builtinNames_) {
    builtinNames_ = std::make_unique<BuiltinNames>();
  }
  return *builtinNames_;
}

namespace {

/// If we should reverse the sides of a binary expression to canonicalize it. We
/// invert in two cases:
///
///  #1. If there is a literal in the left and something else in the right:
///    f("literal", col) => f(col, "literal")
///
///  #2. If none are literal, but the id on the left is higher.
bool shouldInvert(ExprCP left, ExprCP right) {
  if (left->is(PlanType::kLiteralExpr) &&
      right->type() != PlanType::kLiteralExpr) {
    return true;
  } else if (
      (left->type() != PlanType::kLiteralExpr) &&
      (right->type() != PlanType::kLiteralExpr) && (left->id() > right->id())) {
    return true;
  } else {
    return false;
  }
}

} // namespace

void ToGraph::canonicalizeCall(Name& name, ExprVector& args) {
  auto& names = builtinNames();
  if (!names.isCanonicalizable(name)) {
    return;
  }
  VELOX_CHECK_EQ(args.size(), 2, "Expecting binary op {}", name);
  if (shouldInvert(args[0], args[1])) {
    std::swap(args[0], args[1]);
    name = names.reverse(name);
  }
}

ExprCP ToGraph::deduppedCall(
    Name name,
    Value value,
    ExprVector args,
    FunctionSet flags) {
  if (args.size() == 2) {
    canonicalizeCall(name, args);
  }
  ExprDedupKey key = {name, &args};
  auto it = functionDedup_.find(key);
  if (it != functionDedup_.end()) {
    return it->second;
  }
  auto* call =
      make<Call>(name, std::move(value), std::move(args), std::move(flags));
  if (!call->containsNonDeterministic()) {
    key.args = &call->args();
    functionDedup_[key] = call;
  }
  return call;
}

ExprCP ToGraph::makeConstant(const lp::ConstantExpr& constant) {
  auto temp = constant.value();
  auto it = constantDedup_.find(temp);
  if (it != constantDedup_.end()) {
    return it->second;
  }
  auto* literal = make<Literal>(Value(toType(constant.type()), 1), temp.get());
  // The variant will stay live for the optimization duration.
  reverseConstantDedup_[literal] = temp;
  constantDedup_[std::move(temp)] = literal;
  return literal;
}

namespace {
// Returns bits describing function 'name'.
FunctionSet functionBits(Name name) {
  if (auto* md = functionMetadata(name)) {
    return md->functionSet;
  }

  const auto deterministic = velox::isDeterministic(name);
  if (deterministic.has_value() && !deterministic.value()) {
    return FunctionSet(FunctionSet::kNonDeterministic);
  }

  return FunctionSet(0);
}

} // namespace

ExprCP ToGraph::translateExpr(const lp::ExprPtr& expr) {
  if (expr->isInputReference()) {
    return translateColumn(expr->asUnchecked<lp::InputReferenceExpr>()->name());
  }

  if (expr->isConstant()) {
    return makeConstant(*expr->asUnchecked<lp::ConstantExpr>());
  }
  auto path = translateSubfield(expr);
  if (path.has_value()) {
    return path.value();
  }

  if (expr->isLambda()) {
    return translateLambda(expr->asUnchecked<lp::LambdaExpr>());
  }

  ToGraphContext ctx(expr.get());
  ExceptionContextSetter s(makeExceptionContext(&ctx));

  const auto* call = expr->asUnchecked<lp::CallExpr>();
  std::string callName;
  if (call) {
    callName = exec::sanitizeName(call->name());
    auto* metadata = functionMetadata(callName);
    if (metadata && metadata->processSubfields()) {
      auto translated = translateSubfieldFunction(call, metadata);
      if (translated.has_value()) {
        return translated.value();
      }
    }
  }

  const lp::SpecialFormExpr* specialForm = expr->isSpecialForm()
      ? expr->asUnchecked<lp::SpecialFormExpr>()
      : nullptr;
  ExprVector args{expr->inputs().size()};
  PlanObjectSet columns;
  FunctionSet funcs;
  auto& inputs = expr->inputs();
  float cardinality = 1;
  bool allConstant = true;

  for (auto i = 0; i < inputs.size(); ++i) {
    args[i] = translateExpr(inputs[i]);
    allConstant &= args[i]->is(PlanType::kLiteralExpr);
    cardinality = std::max(cardinality, args[i]->value().cardinality);
    if (args[i]->is(PlanType::kCallExpr)) {
      funcs = funcs | args[i]->as<Call>()->functions();
    }
  }

  if (call || specialForm) {
    auto name = call
        ? toName(callName)
        : toName(SpecialFormCallNames::toCallName(specialForm->form()));
    if (allConstant) {
      if (auto literal = tryFoldConstant(expr->type(), name, args)) {
        return literal;
      }
    }
    funcs = funcs | functionBits(name);
    auto* callExpr = deduppedCall(
        name, Value(toType(expr->type()), cardinality), std::move(args), funcs);
    return callExpr;
  }

  VELOX_NYI();
  return nullptr;
}

ExprCP ToGraph::translateLambda(const lp::LambdaExpr* lambda) {
  auto savedRenames = renames_;
  auto row = lambda->signature();
  toType(row);
  toType(lambda->type());
  ColumnVector args;
  for (auto i = 0; i < row->size(); ++i) {
    auto col = make<Column>(
        toName(row->nameOf(i)), nullptr, Value(toType(row->childAt(i)), 1));
    args.push_back(col);
    renames_[row->nameOf(i)] = col;
  }
  auto body = translateExpr(lambda->body());
  renames_ = savedRenames;
  return make<Lambda>(std::move(args), toType(lambda->type()), body);
}

namespace {
// Returns a mask that allows 'op' in the same derived table.
uint64_t allow(PlanType op) {
  return 1UL << static_cast<int32_t>(op);
}

// True if 'op' is in 'mask.
bool contains(uint64_t mask, PlanType op) {
  return 0 != (mask & (1UL << static_cast<int32_t>(op)));
}
} // namespace

std::optional<ExprCP> ToGraph::translateSubfieldFunction(
    const lp::CallExpr* call,
    const FunctionMetadata* metadata) {
  translatedSubfieldFuncs_.insert(call);
  auto subfields = functionSubfields(call, false, false);
  if (subfields.empty()) {
    // The function is accessed as a whole.
    return std::nullopt;
  }
  auto* ctx = queryCtx();
  std::vector<PathCP> paths;
  subfields.forEach([&](auto id) { paths.push_back(ctx->pathById(id)); });
  ExprVector args(call->inputs().size());
  BitSet usedArgs;
  bool allUsed = false;
  if (metadata->argOrdinal.empty()) {
    allUsed = true;
  } else {
    for (auto i = 0; i < paths.size(); ++i) {
      if (std::find(
              metadata->argOrdinal.begin(), metadata->argOrdinal.end(), i) ==
          metadata->argOrdinal.end()) {
        // This argument is not a source of subfields over some field
        // of the return value. Compute this in any case. accessed
        usedArgs.add(i);
        continue;
      }
      auto& step = paths[i]->steps()[0];
      auto maybeArg = stepToArg(step, metadata);
      if (maybeArg.has_value()) {
        usedArgs.add(maybeArg.value());
      }
    }
  }

  float cardinality = 1;
  FunctionSet funcs;
  for (auto i = 0; i < call->inputs().size(); ++i) {
    if (allUsed || usedArgs.contains(i)) {
      args[i] = translateExpr(call->inputs()[i]);
      cardinality = std::max(cardinality, args[i]->value().cardinality);
      if (args[i]->is(PlanType::kCallExpr)) {
        funcs = funcs | args[i]->as<Call>()->functions();
      }
    } else {
      // make a null of the type for the unused arg to keep the tree valid.
      args[i] = make<Literal>(
          Value(toType(call->inputs()[i]->type()), 1),
          make<Variant>(Variant::null(call->inputs()[i]->type()->kind())));
    }
  }
  auto* name = toName(exec::sanitizeName(call->name()));
  funcs = funcs | functionBits(name);
  if (metadata->logicalExplode) {
    auto map = metadata->logicalExplode(call, paths);
    std::unordered_map<PathCP, ExprCP> translated;
    for (auto& pair : map) {
      translated[pair.first] = translateExpr(pair.second);
    }
    trace(OptimizerOptions::kPreprocess, [&]() {
      std::cout << "Explode=" << lp::ExprPrinter::toText(*call) << std::endl;
      std::cout << "num paths=" << paths.size() << std::endl;
      std::cout << "translated=" << map.size() << std::endl;
      if (!translated.empty()) {
        std::cout << "Set function skyline=" << translated.size() << " "
                  << map.size() << std::endl;
      }
    });

    if (!translated.empty()) {
      functionSubfields_[call] =
          SubfieldProjections{.pathToExpr = std::move(translated)};
      return nullptr;
    }
  }
  auto* callExpr =
      make<Call>(name, Value(toType(call->type()), cardinality), args, funcs);
  return callExpr;
}

ExprCP ToGraph::translateColumn(const std::string& name) {
  auto it = renames_.find(name);
  if (it != renames_.end()) {
    return it->second;
  }
  VELOX_FAIL("Cannot resolve column name: {}", name);
}

ExprVector ToGraph::translateColumns(const std::vector<lp::ExprPtr>& source) {
  ExprVector result{source.size()};
  for (auto i = 0; i < source.size(); ++i) {
    result[i] = translateExpr(source[i]); // NOLINT
  }
  return result;
}

AggregationPlanCP ToGraph::translateAggregation(
    const lp::AggregateNode& logicalAgg) {
  ExprVector groupingKeys = translateColumns(logicalAgg.groupingKeys());
  AggregateVector aggregates;
  ColumnVector columns;

  for (auto i = 0; i < logicalAgg.groupingKeys().size(); ++i) {
    auto name = toName(logicalAgg.outputType()->nameOf(i));
    auto* key = groupingKeys[i];

    if (key->is(PlanType::kColumnExpr)) {
      columns.push_back(key->as<Column>());
    } else {
      toType(logicalAgg.outputType()->childAt(i));

      auto* column = make<Column>(name, currentDt_, key->value(), name);
      columns.push_back(column);
    }

    renames_[name] = columns.back();
  }

  // The keys for intermediate are the same as for final.
  ColumnVector intermediateColumns = columns;
  for (auto channel : usedChannels(logicalAgg)) {
    if (channel < logicalAgg.groupingKeys().size()) {
      continue;
    }

    const auto i = channel - logicalAgg.groupingKeys().size();
    const auto& aggregate = logicalAgg.aggregates()[i];
    ExprVector args = translateColumns(aggregate->inputs());

    FunctionSet funcs;
    std::vector<TypePtr> argTypes;
    for (auto& arg : args) {
      funcs = funcs | arg->functions();
      argTypes.push_back(toTypePtr(arg->value().type));
    }
    ExprCP condition = nullptr;
    if (aggregate->filter()) {
      condition = translateExpr(aggregate->filter());
    }
    VELOX_CHECK(aggregate->ordering().empty());

    Name aggName = toName(aggregate->name());
    auto accumulatorType = toType(
        exec::resolveAggregateFunction(aggregate->name(), argTypes).second);
    Value finalValue = Value(toType(aggregate->type()), 1);
    auto* agg = make<Aggregate>(
        aggName,
        finalValue,
        args,
        funcs,
        false,
        condition,
        false,
        accumulatorType);
    auto name = toName(logicalAgg.outputNames()[channel]);
    auto* column = make<Column>(name, currentDt_, agg->value(), name);
    columns.push_back(column);

    auto intermediateValue = agg->value();
    intermediateValue.type = accumulatorType;
    auto* intermediateColumn =
        make<Column>(name, currentDt_, intermediateValue, name);
    intermediateColumns.push_back(intermediateColumn);
    auto dedupped = queryCtx()->dedup(agg);
    aggregates.push_back(dedupped->as<Aggregate>());

    renames_[name] = columns.back();
  }

  return make<AggregationPlan>(
      std::move(groupingKeys),
      std::move(aggregates),
      std::move(columns),
      std::move(intermediateColumns));
}

PlanObjectP ToGraph::addOrderBy(const lp::SortNode& order) {
  ExprVector orderKeys;
  OrderTypeVector orderTypes;
  orderKeys.reserve(order.ordering().size());
  orderTypes.reserve(order.ordering().size());

  for (const auto& field : order.ordering()) {
    auto sort = field.order;
    orderKeys.push_back(translateExpr(field.expression));
    orderTypes.push_back(
        sort.isAscending() ? (sort.isNullsFirst() ? OrderType::kAscNullsFirst
                                                  : OrderType::kAscNullsLast)
                           : (sort.isNullsFirst() ? OrderType::kDescNullsFirst
                                                  : OrderType::kDescNullsLast));
  }

  currentDt_->orderKeys = std::move(orderKeys);
  currentDt_->orderTypes = std::move(orderTypes);

  return currentDt_;
}

void ToGraph::translateUnnest(const logical_plan::UnnestNode& unnest) {
  VELOX_CHECK(!unnest.inputs().empty());

  makeQueryGraph(*unnest.onlyInput(), allow(PlanType::kJoinNode));

  auto* unnestTable = make<UnnestTable>();
  unnestTable->cname = newCName("ut");
  planLeaves_[&unnest] = unnestTable;

  const auto numInputColumns = unnest.onlyInput()->outputType()->size();

  const auto& type = unnest.outputType();

  for (auto i = numInputColumns; i < type->size(); ++i) {
    const auto& name = type->nameOf(i);
    Value value{toType(type->childAt(i)), 1};
    auto* column = make<Column>(toName(name), unnestTable, value, toName(name));

    unnestTable->columns.push_back(column);
    renames_[name] = column;
  }

  currentDt_->tables.push_back(unnestTable);
  currentDt_->tableSet.add(unnestTable);

  // Add join edges.
  for (const auto& unnestExpr : unnest.unnestExpressions()) {
    auto expr = translateExpr(unnestExpr);
    auto leftTables = expr->allTables();

    auto leftTableVector = leftTables.toVector();

    auto* edge = make<JoinEdge>(
        leftTableVector.size() == 1 ? leftTableVector[0] : nullptr,
        unnestTable,
        JoinEdge::Spec{.filter = {expr}, .directed = true});
    currentDt_->joins.push_back(edge);
  }
}

namespace {

// Fills 'leftKeys' and 'rightKeys's from 'conjuncts' so that
// equalities with one side only depending on 'right' go to
// 'rightKeys' and the other side not depending on 'right' goes to
// 'leftKeys'. The left side may depend on more than one table. The
// tables 'leftKeys' depend on are returned in 'allLeft'. The
// conjuncts that are not equalities or have both sides depending
// on right and something else are left in 'conjuncts'.
void extractNonInnerJoinEqualities(
    ExprVector& conjuncts,
    PlanObjectCP right,
    ExprVector& leftKeys,
    ExprVector& rightKeys,
    PlanObjectSet& allLeft) {
  const auto* eq = toName("eq");

  for (auto i = 0; i < conjuncts.size(); ++i) {
    const auto* conjunct = conjuncts[i];
    if (isCallExpr(conjunct, eq)) {
      const auto* eq = conjunct->as<Call>();
      const auto leftTables = eq->argAt(0)->allTables();
      const auto rightTables = eq->argAt(1)->allTables();
      if (rightTables.size() == 1 && rightTables.contains(right) &&
          !leftTables.contains(right)) {
        allLeft.unionSet(leftTables);
        leftKeys.push_back(eq->argAt(0));
        rightKeys.push_back(eq->argAt(1));
        conjuncts.erase(conjuncts.begin() + i);
        --i;
      } else if (
          leftTables.size() == 1 && leftTables.contains(right) &&
          !rightTables.contains(right)) {
        allLeft.unionSet(rightTables);
        leftKeys.push_back(eq->argAt(1));
        rightKeys.push_back(eq->argAt(0));
        conjuncts.erase(conjuncts.begin() + i);
        --i;
      }
    }
  }
}

} // namespace

void ToGraph::translateJoin(const lp::JoinNode& join) {
  const auto& joinLeft = join.left();
  const auto& joinRight = join.right();

  const auto joinType = join.joinType();
  const bool isInner = joinType == lp::JoinType::kInner;

  makeQueryGraph(*joinLeft, allow(PlanType::kJoinNode));

  // For an inner join a join tree on the right can be flattened, for all other
  // kinds it must be kept together in its own dt.

  DerivedTableP previousDt = nullptr;
  if (isNondeterministicWrap_) {
    previousDt = currentDt_;
    currentDt_ = newDt();

    isNondeterministicWrap_ = false;
  }
  makeQueryGraph(*joinRight, isInner ? allow(PlanType::kJoinNode) : 0);

  if (previousDt) {
    finalizeDt(*joinRight, previousDt);
  }

  ExprVector conjuncts;
  translateConjuncts(join.condition(), conjuncts);

  if (isInner) {
    currentDt_->conjuncts.insert(
        currentDt_->conjuncts.end(), conjuncts.begin(), conjuncts.end());
  } else {
    const bool leftOptional =
        joinType == lp::JoinType::kRight || joinType == lp::JoinType::kFull;
    const bool rightOptional =
        joinType == lp::JoinType::kLeft || joinType == lp::JoinType::kFull;

    // If non-inner, and many tables on the right they are one dt. If a single
    // table then this too is the last in 'tables'.
    auto rightTable = currentDt_->tables.back();

    ExprVector leftKeys;
    ExprVector rightKeys;
    PlanObjectSet leftTables;
    extractNonInnerJoinEqualities(
        conjuncts, rightTable, leftKeys, rightKeys, leftTables);

    auto leftTableVector = leftTables.toVector();

    auto* edge = make<JoinEdge>(
        leftTableVector.size() == 1 ? leftTableVector[0] : nullptr,
        rightTable,
        JoinEdge::Spec{
            .filter = std::move(conjuncts),
            .leftOptional = leftOptional,
            .rightOptional = rightOptional});
    currentDt_->joins.push_back(edge);
    for (auto i = 0; i < leftKeys.size(); ++i) {
      edge->addEquality(leftKeys[i], rightKeys[i]);
    }
  }
}

DerivedTableP ToGraph::newDt() {
  auto* dt = make<DerivedTable>();
  dt->cname = newCName("dt");
  return dt;
}

PlanObjectP ToGraph::wrapInDt(const lp::LogicalPlanNode& node) {
  DerivedTableP previousDt = currentDt_;

  currentDt_ = newDt();
  makeQueryGraph(node, kAllAllowedInDt);

  finalizeDt(node, previousDt);

  return currentDt_;
}

void ToGraph::finalizeDt(
    const lp::LogicalPlanNode& node,
    DerivedTableP outerDt) {
  DerivedTableP dt = currentDt_;
  setDtUsedOutput(dt, node);

  currentDt_ = outerDt != nullptr ? outerDt : newDt();
  currentDt_->tables.push_back(dt);
  currentDt_->tableSet.add(dt);

  dt->makeInitialPlan();
}

PlanObjectP ToGraph::makeBaseTable(const lp::TableScanNode& tableScan) {
  const auto* schemaTable =
      schema_.findTable(tableScan.connectorId(), tableScan.tableName());
  VELOX_CHECK_NOT_NULL(
      schemaTable,
      "Table not found: {} via connector {}",
      tableScan.tableName(),
      tableScan.connectorId());

  auto* baseTable = make<BaseTable>();
  baseTable->cname = newCName("t");
  baseTable->schemaTable = schemaTable;
  planLeaves_[&tableScan] = baseTable;

  auto channels = usedChannels(tableScan);
  const auto& type = tableScan.outputType();
  const auto& names = tableScan.columnNames();
  for (auto i : channels) {
    VELOX_DCHECK_LT(i, type->size());

    const auto& name = names[i];
    auto schemaColumn = schemaTable->findColumn(name);
    auto value = schemaColumn->value();
    auto* column = make<Column>(
        toName(name),
        baseTable,
        value,
        toName(type->nameOf(i)),
        schemaColumn->name());
    baseTable->columns.push_back(column);

    const auto kind = column->value().type->kind();
    if (kind == TypeKind::ARRAY || kind == TypeKind::ROW ||
        kind == TypeKind::MAP) {
      BitSet allPaths;
      if (controlSubfields_.hasColumn(&tableScan, i)) {
        baseTable->controlSubfields.ids.push_back(column->id());
        allPaths = controlSubfields_.nodeFields[&tableScan].resultPaths[i];
        baseTable->controlSubfields.subfields.push_back(allPaths);
      }
      if (payloadSubfields_.hasColumn(&tableScan, i)) {
        baseTable->payloadSubfields.ids.push_back(column->id());
        auto payloadPaths =
            payloadSubfields_.nodeFields[&tableScan].resultPaths[i];
        baseTable->payloadSubfields.subfields.push_back(payloadPaths);
        allPaths.unionSet(payloadPaths);
      }
      if (options_.pushdownSubfields) {
        Path::subfieldSkyline(allPaths);
        if (!allPaths.empty()) {
          trace(OptimizerOptions::kPreprocess, [&]() {
            std::cout << "Subfields: " << baseTable->cname << "."
                      << baseTable->schemaTable->name << " " << column->name()
                      << ":" << allPaths.size() << std::endl;
          });
          makeSubfieldColumns(baseTable, column, allPaths);
        }
      }
    }

    renames_[type->nameOf(i)] = column;
  }

  auto* optimization = queryCtx()->optimization();

  optimization->filterUpdated(baseTable, false);

  ColumnVector top;
  std::unordered_map<ColumnCP, TypePtr> map;
  auto scanType = optimization->subfieldPushdownScanType(
      baseTable, baseTable->columns, top, map);

  optimization->setLeafSelectivity(*baseTable, scanType);
  currentDt_->tables.push_back(baseTable);
  currentDt_->tableSet.add(baseTable);
  return baseTable;
}

PlanObjectP ToGraph::makeValuesTable(const lp::ValuesNode& values) {
  auto* valuesTable = make<ValuesTable>(values);
  valuesTable->cname = newCName("vt");
  planLeaves_[&values] = valuesTable;

  auto channels = usedChannels(values);
  const auto& type = values.outputType();
  const auto& names = values.outputType()->names();
  const auto cardinality = valuesTable->cardinality();
  for (auto i : channels) {
    VELOX_DCHECK_LT(i, type->size());

    const auto& name = names[i];
    Value value{toType(type->childAt(i)), cardinality};
    auto* column = make<Column>(toName(name), valuesTable, value, toName(name));
    valuesTable->columns.push_back(column);

    renames_[name] = column;
  }

  currentDt_->tables.push_back(valuesTable);
  currentDt_->tableSet.add(valuesTable);
  return valuesTable;
}

namespace {
const Type* pathType(const Type* type, PathCP path) {
  for (auto& step : path->steps()) {
    switch (step.kind) {
      case StepKind::kField:
        if (step.field) {
          type =
              type->childAt(type->as<TypeKind::ROW>().getChildIdx(step.field))
                  .get();
          break;
        }
        type = type->childAt(step.id).get();
        break;
      case StepKind::kSubscript:
        type = type->childAt(type->kind() == TypeKind::ARRAY ? 0 : 1).get();
        break;
      default:
        VELOX_NYI();
    }
  }
  return type;
}
} // namespace

void ToGraph::makeSubfieldColumns(
    BaseTable* baseTable,
    ColumnCP column,
    const BitSet& paths) {
  SubfieldProjections projections;
  auto* ctx = queryCtx();
  float card =
      baseTable->schemaTable->cardinality * baseTable->filterSelectivity;
  paths.forEach([&](auto id) {
    auto* path = ctx->pathById(id);
    auto type = pathType(column->value().type, path);
    Value value(type, card);
    auto name = fmt::format("{}.{}", column->name(), path->toString());
    auto* subcolumn = make<Column>(
        toName(name), baseTable, value, nullptr, nullptr, column, path);
    baseTable->columns.push_back(subcolumn);
    projections.pathToExpr[path] = subcolumn;
  });
  allColumnSubfields_[column] = std::move(projections);
}

PlanObjectP ToGraph::addProjection(const lp::ProjectNode* project) {
  exprSource_ = project->onlyInput().get();
  const auto& names = project->names();
  const auto& exprs = project->expressions();
  auto channels = usedChannels(*project);
  trace(OptimizerOptions::kPreprocess, [&]() {
    for (auto i = 0; i < exprs.size(); ++i) {
      if (std::find(channels.begin(), channels.end(), i) == channels.end()) {
        std::cout << "P=" << project->id()
                  << " dropped projection name=" << names[i] << " = "
                  << lp::ExprPrinter::toText(*exprs[i]) << std::endl;
      }
    }
  });
  for (auto i : channels) {
    if (exprs[i]->isInputReference()) {
      const auto& name =
          exprs[i]->asUnchecked<lp::InputReferenceExpr>()->name();
      // A variable projected to itself adds no renames. Inputs contain this
      // all the time.
      if (name == names[i]) {
        continue;
      }
    }

    auto expr = translateExpr(exprs.at(i));
    renames_[names[i]] = expr;
  }

  return currentDt_;
}

PlanObjectP ToGraph::addFilter(const lp::FilterNode* filter) {
  exprSource_ = filter->onlyInput().get();

  ExprVector flat;
  translateConjuncts(filter->predicate(), flat);

  if (currentDt_->hasAggregation()) {
    currentDt_->having.insert(
        currentDt_->having.end(), flat.begin(), flat.end());
  } else {
    currentDt_->conjuncts.insert(
        currentDt_->conjuncts.end(), flat.begin(), flat.end());
  }

  return currentDt_;
}

PlanObjectP ToGraph::addAggregation(const lp::AggregateNode& aggNode) {
  currentDt_->aggregation = translateAggregation(aggNode);
  return currentDt_;
}

PlanObjectP ToGraph::addLimit(const lp::LimitNode& limitNode) {
  if (currentDt_->hasLimit()) {
    currentDt_->offset += limitNode.offset();

    if (currentDt_->limit <= limitNode.offset()) {
      currentDt_->limit = 0;
    } else {
      currentDt_->limit =
          std::min(limitNode.count(), currentDt_->limit - limitNode.offset());
    }
  } else {
    currentDt_->limit = limitNode.count();
    currentDt_->offset = limitNode.offset();
  }

  return currentDt_;
}

namespace {
bool hasNondeterministic(const lp::ExprPtr& expr) {
  if (const auto* call = expr->asUnchecked<lp::CallExpr>()) {
    if (functionBits(toName(call->name()))
            .contains(FunctionSet::kNonDeterministic)) {
      return true;
    }
  }
  for (auto& in : expr->inputs()) {
    if (hasNondeterministic(in)) {
      return true;
    }
  }
  return false;
}
} // namespace

DerivedTableP ToGraph::translateSetJoin(
    const lp::SetNode& set,
    DerivedTableP setDt) {
  auto previousDt = currentDt_;
  currentDt_ = setDt;
  for (auto& input : set.inputs()) {
    wrapInDt(*input);
  }

  const bool exists = set.operation() == lp::SetOperation::kIntersect;
  const bool anti = set.operation() == lp::SetOperation::kExcept;

  VELOX_CHECK(exists || anti);

  const auto* left = setDt->tables[0]->as<DerivedTable>();

  for (auto i = 1; i < setDt->tables.size(); ++i) {
    const auto* right = setDt->tables[i]->as<DerivedTable>();

    auto* joinEdge = exists ? JoinEdge::makeExists(left, right)
                            : JoinEdge::makeNotExists(left, right);
    for (auto i = 0; i < left->columns.size(); ++i) {
      joinEdge->addEquality(left->columns[i], right->columns[i]);
    }

    setDt->joins.push_back(joinEdge);
  }

  const auto& type = set.outputType();
  ExprVector exprs;
  ColumnVector columns;
  for (auto i = 0; i < type->size(); ++i) {
    exprs.push_back(left->columns[i]);
    columns.push_back(make<Column>(
        toName(type->nameOf(i)),
        setDt,
        exprs.back()->value(),
        toName(type->nameOf(i))));
    renames_[type->nameOf(i)] = columns.back();
  }

  setDt->aggregation =
      make<AggregationPlan>(exprs, AggregateVector{}, columns, columns);
  for (auto& c : columns) {
    setDt->exprs.push_back(c);
  }
  setDt->columns = columns;
  setDt->makeInitialPlan();
  currentDt_ = previousDt;
  return setDt;
}

void ToGraph::makeUnionDistributionAndStats(
    DerivedTableP setDt,
    DerivedTableP innerDt) {
  if (setDt->distribution == nullptr) {
    setDt->distribution = make<Distribution>();
  }
  if (innerDt == nullptr) {
    innerDt = setDt;
  }
  if (innerDt->children.empty()) {
    VELOX_CHECK_EQ(
        innerDt->columns.size(),
        setDt->columns.size(),
        "Union inputs must have same arity also after pruning");

    auto plan = innerDt->bestInitialPlan()->op;

    setDt->cardinality += plan->resultCardinality();
    for (auto i = 0; i < setDt->columns.size(); ++i) {
      // The Column is created in setDt before all branches are planned so the
      // value is mutated here.
      auto mutableValue =
          const_cast<float*>(&setDt->columns[i]->value().cardinality);
      *mutableValue += plan->columns()[i]->value().cardinality;
    }
  } else {
    for (auto& child : innerDt->children) {
      makeUnionDistributionAndStats(setDt, child);
    }
  }
}

DerivedTableP ToGraph::translateUnion(
    const lp::SetNode& set,
    DerivedTableP setDt,
    bool isTopLevel,
    bool& isLeftLeaf) {
  auto initialRenames = renames_;
  std::vector<DerivedTableP, QGAllocator<DerivedTable*>> children;
  bool isFirst = true;
  DerivedTableP previousDt = currentDt_;
  for (auto& input : set.inputs()) {
    if (!isFirst) {
      renames_ = initialRenames;
    } else {
      isFirst = false;
    }

    currentDt_ = newDt();

    auto& newDt = currentDt_;

    auto isUnionLike =
        [](const lp::LogicalPlanNode& node) -> const lp::SetNode* {
      if (node.kind() == lp::NodeKind::kSet) {
        const auto* set = node.asUnchecked<lp::SetNode>();
        if (set->operation() == lp::SetOperation::kUnion ||
            set->operation() == lp::SetOperation::kUnionAll) {
          return set;
        }
      }

      return nullptr;
    };

    if (auto* setNode = isUnionLike(*input)) {
      auto inner = translateUnion(*setNode, setDt, false, isLeftLeaf);
      children.push_back(inner);
    } else {
      makeQueryGraph(*input, kAllAllowedInDt);

      const auto& type = input->outputType();

      if (isLeftLeaf) {
        // This is the left leaf of a union tree.
        for (auto i : usedChannels(*input)) {
          const auto& name = type->nameOf(i);

          ExprCP inner = translateColumn(name);
          newDt->exprs.push_back(inner);

          // The top dt has the same columns as all the unioned dts.
          auto* outer =
              make<Column>(toName(name), setDt, inner->value(), toName(name));
          setDt->columns.push_back(outer);
          newDt->columns.push_back(outer);
        }
        isLeftLeaf = false;
      } else {
        for (auto i : usedChannels(*input)) {
          ExprCP inner = translateColumn(type->nameOf(i));
          newDt->exprs.push_back(inner);
        }

        // Same outward facing columns as the top dt of union.
        newDt->columns = setDt->columns;
      }

      newDt->makeInitialPlan();
      children.push_back(newDt);
    }
  }

  currentDt_ = previousDt;
  if (isTopLevel) {
    setDt->children = std::move(children);
    setDt->setOp = set.operation();

    makeUnionDistributionAndStats(setDt);

    renames_ = initialRenames;
    for (const auto* column : setDt->columns) {
      renames_[column->name()] = column;
    }
  } else {
    setDt = newDt();
    setDt->children = std::move(children);
    setDt->setOp = set.operation();
  }
  return setDt;
}

DerivedTableP ToGraph::makeQueryGraph(const lp::LogicalPlanNode& logicalPlan) {
  markAllSubfields(logicalPlan.outputType().get(), logicalPlan);

  currentDt_ = newDt();
  makeQueryGraph(logicalPlan, kAllAllowedInDt);
  return currentDt_;
}

namespace {
// Removes 'op' from the set of operators allowed in the current derived
// table. makeQueryGraph() starts a new derived table if it finds an operator
// that does not belong to the mask.
uint64_t makeDtIf(uint64_t mask, PlanType op) {
  return mask & ~(1UL << static_cast<int32_t>(op));
}
} // namespace

PlanObjectP ToGraph::makeQueryGraph(
    const lp::LogicalPlanNode& node,
    uint64_t allowedInDt) {
  ToGraphContext ctx(&node);
  ExceptionContextSetter(makeExceptionContext(&ctx));
  switch (node.kind()) {
    case lp::NodeKind::kValues:
      return makeValuesTable(*node.asUnchecked<lp::ValuesNode>());

    case lp::NodeKind::kTableScan:
      return makeBaseTable(*node.asUnchecked<lp::TableScanNode>());

    case lp::NodeKind::kFilter: {
      // Multiple filters are allowed before a limit. If DT has a groupBy, then
      // filter is added to 'having', otherwise, to 'conjuncts'.
      const auto* filter = node.asUnchecked<lp::FilterNode>();

      if (!isNondeterministicWrap_ &&
          hasNondeterministic(filter->predicate())) {
        // Force wrap the filter and its input inside a dt so the filter
        // does not get mixed with parent nodes.
        makeQueryGraph(*node.onlyInput(), allowedInDt);

        if (currentDt_->hasLimit()) {
          finalizeDt(*node.onlyInput());
        }

        addFilter(filter);
        finalizeDt(node);

        isNondeterministicWrap_ = true;
        return currentDt_;
      }

      isNondeterministicWrap_ = false;
      makeQueryGraph(*node.onlyInput(), allowedInDt);

      if (currentDt_->hasLimit()) {
        finalizeDt(*node.onlyInput());
      }
      return addFilter(filter);
    }

    case lp::NodeKind::kProject:
      // A project is always allowed in a DT. Multiple projects are combined.
      makeQueryGraph(*node.onlyInput(), allowedInDt);
      return addProjection(node.asUnchecked<lp::ProjectNode>());

    case lp::NodeKind::kAggregate:
      if (!contains(allowedInDt, PlanType::kAggregationNode)) {
        return wrapInDt(node);
      }

      // A single groupBy is allowed before a limit. If arrives after orderBy,
      // then orderBy is dropped. If arrives after limit, then starts a new DT.

      makeQueryGraph(*node.onlyInput(), allowedInDt);

      if (currentDt_->hasAggregation() || currentDt_->hasLimit()) {
        finalizeDt(*node.onlyInput());
      } else if (currentDt_->hasOrderBy()) {
        currentDt_->orderKeys.clear();
        currentDt_->orderTypes.clear();
      }

      addAggregation(*node.asUnchecked<lp::AggregateNode>());

      return currentDt_;

    case lp::NodeKind::kJoin:
      if (!contains(allowedInDt, PlanType::kJoinNode)) {
        return wrapInDt(node);
      }

      translateJoin(*node.asUnchecked<lp::JoinNode>());
      return currentDt_;

    case lp::NodeKind::kSort:
      // Multiple orderBys are allowed before a limit. Last one wins. Previous
      // are dropped. If arrives after limit, then starts a new DT.

      makeQueryGraph(*node.onlyInput(), allowedInDt);

      if (currentDt_->hasLimit()) {
        finalizeDt(*node.onlyInput());
      }

      return addOrderBy(*node.asUnchecked<lp::SortNode>());

    case lp::NodeKind::kLimit: {
      // Multiple limits are allowed. If already present, then it is combined
      // with the new limit.
      makeQueryGraph(*node.onlyInput(), allowedInDt);
      return addLimit(*node.asUnchecked<lp::LimitNode>());
    }

    case lp::NodeKind::kSet: {
      auto* setDt = newDt();

      auto* set = node.asUnchecked<lp::SetNode>();
      if (set->operation() == lp::SetOperation::kUnion ||
          set->operation() == lp::SetOperation::kUnionAll) {
        bool isLeftLeaf = true;
        translateUnion(*set, setDt, true, isLeftLeaf);
      } else {
        translateSetJoin(*set, setDt);
      }
      currentDt_->tables.push_back(setDt);
      currentDt_->tableSet.add(setDt);
      return currentDt_;
    }
    case lp::NodeKind::kUnnest:
      translateUnnest(*node.asUnchecked<lp::UnnestNode>());
      return currentDt_;
    default:
      VELOX_NYI(
          "Unsupported PlanNode {}", lp::NodeKindName::toName(node.kind()));
  }
}

// Debug helper functions. Must be in a namespace to be callable from gdb.
std::string leString(const lp::Expr* e) {
  return lp::ExprPrinter::toText(*e);
}

std::string pString(const lp::LogicalPlanNode* p) {
  return lp::PlanPrinter::toText(*p);
}

} // namespace facebook::velox::optimizer
