#pragma once

#include <stdint.h>

#include <exception>
#include <string>

namespace atn {

class Value {
 public:
  Value(uint8_t = 0);

  bool operator==(const Value&) const;
  bool operator!=(const Value&) const;

  uint8_t value() const;

 private:
  uint8_t _value;
};

class ValueHash {
 public:
  uint8_t operator()(const Value& t) const;
};

class InvalidValueException : public std::exception {
 public:
  InvalidValueException(uint8_t) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn