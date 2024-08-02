#pragma once

#include "cell.h"
#include "command.h"
#include "value.h"

namespace atn {

class SetValue : public Command {
 public:
  SetValue(CellPtr, Value);

  void apply();
  void undo();

 private:
  CellPtr _cell;
  Value _value;
};

}  // namespace atn
