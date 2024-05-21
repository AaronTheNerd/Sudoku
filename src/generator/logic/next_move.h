#pragma once

#include "command.h"
#include "technique_enum.hpp"

namespace atn::generator::logic {

using namespace atn::generator::logic;
using namespace atn::generator::command;

class NextMove {
 public:
  NextMove(TechniqueEnum, CommandPtr);

  TechniqueEnum get_technique() const;
  CommandPtr get_command() const;

 private:
  TechniqueEnum _technique;
  CommandPtr _command;
};

}  // namespace atn::generator::logic
