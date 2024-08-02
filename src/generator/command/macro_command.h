#pragma once

#include <vector>

#include "command.h"

namespace atn {

class MacroCommand : public Command {
 public:
  MacroCommand(std::vector<CommandPtr> = {});

  void apply();
  void undo();

  virtual void push(CommandPtr);

 private:
  std::vector<CommandPtr> _commands;
};

}  // namespace atn
