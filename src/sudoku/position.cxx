#include "position.h"

#include <exception>
#include <sstream>

atn::sudoku::Position::Position(uint x, uint y) : _x(), _y() {
  this->x(x);
  this->y(y);
}

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

bool atn::sudoku::Position::operator==(const atn::sudoku::Position& rhs) const {
  return this->x() == rhs.x() && this->y() == rhs.y();
}

bool atn::sudoku::Position::operator!=(const atn::sudoku::Position& rhs) const {
  return !(*this == rhs);
}

void atn::sudoku::Position::_validate_index(uint index) const {
  if (index >= 9) {
    throw atn::sudoku::InvalidPositionIndex(index);
  }
}

uint atn::sudoku::PositionHash::operator()(const atn::sudoku::Position& position) const {
  return 9 * position.y() + position.x();
}

atn::sudoku::InvalidPositionIndex::InvalidPositionIndex(uint index) noexcept {
  std::stringstream ss;
  ss << "Invalid position index received: " << index;
  this->message = ss.str();
}

const char* atn::sudoku::InvalidPositionIndex::what() const noexcept {
  return this->message.c_str();
}
