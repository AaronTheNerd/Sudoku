#include "board.h"

atn::sudoku::Cell& atn::sudoku::Board::get(const atn::sudoku::Position& pos) {
  return this->_board[pos.y()][pos.x()];
}

bool atn::sudoku::Board::is_valid() const {
  return true;
}

atn::sudoku::Board::Board() : _board() {}