// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_UTILS_H_
#define _INCLUDE_UTILS_H_

#include <vector>
#include "sudoku.h"

namespace atn::utils {

atn::BOARD_SPACE on_same_line(const std::vector<atn::Pos>&);

bool in_same_block(const std::vector<atn::Pos>&, uint8_t);

}  // namespace atn::utils

#endif  // _INCLUDE_UTILS_H_
