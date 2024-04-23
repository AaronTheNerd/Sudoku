#pragma once

#include <sys/types.h>

#include <exception>
#include <string>

namespace atn::sudoku {

class Position {
 public:
  uint x() const;
  uint y() const;

  void x(uint);
  void y(uint);

  bool operator==(const atn::sudoku::Position&) const;
  bool operator!=(const atn::sudoku::Position&) const;

  Position(uint, uint);

 private:
  void _validate_index(uint) const;

  uint _x;
  uint _y;
};

class InvalidPositionIndex : public std::exception {
 public:
  InvalidPositionIndex(uint) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn::sudoku