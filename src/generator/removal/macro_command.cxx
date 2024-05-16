#include "macro_command.h"

atn::generator::removal::MacroCommand::MacroCommand(
    std::vector<atn::generator::removal::CommandPtr> commands)
    : _commands(commands) {}

void atn::generator::removal::MacroCommand::apply() {
  for (auto it = this->_commands.begin(); it != this->_commands.end(); ++it) {
    atn::generator::removal::CommandPtr command = *it;
    command->apply();
  }
}

void atn::generator::removal::MacroCommand::undo() {
  for (auto it = this->_commands.rbegin(); it != this->_commands.rend(); ++it) {
    atn::generator::removal::CommandPtr command = *it;
    command->undo();
  }
}
