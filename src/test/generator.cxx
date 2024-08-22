#include "generator.h"

#include <gtest/gtest.h>

#include "difficulty.hpp"

TEST(GeneratorTest, DefaultConstructor) { EXPECT_NO_THROW(atn::Generator{}); }

TEST(GeneratorTest, GetSudoku) {
  atn::Generator gen{};
  EXPECT_NO_THROW(gen.get_sudoku(atn::difficulty::beginner));
}
