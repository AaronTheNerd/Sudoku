#include "value.h"
#include <sstream>

bool atn::sudoku::Value::operator==(const atn::sudoku::Value& rhs) const {
  return this->_value == rhs._value;
}

bool atn::sudoku::Value::operator!=(const atn::sudoku::Value& rhs) const {
  return this->_value != rhs._value;
}

atn::sudoku::Value::Value(): _value(atn::sudoku::UNSET_VALUE) {}

atn::sudoku::Value::Value(uint8_t value): _value(value) {
  if (this->_value > 9) {
    throw atn::sudoku::InvalidValueException{this->_value};
  }
}

atn::sudoku::InvalidValueException::InvalidValueException(uint8_t value) noexcept {
  std::stringstream ss;
  ss << "Invalid value received: " << (int)value;
  this->message = ss.str();
}

const char* atn::sudoku::InvalidValueException::what() const noexcept {
  return this->message.c_str();
}