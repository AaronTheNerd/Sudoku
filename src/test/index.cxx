#include "index.h"

#include <gtest/gtest.h>

#include <vector>

TEST(IndexTest, DefaultConstructor) { EXPECT_NO_THROW(atn::Index{}); }

TEST(IndexTest, ValidConstructor) { EXPECT_NO_THROW(atn::Index{3}); }

TEST(IndexTest, InvalidConstructor) {
  atn::Index i{9};
  EXPECT_TRUE(i.is_invalid());
}

TEST(IndexTest, DefaultBoxConstructor) {
  EXPECT_NO_THROW(atn::BoxIndex{});
}

TEST(IndexTest, ValidBoxConstructor) {
  EXPECT_NO_THROW(atn::BoxIndex{2});
}

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
