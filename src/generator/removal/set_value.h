#pragma once

#include "cell.h"
#include "command.h"
#include "value.h"

namespace atn::generator::removal {

class SetValue : public atn::generator::removal::Command {
 public:
  SetValue(atn::sudoku::CellPtr, atn::sudoku::Value);

  void apply();
  void undo();

 private:
  atn::sudoku::CellPtr _cell;
  atn::sudoku::Value _value;
};

}  // namespace atn::generator::removal
