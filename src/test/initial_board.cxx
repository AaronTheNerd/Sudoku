#include <gtest/gtest.h>

#include <iostream>

#include "initial/generator.h"
#include "initial/recursive.h"

TEST(InitialBoardGeneratorTest, DefaultConstructor) {
  EXPECT_NO_THROW(atn::generator::initial::Recursive{});
}

TEST(InitialBoardGeneratorTest, RecursiveGenerator) {
  atn::generator::initial::Recursive generator{};
  atn::sudoku::Board board = generator.generate();
  atn::sudoku::CellGroupFactory factory{board};
  atn::sudoku::CellGroup board_cell_group = factory.board();

  for (uint index{0}; index < board_cell_group.size(); ++index) {
    atn::sudoku::CellPtr cell = board_cell_group[index];
    EXPECT_TRUE(cell->is_set());
  }
}
