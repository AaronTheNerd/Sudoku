#pragma once

#include "board.h"
#include "cell_group.h"
#include "position.h"

namespace atn::sudoku {

class CellGroupFactory {
 public:
  CellGroupFactory(atn::sudoku::Board&);

  atn::sudoku::CellGroup board() const;
  atn::sudoku::CellGroup row(uint) const;
  atn::sudoku::CellGroup column(uint) const;
  atn::sudoku::CellGroup box(uint, uint) const;
  atn::sudoku::CellGroup area_of_effect(atn::sudoku::Position) const;

 private:
  atn::sudoku::Board& _board;
};

}  // namespace atn::sudoku