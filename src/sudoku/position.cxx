#include "position.h"

#include <exception>
#include <sstream>

atn::Position::Position(atn::Index x, atn::Index y) : _x(x), _y(y) {}

atn::Index atn::Position::x() const { return this->_x; }

atn::Index atn::Position::y() const { return this->_y; }

void atn::Position::x(atn::Index x) { this->_x = x; }

void atn::Position::y(atn::Index y) { this->_y = y; }

std::string atn::Position::to_string() const {
  std::stringstream ss;
  ss << "(" << this->x().to_string() << ", " << this->y().to_string() << ")";
  return ss.str();
}

bool atn::Position::operator==(const atn::Position& rhs) const {
  return this->x() == rhs.x() && this->y() == rhs.y();
}

bool atn::Position::operator!=(const atn::Position& rhs) const {
  return !(*this == rhs);
}

uint atn::PositionHash::operator()(const atn::Position& position) const {
  return 9 * position.y().value() + position.x().value();
}
