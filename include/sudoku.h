// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SUDOKU_H_
#define _INCLUDE_SUDOKU_H_

#include <array> // std::array
#include <bitset> // std::bitset
#include <cstddef> // size_t
#include <string> // std::string
#include <vector> // std::vector

namespace atn {

static const uint8_t UNSET = 0;

struct Pos {
  size_t x = 0;
  size_t y = 0;
};

template<size_t T>
struct Cell {
  uint8_t value;
  Pos pos;
  std::bitset<T * T> options;
  Cell();
  Cell(Pos);
  bool invalid() const;
  static bool compare_options(const Cell<T>&, const Cell<T>&);
};

enum DIFFICULTY {
  EASY, MEDIUM, HARD
};

template<size_t T>
class Sudoku {
 private:
  size_t cell_width;
  std::array<std::array<Cell<T>, T * T>, T * T> board;
  void initialize_cell_width();
  void initialize_blank_board();
  bool propogate_block(Pos, uint8_t);
  bool propogate(Pos, uint8_t);
  bool validate_row() const;
  bool validate_column() const;
  bool validate_block() const;
 public:
  Sudoku();
  Cell<T> get_cell(Pos) const;
  bool set_cell(Pos, uint8_t);
  std::vector<Cell<T>> get_empty_cells();
  bool validate() const;
  std::string to_str() const;
};

} // namespace atn

#include "../src/sudoku.cpp"

#endif // _INCLUDE_SUDOKU_H_
