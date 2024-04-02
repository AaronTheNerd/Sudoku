#include "cell.h"

bool atn::sudoku::Cell::is_set() const {
  return this->value != atn::sudoku::UNSET_VALUE;
}

void atn::sudoku::Cell::set(uint8_t value) {
  this->value = value;
}

uint8_t atn::sudoku::Cell::unset() {
  uint8_t value = this->value;
  this->value = atn::sudoku::UNSET_VALUE;
  return value;
}

atn::sudoku::Cell::Cell(): value(atn::sudoku::UNSET_VALUE) {}

atn::sudoku::Cell::Cell(uint8_t value): value(value) {}