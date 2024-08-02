#pragma once

#include <optional>

#include "board.h"
#include "next_move.h"

namespace atn::generator::logic {

class Technique {
 public:
  Technique(atn::sudoku::BoardPtr);
  std::optional<NextMove> get_next_move() const;

 protected:
  std::optional<NextMove> _next_move;
  atn::sudoku::BoardPtr _board;
};

}  // namespace atn::generator::logic
