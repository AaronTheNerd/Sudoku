#pragma once

#include "command.h"
#include "technique_enum.hpp"

namespace atn::generator::logic {

class NextMove {
 public:
  NextMove(TechniqueEnum, atn::generator::command::CommandPtr);

  TechniqueEnum get_technique() const;
  atn::generator::command::CommandPtr get_command() const;

 private:
  TechniqueEnum _technique;
  atn::generator::command::CommandPtr _command;
};

}  // namespace atn::generator::logic
