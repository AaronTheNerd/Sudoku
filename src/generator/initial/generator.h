#pragma once

#include <memory>

#include "board.h"

namespace atn::generator::initial {

class Generator {
 public:
  virtual atn::sudoku::BoardPtr generate() = 0;
};

typedef std::shared_ptr<Generator> GeneratorPtr;

}  // namespace atn::generator::initial
