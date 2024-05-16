#pragma once

#include <vector>

#include "command.h"

namespace atn::generator::removal {

class MacroCommand : public atn::generator::removal::Command {
 public:
  MacroCommand(std::vector<atn::generator::removal::CommandPtr>);

  void apply();
  void undo();

 private:
  std::vector<atn::generator::removal::CommandPtr> _commands;
};

}  // namespace atn::generator::removal
