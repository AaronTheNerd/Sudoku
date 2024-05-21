#include "cell.h"

atn::sudoku::Cell::Cell(atn::sudoku::Position position) : _position(position), _value(), _options() {}

atn::sudoku::Cell::Cell(atn::sudoku::Position position, atn::sudoku::Value value) : _position(position), _value(value), _options(0) {}

atn::sudoku::Position atn::sudoku::Cell::position() const {
  return this->_position;
}

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

bool atn::sudoku::Cell::has_option(atn::sudoku::Value option) const {
  return this->_options.includes(option);
}

void atn::sudoku::Cell::set_option(atn::sudoku::Value option) {
  return this->_options.set(option);
}

void atn::sudoku::Cell::clear_option(atn::sudoku::Value option) {
  return this->_options.clear(option);
}

void atn::sudoku::Cell::clear_all_options() {
  this->_options.clear_all();
}

uint atn::sudoku::Cell::count_options() const {
  return this->_options.count();
}
