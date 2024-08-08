#include "index.h"

#include <gtest/gtest.h>

#include <vector>

struct IndexBoxConversion {
  atn::Index index;
  atn::BoxIndex expected;
};

TEST(IndexTest, DefaultConstructor) { EXPECT_NO_THROW(atn::Index{}); }

TEST(IndexTest, ValidConstructor) { EXPECT_NO_THROW(atn::Index{3}); }

TEST(IndexTest, InvalidConstructor) {
  atn::Index i{9};
  EXPECT_TRUE(i.is_invalid());
}

TEST(IndexTest, DefaultBoxConstructor) { EXPECT_NO_THROW(atn::BoxIndex{}); }

TEST(IndexTest, ValidBoxConstructor) { EXPECT_NO_THROW(atn::BoxIndex{2}); }

TEST(IndexTest, InvalidBoxConstructor) {
  atn::BoxIndex i{3};
  EXPECT_TRUE(i.is_invalid());
}

TEST(IndexTest, InvalidValueExceptionThrow) {
  atn::Index index{9};
  EXPECT_NO_THROW(index.to_string());
  EXPECT_THROW(index.value(), atn::InvalidIndexValueException);
}

TEST(IndexTest, InvalidBoxValueExceptionThrow) {
  atn::BoxIndex index{3};
  EXPECT_NO_THROW(index.to_string());
  EXPECT_THROW(index.value(), atn::InvalidIndexValueException);
}

TEST(IndexTest, ToString) {
  atn::Index index{2};
  EXPECT_EQ(index.to_string(), "2");
}

TEST(IndexTest, IndexToBoardBoxIndex) {
  std::vector<IndexBoxConversion> test_cases{
      {0, 0}, {1, 0}, {2, 0}, {3, 1}, {4, 1}, {5, 1}, {6, 2}, {7, 2}, {8, 2}};
  for (auto test_case : test_cases) {
    EXPECT_EQ(atn::BoxIndex::index_in_board(test_case.index),
              test_case.expected);
  }
}

TEST(IndexTest, IndexToInsideBoxIndex) {
  std::vector<IndexBoxConversion> test_cases{
      {0, 0}, {1, 1}, {2, 2}, {3, 0}, {4, 1}, {5, 2}, {6, 0}, {7, 1}, {8, 2}};
  for (auto test_case : test_cases) {
    EXPECT_EQ(atn::BoxIndex::index_in_box(test_case.index),
              test_case.expected);
  }
}
