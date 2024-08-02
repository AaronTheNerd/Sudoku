#include "macro_command.h"

atn::MacroCommand::MacroCommand(std::vector<CommandPtr> commands)
    : _commands(commands) {}

void atn::MacroCommand::apply() {
  for (auto it = this->_commands.begin(); it != this->_commands.end(); ++it) {
    CommandPtr command = *it;
    command->apply();
  }
}

void atn::MacroCommand::undo() {
  for (auto it = this->_commands.rbegin(); it != this->_commands.rend(); ++it) {
    CommandPtr command = *it;
    command->undo();
  }
}

void atn::MacroCommand::push(CommandPtr command) {
  this->_commands.push_back(command);
}
