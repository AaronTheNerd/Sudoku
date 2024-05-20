#pragma once

#include <memory>

#include "options.h"
#include "value.h"
#include "position.h"

namespace atn::sudoku {

class Cell {
 public:
  Cell(atn::sudoku::Position = {0, 0});
  Cell(atn::sudoku::Position, atn::sudoku::Value);

  atn::sudoku::Position position() const;
  bool is_set() const;
  void set(atn::sudoku::Value);
  atn::sudoku::Value unset();
  atn::sudoku::Value get() const;
  bool has_option(atn::sudoku::Value) const;
  void set_option(atn::sudoku::Value);
  void clear_option(atn::sudoku::Value);
  void clear_all_options();

 private:
  atn::sudoku::Position _position;
  atn::sudoku::Value _value;
  atn::sudoku::Options _options;
};

typedef std::shared_ptr<atn::sudoku::Cell> CellPtr;

}  // namespace atn::sudoku