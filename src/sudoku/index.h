#pragma once

#include <stdint.h>

#include <exception>
#include <sstream>
#include <string>

namespace atn {

class Index {
 public:
  Index(uint8_t = 0);

  bool operator==(const Index&) const;
  bool operator!=(const Index&) const;
  bool operator<(const Index&) const;
  Index& operator++();

  uint8_t value() const;
  virtual bool is_invalid() const;
  std::string to_string() const;

 protected:
  uint8_t _index;
};

class BoxIndex : public Index {
 public:
  BoxIndex(uint8_t = 0);

  bool is_invalid() const override;
};

class InvalidIndexValueException : public std::exception {
 public:
  InvalidIndexValueException(uint8_t) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn