#pragma once

#include "value.h"

namespace atn::sudoku {

class Options {
 public:
  Options(uint16_t = 0b0000001111111110);

  bool includes(atn::sudoku::Value) const;
  void set(atn::sudoku::Value);
  void clear(atn::sudoku::Value);
  void clear_all();
  uint count();

 private:
  uint16_t _bitset;
};

}  // namespace atn::sudoku
