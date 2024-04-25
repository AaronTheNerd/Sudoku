#pragma once

#include <memory>

#include "value.h"
#include "options.h"

namespace atn::sudoku {

class Cell {
 public:
  bool is_set() const;
  void set(atn::sudoku::Value);
  atn::sudoku::Value unset();
  atn::sudoku::Value get() const;
  bool has_option(atn::sudoku::Value) const;
  void set_option(atn::sudoku::Value);
  void clear_option(atn::sudoku::Value);

  Cell();
  Cell(atn::sudoku::Value);

 private:
  atn::sudoku::Value _value;
  atn::sudoku::Options _options;
};

typedef std::shared_ptr<atn::sudoku::Cell> CellPtr;

}  // namespace atn::sudoku