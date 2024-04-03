#include <vector>
#include <gtest/gtest.h>
#include "value.h"

TEST(ValueTest, DefaultConstrucor) {
  EXPECT_NO_THROW(atn::sudoku::Value{});
}

TEST(ValueTest, ValidConstructor) {
  EXPECT_NO_THROW(atn::sudoku::Value{3});
}

TEST(ValueTest, InvalidConstructor) {
  EXPECT_THROW(atn::sudoku::Value{11}, atn::sudoku::InvalidValueException);
}

TEST(ValueTest, Equality) {
  std::vector<atn::sudoku::Value> values = { {}, {4}, {2}, {4} };
  for (u_int i{0}; i < values.size(); ++i) {
    EXPECT_TRUE(values[i] == values[i]);
  }
  for (u_int i{0}; i < values.size() - 1; ++i) {
    for (u_int j{i + 1}; j < values.size(); ++j) {
      if (i == 1 && j == 3) {
        EXPECT_TRUE(values[i] == values[j]);
      } else {
        EXPECT_FALSE(values[i] == values[j]);
      }
    }
  }
}

TEST(ValueTest, Inequality) {
  std::vector<atn::sudoku::Value> values = { {}, {4}, {2}, {4} };
  for (u_int i{0}; i < values.size(); ++i) {
    EXPECT_FALSE(values[i] != values[i]);
  }
  for (u_int i{0}; i < values.size() - 1; ++i) {
    for (u_int j{i + 1}; j < values.size(); ++j) {
      if (i == 1 && j == 3) {
        EXPECT_FALSE(values[i] != values[j]);
      } else {
        EXPECT_TRUE(values[i] != values[j]);
      }
    }
  }
}
