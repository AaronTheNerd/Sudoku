#pragma once

#include <memory>
#include <vector>

#include "board.h"
#include "cell.h"

namespace atn::sudoku {

typedef std::vector<std::shared_ptr<atn::sudoku::Cell>> CellGroup;

class CellGroupFactory {
 public:
  CellGroupFactory(atn::sudoku::Board&);

  atn::sudoku::CellGroup board() const;
  atn::sudoku::CellGroup row(uint) const;
  atn::sudoku::CellGroup column(uint) const;
  atn::sudoku::CellGroup box(uint, uint) const;
 private:
  atn::sudoku::Board& _board;
};

}  // namespace atn::sudoku