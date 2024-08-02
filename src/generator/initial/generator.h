#pragma once

#include <memory>

#include "board.h"

namespace atn {

class InitialGenerator {
 public:
  virtual BoardPtr generate() = 0;
};

typedef std::shared_ptr<InitialGenerator> InitialGeneratorPtr;

}  // namespace atn
