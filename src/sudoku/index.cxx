#include "index.h"

#include <sstream>

atn::sudoku::Index::Index(uint8_t index) : _index(index) {}

bool atn::sudoku::Index::operator==(const atn::sudoku::Index& rhs) const {
  return this->_index == rhs._index;
}

bool atn::sudoku::Index::operator!=(const atn::sudoku::Index& rhs) const {
  return this->_index != rhs._index;
}

bool atn::sudoku::Index::operator<(const atn::sudoku::Index& rhs) const {
  return this->_index < rhs._index;
}

atn::sudoku::Index& atn::sudoku::Index::operator++() {
  this->_index += 1;
  return *this;
}

uint8_t atn::sudoku::Index::value() const {
  if (this->is_invalid()) {
    throw atn::sudoku::InvalidIndexValueException{this->_index};
  }
  return this->_index;
}

bool atn::sudoku::Index::is_invalid() const { return this->_index >= 9u; }

std::string atn::sudoku::Index::to_string() const {
  std::stringstream ss;
  ss << (int)this->_index;
  return ss.str();
}

atn::sudoku::BoxIndex::BoxIndex(uint8_t index) : Index(index) {}

bool atn::sudoku::BoxIndex::is_invalid() const { return this->_index >= 3u; }

atn::sudoku::InvalidIndexValueException::InvalidIndexValueException(
    uint8_t index) noexcept {
  std::stringstream ss;
  ss << "Invalid index received: " << (int)index;
  this->message = ss.str();
}

const char* atn::sudoku::InvalidIndexValueException::what() const noexcept {
  return this->message.c_str();
}

