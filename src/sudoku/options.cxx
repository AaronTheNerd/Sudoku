#include "options.h"

atn::sudoku::Options::Options(uint16_t bitset) : _bitset(bitset) {}

bool atn::sudoku::Options::includes(atn::sudoku::Value option) const {
  return (this->_bitset & (1 << option.value())) != 0;
}

void atn::sudoku::Options::set(atn::sudoku::Value option) {
  this->_bitset |= (1 << option.value());
}

void atn::sudoku::Options::clear(atn::sudoku::Value option) {
  this->_bitset &= ~(1 << option.value());
}
