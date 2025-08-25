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

#include "axiom/optimizer/Plan.h"
#include "axiom/optimizer/Cost.h"
#include "axiom/optimizer/DerivedTablePrinter.h"

#include <iostream>

namespace facebook::velox::optimizer {

namespace {

// True if single worker, i.e. do not plan remote exchanges
bool isSingleWorker() {
  return queryCtx()->optimization()->runnerOptions().numWorkers == 1;
}

} // namespace

// The dt for which we set a breakpoint for plan candidate.
int32_t debugDt{-1};

// Number of tables in 'debugPlacedTables'
int32_t debugNumPlaced = 0;

// Tables for setting a breakpoint. Join order selection calls planBreakpoint()
// right before evaluating the cost for the tables in 'debugPlacedTables'.
int32_t debugPlaced[10];

void planBreakpoint() {
  // Set breakpoint here for looking at cost of join order in
  // 'debugPlacedTables'.
  LOG(INFO) << "Join order breakpoint";
}

void PlanState::debugSetFirstTable(int32_t id) {
  if (dt->id() == debugDt) {
    debugPlacedTables.resize(1);
    debugPlacedTables[0] = id;
  }
}

PlanStateSaver::PlanStateSaver(PlanState& state, const JoinCandidate& candidate)
    : PlanStateSaver(state) {
  if (state.dt->id() != debugDt) {
    return;
  }
  state.debugPlacedTables.push_back(candidate.tables[0]->id());
  if (debugNumPlaced == 0) {
    return;
  }

  for (auto i = 0; i < debugNumPlaced; ++i) {
    if (debugPlaced[i] != state.debugPlacedTables[i]) {
      return;
    }
  }
  planBreakpoint();
}

Optimization::Optimization(
    const logical_plan::LogicalPlanNode& plan,
    const Schema& schema,
    History& history,
    std::shared_ptr<core::QueryCtx> _queryCtx,
    velox::core::ExpressionEvaluator& evaluator,
    OptimizerOptions options,
    axiom::runner::MultiFragmentPlan::Options runnerOptions)
    : options_(std::move(options)),
      runnerOptions_(std::move(runnerOptions)),
      isSingleWorker_(runnerOptions_.numWorkers == 1),
      logicalPlan_(&plan),
      history_(history),
      queryCtx_(std::move(_queryCtx)),
      toGraph_{schema, evaluator, options_},
      toVelox_{runnerOptions_, options_} {
  queryCtx()->optimization() = this;
  root_ = toGraph_.makeQueryGraph(*logicalPlan_);
  root_->distributeConjuncts();
  root_->addImpliedJoins();
  root_->linkTablesToJoins();
  for (auto* join : root_->joins) {
    join->guessFanout();
  }
  toGraph_.setDtOutput(root_, *logicalPlan_);

  LOG(ERROR) << std::endl << DerivedTablePrinter::toText(*root_);
}

void Optimization::trace(
    int32_t event,
    int32_t id,
    const Cost& cost,
    RelationOp& plan) {
  if (event & options_.traceFlags) {
    std::cout << (event == OptimizerOptions::kRetained ? "Retained: "
                                                       : "Abandoned: ")
              << id << ": " << cost.toString(true, true) << ": " << " "
              << plan.toString(true, false) << std::endl;
  }
}

PlanP Optimization::bestPlan() {
  PlanObjectSet targetColumns;
  targetColumns.unionColumns(root_->columns);

  topState_.dt = root_;
  topState_.setTargetColumnsForDt(targetColumns);

  makeJoins(nullptr, topState_);

  return topState_.plans.best();
}

Plan::Plan(RelationOpPtr _op, const PlanState& state)
    : op(std::move(_op)),
      cost(state.cost),
      tables(state.placed),
      columns(state.targetColumns),
      fullyImported(state.dt->fullyImported) {}

bool Plan::isStateBetter(const PlanState& state, float perRowMargin) const {
  return cost.unitCost * cost.inputCardinality + cost.setupCost >
      state.cost.unitCost * state.cost.inputCardinality + state.cost.setupCost +
      perRowMargin * state.cost.fanout;
}

std::string Plan::printCost() const {
  return cost.toString(true, false);
}

std::string Plan::toString(bool detail) const {
  queryCtx()->contextPlan() = const_cast<Plan*>(this);
  auto result = op->toString(true, detail);
  queryCtx()->contextPlan() = nullptr;
  return result;
}

void PlanState::addCost(RelationOp& op) {
  cost.unitCost += cost.inputCardinality * cost.fanout * op.cost().unitCost;
  cost.setupCost += op.cost().setupCost;
  cost.fanout *= op.cost().fanout;
  cost.totalBytes += op.cost().totalBytes;
  cost.transferBytes += op.cost().transferBytes;
}

void PlanState::addNextJoin(
    const JoinCandidate* candidate,
    RelationOpPtr plan,
    HashBuildVector builds,
    std::vector<NextJoin>& toTry) const {
  if (!isOverBest()) {
    toTry.emplace_back(candidate, plan, cost, placed, columns, builds);
  } else {
    optimization.trace(OptimizerOptions::kExceededBest, dt->id(), cost, *plan);
  }
}

void PlanState::addBuilds(const HashBuildVector& added) {
  for (auto build : added) {
    if (std::find(builds.begin(), builds.end(), build) == builds.end()) {
      builds.push_back(build);
    }
  }
}

void PlanState::setTargetColumnsForDt(const PlanObjectSet& target) {
  targetColumns = target;
  for (auto i = 0; i < dt->columns.size(); ++i) {
    if (target.contains(dt->columns[i])) {
      targetColumns.unionColumns(dt->exprs[i]);
    }
  }
  for (const auto& having : dt->having) {
    targetColumns.unionColumns(having);
  }
}

const PlanObjectSet& PlanState::downstreamColumns() const {
  auto it = downstreamPrecomputed.find(placed);
  if (it != downstreamPrecomputed.end()) {
    return it->second;
  }

  PlanObjectSet result;
  for (auto join : dt->joins) {
    bool addFilter = false;
    if (!placed.contains(join->rightTable())) {
      addFilter = true;
      result.unionColumns(join->leftKeys());
    }
    if (join->leftTable() && !placed.contains(join->leftTable())) {
      addFilter = true;
      result.unionColumns(join->rightKeys());
    }
    if (addFilter && !join->filter().empty()) {
      result.unionColumns(join->filter());
    }
  }

  for (auto& conjunct : dt->conjuncts) {
    if (!placed.contains(conjunct)) {
      result.unionColumns(conjunct);
    }
  }

  if (dt->aggregation && !placed.contains(dt->aggregation)) {
    auto aggToPlace = dt->aggregation;
    const auto numGroupingKeys = aggToPlace->groupingKeys().size();
    for (auto i = 0; i < aggToPlace->columns().size(); ++i) {
      // Grouping columns must be computed anyway, aggregates only if referenced
      // by enclosing.
      if (i < numGroupingKeys) {
        result.unionColumns(aggToPlace->groupingKeys()[i]);
      } else if (targetColumns.contains(aggToPlace->columns()[i])) {
        result.unionColumns(aggToPlace->aggregates()[i - numGroupingKeys]);
      }
    }
  }

  result.unionSet(targetColumns);
  return downstreamPrecomputed[placed] = std::move(result);
}

std::string PlanState::printCost() const {
  return cost.toString(true, true);
}

std::string PlanState::printPlan(RelationOpPtr op, bool detail) const {
  auto plan = std::make_unique<Plan>(op, *this);
  return plan->toString(detail);
}

PlanP PlanSet::addPlan(RelationOpPtr plan, PlanState& state) {
  int32_t replaceIndex = -1;
  const float shuffleCostPerRow =
      shuffleCost(plan->columns()) * state.cost.fanout;

  if (!plans.empty()) {
    // Compare with existing. If there is one with same distribution and new is
    // better, replace. If there is one with a different distribution and the
    // new one can produce the same distribution by repartition, for cheaper,
    // add the new one and delete the old one.
    for (auto i = 0; i < plans.size(); ++i) {
      auto old = plans[i].get();
      if (state.input != old->input) {
        continue;
      }

      const bool newIsBetter = old->isStateBetter(state);
      const bool newIsBetterWithShuffle =
          old->isStateBetter(state, shuffleCostPerRow);
      const bool sameDist =
          old->op->distribution().isSamePartition(plan->distribution());
      const bool sameOrder =
          old->op->distribution().isSameOrder(plan->distribution());
      if (sameDist && sameOrder) {
        if (newIsBetter) {
          replaceIndex = i;
          continue;
        }
        // There's a better one with same dist and partition.
        return nullptr;
      }

      if (newIsBetterWithShuffle && old->op->distribution().orderKeys.empty()) {
        // Old plan has no order and is worse than new plus shuffle. Can't win.
        // Erase.
        queryCtx()->optimization()->trace(
            OptimizerOptions::kExceededBest,
            state.dt->id(),
            old->cost,
            *old->op);
        plans.erase(plans.begin() + i);
        --i;
        continue;
      }

      if (plan->distribution().orderKeys.empty() &&
          !old->isStateBetter(state, -shuffleCostPerRow)) {
        // New has no order and old would beat it even after adding shuffle.
        return nullptr;
      }
    }
  }

  auto newPlan = std::make_unique<Plan>(plan, state);
  auto* result = newPlan.get();
  auto newPlanCost =
      result->cost.unitCost + result->cost.setupCost + shuffleCostPerRow;
  if (bestCostWithShuffle == 0 || newPlanCost < bestCostWithShuffle) {
    bestCostWithShuffle = newPlanCost;
  }
  if (replaceIndex >= 0) {
    plans[replaceIndex] = std::move(newPlan);
  } else {
    plans.push_back(std::move(newPlan));
  }
  return result;
}

PlanP PlanSet::best(const Distribution& distribution, bool& needsShuffle) {
  PlanP best = nullptr;
  PlanP match = nullptr;
  float bestCost = -1;
  float matchCost = -1;

  const bool single = isSingleWorker();

  for (const auto& plan : plans) {
    const float cost =
        plan->cost.fanout * plan->cost.unitCost + plan->cost.setupCost;

    auto update = [&](PlanP& current, float& currentCost) {
      if (!current || cost < currentCost) {
        current = plan.get();
        currentCost = cost;
      }
    };

    update(best, bestCost);
    if (!single && plan->op->distribution().isSamePartition(distribution)) {
      update(match, matchCost);
    }
  }

  VELOX_DCHECK_NOT_NULL(best);

  if (single || best == match) {
    return best;
  }

  if (match) {
    const float shuffle = shuffleCost(best->op->columns()) * best->cost.fanout;
    if (matchCost <= bestCost + shuffle) {
      return match;
    }
  }

  needsShuffle = true;
  return best;
}

const JoinEdgeVector& joinedBy(PlanObjectCP table) {
  if (table->is(PlanType::kTableNode)) {
    return table->as<BaseTable>()->joinedBy;
  }

  if (table->is(PlanType::kValuesTableNode)) {
    return table->as<ValuesTable>()->joinedBy;
  }

  if (table->is(PlanType::kUnnestTableNode)) {
    return table->as<UnnestTable>()->joinedBy;
  }

  VELOX_DCHECK(table->is(PlanType::kDerivedTableNode));
  return table->as<DerivedTable>()->joinedBy;
}

namespace {
// Traverses joins from 'candidate'. Follows any join that goes to a table not
// in 'visited' with a fanout < 'maxFanout'. 'fanoutFromRoot' is the product of
// the fanouts between 'candidate' and the 'candidate' of the top level call to
// this. 'path' is the set of joined tables between this invocation and the top
// level. 'fanoutFromRoot' is thus the selectivity of the linear join sequence
// in 'path'. When a reducing join sequence is found, the tables on the path
// are added to 'result'. 'reduction' is the product of the fanouts of all the
// reducing join paths added to 'result'.
void reducingJoinsRecursive(
    const PlanState& state,
    PlanObjectCP candidate,
    float fanoutFromRoot,
    float maxFanout,
    std::vector<PlanObjectCP>& path,
    PlanObjectSet& visited,
    PlanObjectSet& result,
    float& reduction,
    std::function<void(const std::vector<PlanObjectCP>& path, float reduction)>
        resultFunc = nullptr) {
  bool isLeaf = true;
  for (auto join : joinedBy(candidate)) {
    if (join->leftOptional() || join->rightOptional()) {
      continue;
    }
    JoinSide other = join->sideOf(candidate, true);
    if (!state.dt->hasTable(other.table) || !state.dt->hasJoin(join)) {
      continue;
    }
    if (other.table->type() != PlanType::kTableNode &&
        other.table->type() != PlanType::kValuesTableNode) {
      continue;
    }
    if (visited.contains(other.table)) {
      continue;
    }
    if (other.fanout > maxFanout) {
      continue;
    }
    visited.add(other.table);
    auto fanout = fanoutFromRoot * other.fanout;
    if (fanout < 0.9) {
      result.add(other.table);
      for (auto step : path) {
        result.add(step);
        maxFanout = 1;
      }
    }
    path.push_back(other.table);
    isLeaf = false;
    reducingJoinsRecursive(
        state,
        other.table,
        fanout,
        maxFanout,
        path,
        visited,
        result,
        reduction,
        resultFunc);
    path.pop_back();
  }
  if (fanoutFromRoot < 1 && isLeaf) {
    // We are at the end of a reducing sequence of joins. Update the total
    // fanout for the set of all reducing join paths from the top level
    // 'candidate'.
    reduction *= fanoutFromRoot;
    if (resultFunc) {
      resultFunc(path, fanoutFromRoot);
    }
  }
}

JoinCandidate reducingJoins(
    const PlanState& state,
    const JoinCandidate& candidate) {
  // For an inner join, see if can bundle reducing joins on the build.
  JoinCandidate reducing;
  reducing.join = candidate.join;
  reducing.fanout = candidate.fanout;
  PlanObjectSet reducingSet;
  if (candidate.join->isInner()) {
    PlanObjectSet visited = state.placed;
    VELOX_DCHECK(!candidate.tables.empty());
    visited.add(candidate.tables[0]);
    reducingSet.add(candidate.tables[0]);
    std::vector<PlanObjectCP> path{candidate.tables[0]};
    float reduction = 1;
    reducingJoinsRecursive(
        state,
        candidate.tables[0],
        1,
        1.2,
        path,
        visited,
        reducingSet,
        reduction);
    if (reduction < 0.9) {
      // The only table in 'candidate' must be first in the bushy table list.
      reducing.tables = candidate.tables;
      reducingSet.forEach([&](auto object) {
        if (object != reducing.tables[0]) {
          reducing.tables.push_back(object);
        }
      });
      reducing.fanout = candidate.fanout * reduction;
    }
  }
  if (!state.dt->noImportOfExists) {
    PlanObjectSet exists;
    float reduction = 1;
    VELOX_DCHECK(!candidate.tables.empty());
    std::vector<PlanObjectCP> path{candidate.tables[0]};
    // Look for reducing joins that were not added before, also covering already
    // placed tables. This may copy reducing joins from a probe to the
    // corresponding build.
    reducingSet.add(candidate.tables[0]);
    reducingSet.unionSet(state.dt->importedExistences);
    reducingJoinsRecursive(
        state,
        candidate.tables[0],
        1,
        1.2,
        path,
        reducingSet,
        exists,
        reduction,
        [&](auto& path, float reduction) {
          if (reduction < 0.7) {
            // The original table is added to the reducing existences because
            // the path starts with it but it is not joined twice since it
            // already is the start of the main join.
            PlanObjectSet added;
            for (auto i = 1; i < path.size(); ++i) {
              added.add(path[i]);
            }
            reducing.existences.push_back(std::move(added));
          }
        });
  }
  if (reducing.tables.empty() && reducing.existences.empty()) {
    // No reduction.
    return JoinCandidate{};
  }
  if (reducing.tables.empty()) {
    // No reducing joins but reducing existences from probe side.
    reducing.tables = candidate.tables;
  }
  return reducing;
}

// Calls 'func' with join, joined table and fanout for the joinable tables.
template <typename Func>
void forJoinedTables(const PlanState& state, Func func) {
  std::unordered_set<JoinEdgeP> visited;
  state.placed.forEach([&](PlanObjectCP placedTable) {
    if (!placedTable->isTable()) {
      return;
    }

    for (auto join : joinedBy(placedTable)) {
      if (join->isNonCommutative()) {
        if (!visited.insert(join).second) {
          continue;
        }
        bool usable = true;
        for (auto key : join->leftKeys()) {
          if (!key->allTables().isSubset(state.placed)) {
            // All items that the left key depends on must be placed.
            usable = false;
            break;
          }
        }
        if (usable) {
          func(join, join->rightTable(), join->lrFanout());
        }
      } else {
        auto [table, fanout] = join->otherTable(placedTable);
        if (!state.dt->hasTable(table)) {
          continue;
        }
        func(join, table, fanout);
      }
    }
  });
}
} // namespace

JoinSide JoinCandidate::sideOf(PlanObjectCP side, bool other) const {
  return join->sideOf(side, other);
}

namespace {
bool hasEqual(ExprCP key, const ExprVector& keys) {
  if (key->type() != PlanType::kColumnExpr ||
      !key->as<Column>()->equivalence()) {
    return false;
  }

  for (auto& e : keys) {
    if (key->sameOrEqual(*e)) {
      return true;
    }
  }

  return false;
}
} // namespace

void JoinCandidate::addEdge(PlanState& state, JoinEdgeP edge) {
  auto* joined = tables[0];
  auto newTableSide = edge->sideOf(joined);
  auto newPlacedSide = edge->sideOf(joined, true);
  VELOX_CHECK_NOT_NULL(newPlacedSide.table);
  if (!state.placed.contains(newPlacedSide.table)) {
    return;
  }

  auto tableSide = join->sideOf(joined);
  auto placedSide = join->sideOf(joined, true);
  for (auto i = 0; i < newPlacedSide.keys.size(); ++i) {
    auto* key = newPlacedSide.keys[i];
    if (!hasEqual(key, tableSide.keys)) {
      if (!compositeEdge) {
        compositeEdge = make<JoinEdge>(*join);
        join = compositeEdge;
      }
      auto [other, preFanout] = join->otherTable(placedSide.table);
      // do not recompute a fanout after adding more equalities. This makes the
      // join edge non-binary and it cannot be sampled.
      join->setFanouts(join->rlFanout(), join->lrFanout());
      if (joined == join->rightTable()) {
        join->addEquality(key, newTableSide.keys[i]);
      } else {
        join->addEquality(newTableSide.keys[i], key);
      }
      auto [other2, postFanout] = join->otherTable(placedSide.table);
      auto change = postFanout > 0 ? preFanout / postFanout : 0;
      fanout = change > 0 ? fanout / change : preFanout / 2;
    }
  }
}

bool JoinCandidate::isDominantEdge(PlanState& state, JoinEdgeP edge) {
  auto* joined = tables[0];
  auto newPlacedSide = edge->sideOf(joined, true);
  VELOX_CHECK_NOT_NULL(newPlacedSide.table);
  if (!state.placed.contains(newPlacedSide.table)) {
    return false;
  }
  auto tableSide = join->sideOf(joined);
  auto placedSide = join->sideOf(joined, true);
  for (auto i = 0; i < newPlacedSide.keys.size(); ++i) {
    auto* key = newPlacedSide.keys[i];
    if (!hasEqual(key, tableSide.keys)) {
      return false;
    }
  }
  return newPlacedSide.keys.size() > placedSide.keys.size();
}

std::string JoinCandidate::toString() const {
  std::stringstream out;
  out << join->toString() << " fanout " << fanout;
  for (auto i = 1; i < tables.size(); ++i) {
    out << " + " << tables[i]->toString();
  }
  if (!existences.empty()) {
    out << " exists " << existences[0].toString(false);
  }
  return out.str();
}

bool NextJoin::isWorse(const NextJoin& other) const {
  float shuffle =
      plan->distribution().isSamePartition(other.plan->distribution())
      ? 0
      : plan->cost().fanout * shuffleCost(plan->columns());
  return cost.unitCost + cost.setupCost + shuffle >
      other.cost.unitCost + other.cost.setupCost;
}

namespace {
bool addExtraEdges(PlanState& state, JoinCandidate& candidate) {
  // See if there are more join edges from the first of 'candidate' to already
  // placed tables. Fill in the non-redundant equalities into the join edge.
  // Make a new edge if the edge would be altered.
  auto* originalJoin = candidate.join;
  auto* table = candidate.tables[0];
  for (auto* otherJoin : joinedBy(table)) {
    if (otherJoin == originalJoin || !otherJoin->isInner()) {
      continue;
    }
    auto [otherTable, fanout] = otherJoin->otherTable(table);
    if (!state.dt->hasTable(otherTable)) {
      continue;
    }
    if (candidate.isDominantEdge(state, otherJoin)) {
      return false;
    }
    candidate.addEdge(state, otherJoin);
  }
  return true;
}
} // namespace

std::vector<JoinCandidate> Optimization::nextJoins(PlanState& state) {
  std::vector<JoinCandidate> candidates;
  candidates.reserve(state.dt->tables.size());
  forJoinedTables(
      state, [&](JoinEdgeP join, PlanObjectCP joined, float fanout) {
        if (!state.placed.contains(joined) && state.dt->hasJoin(join) &&
            state.dt->hasTable(joined)) {
          candidates.emplace_back(join, joined, fanout);
          if (join->isInner()) {
            if (!addExtraEdges(state, candidates.back())) {
              // Drop the candidate if the edge was a subsumed in some other
              // edge.
              candidates.pop_back();
            }
          }
        }
      });

  std::vector<JoinCandidate> bushes;
  // Take the  first hand joined tables and bundle them with reducing joins that
  // can go on the build side.
  for (auto& candidate : candidates) {
    auto bush = reducingJoins(state, candidate);
    if (!bush.tables.empty()) {
      bushes.push_back(std::move(bush));
    }
  }
  candidates.insert(candidates.begin(), bushes.begin(), bushes.end());
  std::sort(
      candidates.begin(),
      candidates.end(),
      [](const JoinCandidate& left, const JoinCandidate& right) {
        return left.fanout < right.fanout;
      });
  if (candidates.empty()) {
    // There are no join edges. There could still be cross joins.
    state.dt->startTables.forEach([&](PlanObjectCP object) {
      if (!state.placed.contains(object)) {
        candidates.emplace_back(nullptr, object, tableCardinality(object));
      }
    });
  }
  return candidates;
}

size_t MemoKey::hash() const {
  size_t hash = tables.hash();
  for (auto& exists : existences) {
    hash = bits::commutativeHashMix(hash, exists.hash());
  }
  return hash;
}

bool MemoKey::operator==(const MemoKey& other) const {
  if (firstTable == other.firstTable && columns == other.columns &&
      tables == other.tables) {
    if (existences.size() != other.existences.size()) {
      return false;
    }
    for (auto& e : existences) {
      for (auto& e2 : other.existences) {
        if (e2 == e) {
          break;
        }
      }
    }
    return true;
  }
  return false;
}

namespace {
constexpr uint32_t kNotFound = ~0U;

/// Returns index of 'expr' in collection 'exprs'. kNotFound if not found.
/// Compares with equivalence classes, so that equal columns are
/// interchangeable.
template <typename V>
uint32_t position(const V& exprs, const Expr& expr) {
  for (auto i = 0; i < exprs.size(); ++i) {
    if (exprs[i]->sameOrEqual(expr)) {
      return i;
    }
  }
  return kNotFound;
}

/// Returns index of 'expr' in collection 'exprs'. kNotFound if not found.
/// Compares with equivalence classes, so that equal columns are
/// interchangeable. Applies 'getter' to each element of 'exprs' before
/// comparison.
template <typename V, typename Getter>
uint32_t position(const V& exprs, Getter getter, const Expr& expr) {
  for (auto i = 0; i < exprs.size(); ++i) {
    if (getter(exprs[i])->sameOrEqual(expr)) {
      return i;
    }
  }
  return kNotFound;
}

RelationOpPtr repartitionForAgg(const RelationOpPtr& plan, PlanState& state) {
  // No shuffle if all grouping keys are in partitioning.
  if (isSingleWorker() || plan->distribution().distributionType.isGather) {
    return plan;
  }

  const auto* agg = state.dt->aggregation;

  // If no grouping and not yet gathered on a single node, add a gather before
  // final agg.
  if (agg->groupingKeys().empty() &&
      !plan->distribution().distributionType.isGather) {
    auto* gather =
        make<Repartition>(plan, Distribution::gather(), plan->columns());
    state.addCost(*gather);
    return gather;
  }

  // 'intermediateColumns' contains grouping keys followed by partial agg
  // results.
  ExprVector keyValues;
  for (auto i = 0; i < agg->groupingKeys().size(); ++i) {
    keyValues.push_back(agg->intermediateColumns()[i]);
  }

  bool shuffle = false;
  for (auto& key : keyValues) {
    auto nthKey = position(plan->distribution().partition, *key);
    if (nthKey == kNotFound) {
      shuffle = true;
      break;
    }
  }
  if (!shuffle) {
    return plan;
  }

  Distribution distribution{
      plan->distribution().distributionType, std::move(keyValues)};
  auto* repartition =
      make<Repartition>(plan, std::move(distribution), plan->columns());
  state.addCost(*repartition);
  return repartition;
}

} // namespace

void Optimization::addPostprocess(
    DerivedTableCP dt,
    RelationOpPtr& plan,
    PlanState& state) {
  if (dt->aggregation) {
    const auto& aggPlan = dt->aggregation;

    auto* partialAgg = make<Aggregation>(
        plan,
        aggPlan->groupingKeys(),
        aggPlan->aggregates(),
        core::AggregationNode::Step::kPartial,
        aggPlan->intermediateColumns());

    state.placed.add(aggPlan);
    state.addCost(*partialAgg);
    plan = repartitionForAgg(partialAgg, state);

    ExprVector finalGroupingKeys;
    for (auto i = 0; i < aggPlan->groupingKeys().size(); ++i) {
      finalGroupingKeys.push_back(aggPlan->intermediateColumns()[i]);
    }

    auto* finalAgg = make<Aggregation>(
        plan,
        finalGroupingKeys,
        aggPlan->aggregates(),
        core::AggregationNode::Step::kFinal,
        aggPlan->columns());

    state.addCost(*finalAgg);
    plan = finalAgg;
  }
  if (!dt->having.empty()) {
    auto filter = make<Filter>(plan, dt->having);
    state.addCost(*filter);
    plan = filter;
  }
  if (dt->hasOrderBy()) {
    auto* orderBy = make<OrderBy>(
        plan, dt->orderKeys, dt->orderTypes, dt->limit, dt->offset);
    state.addCost(*orderBy);
    plan = orderBy;
  }
  if (!dt->columns.empty()) {
    auto* project = make<Project>(plan, dt->exprs, dt->columns);
    plan = project;
  }
  if (!dt->hasOrderBy() && dt->hasLimit()) {
    auto limit = make<Limit>(plan, dt->limit, dt->offset);
    state.addCost(*limit);
    plan = limit;
  }
}

namespace {

CPSpan<Column> leadingColumns(const ExprVector& exprs) {
  int32_t i = 0;
  for (; i < exprs.size(); ++i) {
    if (exprs[i]->type() != PlanType::kColumnExpr) {
      break;
    }
  }
  return CPSpan(reinterpret_cast<ColumnCP const*>(&exprs[0]), i);
}

bool isIndexColocated(
    const IndexInfo& info,
    const ExprVector& lookupValues,
    const RelationOpPtr& input) {
  if (info.index->distribution().isBroadcast &&
      input->distribution().distributionType.locus ==
          info.index->distribution().distributionType.locus) {
    return true;
  }

  // True if 'input' is partitioned so that each partitioning key is joined to
  // the corresponding partition key in 'info'.
  if (input->distribution().distributionType !=
      info.index->distribution().distributionType) {
    return false;
  }
  if (input->distribution().partition.empty()) {
    return false;
  }
  if (input->distribution().partition.size() !=
      info.index->distribution().partition.size()) {
    return false;
  }
  for (auto i = 0; i < input->distribution().partition.size(); ++i) {
    auto nthKey = position(lookupValues, *input->distribution().partition[i]);
    if (nthKey != kNotFound) {
      if (info.schemaColumn(info.lookupKeys.at(nthKey)) !=
          info.index->distribution().partition.at(i)) {
        return false;
      }
    } else {
      return false;
    }
  }
  return true;
}

RelationOpPtr repartitionForIndex(
    const IndexInfo& info,
    const ExprVector& lookupValues,
    const RelationOpPtr& plan,
    PlanState& state) {
  if (isSingleWorker() || isIndexColocated(info, lookupValues, plan)) {
    return plan;
  }

  ExprVector keyExprs;
  auto& partition = info.index->distribution().partition;
  for (auto key : partition) {
    // partition is in schema columns, lookupKeys is in BaseTable columns. Use
    // the schema column of lookup key for matching.
    auto nthKey = position(
        info.lookupKeys,
        [](auto c) {
          return c->is(PlanType::kColumnExpr)
              ? c->template as<Column>()->schemaColumn()
              : c;
        },
        *key);
    if (nthKey == kNotFound) {
      return nullptr;
    }

    keyExprs.push_back(lookupValues[nthKey]);
  }

  Distribution distribution{
      info.index->distribution().distributionType, std::move(keyExprs)};
  auto* repartition =
      make<Repartition>(plan, std::move(distribution), plan->columns());
  state.addCost(*repartition);
  return repartition;
}

float fanoutJoinTypeLimit(core::JoinType joinType, float fanout) {
  switch (joinType) {
    case core::JoinType::kLeft:
      return std::max<float>(1, fanout);
    case core::JoinType::kLeftSemiFilter:
      return std::min<float>(1, fanout);
    case core::JoinType::kAnti:
      return 1 - std::min<float>(1, fanout);
    case core::JoinType::kLeftSemiProject:
    case core::JoinType::kRightSemiProject:
      return 1;
    default:
      return fanout;
  }
}
} // namespace

void Optimization::joinByIndex(
    const RelationOpPtr& plan,
    const JoinCandidate& candidate,
    PlanState& state,
    std::vector<NextJoin>& toTry) {
  if (candidate.tables.size() != 1 ||
      candidate.tables[0]->type() != PlanType::kTableNode ||
      !candidate.existences.empty()) {
    // Index applies to single base tables.
    return;
  }
  auto rightTable = candidate.tables.at(0)->as<BaseTable>();
  auto left = candidate.sideOf(rightTable, true);
  auto right = candidate.sideOf(rightTable);
  auto& keys = right.keys;
  auto keyColumns = leadingColumns(keys);
  if (keyColumns.empty()) {
    return;
  }
  for (auto& index : rightTable->schemaTable->columnGroups) {
    auto info = rightTable->schemaTable->indexInfo(index, keyColumns);
    if (info.lookupKeys.empty()) {
      continue;
    }
    PlanStateSaver save(state, candidate);
    auto newPartition = repartitionForIndex(info, left.keys, plan, state);
    if (!newPartition) {
      continue;
    }
    state.placed.add(candidate.tables.at(0));
    auto joinType = right.leftJoinType();
    if (joinType == core::JoinType::kFull ||
        joinType == core::JoinType::kRight) {
      // Not available by index.
      return;
    }
    auto fanout = fanoutJoinTypeLimit(
        joinType, info.scanCardinality * rightTable->filterSelectivity);

    auto lookupKeys = left.keys;
    // The number of keys is  the prefix that matches index order.
    lookupKeys.resize(info.lookupKeys.size());
    state.columns.unionSet(TableScan::availableColumns(rightTable, index));
    auto c = state.downstreamColumns();
    c.intersect(state.columns);
    for (auto& filter : rightTable->filter) {
      c.unionSet(filter->columns());
    }

    auto columns = c.toVector<Column>();

    auto* scan = make<TableScan>(
        newPartition,
        newPartition->distribution(),
        rightTable,
        info.index,
        fanout,
        columns,
        lookupKeys,
        joinType,
        candidate.join->filter());

    state.columns.unionSet(c);
    state.addCost(*scan);
    state.addNextJoin(&candidate, scan, {}, toTry);
  }
}

// Returns the positions in 'keys' for the expressions that determine the
// partition. empty if the partition is not decided by 'keys'
std::vector<uint32_t> joinKeyPartition(
    const RelationOpPtr& op,
    const ExprVector& keys) {
  std::vector<uint32_t> positions;
  for (unsigned i = 0; i < op->distribution().partition.size(); ++i) {
    auto nthKey = position(keys, *op->distribution().partition[i]);
    if (nthKey == kNotFound) {
      return {};
    }
    positions.push_back(nthKey);
  }
  return positions;
}

namespace {
PlanObjectSet availableColumns(PlanObjectCP object) {
  PlanObjectSet set;
  if (object->is(PlanType::kTableNode)) {
    for (auto& c : object->as<BaseTable>()->columns) {
      set.add(c);
    }
  } else if (object->is(PlanType::kValuesTableNode)) {
    for (auto& c : object->as<ValuesTable>()->columns) {
      set.add(c);
    }
  } else if (object->is(PlanType::kUnnestTableNode)) {
    for (auto& c : object->as<UnnestTable>()->columns) {
      set.add(c);
    }
  } else if (object->is(PlanType::kDerivedTableNode)) {
    for (auto& c : object->as<DerivedTable>()->columns) {
      set.add(c);
    }
  } else {
    VELOX_UNREACHABLE("Joinable must be a table or derived table");
  }
  return set;
}

bool isBroadcastableSize(PlanP build, PlanState& /*state*/) {
  return build->cost.fanout < 100'000;
}

// The 'other' side gets shuffled to align with 'input'. If 'input' is not
// partitioned on its keys, shuffle the 'input' too.
void alignJoinSides(
    RelationOpPtr& input,
    const ExprVector& keys,
    PlanState& state,
    RelationOpPtr& otherInput,
    const ExprVector& otherKeys,
    PlanState& otherState) {
  auto part = joinKeyPartition(input, keys);
  if (part.empty()) {
    Distribution distribution{
        otherInput->distribution().distributionType, keys};
    auto* repartition =
        make<Repartition>(input, std::move(distribution), input->columns());
    state.addCost(*repartition);
    input = repartition;
  }

  ExprVector distColumns;
  for (size_t i = 0; i < keys.size(); ++i) {
    auto nthKey = position(input->distribution().partition, *keys[i]);
    if (nthKey != kNotFound) {
      if (distColumns.size() <= nthKey) {
        distColumns.resize(nthKey + 1);
      }
      distColumns[nthKey] = otherKeys[i];
    }
  }

  Distribution distribution{
      input->distribution().distributionType, std::move(distColumns)};
  auto* repartition = make<Repartition>(
      otherInput, std::move(distribution), otherInput->columns());
  otherState.addCost(*repartition);
  otherInput = repartition;
}

} // namespace

void Optimization::joinByHash(
    const RelationOpPtr& plan,
    const JoinCandidate& candidate,
    PlanState& state,
    std::vector<NextJoin>& toTry) {
  VELOX_DCHECK(!candidate.tables.empty());
  auto build = candidate.sideOf(candidate.tables[0]);
  auto probe = candidate.sideOf(candidate.tables[0], true);

  const auto partKeys = joinKeyPartition(plan, probe.keys);
  ExprVector copartition;
  if (partKeys.empty()) {
    // Prefer to make a build partitioned on join keys and shuffle probe to
    // align with build.
    copartition = build.keys;
  }

  PlanStateSaver save(state, candidate);

  PlanObjectSet buildFilterColumns;
  for (auto& filter : candidate.join->filter()) {
    buildFilterColumns.unionColumns(filter);
  }
  buildFilterColumns.intersect(availableColumns(candidate.tables[0]));

  PlanObjectSet buildTables;
  PlanObjectSet buildColumns;
  for (auto buildTable : candidate.tables) {
    buildColumns.unionSet(availableColumns(buildTable));
    buildTables.add(buildTable);
  }

  buildColumns.intersect(state.downstreamColumns());
  buildColumns.unionColumns(build.keys);
  buildColumns.unionSet(buildFilterColumns);
  state.columns.unionSet(buildColumns);

  MemoKey memoKey{
      candidate.tables[0], buildColumns, buildTables, candidate.existences};

  Distribution forBuild;
  if (plan->distribution().distributionType.isGather) {
    forBuild = Distribution::gather();
  } else {
    forBuild = {plan->distribution().distributionType, copartition};
  }

  PlanObjectSet empty;
  bool needsShuffle = false;
  auto buildPlan = makePlan(
      memoKey, forBuild, empty, candidate.existsFanout, state, needsShuffle);

  // The build side tables are all joined if the first build is a
  // table but if it is a derived table (most often with aggregation),
  // only some of the tables may be fully joined.
  if (candidate.tables[0]->is(PlanType::kDerivedTableNode)) {
    state.placed.add(candidate.tables[0]);
    state.placed.unionSet(buildPlan->fullyImported);
  } else {
    state.placed.unionSet(buildTables);
  }

  PlanState buildState(state.optimization, state.dt, buildPlan);
  RelationOpPtr buildInput = buildPlan->op;
  RelationOpPtr probeInput = plan;

  if (!isSingleWorker_) {
    if (!partKeys.empty()) {
      if (needsShuffle) {
        if (copartition.empty()) {
          for (auto i : partKeys) {
            copartition.push_back(build.keys[i]);
          }
        }
        Distribution distribution{
            plan->distribution().distributionType, copartition};
        auto* repartition = make<Repartition>(
            buildInput, std::move(distribution), buildInput->columns());
        buildState.addCost(*repartition);
        buildInput = repartition;
      }
    } else if (
        candidate.join->isBroadcastableType() &&
        isBroadcastableSize(buildPlan, state)) {
      auto* broadcast = make<Repartition>(
          buildInput,
          Distribution::broadcast(plan->distribution().distributionType),
          buildInput->columns());
      buildState.addCost(*broadcast);
      buildInput = broadcast;
    } else {
      // The probe gets shuffled to align with build. If build is not
      // partitioned on its keys, shuffle the build too.
      alignJoinSides(
          buildInput, build.keys, buildState, probeInput, probe.keys, state);
    }
  }

  auto* buildOp =
      make<HashBuild>(buildInput, ++buildCounter_, build.keys, buildPlan);
  buildState.addCost(*buildOp);

  ColumnVector columns;
  PlanObjectSet columnSet;
  ColumnCP mark = nullptr;
  PlanObjectSet probeColumns;
  probeColumns.unionColumns(plan->columns());

  const auto joinType = build.leftJoinType();
  const bool probeOnly = joinType == core::JoinType::kLeftSemiFilter ||
      joinType == core::JoinType::kLeftSemiProject ||
      joinType == core::JoinType::kAnti ||
      joinType == core::JoinType::kLeftSemiProject;

  state.downstreamColumns().forEach([&](auto object) {
    auto column = reinterpret_cast<ColumnCP>(object);
    if (column == build.markColumn) {
      mark = column;
      columnSet.add(object);
      return;
    }
    if ((probeOnly || !buildColumns.contains(column)) &&
        !probeColumns.contains(column)) {
      return;
    }
    columnSet.add(object);
    columns.push_back(column);
  });

  // If there is an existence flag, it is the rightmost result column.
  if (mark) {
    const_cast<Value*>(&mark->value())->trueFraction =
        std::min<float>(1, candidate.fanout);
    columns.push_back(mark);
  }
  state.columns = columnSet;
  const auto fanout = fanoutJoinTypeLimit(joinType, candidate.fanout);
  auto* join = make<Join>(
      JoinMethod::kHash,
      joinType,
      probeInput,
      buildOp,
      probe.keys,
      build.keys,
      candidate.join->filter(),
      fanout,
      std::move(columns));
  state.addCost(*join);
  state.cost.setupCost += buildState.cost.unitCost + buildState.cost.setupCost;
  state.cost.totalBytes += buildState.cost.totalBytes;
  state.cost.transferBytes += buildState.cost.transferBytes;
  join->buildCost = buildState.cost;
  state.addNextJoin(&candidate, join, {buildOp}, toTry);
}

core::JoinType reverseJoinType(core::JoinType joinType) {
  switch (joinType) {
    case core::JoinType::kLeft:
      return core::JoinType::kRight;
    case core::JoinType::kRight:
      return core::JoinType::kLeft;
    case core::JoinType::kLeftSemiFilter:
      return core::JoinType::kRightSemiFilter;
    case core::JoinType::kLeftSemiProject:
      return core::JoinType::kRightSemiProject;
    default:
      return joinType;
  }
}

void Optimization::joinByHashRight(
    const RelationOpPtr& plan,
    const JoinCandidate& candidate,
    PlanState& state,
    std::vector<NextJoin>& toTry) {
  VELOX_DCHECK(!candidate.tables.empty());
  auto probe = candidate.sideOf(candidate.tables[0]);
  auto build = candidate.sideOf(candidate.tables[0], true);

  PlanStateSaver save(state, candidate);

  PlanObjectSet probeFilterColumns;
  for (auto& filter : candidate.join->filter()) {
    probeFilterColumns.unionColumns(filter);
  }
  probeFilterColumns.intersect(availableColumns(candidate.tables[0]));

  PlanObjectSet probeTables;
  PlanObjectSet probeColumns;
  for (auto probeTable : candidate.tables) {
    probeColumns.unionSet(availableColumns(probeTable));
    state.placed.add(probeTable);
    probeTables.add(probeTable);
  }

  probeColumns.intersect(state.downstreamColumns());
  probeColumns.unionColumns(probe.keys);
  probeColumns.unionSet(probeFilterColumns);
  state.columns.unionSet(probeColumns);

  auto memoKey = MemoKey{
      candidate.tables[0], probeColumns, probeTables, candidate.existences};

  PlanObjectSet empty;
  bool needsShuffle = false;
  auto probePlan = makePlan(
      memoKey,
      Distribution{plan->distribution().distributionType, {}},
      empty,
      candidate.existsFanout,
      state,
      needsShuffle);

  PlanState probeState(state.optimization, state.dt, probePlan);

  RelationOpPtr probeInput = probePlan->op;
  RelationOpPtr buildInput = plan;

  if (!isSingleWorker_) {
    // The build gets shuffled to align with probe. If probe is not partitioned
    // on its keys, shuffle the probe too.
    alignJoinSides(
        probeInput, probe.keys, probeState, buildInput, build.keys, state);
  }

  auto* buildOp =
      make<HashBuild>(buildInput, ++buildCounter_, build.keys, nullptr);
  state.addCost(*buildOp);

  PlanObjectSet buildColumns;
  buildColumns.unionColumns(buildInput->columns());

  const auto leftJoinType = probe.leftJoinType();
  const auto fanout = fanoutJoinTypeLimit(leftJoinType, candidate.fanout);

  // Change the join type to the right join variant.
  const auto rightJoinType = reverseJoinType(leftJoinType);
  VELOX_CHECK(
      leftJoinType != rightJoinType,
      "Join type does not have right hash join variant");

  const bool buildOnly = rightJoinType == core::JoinType::kRightSemiFilter ||
      rightJoinType == core::JoinType::kRightSemiProject;

  ColumnVector columns;
  PlanObjectSet columnSet;
  ColumnCP mark = nullptr;

  state.downstreamColumns().forEach([&](auto object) {
    auto column = reinterpret_cast<ColumnCP>(object);
    if (column == probe.markColumn) {
      mark = column;
      return;
    }
    if (!buildColumns.contains(column) &&
        (buildOnly || !probeColumns.contains(column))) {
      return;
    }
    columnSet.add(object);
    columns.push_back(column);
  });

  if (mark) {
    const_cast<Value*>(&mark->value())->trueFraction =
        std::min<float>(1, candidate.fanout);
    columns.push_back(mark);
  }

  const auto buildCost = state.cost.unitCost;

  state.columns = columnSet;
  state.cost = probeState.cost;
  state.cost.setupCost += buildCost;

  auto* join = make<Join>(
      JoinMethod::kHash,
      rightJoinType,
      probeInput,
      buildOp,
      probe.keys,
      build.keys,
      candidate.join->filter(),
      fanout,
      std::move(columns));
  state.addCost(*join);

  state.addNextJoin(&candidate, join, {buildOp}, toTry);
}

void Optimization::crossJoinUnnest(
    const RelationOpPtr& plan,
    const JoinCandidate& candidate,
    PlanState& state,
    std::vector<NextJoin>& toTry) {
  auto c = state.downstreamColumns();
  c.intersect(state.columns);

  auto unnestTable = candidate.tables.at(0)->as<UnnestTable>();
  c.unionColumns(unnestTable->columns);

  auto* unnest =
      make<Unnest>(plan, candidate.join->filter(), c.toVector<Column>());

  state.placed.add(candidate.tables.at(0));
  state.columns.unionSet(c);
  state.addCost(*unnest);
  state.addNextJoin(&candidate, unnest, {}, toTry);
}

void Optimization::crossJoin(
    const RelationOpPtr& plan,
    const JoinCandidate& candidate,
    PlanState& state,
    std::vector<NextJoin>& toTry) {
  VELOX_NYI("No cross joins");
}

void Optimization::addJoin(
    const JoinCandidate& candidate,
    const RelationOpPtr& plan,
    PlanState& state,
    std::vector<NextJoin>& result) {
  std::vector<NextJoin> toTry;
  if (!candidate.join) {
    crossJoin(plan, candidate, state, toTry);
    return;
  }

  if (candidate.tables.size() == 1 &&
      candidate.tables[0]->is(PlanType::kUnnestTableNode)) {
    crossJoinUnnest(plan, candidate, state, toTry);
    result.insert(result.end(), toTry.begin(), toTry.end());
    return;
  }

  joinByIndex(plan, candidate, state, toTry);

  const auto sizeAfterIndex = toTry.size();
  joinByHash(plan, candidate, state, toTry);
  if (toTry.size() > sizeAfterIndex && candidate.join->isNonCommutative() &&
      candidate.join->hasRightHashVariant()) {
    // There is a hash based candidate with a non-commutative join. Try a right
    // join variant.
    joinByHashRight(plan, candidate, state, toTry);
  }

  // If one is much better do not try the other.
  if (toTry.size() == 2 && candidate.tables.size() == 1) {
    if (toTry[0].isWorse(toTry[1])) {
      toTry.erase(toTry.begin());
    } else if (toTry[1].isWorse(toTry[0])) {
      toTry.erase(toTry.begin() + 1);
    }
  }
  result.insert(result.end(), toTry.begin(), toTry.end());
}

namespace {

// Sets 'columns' to the columns in 'downstream' that exist
// in 'index' of 'table'.
ColumnVector indexColumns(
    const PlanObjectSet& downstream,
    BaseTableCP table,
    ColumnGroupP index) {
  ColumnVector result;
  downstream.forEach([&](PlanObjectCP object) {
    auto* column = object->as<Column>();
    if (!column->schemaColumn()) {
      return;
    }
    if (table != column->relation()) {
      return;
    }
    if (position(index->columns(), *column->schemaColumn()) != kNotFound) {
      result.push_back(column);
    }
  });
  return result;
}
} // namespace

void Optimization::tryNextJoins(
    PlanState& state,
    const std::vector<NextJoin>& nextJoins) {
  for (auto& next : nextJoins) {
    PlanStateSaver save(state);
    state.placed = next.placed;
    state.columns = next.columns;
    state.cost = next.cost;
    state.addBuilds(next.newBuilds);
    makeJoins(next.plan, state);
  }
}

RelationOpPtr Optimization::placeSingleRowDt(
    RelationOpPtr plan,
    DerivedTableCP subquery,
    ExprCP filter,
    PlanState& state) {
  MemoKey memoKey;
  memoKey.firstTable = subquery;
  memoKey.tables.add(subquery);
  for (const auto& column : subquery->columns) {
    memoKey.columns.add(column);
  }

  const auto broadcast = Distribution::broadcast({});

  PlanObjectSet empty;
  bool needsShuffle = false;
  auto rightPlan = makePlan(memoKey, broadcast, empty, 1, state, needsShuffle);

  auto rightOp = rightPlan->op;
  if (needsShuffle) {
    rightOp = make<Repartition>(rightOp, broadcast, rightOp->columns());
  }

  auto resultColumns = plan->columns();
  resultColumns.insert(
      resultColumns.end(),
      rightOp->columns().begin(),
      rightOp->columns().end());
  auto* join = Join::makeCrossJoin(
      std::move(plan), std::move(rightOp), std::move(resultColumns));
  state.addCost(*join);
  return join;
}

void Optimization::placeDerivedTable(DerivedTableCP from, PlanState& state) {
  PlanStateSaver save(state);

  state.placed.add(from);

  PlanObjectSet dtColumns;
  for (const auto& column : from->columns) {
    dtColumns.add(column);
  }

  dtColumns.intersect(state.downstreamColumns());
  state.columns.unionSet(dtColumns);

  MemoKey key;
  key.columns = std::move(dtColumns);
  key.firstTable = from;
  key.tables.add(from);

  bool ignore = false;
  auto plan = makePlan(key, Distribution{}, PlanObjectSet{}, 1, state, ignore);

  // Make plans based on the dt alone as first.
  makeJoins(plan->op, state);

  // We see if there are reducing joins to import inside the dt.
  PlanObjectSet visited = state.placed;
  visited.add(from);
  visited.unionSet(state.dt->importedExistences);
  visited.unionSet(state.dt->fullyImported);

  PlanObjectSet reducingSet;
  reducingSet.add(from);

  std::vector<PlanObjectCP> path{from};

  float reduction = 1;
  reducingJoinsRecursive(
      state, from, 1, 1.2, path, visited, reducingSet, reduction);

  if (reduction < 0.9) {
    key.tables = reducingSet;
    key.columns = state.downstreamColumns();
    plan = makePlan(key, Distribution{}, PlanObjectSet{}, 1, state, ignore);
    // Not all reducing joins are necessarily retained in the plan. Only mark
    // the ones fully imported as placed.
    state.placed.unionSet(plan->fullyImported);
    makeJoins(plan->op, state);
  }
}

bool Optimization::placeConjuncts(
    RelationOpPtr plan,
    PlanState& state,
    bool allowNondeterministic) {
  PlanStateSaver save(state);

  PlanObjectSet columnsAndSingles = state.columns;
  state.dt->singleRowDts.forEach([&](PlanObjectCP object) {
    columnsAndSingles.unionColumns(object->as<DerivedTable>()->columns);
  });

  ExprVector filters;
  for (auto& conjunct : state.dt->conjuncts) {
    if (!allowNondeterministic && conjunct->containsNonDeterministic()) {
      continue;
    }
    if (state.placed.contains(conjunct)) {
      continue;
    }
    if (conjunct->columns().isSubset(state.columns)) {
      state.columns.add(conjunct);
      filters.push_back(conjunct);
      continue;
    }
    if (conjunct->columns().isSubset(columnsAndSingles)) {
      // The filter depends on placed tables and non-correlated single row
      // subqueries.
      std::vector<DerivedTableCP> placeable;
      auto subqColumns = conjunct->columns();
      subqColumns.except(state.columns);
      subqColumns.forEach([&](PlanObjectCP object) {
        state.dt->singleRowDts.forEach([&](PlanObjectCP dtObject) {
          auto subquery = dtObject->as<DerivedTable>();
          // If the subquery provides columns for the filter, place it.
          const auto& conjunctColumns = conjunct->columns();
          for (auto subqColumn : subquery->columns) {
            if (conjunctColumns.contains(subqColumn)) {
              placeable.push_back(subquery);
              break;
            }
          }
        });
      });

      for (auto i = 0; i < placeable.size(); ++i) {
        state.placed.add(conjunct);
        plan = placeSingleRowDt(
            plan,
            placeable[i],
            (i == placeable.size() - 1 ? conjunct : nullptr),
            state);
        makeJoins(plan, state);
        return true;
      }
    }
  }

  if (!filters.empty()) {
    for (auto& filter : filters) {
      state.placed.add(filter);
    }
    auto* filter = make<Filter>(plan, std::move(filters));
    state.addCost(*filter);
    makeJoins(filter, state);
    return true;
  }
  return false;
}

namespace {

float startingScore(PlanObjectCP table) {
  if (table->is(PlanType::kTableNode)) {
    return table->as<BaseTable>()->schemaTable->cardinality;
  }

  if (table->is(PlanType::kValuesTableNode)) {
    return table->as<ValuesTable>()->cardinality();
  }

  return 10;
}
} // namespace

void Optimization::makeJoins(RelationOpPtr plan, PlanState& state) {
  auto& dt = state.dt;
  if (!plan) {
    auto firstTables = dt->startTables.toVector();
    std::vector<float> scores(firstTables.size());

    for (auto i = 0; i < firstTables.size(); ++i) {
      auto table = firstTables[i];
      state.debugSetFirstTable(table->id());
      scores.at(i) = startingScore(table);
    }
    std::vector<int32_t> ids(firstTables.size());
    std::iota(ids.begin(), ids.end(), 0);
    std::sort(ids.begin(), ids.end(), [&](int32_t left, int32_t right) {
      return scores[left] > scores[right];
    });
    for (auto i : ids) {
      auto from = firstTables.at(i);
      if (from->is(PlanType::kTableNode)) {
        auto table = from->as<BaseTable>();
        auto indices = table->as<BaseTable>()->chooseLeafIndex();
        // Make plan starting with each relevant index of the table.
        const auto downstream = state.downstreamColumns();
        for (auto index : indices) {
          PlanStateSaver save(state);
          state.placed.add(table);
          auto columns = indexColumns(downstream, table, index);

          state.columns.unionObjects(columns);
          auto distribution =
              TableScan::outputDistribution(table, index, columns);
          auto* scan = make<TableScan>(
              nullptr,
              std::move(distribution),
              table,
              index,
              index->table->cardinality * table->filterSelectivity,
              std::move(columns));
          state.addCost(*scan);
          makeJoins(scan, state);
        }
      } else if (from->is(PlanType::kValuesTableNode)) {
        const auto* valuesTable = from->as<ValuesTable>();
        ColumnVector columns;
        state.downstreamColumns().forEach([&](PlanObjectCP object) {
          auto* column = object->as<Column>();
          if (valuesTable == column->relation()) {
            columns.push_back(column);
          }
        });

        PlanStateSaver save{state};
        state.placed.add(valuesTable);
        state.columns.unionObjects(columns);
        auto* scan = make<Values>(*valuesTable, std::move(columns));
        state.addCost(*scan);
        makeJoins(scan, state);
      } else {
        // Start with a derived table.
        placeDerivedTable(from->as<const DerivedTable>(), state);
      }
    }
  } else {
    if (state.isOverBest()) {
      trace(OptimizerOptions::kExceededBest, dt->id(), state.cost, *plan);
      return;
    }
    // Add multitable filters not associated to a non-inner join.
    if (placeConjuncts(plan, state, false)) {
      return;
    }
    auto candidates = nextJoins(state);
    if (candidates.empty()) {
      if (placeConjuncts(plan, state, true)) {
        return;
      }
      addPostprocess(dt, plan, state);
      auto kept = state.plans.addPlan(plan, state);
      trace(
          kept ? OptimizerOptions::kRetained : OptimizerOptions::kExceededBest,
          dt->id(),
          state.cost,
          *plan);

      return;
    }
    std::vector<NextJoin> nextJoins;
    nextJoins.reserve(candidates.size());
    for (auto& candidate : candidates) {
      addJoin(candidate, plan, state, nextJoins);
    }
    tryNextJoins(state, nextJoins);
  }
}

namespace {
RelationOpPtr makeDistinct(const RelationOpPtr& input) {
  ExprVector groupingKeys;
  for (const auto& column : input->columns()) {
    groupingKeys.push_back(column);
  }

  return make<Aggregation>(
      input,
      groupingKeys,
      AggregateVector{},
      velox::core::AggregationNode::Step::kSingle,
      input->columns());
}

Distribution somePartition(const RelationOpPtrVector& inputs) {
  float card = 1;

  // A simple type and many values is a good partitioning key.
  auto score = [&](ColumnCP column) {
    const auto& value = column->value();
    const auto card = value.cardinality;
    return value.type->kind() >= TypeKind::ARRAY ? card / 10000 : card;
  };

  const auto& firstInput = inputs[0];
  auto inputColumns = firstInput->columns();
  std::sort(
      inputColumns.begin(),
      inputColumns.end(),
      [&](ColumnCP left, ColumnCP right) {
        return score(left) > score(right);
      });

  ExprVector columns;
  for (const auto* column : inputColumns) {
    card *= column->value().cardinality;
    columns.push_back(column);
    if (card > 100'000) {
      break;
    }
  }

  DistributionType distributionType;
  distributionType.numPartitions =
      queryCtx()->optimization()->runnerOptions().numWorkers;
  distributionType.locus = firstInput->distribution().distributionType.locus;

  return {distributionType, std::move(columns)};
}

// Adds the costs in the input states to the first state and if 'distinct' is
// not null adds the cost of that to the first state.
PlanP unionPlan(
    std::vector<PlanState>& states,
    const std::vector<PlanP>& inputPlans,
    const RelationOpPtr& result,
    Aggregation* distinct) {
  auto& firstState = states[0];

  PlanObjectSet fullyImported = inputPlans[0]->fullyImported;
  for (auto i = 1; i < states.size(); ++i) {
    const auto& otherCost = states[i].cost;
    fullyImported.intersect(inputPlans[i]->fullyImported);
    firstState.cost.add(otherCost);
    // The input cardinality is not additive, the fanout and other metrics are.
    firstState.cost.inputCardinality -= otherCost.inputCardinality;
  }
  if (distinct) {
    firstState.addCost(*distinct);
  }
  auto plan = make<Plan>(result, states[0]);
  plan->fullyImported = fullyImported;
  return plan;
}
} // namespace

PlanP Optimization::makePlan(
    const MemoKey& key,
    const Distribution& distribution,
    const PlanObjectSet& boundColumns,
    float existsFanout,
    PlanState& state,
    bool& needsShuffle) {
  needsShuffle = false;
  if (key.firstTable->is(PlanType::kDerivedTableNode) &&
      key.firstTable->as<DerivedTable>()->setOp.has_value()) {
    return makeUnionPlan(
        key, distribution, boundColumns, existsFanout, state, needsShuffle);
  } else {
    return makeDtPlan(key, distribution, existsFanout, state, needsShuffle);
  }
}

PlanP Optimization::makeUnionPlan(
    const MemoKey& key,
    const Distribution& distribution,
    const PlanObjectSet& boundColumns,
    float existsFanout,
    PlanState& state,
    bool& needsShuffle) {
  const auto* setDt = key.firstTable->as<DerivedTable>();

  RelationOpPtrVector inputs;
  std::vector<PlanP> inputPlans;
  std::vector<PlanState> inputStates;
  std::vector<bool> inputNeedsShuffle;

  for (auto* inputDt : setDt->children) {
    MemoKey inputKey = key;
    inputKey.firstTable = inputDt;
    inputKey.tables.erase(key.firstTable);
    inputKey.tables.add(inputDt);

    bool inputShuffle = false;
    auto inputPlan = makePlan(
        inputKey,
        distribution,
        boundColumns,
        existsFanout,
        state,
        inputShuffle);
    inputPlans.push_back(inputPlan);
    inputStates.emplace_back(*this, setDt, inputPlans.back());
    inputs.push_back(inputPlan->op);
    inputNeedsShuffle.push_back(inputShuffle);
  }

  const bool isDistinct =
      setDt->setOp.value() == logical_plan::SetOperation::kUnion;
  if (isSingleWorker_) {
    RelationOpPtr result = make<UnionAll>(inputs);
    Aggregation* distinct = nullptr;
    if (isDistinct) {
      result = makeDistinct(result);
      distinct = result->as<Aggregation>();
    }
    return unionPlan(inputStates, inputPlans, result, distinct);
  }

  if (distribution.partition.empty()) {
    if (isDistinct) {
      // Pick some partitioning key and shuffle on that and make distinct.
      Distribution someDistribution = somePartition(inputs);
      for (auto i = 0; i < inputs.size(); ++i) {
        inputs[i] = make<Repartition>(
            inputs[i], someDistribution, inputs[i]->columns());
        inputStates[i].addCost(*inputs[i]);
      }
    }
  } else {
    // Some need a shuffle. Add the shuffles, add an optional distinct and
    // return with no shuffle needed.
    for (auto i = 0; i < inputs.size(); ++i) {
      if (inputNeedsShuffle[i]) {
        inputs[i] =
            make<Repartition>(inputs[i], distribution, inputs[i]->columns());
        inputStates[i].addCost(*inputs[i]);
      }
    }
  }

  RelationOpPtr result = make<UnionAll>(inputs);
  Aggregation* distinct = nullptr;
  if (isDistinct) {
    result = makeDistinct(result);
    distinct = result->as<Aggregation>();
  }
  return unionPlan(inputStates, inputPlans, result, distinct);
}

PlanP Optimization::makeDtPlan(
    const MemoKey& key,
    const Distribution& distribution,
    float existsFanout,
    PlanState& state,
    bool& needsShuffle) {
  auto it = memo_.find(key);
  PlanSet* plans;
  if (it == memo_.end()) {
    DerivedTable dt;
    dt.import(
        *state.dt, key.firstTable, key.tables, key.existences, existsFanout);

    PlanState inner(*this, &dt);
    if (key.firstTable->is(PlanType::kDerivedTableNode)) {
      inner.setTargetColumnsForDt(key.columns);
    } else {
      inner.targetColumns = key.columns;
    }

    makeJoins(nullptr, inner);
    memo_[key] = std::move(inner.plans);
    plans = &memo_[key];
  } else {
    plans = &it->second;
  }
  return plans->best(distribution, needsShuffle);
}

} // namespace facebook::velox::optimizer
