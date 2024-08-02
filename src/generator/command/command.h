#pragma once

#include <memory>

namespace atn {

class Command;

typedef std::shared_ptr<Command> CommandPtr;

class Command {
 public:
  virtual void apply() = 0;
  virtual void undo() = 0;

  void push(CommandPtr);
};

}  // namespace atn
