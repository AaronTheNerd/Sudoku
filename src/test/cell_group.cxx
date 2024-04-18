#include "cell_group.h"

#include <gtest/gtest.h>

#include <vector>

#include "board.h"
#include "test_utils.h"

TEST(CellGroupTest, Constructor) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  EXPECT_NO_THROW(atn::sudoku::CellGroupFactory{board});
}

TEST(CellGroupTest, InvalidIndex) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::sudoku::CellGroupFactory factory{board};
  EXPECT_THROW(factory.row(9), std::exception);
  EXPECT_THROW(factory.column(9), std::exception);
  EXPECT_THROW(factory.box(0, 3), std::exception);
  EXPECT_THROW(factory.box(3, 0), std::exception);
}

TEST(CellGroupTest, Board) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::sudoku::CellGroupFactory factory{board};
  atn::sudoku::CellGroup group = factory.board();
  EXPECT_EQ(group.size(), 81);
}

TEST(CellGroupTest, Row) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 1, 1, 1, 1, 1, 1, 1, 1},
                                       {2, 2, 2, 2, 2, 2, 2, 2, 2},
                                       {3, 3, 3, 3, 3, 3, 3, 3, 3},
                                       {4, 4, 4, 4, 4, 4, 4, 4, 4},
                                       {5, 5, 5, 5, 5, 5, 5, 5, 5},
                                       {6, 6, 6, 6, 6, 6, 6, 6, 6},
                                       {7, 7, 7, 7, 7, 7, 7, 7, 7},
                                       {8, 8, 8, 8, 8, 8, 8, 8, 8},
                                       {9, 9, 9, 9, 9, 9, 9, 9, 9}});
  atn::sudoku::CellGroupFactory factory{board};
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(0),
                                              {1, 1, 1, 1, 1, 1, 1, 1, 1})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(1),
                                              {2, 2, 2, 2, 2, 2, 2, 2, 2})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(2),
                                              {3, 3, 3, 3, 3, 3, 3, 3, 3})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(3),
                                              {4, 4, 4, 4, 4, 4, 4, 4, 4})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(4),
                                              {5, 5, 5, 5, 5, 5, 5, 5, 5})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(5),
                                              {6, 6, 6, 6, 6, 6, 6, 6, 6})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(6),
                                              {7, 7, 7, 7, 7, 7, 7, 7, 7})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(7),
                                              {8, 8, 8, 8, 8, 8, 8, 8, 8})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.row(8),
                                              {9, 9, 9, 9, 9, 9, 9, 9, 9})));
}

TEST(CellGroupTest, Column) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9}});
  atn::sudoku::CellGroupFactory factory{board};
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(0),
                                              {1, 1, 1, 1, 1, 1, 1, 1, 1})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(1),
                                              {2, 2, 2, 2, 2, 2, 2, 2, 2})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(2),
                                              {3, 3, 3, 3, 3, 3, 3, 3, 3})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(3),
                                              {4, 4, 4, 4, 4, 4, 4, 4, 4})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(4),
                                              {5, 5, 5, 5, 5, 5, 5, 5, 5})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(5),
                                              {6, 6, 6, 6, 6, 6, 6, 6, 6})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(6),
                                              {7, 7, 7, 7, 7, 7, 7, 7, 7})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(7),
                                              {8, 8, 8, 8, 8, 8, 8, 8, 8})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.column(8),
                                              {9, 9, 9, 9, 9, 9, 9, 9, 9})));
}

TEST(CellGroupTest, Box) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 1, 1, 2, 2, 2, 3, 3, 3},
                                       {1, 1, 1, 2, 2, 2, 3, 3, 3},
                                       {1, 1, 1, 2, 2, 2, 3, 3, 3},
                                       {4, 4, 4, 5, 5, 5, 6, 6, 6},
                                       {4, 4, 4, 5, 5, 5, 6, 6, 6},
                                       {4, 4, 4, 5, 5, 5, 6, 6, 6},
                                       {7, 7, 7, 8, 8, 8, 9, 9, 9},
                                       {7, 7, 7, 8, 8, 8, 9, 9, 9},
                                       {7, 7, 7, 8, 8, 8, 9, 9, 9}});
  atn::sudoku::CellGroupFactory factory{board};
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(0, 0),
                                              {1, 1, 1, 1, 1, 1, 1, 1, 1})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(1, 0),
                                              {2, 2, 2, 2, 2, 2, 2, 2, 2})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(2, 0),
                                              {3, 3, 3, 3, 3, 3, 3, 3, 3})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(0, 1),
                                              {4, 4, 4, 4, 4, 4, 4, 4, 4})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(1, 1),
                                              {5, 5, 5, 5, 5, 5, 5, 5, 5})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(2, 1),
                                              {6, 6, 6, 6, 6, 6, 6, 6, 6})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(0, 2),
                                              {7, 7, 7, 7, 7, 7, 7, 7, 7})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(1, 2),
                                              {8, 8, 8, 8, 8, 8, 8, 8, 8})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(factory.box(2, 2),
                                              {9, 9, 9, 9, 9, 9, 9, 9, 9})));
}

TEST(CellGroupTest, Mutability) {
  atn::sudoku::Board board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::sudoku::CellGroupFactory factory{board};
  atn::sudoku::Value value{3};
  board.get(atn::sudoku::Position{0, 0}).set(value);
  atn::sudoku::CellGroup row = factory.row(0);
  EXPECT_EQ(row[0]->get(), value);
}
