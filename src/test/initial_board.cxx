#include <gtest/gtest.h>

#include <iostream>

#include "initial/generator.h"
#include "initial/recursive.h"

TEST(InitialBoardGeneratorTest, DefaultConstructor) {
  EXPECT_NO_THROW(atn::generator::initial::Recursive{});
}

TEST(InitialBoardGeneratorTest, RecursiveGenerator) {
  atn::generator::initial::Recursive generator{};
  atn::sudoku::BoardPtr board = generator.generate();
  atn::sudoku::CellGroup board_cell_group = board->board();
  std::vector<atn::sudoku::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (uint index{0}; index < board_cell_group.size(); ++index) {
    atn::sudoku::CellPtr cell = board_cell_group[index];
    EXPECT_TRUE(cell->is_set());
    for (auto& value : values) {
      EXPECT_FALSE(cell->has_option(value));
    }
  }
}
