#pragma once

#include <stdint.h>

#include <exception>
#include <sstream>
#include <string>

namespace atn {

class BoxIndex;

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

  static Index from_boxes(BoxIndex board_index, BoxIndex internal_index);

 protected:
  uint8_t _index;
};

class BoxIndex : public Index {
 public:
  BoxIndex(uint8_t = 0);

  bool is_invalid() const override;

  static BoxIndex index_in_box(Index);
  static BoxIndex index_in_board(Index);
};

class InvalidIndexValueException : public std::exception {
 public:
  InvalidIndexValueException(uint8_t) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn