#include "board.h"

atn::sudoku::CellPtr atn::sudoku::Board::get(const atn::sudoku::Position& pos) {
  return this->_board[pos.y()][pos.x()];
}

atn::sudoku::Board::Board() : _board() { this->initialize_board(); }

void atn::sudoku::Board::initialize_board() {
  for (uint y{0}; y < 9u; ++y) {
    for (uint x{0}; x < 9u; ++x) {
      this->_board[y][x] = std::make_shared<atn::sudoku::Cell>();
    }
  }
}
