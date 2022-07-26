// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SUDOKU_H_
#define _INCLUDE_SUDOKU_H_

#include <array>          // std::array
#include <bitset>         // std::bitset
#include <cstddef>        // uint8_t
#include <string>         // std::string
#include <unordered_map>  // std::unordered_map
#include <vector>         // std::vector

namespace atn {

enum BOARD_SPACE : uint8_t { ROW, COLUMN, BLOCK, INVALID_SPACE };

static const uint8_t UNSET = 0;

struct Pos {
  uint8_t x = 0;
  uint8_t y = 0;
  bool operator==(const Pos& rhs) const {
    return this->x == rhs.x && this->y == rhs.y;
  }
  std::string to_str() const {
    return "(" + std::to_string(int(x)) + ", " + std::to_string(int(y)) + ")";
  }
};

template <uint8_t T>
struct Cell {
  Pos pos;
  uint8_t value;
  std::bitset<T * T> options;
  Cell();
  Cell(Pos);
  Cell(Pos, uint8_t);
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
  Sudoku(std::array<std::array<uint8_t, T * T>, T * T>);
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
