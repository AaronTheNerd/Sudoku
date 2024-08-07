#include "options.h"

#include <gtest/gtest.h>

#include <vector>

#include "value.h"

TEST(OptionsTest, DefaultAllSet) {
  atn::Options options{};
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint index{0}; index < values.size(); ++index) {
    EXPECT_TRUE(options.includes(values[index]));
  }
}

TEST(OptionsTest, SetEmpty) {
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint iteration{0}; iteration < values.size(); ++iteration) {
    atn::Options options{0};
    options.set(values[iteration]);
    for (uint index{0}; index < values.size(); ++index) {
      if (index == iteration) {
        EXPECT_TRUE(options.includes(values[index]));
      } else {
        EXPECT_FALSE(options.includes(values[index]));
      }
    }
  }
}

TEST(OptionsTest, SetFull) {
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint iteration{0}; iteration < values.size(); ++iteration) {
    atn::Options options{};
    options.set(values[iteration]);
    for (uint index{0}; index < values.size(); ++index) {
      EXPECT_TRUE(options.includes(values[index]));
    }
  }
}

TEST(OptionsTest, ClearFull) {
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint iteration{0}; iteration < values.size(); ++iteration) {
    atn::Options options{};
    options.clear(values[iteration]);
    for (uint index{0}; index < values.size(); ++index) {
      if (index == iteration) {
        EXPECT_FALSE(options.includes(values[index]));
      } else {
        EXPECT_TRUE(options.includes(values[index]));
      }
    }
  }
}

TEST(OptionsTest, ClearEmpty) {
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (uint iteration{0}; iteration < values.size(); ++iteration) {
    atn::Options options{0};
    options.clear(values[iteration]);
    for (uint index{0}; index < values.size(); ++index) {
      EXPECT_FALSE(options.includes(values[index]));
    }
  }
}

TEST(OptionsTest, ClearAll) {
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  atn::Options options;
  options.clear_all();
  for (uint index{0}; index < values.size(); ++index) {
    EXPECT_FALSE(options.includes(values[index]));
  }
}

TEST(OptionsTest, Count) {
  atn::Options options;
  EXPECT_EQ(options.count(), 9);
  options.clear_all();
  EXPECT_EQ(options.count(), 0);
}
