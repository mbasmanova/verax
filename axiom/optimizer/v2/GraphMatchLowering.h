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

#include "axiom/optimizer/v2/Translator.h"

namespace facebook::axiom::optimizer::v2 {

/// Lowers one graph match. Binds each pattern name to the translated plan of
/// the element table it matches, joins the elements on identity, and filters
/// the joined rows with the term predicates and the match predicate.
class Translator::GraphMatchLowering {
 public:
  GraphMatchLowering(
      Translator& translator,
      const logical_plan::GraphMatchNode& match)
      : translator_{translator}, match_{match}, graph_{*match.graph()} {}

  /// Returns the lowered match with its outputs in 'required', or nullopt when
  /// the match is empty: a pattern can match no table, or an edge cannot
  /// connect the vertices next to it.
  std::optional<Translated> lower(const LpNameSet& required);

 private:
  // A vertex or edge that patterns bind: the table that backs it, and its
  // translated plan with that plan's columns by name.
  struct Element {
    const logical_plan::PropertyGraph::ElementTable* table;
    NodeCP node;
    Scope scope;

    ExprVector columns(const std::vector<std::string>& names) const;
  };

  // Elements 'leftElement' and 'rightElement' match where 'leftKeys' equal
  // 'rightKeys'.
  struct Connection {
    size_t leftElement;
    ExprVector leftKeys;
    size_t rightElement;
    ExprVector rightKeys;
  };

  // Returns the element 'pattern' binds, or nullopt if it can match no table.
  std::optional<size_t> bind(
      const logical_plan::GraphElementPattern& pattern,
      bool edge);

  // Binds the patterns of 'path' and connects adjacent ones. Returns false if
  // a pattern can match no table, or an edge cannot connect the vertices next
  // to it.
  bool addPath(const logical_plan::GraphPathPattern& path);

  // Joins the elements, each on its connections to the elements joined
  // before it. Joins next an element connected to those, so a pattern whose
  // paths share names joins without a cross product.
  NodeCP join();

  // Translates the term predicates and the match predicate.
  ExprVector translatePredicates() const;

  // Returns the outputs in 'required' by output name.
  Scope outputs(const LpNameSet& required);

  Translator& translator_;
  const logical_plan::GraphMatchNode& match_;
  const logical_plan::PropertyGraph& graph_;

  // Bound elements, in the order patterns first name them.
  std::vector<Element> elements_;

  // Index in 'elements_' of the element each pattern name binds.
  folly::F14FastMap<std::string, size_t> elementByName_;

  // Pairs of adjacent elements and the columns they match on.
  std::vector<Connection> connections_;

  // Pattern name to a ROW of its element's properties, which predicates
  // dereference.
  Scope patternScope_;

  // Number of edges in each named path.
  folly::F14FastMap<std::string, int64_t> pathLengths_;

  // Term predicates and the match predicate.
  std::vector<const logical_plan::Expr*> predicates_;
};

} // namespace facebook::axiom::optimizer::v2
