#pragma once

#include <random>

#include "../initial/generator.h"
#include "cell_group.h"

namespace atn::generator::initial {

class Recursive : public Generator {
 public:
  atn::sudoku::Board generate();

  Recursive();

 private:
  void clear_board();
  bool add_value(uint);
  atn::sudoku::Position get_position(uint) const;
  std::vector<atn::sudoku::Value> get_shuffled_values();
  bool safe_to_add(atn::sudoku::Value, atn::sudoku::Position) const;
  bool cell_group_contains(atn::sudoku::CellGroup, atn::sudoku::Value) const;

  atn::sudoku::Board _board;
  atn::sudoku::CellGroupFactory _factory;
  std::default_random_engine _rng;

 protected:
  const std::vector<atn::sudoku::Value> _values{
      atn::sudoku::Value{1}, atn::sudoku::Value{2}, atn::sudoku::Value{3},
      atn::sudoku::Value{4}, atn::sudoku::Value{5}, atn::sudoku::Value{6},
      atn::sudoku::Value{7}, atn::sudoku::Value{8}, atn::sudoku::Value{9}};
};

}  // namespace atn::generator::initial
