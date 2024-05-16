#pragma once

#include <vector>

#include "cell.h"
#include "command.h"
#include "value.h"

namespace atn::generator::command {

class ClearOptions : public atn::generator::command::Command {
 public:
  ClearOptions(atn::sudoku::CellPtr, std::vector<atn::sudoku::Value>);

  void apply();
  void undo();

 private:
  atn::sudoku::CellPtr _cell;
  std::vector<atn::sudoku::Value> _options;
};

}  // namespace atn::generator::command
