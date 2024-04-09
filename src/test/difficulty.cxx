#include "difficulty.hpp"

#include <gtest/gtest.h>

TEST(DifficultyTest, BeginnerRange) {
  EXPECT_EQ(atn::generator::difficulty::beginner.min(), 3600);
  EXPECT_EQ(atn::generator::difficulty::beginner.max(), 4500);
}

TEST(DifficultyTest, EasyRange) {
  EXPECT_EQ(atn::generator::difficulty::easy.min(), 4300);
  EXPECT_EQ(atn::generator::difficulty::easy.max(), 5500);
}

TEST(DifficultyTest, MediumRange) {
  EXPECT_EQ(atn::generator::difficulty::medium.min(), 5300);
  EXPECT_EQ(atn::generator::difficulty::medium.max(), 6900);
}

TEST(DifficultyTest, TrickyRange) {
  EXPECT_EQ(atn::generator::difficulty::tricky.min(), 6500);
  EXPECT_EQ(atn::generator::difficulty::tricky.max(), 9300);
}

TEST(DifficultyTest, FiendishRange) {
  EXPECT_EQ(atn::generator::difficulty::fiendish.min(), 8300);
  EXPECT_EQ(atn::generator::difficulty::fiendish.max(), 14000);
}

TEST(DifficultyTest, DiabolicalRange) {
  EXPECT_EQ(atn::generator::difficulty::diabolical.min(), 11000);
  EXPECT_EQ(atn::generator::difficulty::diabolical.max(), 25000);
}

TEST(DifficultyTest, BelowRange) {
  EXPECT_FALSE(atn::generator::difficulty::beginner.in_range(3599));
  EXPECT_FALSE(atn::generator::difficulty::easy.in_range(4299));
  EXPECT_FALSE(atn::generator::difficulty::medium.in_range(5299));
  EXPECT_FALSE(atn::generator::difficulty::tricky.in_range(6499));
  EXPECT_FALSE(atn::generator::difficulty::fiendish.in_range(8299));
  EXPECT_FALSE(atn::generator::difficulty::diabolical.in_range(10999));
}

TEST(DifficultyTest, AboveRange) {
  EXPECT_FALSE(atn::generator::difficulty::beginner.in_range(4501));
  EXPECT_FALSE(atn::generator::difficulty::easy.in_range(5501));
  EXPECT_FALSE(atn::generator::difficulty::medium.in_range(6901));
  EXPECT_FALSE(atn::generator::difficulty::tricky.in_range(9301));
  EXPECT_FALSE(atn::generator::difficulty::fiendish.in_range(14001));
  EXPECT_FALSE(atn::generator::difficulty::diabolical.in_range(25001));
}

TEST(DifficultyTest, LowerBoundInRange) {
  EXPECT_TRUE(atn::generator::difficulty::beginner.in_range(3600));
  EXPECT_TRUE(atn::generator::difficulty::easy.in_range(4300));
  EXPECT_TRUE(atn::generator::difficulty::medium.in_range(5300));
  EXPECT_TRUE(atn::generator::difficulty::tricky.in_range(6500));
  EXPECT_TRUE(atn::generator::difficulty::fiendish.in_range(8300));
  EXPECT_TRUE(atn::generator::difficulty::diabolical.in_range(11000));
}

TEST(DifficultyTest, UpperBoundInRange) {
  EXPECT_TRUE(atn::generator::difficulty::beginner.in_range(4500));
  EXPECT_TRUE(atn::generator::difficulty::easy.in_range(5500));
  EXPECT_TRUE(atn::generator::difficulty::medium.in_range(6900));
  EXPECT_TRUE(atn::generator::difficulty::tricky.in_range(9300));
  EXPECT_TRUE(atn::generator::difficulty::fiendish.in_range(14000));
  EXPECT_TRUE(atn::generator::difficulty::diabolical.in_range(25000));
}
