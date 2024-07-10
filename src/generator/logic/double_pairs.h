#pragma once

#include <optional>

#include "board.h"
#include "technique.h"

namespace atn::generator::logic {

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

class DoublePairs : public Technique {
 public:
  DoublePairs(BoardPtr);

 private:
  void find_next_move();
};

}  // namespace atn::generator::logic
