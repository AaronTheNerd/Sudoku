#include "generator.h"

#include <gtest/gtest.h>

#include "difficulty.hpp"

TEST(GeneratorTest, DefaultConstructor) {
  EXPECT_NO_THROW(atn::generator::Generator{});
}

TEST(GeneratorTest, GetSudoku) {
  atn::generator::Generator gen{};
  EXPECT_NO_THROW(gen.get_sudoku(atn::generator::difficulty::beginner));
}
