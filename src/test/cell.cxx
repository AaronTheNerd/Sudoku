#include <gtest/gtest.h>
#include "cell.h"

TEST(CellTest, DefaultConstrucor) {
  atn::sudoku::Cell cell;
  EXPECT_EQ(cell.get(), atn::sudoku::UNSET_VALUE);
}

TEST(CellTest, Constructor) {
  atn::sudoku::Cell cell{2};
  EXPECT_EQ(cell.get(), 2);
}

TEST(CellTest, IsUnset) {
  atn::sudoku::Cell cell;
  EXPECT_FALSE(cell.is_set());
}

TEST(CellTest, IsSet) {
  atn::sudoku::Cell cell{3};
  EXPECT_TRUE(cell.is_set());
}

TEST(CellTest, SetValue) {
  atn::sudoku::Cell cell;
  cell.set(4);
  EXPECT_TRUE(cell.is_set());
  EXPECT_EQ(cell.get(), 4);
}

TEST(CellTest, SetNewValue) {
  atn::sudoku::Cell cell{1};
  cell.set(5);
  EXPECT_TRUE(cell.is_set());
  EXPECT_EQ(cell.get(), 5);
}

TEST(CellTest, UnsetValue) {
  atn::sudoku::Cell cell{1};
  cell.unset();
  EXPECT_FALSE(cell.is_set());
}
