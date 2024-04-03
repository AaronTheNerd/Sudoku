#include "value.h"
#include <sstream>

bool atn::sudoku::Value::operator==(const atn::sudoku::Value& rhs) const {
  return this->value == rhs.value;
}

bool atn::sudoku::Value::operator!=(const atn::sudoku::Value& rhs) const {
  return this->value != rhs.value;
}

atn::sudoku::Value::Value(): value(atn::sudoku::UNSET_VALUE) {}

atn::sudoku::Value::Value(uint8_t value): value(value) {
  if (this->value > 9) {
    throw atn::sudoku::InvalidValueException{this->value};
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