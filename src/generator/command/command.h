#pragma once

#include <memory>

namespace atn::generator::command {

class Command {
 public:
  virtual void apply() = 0;
  virtual void undo() = 0;
};

typedef std::shared_ptr<Command> CommandPtr;

}  // namespace atn::generator::command