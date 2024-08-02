#pragma once

#include <optional>

#include "board.h"
#include "technique.h"

namespace atn {

class DoublePairs : public Technique {
 public:
  DoublePairs(BoardPtr);

 private:
  void find_next_move();
};

}  // namespace atn
