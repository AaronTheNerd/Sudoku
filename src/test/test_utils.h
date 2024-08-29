#pragma once

#include <sys/types.h>

#include <vector>

#include "board.h"
#include "cell_group.h"
#include "value.h"

namespace atn {

atn::BoardPtr generate_board(std::vector<std::vector<atn::Value>> input);

bool cell_group_eq(atn::CellGroup group, std::vector<uint8_t> test);

bool cell_has_options_set(atn::CellPtr, std::vector<atn::Value>);

struct BoardNode {
  atn::Value value;
  std::vector<atn::Value> options;
};

atn::BoardPtr generate_board_with_options(
    std::vector<std::vector<BoardNode>> input);

struct BoardState {
  atn::Position pos;
  BoardNode node;
};

void expect_board_state(atn::BoardPtr, std::vector<BoardState>);

atn::BoardPtr generate_board_and_options(std::vector<std::vector<atn::Value>>);

}  // namespace atn
