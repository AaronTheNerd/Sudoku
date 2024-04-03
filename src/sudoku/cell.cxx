#include "cell.h"

bool atn::sudoku::Cell::is_set() const {
  return this->value != atn::sudoku::Value{};
}

void atn::sudoku::Cell::set(atn::sudoku::Value value) {
  this->value = value;
}

atn::sudoku::Value atn::sudoku::Cell::unset() {
  atn::sudoku::Value value = this->value;
  this->value = atn::sudoku::Value{};
  return value;
}

atn::sudoku::Value atn::sudoku::Cell::get() const {
  return this->value;
}

atn::sudoku::Cell::Cell(): value() {}

atn::sudoku::Cell::Cell(atn::sudoku::Value value): value(value) {}