#include "cell.h"

#include <gtest/gtest.h>

TEST(CellTest, DefaultConstructor) {
  atn::Value unset_value;
  atn::Cell cell;
  EXPECT_EQ(cell.get(), unset_value);
}

TEST(CellTest, Constructor) {
  atn::Value value{2};
  atn::Cell cell{{0, 0}, value};
  EXPECT_EQ(cell.get(), value);
}

TEST(CellTest, DefaultIsUnset) {
  atn::Cell cell;
  EXPECT_FALSE(cell.is_set());
}

TEST(CellTest, IsSet) {
  atn::Value value{3};
  atn::Cell cell{{0, 0}, value};
  EXPECT_TRUE(cell.is_set());
}

TEST(CellTest, SetValue) {
  atn::Value value{4};
  atn::Cell cell;
  cell.set(value);
  EXPECT_TRUE(cell.is_set());
  EXPECT_EQ(cell.get(), value);
}

TEST(CellTest, SetNewValue) {
  atn::Value old_value{1}, new_value{5};
  atn::Cell cell{{0, 0}, old_value};
  cell.set(new_value);
  EXPECT_TRUE(cell.is_set());
  EXPECT_EQ(cell.get(), new_value);
}

TEST(CellTest, UnsetValue) {
  atn::Value original_value{1};
  atn::Cell cell{{0, 0}, original_value};
  atn::Value return_value = cell.unset();
  EXPECT_FALSE(cell.is_set());
  EXPECT_EQ(return_value, original_value);
}

TEST(CellTest, DefaultAllOptions) {
  atn::Cell cell{};
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint index{0}; index < values.size(); ++index) {
    EXPECT_TRUE(cell.has_option(values[index]));
  }
}

TEST(CellTest, ConstructValueNoOptions) {
  atn::Cell cell{{0, 0}, 3};
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint index{0}; index < values.size(); ++index) {
    EXPECT_FALSE(cell.has_option(values[index]));
  }
}

TEST(CellTest, PositionGetter) {
  atn::Position position{3, 3};
  atn::Cell cell{position};
  EXPECT_EQ(position, cell.position());
}
