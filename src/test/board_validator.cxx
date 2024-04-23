#include <gtest/gtest.h>

#include "test_utils.h"
#include "validate.h"

TEST(BoardValidatorTest, InvalidRow) {
  atn::sudoku::Board board;
  atn::sudoku::Value value{1};
  atn::sudoku::Position position_1{1, 3}, position_2{6, 3};
  atn::sudoku::CellPtr cell_1 = board.get(position_1);
  atn::sudoku::CellPtr cell_2 = board.get(position_2);
  cell_1->set(value);
  cell_2->set(value);
  EXPECT_FALSE(atn::sudoku::validate(board));
}

TEST(BoardValidatorTest, InvalidColumn) {
  atn::sudoku::Board board;
  atn::sudoku::Value value{1};
  atn::sudoku::Position position_1{3, 1}, position_2{3, 6};
  atn::sudoku::CellPtr cell_1 = board.get(position_1);
  atn::sudoku::CellPtr cell_2 = board.get(position_2);
  cell_1->set(value);
  cell_2->set(value);
  EXPECT_FALSE(atn::sudoku::validate(board));
}

TEST(BoardValidatorTest, InvalidBox) {
  atn::sudoku::Board board;
  atn::sudoku::Value value{1};
  atn::sudoku::Position position_1{0, 0}, position_2{2, 2};
  atn::sudoku::CellPtr cell_1 = board.get(position_1);
  atn::sudoku::CellPtr cell_2 = board.get(position_2);
  cell_1->set(value);
  cell_2->set(value);
  EXPECT_FALSE(atn::sudoku::validate(board));
}

TEST(BoardValidatorTest, ValidFull) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 2, 3, 6, 7, 8, 9, 4, 5},
                                       {5, 8, 4, 2, 3, 9, 7, 6, 1},
                                       {9, 6, 7, 1, 4, 5, 3, 2, 8},
                                       {3, 7, 2, 4, 6, 1, 5, 8, 9},
                                       {6, 9, 1, 5, 8, 3, 2, 7, 4},
                                       {4, 5, 8, 7, 9, 2, 6, 1, 3},
                                       {8, 3, 6, 9, 2, 4, 1, 5, 7},
                                       {2, 1, 9, 8, 5, 7, 4, 3, 6},
                                       {7, 4, 5, 3, 1, 6, 8, 9, 2}});
  EXPECT_TRUE(atn::sudoku::validate(board));
}
