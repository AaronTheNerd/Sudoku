#include "next_move.h"

atn::NextMove::NextMove(TechniqueEnum technique, CommandPtr command)
    : _technique(technique), _command(command) {}

atn::TechniqueEnum atn::NextMove::get_technique() const {
  return this->_technique;
}

atn::CommandPtr atn::NextMove::get_command() const { return this->_command; }