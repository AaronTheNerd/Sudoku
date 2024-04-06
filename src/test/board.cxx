#include "board.h"

#include <gtest/gtest.h>

TEST(BoardTest, DefaultConstructor) { EXPECT_NO_THROW(atn::sudoku::Board{}); }

TEST(BoardTest, Get) {
  atn::sudoku::Board board;
  atn::sudoku::Cell& cell = board.get(atn::sudoku::Position{4, 4});
  EXPECT_FALSE(cell.is_set());
}

TEST(BoardTest, GetMutable) {
  atn::sudoku::Board board;
  atn::sudoku::Position pos{3, 1};
  atn::sudoku::Cell& cell = board.get(pos);
  atn::sudoku::Value value{1};
  cell.set(value);

  atn::sudoku::Cell cell2 = board.get(pos);
  EXPECT_EQ(cell2.get(), value);
}

TEST(BoardTest, GetImmutable) {
  atn::sudoku::Board board;
  atn::sudoku::Position pos{3, 1};
  atn::sudoku::Cell cell = board.get(pos);
  atn::sudoku::Value value{1};
  cell.set(value);

  atn::sudoku::Cell cell2 = board.get(pos);
  EXPECT_FALSE(cell2.is_set());
}
