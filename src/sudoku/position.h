#pragma once

#include <sys/types.h>

#include <exception>
#include <string>

#include "index.h"

namespace atn {

class Position {
 public:
  Position(Index, Index);

  Index x() const;
  Index y() const;

  void x(Index);
  void y(Index);

  std::string to_string() const;

  bool operator==(const Position&) const;
  bool operator!=(const Position&) const;

 private:
  Index _x;
  Index _y;
};

class PositionHash {
 public:
  uint operator()(const Position& p) const;
};

}  // namespace atn