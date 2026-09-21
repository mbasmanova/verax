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

namespace facebook::axiom::optimizer {

/// Renders a MultiFragmentPlan as JSON.
class MultiFragmentPlanPrinter {
 public:
  /// Returns the graph of the plan: the fragments, the tables each scans and
  /// the exchanges connecting them.
  ///
  ///   {
  ///     "fragments": [
  ///       {"id": 3, "type": "SOURCE",
  ///        "scans": [{"nodeId": "0", "table": "tiny.nation"}],
  ///        "output": {"nodeId": "2", "consumerFragmentId": 2}},
  ///       {"id": 2, "type": "FIXED", "numRemotePartitions": 4,
  ///        "exchanges": [{"nodeId": "3", "producerFragmentId": 3}],
  ///        "output": {"nodeId": "5", "consumerFragmentId": 1}},
  ///       {"id": 1, "type": "SINGLE",
  ///        "exchanges": [{"nodeId": "6", "producerFragmentId": 2}]}
  ///     ]
  ///   }
  ///
  /// 'output' describes the fragment's PartitionedOutputNode, which serializes
  /// results for a reader on another worker: 'consumerFragmentId' names the
  /// fragment reading them, and is absent when the client reads them directly.
  /// A fragment whose results are consumed in process has no 'output' at all,
  /// which is the final fragment unless
  /// MultiFragmentPlan::Options::remoteOutput is set.
  ///
  /// 'numRemotePartitions' is reported for kFixed fragments, which are the only
  /// ones that have it. 'scans' and 'exchanges' are each omitted when empty.
  static folly::dynamic toGraphJson(const MultiFragmentPlan& plan);
};

} // namespace facebook::axiom::optimizer
