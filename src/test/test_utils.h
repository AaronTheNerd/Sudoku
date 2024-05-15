#pragma once

#include <sys/types.h>

#include <vector>

#include "board.h"
#include "cell_group.h"

namespace atn::test_utils {

atn::sudoku::Board generate_board(std::vector<std::vector<uint8_t>> input);

bool cell_group_eq(atn::sudoku::CellGroup group, std::vector<uint8_t> test);

bool cell_has_options_set(atn::sudoku::CellPtr,
                          std::vector<atn::sudoku::Value>);

}  // namespace atn::test_utils
