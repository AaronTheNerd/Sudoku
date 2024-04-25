#pragma once

#include <array>

#include "cell.h"
#include "position.h"

namespace atn::sudoku {

class Board {
 public:
  Board();

  atn::sudoku::CellPtr get(const atn::sudoku::Position&);

 private:
  void initialize_board();
  std::array<std::array<atn::sudoku::CellPtr, 9>, 9> _board;
};

}  // namespace atn::sudoku