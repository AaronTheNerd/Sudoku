// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SUDOKU_H_
#define _INCLUDE_SUDOKU_H_

#include <array>    // std::array
#include <bitset>   // std::bitset
#include <cstddef>  // uint8_t
#include <string>   // std::string
#include <vector>   // std::vector

namespace atn {

enum DIFFICULTY {
  SOLUTION  = 0,
  VERY_EASY = 4000,
  EASY      = 4900,
  MEDIUM    = 6000,
  HARD      = 7600,
  KILLER    = 10000,
  EVIL      = 18000
};

static const uint8_t UNSET = 0;

struct Pos {
  uint8_t x = 0;
  uint8_t y = 0;
};

template <uint8_t T>
struct Cell {
  uint8_t value;
  Pos pos;
  std::bitset<T * T> options;
  Cell();
  Cell(Pos);
  bool invalid() const;
  static bool compare_options(const Cell<T>&, const Cell<T>&);
};

template <uint8_t T>
class Sudoku {
 private:
  uint8_t cell_width;
  std::array<std::array<Cell<T>, T * T>, T * T> board;
  void initialize_cell_width();
  void initialize_blank_board();
  bool propogate_block(Pos, uint8_t);
  bool propogate(Pos, uint8_t);
  bool validate_row() const;
  bool validate_column() const;
  bool validate_block() const;
  void fix_options(Pos);
  std::bitset<T * T> contains_row_column(Pos);
  std::bitset<T * T> contains_block(uint8_t, uint8_t);

 public:
  Sudoku();
  Cell<T>& at(Pos);
  Cell<T> get(Pos) const;
  bool set(Pos, uint8_t);
  void unset(Pos);
  void unset(std::vector<Cell<T>>);
  void fix_options();
  std::vector<Cell<T>> get_empty_cells();
  bool validate() const;
  std::string to_str() const;
};

}  // namespace atn

#include "../src/sudoku.cpp"

#endif  // _INCLUDE_SUDOKU_H_
