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

#include "axiom/optimizer/MultiFragmentPlanPrinter.h"
#include "velox/core/PlanNode.h"

namespace facebook::axiom::optimizer {

namespace {

// The estimate fields of a node's prediction. See toGraphJson.
folly::dynamic toJson(const NodePrediction& prediction) {
  folly::dynamic estimate = folly::dynamic::object;
  if (prediction.numRawInputRows.has_value()) {
    estimate["rawInputRows"] =
        static_cast<int64_t>(*prediction.numRawInputRows);
  }
  if (prediction.numRawInputBytesPerRow.has_value()) {
    estimate["rawInputBytesPerRow"] = *prediction.numRawInputBytesPerRow;
  }
  if (prediction.numSplits.has_value()) {
    estimate["splits"] = static_cast<int64_t>(*prediction.numSplits);
  }
  estimate["outputRows"] = prediction.cardinality;
  if (prediction.numOutputBytesPerRow.has_value()) {
    estimate["outputBytesPerRow"] = *prediction.numOutputBytesPerRow;
  }
  return estimate;
}

void collectScans(
    const velox::core::PlanNode& node,
    const NodePredictionMap* prediction,
    folly::dynamic& scans) {
  if (const auto* scan = node.as<velox::core::TableScanNode>()) {
    VELOX_CHECK_NOT_NULL(scan->tableHandle(), "Scan has no table handle");
    folly::dynamic entry = folly::dynamic::object;
    entry["nodeId"] = scan->id();
    entry["table"] = scan->tableHandle()->name();
    if (prediction != nullptr) {
      if (auto it = prediction->find(scan->id()); it != prediction->end()) {
        entry["estimate"] = toJson(it->second);
      }
    }
    scans.push_back(std::move(entry));
  }
  for (const auto& source : node.sources()) {
    collectScans(*source, prediction, scans);
  }
}

// Renders 'plan', with estimates from 'prediction' unless it is null.
folly::dynamic toGraph(
    const MultiFragmentPlan& plan,
    const NodePredictionMap* prediction) {
  // InputStage names the producer, so invert the edges once to find each
  // fragment's consumer.
  folly::F14FastMap<int32_t, int32_t> consumerOf;
  for (const auto& fragment : plan.fragments()) {
    for (const auto& input : fragment.inputStages) {
      consumerOf[input.producerFragmentId] = fragment.fragmentId;
    }
  }

  folly::dynamic fragments = folly::dynamic::array;
  for (const auto& fragment : plan.fragments()) {
    folly::dynamic entry = folly::dynamic::object;
    entry["id"] = fragment.fragmentId;
    entry["type"] = std::string{FragmentTypeName::toName(fragment.type)};
    if (fragment.numRemotePartitions.has_value()) {
      entry["numRemotePartitions"] = fragment.numRemotePartitions.value();
    }

    folly::dynamic scans = folly::dynamic::array;
    collectScans(*fragment.fragment.planNode, prediction, scans);
    if (!scans.empty()) {
      entry["scans"] = std::move(scans);
    }

    if (!fragment.inputStages.empty()) {
      folly::dynamic exchanges = folly::dynamic::array;
      for (const auto& input : fragment.inputStages) {
        exchanges.push_back(
            folly::dynamic::object("nodeId", input.consumerNodeId)(
                "producerFragmentId", input.producerFragmentId));
      }
      entry["exchanges"] = std::move(exchanges);
    }

    if (const auto* output = fragment.fragment.planNode
                                 ->as<velox::core::PartitionedOutputNode>()) {
      folly::dynamic outputEntry = folly::dynamic::object;
      outputEntry["nodeId"] = output->id();
      if (auto it = consumerOf.find(fragment.fragmentId);
          it != consumerOf.end()) {
        outputEntry["consumerFragmentId"] = it->second;
      }
      entry["output"] = std::move(outputEntry);
    }

    fragments.push_back(std::move(entry));
  }

  return folly::dynamic::object("fragments", std::move(fragments));
}

} // namespace

folly::dynamic MultiFragmentPlanPrinter::toGraphJson(
    const MultiFragmentPlan& plan,
    const NodePredictionMap& prediction) {
  return toGraph(plan, &prediction);
}

folly::dynamic MultiFragmentPlanPrinter::toGraphJson(
    const MultiFragmentPlan& plan) {
  return toGraph(plan, nullptr);
}

} // namespace facebook::axiom::optimizer
