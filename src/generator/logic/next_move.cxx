#include "next_move.h"

using namespace atn::generator::command;
using namespace atn::generator::logic;

atn::generator::logic::NextMove::NextMove(TechniqueEnum technique,
                                          CommandPtr command)
    : _technique(technique), _command(command) {}

TechniqueEnum atn::generator::logic::NextMove::get_technique() const {
  return this->_technique;
}

CommandPtr atn::generator::logic::NextMove::get_command() const {
  return this->_command;
}