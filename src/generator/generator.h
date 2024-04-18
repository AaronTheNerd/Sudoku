#pragma once

#include "board.h"
#include "difficulty.hpp"

namespace atn::generator {

class Generator {
 public:
  Generator();

  atn::sudoku::Board get_sudoku(const atn::generator::DifficultyRange&);

 private:
  atn::sudoku::Board _board;
};

}  // namespace atn::generator
