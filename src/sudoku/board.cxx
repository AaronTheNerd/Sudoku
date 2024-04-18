#include "board.h"

atn::sudoku::CellPtr atn::sudoku::Board::get(const atn::sudoku::Position& pos) {
  return this->_board[pos.y()][pos.x()];
}

bool atn::sudoku::Board::is_valid() const {
  return this->is_valid_rows() && this->is_valid_columns() &&
         this->is_valid_boxes();
}

bool atn::sudoku::Board::is_valid_rows() const { return true; }

bool atn::sudoku::Board::is_valid_columns() const { return true; }

bool atn::sudoku::Board::is_valid_boxes() const { return true; }

atn::sudoku::Board::Board() : _board() { this->initialize_board(); }

void atn::sudoku::Board::initialize_board() {
  for (uint y{0}; y < 9u; ++y) {
    for (uint x{0}; x < 9u; ++x) {
      this->_board[y][x] = std::make_shared<atn::sudoku::Cell>();
    }
  }
}
