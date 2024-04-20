#pragma once

#include <memory>

#include "value.h"

namespace atn::sudoku {

class Cell {
 public:
  bool is_set() const;
  void set(atn::sudoku::Value);
  atn::sudoku::Value unset();
  atn::sudoku::Value get() const;

  Cell();
  Cell(atn::sudoku::Value);

 private:
  atn::sudoku::Value _value;
};

typedef std::shared_ptr<atn::sudoku::Cell> CellPtr;

}  // namespace atn::sudoku