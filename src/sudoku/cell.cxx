#include "cell.h"

atn::Cell::Cell(atn::Position position)
    : _position(position), _value(), _options() {}

atn::Cell::Cell(atn::Position position, atn::Value value)
    : _position(position), _value(value), _options(0) {}

atn::Position atn::Cell::position() const { return this->_position; }

bool atn::Cell::is_set() const { return this->_value != Value{}; }

void atn::Cell::set(atn::Value value) { this->_value = value; }

atn::Value atn::Cell::unset() {
  Value value = this->_value;
  this->_value = Value{};
  return value;
}

atn::Value atn::Cell::get() const { return this->_value; }

bool atn::Cell::has_option(atn::Value option) const {
  return this->_options.includes(option);
}

void atn::Cell::set_option(atn::Value option) {
  return this->_options.set(option);
}

void atn::Cell::clear_option(atn::Value option) {
  return this->_options.clear(option);
}

void atn::Cell::clear_all_options() { this->_options.clear_all(); }

uint atn::Cell::count_options() const { return this->_options.count(); }
