#include "position.h"

#include <gtest/gtest.h>

TEST(PositionTest, Constructor) {
  EXPECT_NO_THROW((atn::sudoku::Position{3, 3}));
}

TEST(PositionTest, Setter) {
  atn::sudoku::Position pos{0, 0};
  pos.x(1);
  pos.y(2);
  EXPECT_EQ(1, pos.x().value());
  EXPECT_EQ(2, pos.y().value());
}

TEST(PositionTest, Getter) {
  atn::sudoku::Position pos{1, 2};
  EXPECT_EQ(1, pos.x().value());
  EXPECT_EQ(2, pos.y().value());
}

TEST(PositionTest, Equality) {
  atn::sudoku::Position pos1{0, 1}, pos2{0, 0}, pos3{1, 0}, pos4{0, 1};
  EXPECT_TRUE(pos1 == pos1);
  EXPECT_FALSE(pos1 == pos2);
  EXPECT_FALSE(pos1 == pos3);
  EXPECT_TRUE(pos1 == pos4);
  EXPECT_TRUE(pos2 == pos2);
  EXPECT_FALSE(pos2 == pos3);
  EXPECT_FALSE(pos2 == pos4);
  EXPECT_TRUE(pos3 == pos3);
  EXPECT_FALSE(pos3 == pos4);
  EXPECT_TRUE(pos4 == pos4);
}

TEST(PositionTest, Inequality) {
  atn::sudoku::Position pos1{0, 1}, pos2{0, 0}, pos3{1, 0}, pos4{0, 1};
  EXPECT_FALSE(pos1 != pos1);
  EXPECT_TRUE(pos1 != pos2);
  EXPECT_TRUE(pos1 != pos3);
  EXPECT_FALSE(pos1 != pos4);
  EXPECT_FALSE(pos2 != pos2);
  EXPECT_TRUE(pos2 != pos3);
  EXPECT_TRUE(pos2 != pos4);
  EXPECT_FALSE(pos3 != pos3);
  EXPECT_TRUE(pos3 != pos4);
  EXPECT_FALSE(pos4 != pos4);
}

TEST(PositionTest, ToString) {
  atn::sudoku::Position pos{1, 2};
  EXPECT_EQ(pos.to_string(), "(1, 2)");
}
