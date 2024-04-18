#pragma once

#include <memory>

#include "board.h"

namespace atn::generator {

class InitialBoardGenerator {
 public:
  virtual atn::sudoku::Board generate() = 0;
};

typedef std::shared_ptr<InitialBoardGenerator> InitialBoardGeneratorPtr;

}  // namespace atn::generator
