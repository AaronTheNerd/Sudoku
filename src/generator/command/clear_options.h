#pragma once

#include <vector>

#include "cell.h"
#include "command.h"
#include "value.h"

namespace atn {

class ClearOptions : public Command {
 public:
  ClearOptions(CellPtr, std::vector<Value>);

  void apply();
  void undo();

 private:
  CellPtr _cell;
  std::vector<Value> _options;
};

}  // namespace atn
