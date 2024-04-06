#pragma once

#include <array>

#include "cell.h"
#include "position.h"

namespace atn::sudoku {

class Board {
 public:
  atn::sudoku::Cell& get(const atn::sudoku::Position&);

  Board();

 private:
  std::array<std::array<atn::sudoku::Cell, 9>, 9> _board;
};

}  // namespace atn::sudoku