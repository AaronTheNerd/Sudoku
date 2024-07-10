#pragma once

#include <optional>

#include "board.h"
#include "next_move.h"

namespace atn::generator::logic {

using namespace atn::generator::logic;
using namespace atn::sudoku;

class Technique {
 public:
  Technique(BoardPtr);
  std::optional<NextMove> get_next_move() const;

 protected:
  std::optional<NextMove> _next_move;
  BoardPtr _board;
};

}  // namespace atn::generator::logic
