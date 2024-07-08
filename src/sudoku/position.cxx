#include "position.h"

#include <exception>
#include <sstream>

atn::sudoku::Position::Position(atn::sudoku::Index x, atn::sudoku::Index y)
    : _x(x), _y(y) {}

atn::sudoku::Index atn::sudoku::Position::x() const { return this->_x; }

atn::sudoku::Index atn::sudoku::Position::y() const { return this->_y; }

void atn::sudoku::Position::x(atn::sudoku::Index x) { this->_x = x; }

void atn::sudoku::Position::y(atn::sudoku::Index y) { this->_y = y; }

std::string atn::sudoku::Position::to_string() const {
  std::stringstream ss;
  ss << "(" << this->x().to_string() << ", " << this->y().to_string() << ")";
  return ss.str();
}

bool atn::sudoku::Position::operator==(const atn::sudoku::Position& rhs) const {
  return this->x() == rhs.x() && this->y() == rhs.y();
}

bool atn::sudoku::Position::operator!=(const atn::sudoku::Position& rhs) const {
  return !(*this == rhs);
}

uint atn::sudoku::PositionHash::operator()(
    const atn::sudoku::Position& position) const {
  return 9 * position.y().value() + position.x().value();
}
