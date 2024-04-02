#pragma once

#include <stdint.h>

namespace atn::sudoku {

const uint8_t UNSET_VALUE{0};

class Cell {
 public:
  bool is_set() const;
  void set(uint8_t);
  uint8_t unset();

  uint8_t get() const;

  Cell();
  Cell(uint8_t);
 private:
  uint8_t value;
};

}