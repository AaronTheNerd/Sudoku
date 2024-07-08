#include "board.h"

#include <gtest/gtest.h>

#include "test_utils.h"

TEST(BoardTest, FactoryFunction) {
  EXPECT_NO_THROW(atn::sudoku::Board::create());
}

TEST(BoardTest, Get) {
  atn::sudoku::BoardPtr board = atn::sudoku::Board::create();
  atn::sudoku::CellPtr cell = board->get(atn::sudoku::Position{4, 4});
  EXPECT_FALSE(cell->is_set());
}

TEST(BoardTest, GetMutable) {
  atn::sudoku::BoardPtr board = atn::sudoku::Board::create();
  atn::sudoku::Position pos{3, 1};
  atn::sudoku::CellPtr cell = board->get(pos);
  atn::sudoku::Value value{1};
  cell->set(value);

  atn::sudoku::CellPtr cell2 = board->get(pos);
  EXPECT_EQ(cell2->get(), value);
}

TEST(BoardTest, InvalidIndex) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  EXPECT_THROW(board->get({0, 9}), atn::sudoku::InvalidIndexValueException);
  EXPECT_THROW(board->get({9, 0}), atn::sudoku::InvalidIndexValueException);
  EXPECT_THROW(board->row(9), atn::sudoku::InvalidIndexValueException);
  EXPECT_THROW(board->column(9), atn::sudoku::InvalidIndexValueException);
  EXPECT_THROW(board->box(0, 3), atn::sudoku::InvalidIndexValueException);
  EXPECT_THROW(board->box(3, 0), atn::sudoku::InvalidIndexValueException);
}

TEST(BoardTest, Board) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::sudoku::CellGroup group = board->board();
  EXPECT_EQ(group.size(), 81);
}

TEST(BoardTest, Row) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 1, 1, 1, 1, 1, 1, 1, 1},
                                       {2, 2, 2, 2, 2, 2, 2, 2, 2},
                                       {3, 3, 3, 3, 3, 3, 3, 3, 3},
                                       {4, 4, 4, 4, 4, 4, 4, 4, 4},
                                       {5, 5, 5, 5, 5, 5, 5, 5, 5},
                                       {6, 6, 6, 6, 6, 6, 6, 6, 6},
                                       {7, 7, 7, 7, 7, 7, 7, 7, 7},
                                       {8, 8, 8, 8, 8, 8, 8, 8, 8},
                                       {9, 9, 9, 9, 9, 9, 9, 9, 9}});
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(0),
                                              {1, 1, 1, 1, 1, 1, 1, 1, 1})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(1),
                                              {2, 2, 2, 2, 2, 2, 2, 2, 2})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(2),
                                              {3, 3, 3, 3, 3, 3, 3, 3, 3})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(3),
                                              {4, 4, 4, 4, 4, 4, 4, 4, 4})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(4),
                                              {5, 5, 5, 5, 5, 5, 5, 5, 5})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(5),
                                              {6, 6, 6, 6, 6, 6, 6, 6, 6})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(6),
                                              {7, 7, 7, 7, 7, 7, 7, 7, 7})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(7),
                                              {8, 8, 8, 8, 8, 8, 8, 8, 8})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->row(8),
                                              {9, 9, 9, 9, 9, 9, 9, 9, 9})));
}

TEST(BoardTest, Column) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {1, 2, 3, 4, 5, 6, 7, 8, 9}});
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(0),
                                              {1, 1, 1, 1, 1, 1, 1, 1, 1})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(1),
                                              {2, 2, 2, 2, 2, 2, 2, 2, 2})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(2),
                                              {3, 3, 3, 3, 3, 3, 3, 3, 3})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(3),
                                              {4, 4, 4, 4, 4, 4, 4, 4, 4})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(4),
                                              {5, 5, 5, 5, 5, 5, 5, 5, 5})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(5),
                                              {6, 6, 6, 6, 6, 6, 6, 6, 6})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(6),
                                              {7, 7, 7, 7, 7, 7, 7, 7, 7})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(7),
                                              {8, 8, 8, 8, 8, 8, 8, 8, 8})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->column(8),
                                              {9, 9, 9, 9, 9, 9, 9, 9, 9})));
}

TEST(BoardTest, Box) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 1, 1, 2, 2, 2, 3, 3, 3},
                                       {1, 1, 1, 2, 2, 2, 3, 3, 3},
                                       {1, 1, 1, 2, 2, 2, 3, 3, 3},
                                       {4, 4, 4, 5, 5, 5, 6, 6, 6},
                                       {4, 4, 4, 5, 5, 5, 6, 6, 6},
                                       {4, 4, 4, 5, 5, 5, 6, 6, 6},
                                       {7, 7, 7, 8, 8, 8, 9, 9, 9},
                                       {7, 7, 7, 8, 8, 8, 9, 9, 9},
                                       {7, 7, 7, 8, 8, 8, 9, 9, 9}});
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(0, 0),
                                              {1, 1, 1, 1, 1, 1, 1, 1, 1})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(1, 0),
                                              {2, 2, 2, 2, 2, 2, 2, 2, 2})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(2, 0),
                                              {3, 3, 3, 3, 3, 3, 3, 3, 3})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(0, 1),
                                              {4, 4, 4, 4, 4, 4, 4, 4, 4})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(1, 1),
                                              {5, 5, 5, 5, 5, 5, 5, 5, 5})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(2, 1),
                                              {6, 6, 6, 6, 6, 6, 6, 6, 6})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(0, 2),
                                              {7, 7, 7, 7, 7, 7, 7, 7, 7})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(1, 2),
                                              {8, 8, 8, 8, 8, 8, 8, 8, 8})));
  EXPECT_TRUE((atn::test_utils::cell_group_eq(board->box(2, 2),
                                              {9, 9, 9, 9, 9, 9, 9, 9, 9})));
}

TEST(BoardTest, Mutability) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  atn::sudoku::Value value{3};
  board->get(atn::sudoku::Position{0, 0})->set(value);
  atn::sudoku::CellGroup row = board->row(0);
  EXPECT_EQ(row[0]->get(), value);
}

TEST(BoardTest, AreaOfEffect) {
  atn::sudoku::BoardPtr board =
      atn::test_utils::generate_board({{1, 2, 3, 4, 5, 6, 7, 8, 9},
                                       {2, 3, 4, 5, 6, 7, 8, 9, 1},
                                       {3, 4, 5, 6, 7, 8, 9, 1, 2},
                                       {4, 5, 6, 7, 8, 9, 1, 2, 3},
                                       {5, 6, 7, 8, 9, 1, 2, 3, 4},
                                       {6, 7, 8, 9, 1, 2, 3, 4, 5},
                                       {7, 8, 9, 1, 2, 3, 4, 5, 6},
                                       {8, 9, 1, 2, 3, 4, 5, 6, 7},
                                       {9, 1, 2, 3, 4, 5, 6, 7, 8}});
  for (atn::sudoku::Index x{0}; x < 9; ++x) {
    for (atn::sudoku::Index y{0}; y < 9; ++y) {
      atn::sudoku::Position position{x, y};
      atn::sudoku::CellGroup area_of_effect = board->area_of_effect({0, 0});
      EXPECT_EQ(area_of_effect.size(), 20);
    }
  }
}
