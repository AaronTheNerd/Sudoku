#pragma once

#include <vector>

#include "command.h"
#include "cell.h"
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
