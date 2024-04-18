#include "generator.h"

#include <gtest/gtest.h>
#include <iostream>

#include "recursive.h"

TEST(InitialBoardGeneratorTest, DefaultConstructor) {
  EXPECT_NO_THROW(atn::generator::Recursive{});
}

TEST(InitialBoardGeneratorTest, RecursiveGenerator) {
  atn::generator::Recursive generator{};
  atn::sudoku::Board board = generator.generate();
  atn::sudoku::CellGroupFactory factory{board};
  atn::sudoku::CellGroup board_cell_group = factory.board();
  
  for (uint index{0}; index < board_cell_group.size(); ++index) {
    atn::sudoku::CellPtr cell = board_cell_group[index];
    EXPECT_TRUE(cell->is_set());
  }
}

