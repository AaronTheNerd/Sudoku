#pragma once

#include <vector>

#include "command.h"

namespace atn::generator::command {

class MacroCommand : public atn::generator::command::Command {
 public:
  MacroCommand(std::vector<atn::generator::command::CommandPtr>);

  void apply();
  void undo();

 private:
  std::vector<atn::generator::command::CommandPtr> _commands;
};

}  // namespace atn::generator::command
