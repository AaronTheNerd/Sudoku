#include "cell_group.h"
#include "test_utils.h"

#include <gtest/gtest.h>

TEST(CellGroupTest, DefaultConstructor) {
  EXPECT_NO_THROW(atn::CellGroup{});
}

TEST(CellGroupTest, DefaultSizeZero) {
  atn::CellGroup group;
  EXPECT_EQ(group.size(), 0);
}

TEST(CellGroupTest, Insert) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  EXPECT_EQ(group.size(), 1);
  EXPECT_EQ(group[0]->get(), atn::Value{1});
}

TEST(CellGroupTest, CannotInsertDuplicates) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  group.insert(board->get({0, 1}));
  group.insert(board->get({1, 0}));
  group.insert(board->get({0, 2}));
  EXPECT_EQ(group.size(), 4);
  group.insert(board->get({1, 0}));
  EXPECT_EQ(group.size(), 4);
}

TEST(CellGroupTest, Find) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  group.insert(board->get({0, 1}));
  group.insert(board->get({1, 0}));
  group.insert(board->get({0, 2}));
  atn::CellGroup::const_iterator it = group.find(board->get({1, 0}));
  EXPECT_NE(it, group.end());
}

TEST(CellGroupTest, FindNotContained) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  group.insert(board->get({0, 1}));
  group.insert(board->get({1, 0}));
  group.insert(board->get({0, 2}));
  atn::CellGroup::const_iterator it = group.find(board->get({2, 0}));
  EXPECT_EQ(it, group.end());
}

TEST(CellGroupTest, Includes) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  group.insert(board->get({0, 1}));
  group.insert(board->get({1, 0}));
  group.insert(board->get({0, 2}));
  EXPECT_TRUE(group.includes(board->get({0, 1})));
  EXPECT_FALSE(group.includes(board->get({4, 0})));
}

TEST(CellGroupTest, Erase) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  group.insert(board->get({0, 1}));
  group.insert(board->get({1, 0}));
  group.insert(board->get({0, 2}));
  EXPECT_EQ(group.size(), 4);
  group.erase(board->get({0, 1}));
  EXPECT_EQ(group.size(), 3);
  EXPECT_NE(group[2], board->get({0, 1}));
}

TEST(CellGroupTest, EraseNotContainedCell) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group;
  group.insert(board->get({0, 0}));
  group.insert(board->get({0, 1}));
  group.insert(board->get({1, 0}));
  group.insert(board->get({0, 2}));
  EXPECT_EQ(group.size(), 4);
  group.erase(board->get({2, 0}));
  EXPECT_EQ(group.size(), 4);
}

TEST(CellGroupTest, OrOperator) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group1, group2, group_or;
  group1.insert(board->get({0, 0}));
  group1.insert(board->get({0, 1}));
  group1.insert(board->get({1, 0}));
  group1.insert(board->get({0, 2}));

  group2.insert(board->get({0, 3}));
  group2.insert(board->get({0, 1}));
  group2.insert(board->get({1, 0}));
  group2.insert(board->get({1, 2}));

  EXPECT_EQ(group1.size(), 4);
  EXPECT_EQ(group2.size(), 4);

  group_or = group1 || group2;
  EXPECT_EQ(group_or.size(), 6);

  EXPECT_TRUE(group_or.includes(board->get({0, 0})));
  EXPECT_TRUE(group_or.includes(board->get({0, 1})));
  EXPECT_TRUE(group_or.includes(board->get({1, 0})));
  EXPECT_TRUE(group_or.includes(board->get({0, 2})));
  EXPECT_TRUE(group_or.includes(board->get({0, 3})));
  EXPECT_TRUE(group_or.includes(board->get({1, 2})));
}

TEST(CellGroupTest, AndOperator) {
  atn::BoardPtr board = atn::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                             {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                             {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                             {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                             {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                             {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                             {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                             {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                             {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::CellGroup group1, group2, group_and;
  group1.insert(board->get({0, 0}));
  group1.insert(board->get({0, 1}));
  group1.insert(board->get({1, 0}));
  group1.insert(board->get({0, 2}));

  group2.insert(board->get({0, 3}));
  group2.insert(board->get({0, 1}));
  group2.insert(board->get({1, 0}));
  group2.insert(board->get({1, 2}));

  EXPECT_EQ(group1.size(), 4);
  EXPECT_EQ(group2.size(), 4);

  group_and = group1 && group2;
  EXPECT_EQ(group_and.size(), 2);
  EXPECT_TRUE(group_and.includes(board->get({0, 1})));
  EXPECT_TRUE(group_and.includes(board->get({1, 0})));

  EXPECT_FALSE(group_and.includes(board->get({0, 0})));
  EXPECT_FALSE(group_and.includes(board->get({0, 2})));
  EXPECT_FALSE(group_and.includes(board->get({0, 3})));
  EXPECT_FALSE(group_and.includes(board->get({1, 2})));
}
