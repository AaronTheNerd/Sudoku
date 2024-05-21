
#include "test_utils.h"

#include <algorithm>

atn::sudoku::Board atn::test_utils::generate_board(
    std::vector<std::vector<uint8_t>> input) {
  atn::sudoku::Board board{};
  for (uint y = 0; y < 9; ++y) {
    for (uint x = 0; x < 9; ++x) {
      atn::sudoku::Position pos{x, y};
      atn::sudoku::Value value{input[y][x]};
      board.get(pos)->set(value);
    }
  }
  return board;
}

bool atn::test_utils::cell_group_eq(atn::sudoku::CellGroup group,
                                    std::vector<uint8_t> test) {
  if (group.size() != test.size()) return false;
  for (uint index{0}; index < group.size(); ++index) {
    if (group[index]->get() != atn::sudoku::Value{test[index]}) return false;
  }
  return true;
}

bool atn::test_utils::cell_has_options_set(
    atn::sudoku::CellPtr cell, std::vector<atn::sudoku::Value> options) {
  std::vector<atn::sudoku::Value> all_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto it = all_values.begin(); it != all_values.end(); ++it) {
    bool should_be_in_options =
        std::find(options.begin(), options.end(), *it) != options.end();
    bool in_options = cell->has_option(*it);
    if (in_options != should_be_in_options) {
      return false;
    }
  }
  return true;
}

atn::sudoku::Board atn::test_utils::generate_board_with_options(std::vector<std::vector<atn::test_utils::BoardNode>> input) {
  atn::sudoku::Board board;
  for (uint y = 0; y < 9; ++y) {
    for (uint x = 0; x < 9; ++x) {
      atn::sudoku::Position pos{x, y};
      atn::test_utils::BoardNode node = input[y][x];
      atn::sudoku::Value value = node.value;
      atn::sudoku::CellPtr cell = board.get(pos);
      if (value.value() != 0u) {
        cell->set(value);
      }
      std::vector<atn::sudoku::Value> options = node.options;
      cell->clear_all_options();
      for (auto option : options) {
        cell->set_option(option);
      }
    }
  }
  return board;
}
