#pragma once

#include <array>

#include "cell.h"
#include "position.h"

namespace atn::sudoku {

class Board {
 public:
  atn::sudoku::CellPtr get(const atn::sudoku::Position&);
  bool is_valid() const;

  Board();

 private:
  void initialize_board();
  bool is_valid_rows() const;
  bool is_valid_columns() const;
  bool is_valid_boxes() const;

  std::array<std::array<atn::sudoku::CellPtr, 9>, 9> _board;
};

}  // namespace atn::sudoku