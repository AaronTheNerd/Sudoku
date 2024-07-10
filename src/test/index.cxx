#include "index.h"

#include <gtest/gtest.h>

#include <vector>

TEST(IndexTest, DefaultConstructor) { EXPECT_NO_THROW(atn::sudoku::Index{}); }

TEST(IndexTest, ValidConstructor) { EXPECT_NO_THROW(atn::sudoku::Index{3}); }

TEST(IndexTest, InvalidConstructor) {
  atn::sudoku::Index i{9};
  EXPECT_TRUE(i.is_invalid());
}

TEST(IndexTest, DefaultBoxConstructor) {
  EXPECT_NO_THROW(atn::sudoku::BoxIndex{});
}

TEST(IndexTest, ValidBoxConstructor) {
  EXPECT_NO_THROW(atn::sudoku::BoxIndex{2});
}

TEST(IndexTest, InvalidBoxConstructor) {
  atn::sudoku::BoxIndex i{3};
  EXPECT_TRUE(i.is_invalid());
}

TEST(IndexTest, InvalidValueExceptionThrow) {
  atn::sudoku::Index index{9};
  EXPECT_NO_THROW(index.to_string());
  EXPECT_THROW(index.value(), atn::sudoku::InvalidIndexValueException);
}

TEST(IndexTest, InvalidBoxValueExceptionThrow) {
  atn::sudoku::BoxIndex index{3};
  EXPECT_NO_THROW(index.to_string());
  EXPECT_THROW(index.value(), atn::sudoku::InvalidIndexValueException);
}

TEST(IndexTest, ToString) {
  atn::sudoku::Index index{2};
  EXPECT_EQ(index.to_string(), "2");
}
