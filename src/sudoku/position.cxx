#include "position.h"

#include <exception>
#include <sstream>

uint atn::sudoku::Position::x() const { return this->_x; }

uint atn::sudoku::Position::y() const { return this->_y; }

void atn::sudoku::Position::x(uint x) {
  this->_validate_index(x);
  this->_x = x;
}

void atn::sudoku::Position::y(uint y) {
  this->_validate_index(y);
  this->_y = y;
}

atn::sudoku::Position::Position(uint x, uint y) : _x(), _y() {
  this->x(x);
  this->y(y);
}

void atn::sudoku::Position::_validate_index(uint index) const {
  if (index >= 9) {
    throw atn::sudoku::InvalidPositionIndex(index);
  }
}

atn::sudoku::InvalidPositionIndex::InvalidPositionIndex(uint index) noexcept {
  std::stringstream ss;
  ss << "Invalid position index received: " << index;
  this->message = ss.str();
}

const char* atn::sudoku::InvalidPositionIndex::what() const noexcept {
  return this->message.c_str();
}
