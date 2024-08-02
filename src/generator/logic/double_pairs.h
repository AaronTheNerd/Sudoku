#pragma once

#include <optional>

#include "board.h"
#include "technique.h"

namespace atn::generator::logic {

class DoublePairs : public Technique {
 public:
  DoublePairs(atn::sudoku::BoardPtr);

 private:
  void find_next_move();
};

}  // namespace atn::generator::logic
