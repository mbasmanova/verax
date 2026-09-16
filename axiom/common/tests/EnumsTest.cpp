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

#include "axiom/common/Enums.h"

#include <gtest/gtest.h>

namespace facebook::axiom {
namespace {

enum class Color { kRed, kGreen, kBlue };

AXIOM_DECLARE_ENUM_NAME(Color);

const auto& colorNames() {
  static const folly::F14FastMap<Color, std::string_view> kNames = {
      {Color::kBlue, "BLUE"},
      {Color::kRed, "RED"},
      {Color::kGreen, "GREEN"},
  };
  return kNames;
}

AXIOM_DEFINE_ENUM_NAME(Color, colorNames);

struct Shape {
  enum class Kind { kCircle, kSquare, kTriangle };

  AXIOM_DECLARE_EMBEDDED_ENUM_NAME(Kind);
};

const auto& shapeKindNames() {
  static const folly::F14FastMap<Shape::Kind, std::string_view> kNames = {
      {Shape::Kind::kTriangle, "TRIANGLE"},
      {Shape::Kind::kCircle, "CIRCLE"},
      {Shape::Kind::kSquare, "SQUARE"},
  };
  return kNames;
}

AXIOM_DEFINE_EMBEDDED_ENUM_NAME(Shape, Kind, shapeKindNames);

// Names are listed in enum-value order, whatever order the mapping is
// written in.
TEST(EnumsTest, allNames) {
  EXPECT_EQ(ColorName::allNames(), "RED, GREEN, BLUE");
  EXPECT_EQ(Shape::allKindNames(), "CIRCLE, SQUARE, TRIANGLE");
}

TEST(EnumsTest, toColor) {
  EXPECT_EQ(ColorName::toColor("GREEN"), Color::kGreen);
  EXPECT_EQ(ColorName::tryToColor("GREEN"), Color::kGreen);
  EXPECT_EQ(ColorName::tryToColor("green"), std::nullopt);
  EXPECT_EQ(ColorName::tryToColor("MAUVE"), std::nullopt);
}

} // namespace
} // namespace facebook::axiom
