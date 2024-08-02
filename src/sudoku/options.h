#pragma once

#include "value.h"

namespace atn {

class Options {
 public:
  Options(uint16_t = 0b0000001111111110);

  bool includes(Value) const;
  void set(Value);
  void clear(Value);
  void clear_all();
  uint count() const;

 private:
  uint16_t _bitset;
};

}  // namespace atn
