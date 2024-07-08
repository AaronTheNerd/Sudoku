#pragma once

#include <sys/types.h>

#include <vector>

#include "board.h"
#include "cell_group.h"
#include "value.h"

namespace atn::test_utils {

atn::sudoku::BoardPtr generate_board(std::vector<std::vector<uint8_t>> input);

bool cell_group_eq(atn::sudoku::CellGroup group, std::vector<uint8_t> test);

bool cell_has_options_set(atn::sudoku::CellPtr,
                          std::vector<atn::sudoku::Value>);

struct BoardNode {
  atn::sudoku::Value value;
  std::vector<atn::sudoku::Value> options;
};

atn::sudoku::BoardPtr generate_board_with_options(
    std::vector<std::vector<BoardNode>> input);

struct BoardState {
  atn::sudoku::Position pos;
  BoardNode node;
};

void expect_board_state(atn::sudoku::BoardPtr, std::vector<BoardState>);

}  // namespace atn::test_utils
