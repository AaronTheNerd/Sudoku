#include "cell.h"

#include <gtest/gtest.h>

TEST(CellTest, DefaultConstructor) {
  atn::sudoku::Value unset_value;
  atn::sudoku::Cell cell;
  EXPECT_EQ(cell.get(), unset_value);
}

TEST(CellTest, Constructor) {
  atn::sudoku::Value value{2};
  atn::sudoku::Cell cell{value};
  EXPECT_EQ(cell.get(), value);
}

TEST(CellTest, DefaultIsUnset) {
  atn::sudoku::Cell cell;
  EXPECT_FALSE(cell.is_set());
}

TEST(CellTest, IsSet) {
  atn::sudoku::Value value{3};
  atn::sudoku::Cell cell{value};
  EXPECT_TRUE(cell.is_set());
}

TEST(CellTest, SetValue) {
  atn::sudoku::Value value{4};
  atn::sudoku::Cell cell;
  cell.set(value);
  EXPECT_TRUE(cell.is_set());
  EXPECT_EQ(cell.get(), value);
}

TEST(CellTest, SetNewValue) {
  atn::sudoku::Value old_value{1}, new_value{5};
  atn::sudoku::Cell cell{old_value};
  cell.set(new_value);
  EXPECT_TRUE(cell.is_set());
  EXPECT_EQ(cell.get(), new_value);
}

TEST(CellTest, UnsetValue) {
  atn::sudoku::Value original_value{1};
  atn::sudoku::Cell cell{original_value};
  atn::sudoku::Value return_value = cell.unset();
  EXPECT_FALSE(cell.is_set());
  EXPECT_EQ(return_value, original_value);
}

TEST(CellTest, DefaultAllOptions) {
  atn::sudoku::Cell cell{};
  std::vector<atn::sudoku::Value> values{{1}, {2}, {3}, {4}, {5},
                                         {6}, {7}, {8}, {9}};
  for (uint index{0}; index < values.size(); ++index) {
    EXPECT_TRUE(cell.has_option(values[index]));
  }
}

TEST(CellTest, ConstructValueNoOptions) {
  atn::sudoku::Cell cell{{3}};
  std::vector<atn::sudoku::Value> values{{1}, {2}, {3}, {4}, {5},
                                         {6}, {7}, {8}, {9}};
  for (uint index{0}; index < values.size(); ++index) {
    EXPECT_FALSE(cell.has_option(values[index]));
  }
}
