#include "test_utils.h"

#include <gtest/gtest.h>

#include <algorithm>

atn::BoardPtr atn::generate_board(
    std::vector<std::vector<uint8_t>> input) {
  atn::BoardPtr board = atn::Board::create();
  for (uint8_t y{0}; y < 9; ++y) {
    for (uint8_t x{0}; x < 9; ++x) {
      atn::Position pos{x, y};
      atn::Value value{input[y][x]};
      board->get(pos)->set(value);
    }
  }
  return board;
}

bool atn::cell_group_eq(atn::CellGroup group,
                                    std::vector<uint8_t> test) {
  if (group.size() != test.size()) return false;
  for (uint index{0}; index < group.size(); ++index) {
    if (group[index]->get() != atn::Value{test[index]}) return false;
  }
  return true;
}

bool atn::cell_has_options_set(
    atn::CellPtr cell, std::vector<atn::Value> options) {
  std::vector<atn::Value> all_values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
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

atn::BoardPtr atn::generate_board_with_options(
    std::vector<std::vector<atn::BoardNode>> input) {
  atn::BoardPtr board = atn::Board::create();
  for (uint8_t y = 0; y < 9; ++y) {
    for (uint8_t x = 0; x < 9; ++x) {
      atn::Position pos{x, y};
      atn::BoardNode node = input[y][x];
      atn::Value value = node.value;
      atn::CellPtr cell = board->get(pos);
      if (value.value() != 0u) {
        cell->set(value);
      }
      std::vector<atn::Value> options = node.options;
      cell->clear_all_options();
      for (auto option : options) {
        cell->set_option(option);
      }
    }
  }
  return board;
}

void atn::expect_board_state(
    atn::BoardPtr board,
    std::vector<atn::BoardState> states) {
  for (auto state : states) {
    auto cell = board->get(state.pos);
    if (state.node.value == 0u) {
      EXPECT_FALSE(cell->is_set());
    } else {
      EXPECT_EQ(cell->get(), state.node.value);
    }
    EXPECT_TRUE(cell_has_options_set(cell, state.node.options));
  }
}
