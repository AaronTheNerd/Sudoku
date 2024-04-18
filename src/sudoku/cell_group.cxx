#include "cell_group.h"

atn::sudoku::CellGroupFactory::CellGroupFactory(atn::sudoku::Board& board)
    : _board(board) {}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::board() const {
  CellGroup group;
  for (uint y{0}; y < 9; ++y) {
    for (uint x{0}; x < 9; ++x) {
      atn::sudoku::Position position{x, y};
      group.push_back(this->_board.get(position));
    }
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::row(uint y) const {
  CellGroup group;
  for (uint x{0}; x < 9; ++x) {
    atn::sudoku::Position position{x, y};
    group.push_back(this->_board.get(position));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::column(uint x) const {
  CellGroup group;
  for (uint y{0}; y < 9; ++y) {
    atn::sudoku::Position position{x, y};
    group.push_back(this->_board.get(position));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::box(uint box_x,
                                                          uint box_y) const {
  CellGroup group;
  for (uint y{0}; y < 3; ++y) {
    for (uint x{0}; x < 3; ++x) {
      atn::sudoku::Position position{3 * box_x + x, 3 * box_y + y};
      group.push_back(this->_board.get(position));
    }
  }
  return group;
}