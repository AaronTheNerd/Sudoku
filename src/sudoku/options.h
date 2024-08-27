#pragma once

#include <bitset>

#include "value.h"

namespace atn {

class Options {
 public:
  Options(std::bitset<9> = 0b111111111);

  bool includes(Value) const;
  void set(Value);
  void clear(Value);
  void clear_all();
  uint count() const;
  std::bitset<9> bitset() const;

 private:
  std::bitset<9> _bitset;
};

}  // namespace atn
