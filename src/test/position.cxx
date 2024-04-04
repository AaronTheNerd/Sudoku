#include "position.h"

#include <gtest/gtest.h>

TEST(PositionTest, Constructor) {
  EXPECT_NO_THROW((atn::sudoku::Position{0, 0}));
}

TEST(PositionTest, InvalidConstructor) {
  EXPECT_THROW((atn::sudoku::Position{10, 0}),
               atn::sudoku::InvalidPositionIndex);
  EXPECT_THROW((atn::sudoku::Position{0, 10}),
               atn::sudoku::InvalidPositionIndex);
}

TEST(PositionTest, InvalidSetter) {
  atn::sudoku::Position pos{0, 0};
  EXPECT_THROW(pos.x(11), atn::sudoku::InvalidPositionIndex);
  EXPECT_THROW(pos.y(11), atn::sudoku::InvalidPositionIndex);
}

TEST(PositionTest, Setter) {
  atn::sudoku::Position pos{0, 0};
  pos.x(1);
  pos.y(2);
  EXPECT_EQ(1, pos.x());
  EXPECT_EQ(2, pos.y());
}

TEST(PositionTest, Getter) {
  atn::sudoku::Position pos{1, 2};
  EXPECT_EQ(1, pos.x());
  EXPECT_EQ(2, pos.y());
}
