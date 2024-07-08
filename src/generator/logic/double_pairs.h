#pragma once

#include <optional>

#include "board.h"
#include "technique.h"

namespace atn::generator::logic {

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

class DoublePairs : Technique {
 public:
  DoublePairs(BoardPtr);
  std::optional<NextMove> get_next_move();

 private:
  std::optional<NextMove> _next_move;
  BoardPtr _board;
};

}  // namespace atn::generator::logic
