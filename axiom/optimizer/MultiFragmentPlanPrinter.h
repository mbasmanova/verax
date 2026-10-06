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

#include <folly/dynamic.h>
#include "axiom/optimizer/MultiFragmentPlan.h"
#include "axiom/optimizer/NodePrediction.h"

namespace facebook::axiom::optimizer {

/// Renders a MultiFragmentPlan as JSON.
class MultiFragmentPlanPrinter {
 public:
  /// Returns the plan's fragments, each with its control nodes and where its
  /// output goes.
  ///
  ///   {
  ///     "fragments": [
  ///       {"id": 2, "type": "SOURCE",
  ///        "tree": [
  ///          {"nodeId": "1", "kind": "Agg", "step": "PARTIAL",
  ///           "numGroupingKeys": 0,
  ///           "children": [
  ///             {"nodeId": "0", "kind": "Scan", "table": "tiny.nation"}]}],
  ///        "output": {"nodeId": "2", "consumerFragmentId": 1}},
  ///       {"id": 1, "type": "SINGLE",
  ///        "tree": [
  ///          {"nodeId": "4", "kind": "Agg", "step": "FINAL",
  ///           "numGroupingKeys": 0,
  ///           "children": [
  ///             {"nodeId": "3", "kind": "Exchange",
  ///              "distribution": "gather", "producerFragmentId": 2}]}]}
  ///     ]
  ///   }
  ///
  /// 'tree' is the fragment's control nodes, nested, root first; see
  /// toSummaryText for which nodes these are. Each node has 'nodeId', 'kind'
  /// and, when it has inputs, 'children'. Depending on the kind it also has:
  ///   - Scan: 'table'.
  ///   - Join: 'algorithm', 'joinType', 'numJoinKeys'. The algorithm is one
  ///     of HashJoin, MergeJoin, IndexLookupJoin, NestedLoopJoin, SpatialJoin.
  ///   - Agg: 'step', 'numGroupingKeys'.
  ///   - Exchange: 'producerFragmentId', the fragment it reads, and
  ///     'distribution', how that fragment's output reaches it: hash, gather,
  ///     broadcast or arbitrary. That fragment's tree is in its own entry.
  ///   - Window: 'numPartitionKeys', 'numOrderKeys'.
  ///   - TopN, Limit: 'count'.
  ///
  /// 'output' describes the fragment's PartitionedOutputNode, which serializes
  /// results for a reader on another worker: 'consumerFragmentId' names the
  /// fragment reading them, and is absent when the client reads them directly.
  /// A fragment whose results are consumed in process has no 'output' at all,
  /// which is the final fragment unless
  /// MultiFragmentPlan::Options::remoteOutput is set.
  ///
  /// 'numRemotePartitions' is reported for kFixed fragments, which are the only
  /// ones that have it.
  static folly::dynamic toSummaryJson(const MultiFragmentPlan& plan);

  /// Returns toSummaryJson(plan) with the optimizer's estimate on each tree
  /// node that has an entry in 'prediction':
  ///
  ///   {"nodeId": "0", "kind": "Scan", "table": "tiny.nation",
  ///    "estimate": {
  ///      "rawInputRows": 25,
  ///      "rawInputBytesPerRow": 16,
  ///      "splits": 1,
  ///      "outputRows": 25,
  ///      "outputBytesPerRow": 8}}
  ///
  /// 'estimate' is omitted for a node with no entry, and each field is
  /// omitted when unknown:
  ///   - 'rawInputRows': rows a scan reads, before the filters it evaluates.
  ///   - 'rawInputBytesPerRow': uncompressed bytes per row a scan reads, for
  ///     the columns it produces and those only its filters read.
  ///   - 'splits': splits a scan produces.
  ///   - 'outputRows': rows the node produces.
  ///   - 'outputBytesPerRow': uncompressed bytes per row it produces.
  static folly::dynamic toSummaryJson(
      const MultiFragmentPlan& plan,
      const NodePredictionMap& prediction);

  /// Returns the plan as one indented tree of its control nodes, root on top.
  /// At an exchange the tree continues into the fragment it reads:
  ///
  ///   Agg (FINAL) global
  ///     Gather F2 (FIXED, 4 workers) → F1
  ///       Agg (PARTIAL) global
  ///         HashJoin (INNER) 1 key
  ///           Scan "default"."lineitem"
  ///           Broadcast F3 (SOURCE) → F2
  ///             Scan "default"."orders"
  ///
  /// An exchange line says how rows move (Shuffle for hash partitioning,
  /// otherwise Gather, Broadcast or Arbitrary) and names the fragment it reads
  /// with its type and, unless it is a SOURCE fragment, the number of workers
  /// that run it.
  ///
  /// Control nodes are scans, joins, aggregations, exchanges, unions (a local
  /// exchange or an exchange with two or more inputs, and MixedUnion),
  /// windows, and TopN, OrderBy, Limit, RowNumber, TopNRowNumber, GroupId,
  /// MarkDistinct, EnforceDistinct, Unnest, EnforceSingleRow, TableWrite and
  /// Values. Keys are given as counts.
  static std::string toSummaryText(const MultiFragmentPlan& plan);

  /// Returns toSummaryText(plan) with the optimizer's estimate for each node
  /// that has one, on its own line indented twice as deep as a child:
  ///
  ///   HashJoin (INNER) 1 key
  ///       Estimate: 1,200 rows
  ///     Scan "default"."orders"
  ///         Estimate: 15,000 rows
  static std::string toSummaryText(
      const MultiFragmentPlan& plan,
      const NodePredictionMap& prediction);
};

} // namespace facebook::axiom::optimizer
