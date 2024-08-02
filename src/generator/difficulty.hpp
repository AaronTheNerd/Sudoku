#pragma once

#include "sys/types.h"

namespace atn {

class DifficultyRange {
 public:
  constexpr uint min() const { return this->_min; }
  constexpr uint max() const { return this->_max; }

  bool in_range(uint value) const {
    return value >= this->min() && value <= this->max();
  }

  constexpr DifficultyRange(uint min, uint max) : _min(min), _max(max) {}

 private:
  uint _min;
  uint _max;
};

namespace difficulty {

constexpr DifficultyRange beginner{3600, 4500};
constexpr DifficultyRange easy{4300, 5500};
constexpr DifficultyRange medium{5300, 6900};
constexpr DifficultyRange tricky{6500, 9300};
constexpr DifficultyRange fiendish{8300, 14000};
constexpr DifficultyRange diabolical{11000, 25000};

}  // namespace difficulty

}  // namespace atn
