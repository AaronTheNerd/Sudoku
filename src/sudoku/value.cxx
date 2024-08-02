#include "value.h"

#include <sstream>

atn::Value::Value(uint8_t value) : _value(value) {
  if (this->_value > 9) {
    throw InvalidValueException{this->_value};
  }
}

bool atn::Value::operator==(const atn::Value& rhs) const {
  return this->_value == rhs._value;
}

bool atn::Value::operator!=(const atn::Value& rhs) const {
  return this->_value != rhs._value;
}

uint8_t atn::Value::value() const { return this->_value; }

uint8_t atn::ValueHash::operator()(const atn::Value& value) const {
  return value.value();
}

atn::InvalidValueException::InvalidValueException(uint8_t value) noexcept {
  std::stringstream ss;
  ss << "Invalid value received: " << (int)value;
  this->message = ss.str();
}

const char* atn::InvalidValueException::what() const noexcept {
  return this->message.c_str();
}