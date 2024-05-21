#pragma once

#include "next_move.h"
#include <optional>

namespace atn::generator::logic {

class Technique {
 public:
  virtual std::optional<atn::generator::logic::NextMove> get_next_move() = 0;
};

}  // namespace atn::generator::logic
