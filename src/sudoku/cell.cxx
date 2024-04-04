#include "cell.h"

bool atn::sudoku::Cell::is_set() const {
  return this->_value != atn::sudoku::Value{};
}

void atn::sudoku::Cell::set(atn::sudoku::Value value) { this->_value = value; }

atn::sudoku::Value atn::sudoku::Cell::unset() {
  atn::sudoku::Value value = this->_value;
  this->_value = atn::sudoku::Value{};
  return value;
}

atn::sudoku::Value atn::sudoku::Cell::get() const { return this->_value; }

atn::sudoku::Cell::Cell() : _value() {}

atn::sudoku::Cell::Cell(atn::sudoku::Value value) : _value(value) {}