#pragma once

#include <stdint.h>

#include <exception>
#include <string>

namespace atn::sudoku {

const uint8_t UNSET_VALUE{0};

class Value {
 public:
  bool operator==(const Value&) const;
  bool operator!=(const Value&) const;

  Value();
  Value(uint8_t);

 private:
  uint8_t _value;
};

class InvalidValueException : public std::exception {
 public:
  InvalidValueException(uint8_t) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn::sudoku