#include "macro_command.h"

atn::generator::command::MacroCommand::MacroCommand(
    std::vector<atn::generator::command::CommandPtr> commands)
    : _commands(commands) {}

void atn::generator::command::MacroCommand::apply() {
  for (auto it = this->_commands.begin(); it != this->_commands.end(); ++it) {
    atn::generator::command::CommandPtr command = *it;
    command->apply();
  }
}

void atn::generator::command::MacroCommand::undo() {
  for (auto it = this->_commands.rbegin(); it != this->_commands.rend(); ++it) {
    atn::generator::command::CommandPtr command = *it;
    command->undo();
  }
}

void atn::generator::command::MacroCommand::push(CommandPtr command) {
  this->_commands.push_back(command);
}
