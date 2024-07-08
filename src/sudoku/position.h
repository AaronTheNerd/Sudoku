#pragma once

#include <sys/types.h>

#include <exception>
#include <string>

#include "index.h"

namespace atn::sudoku {

class Position {
 public:
  Position(Index, Index);

  Index x() const;
  Index y() const;

  void x(Index);
  void y(Index);

  std::string to_string() const;

  bool operator==(const atn::sudoku::Position&) const;
  bool operator!=(const atn::sudoku::Position&) const;

 private:
  Index _x;
  Index _y;
};

class PositionHash {
 public:
  uint operator()(const atn::sudoku::Position& p) const;
};

}  // namespace atn::sudoku