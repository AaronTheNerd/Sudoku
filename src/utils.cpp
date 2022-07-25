// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_UTILS_CPP_
#define _SRC_UTILS_CPP_

#include "utils.h"

namespace {}  // namespace

atn::BOARD_SPACE atn::utils::on_same_line(
    const std::vector<atn::Pos>& positions) {
  if (positions.size() == 0) {
    return atn::INVALID_SPACE;
  }
  // Initialize variables
  uint8_t const_coord;
  atn::BOARD_SPACE space;
  // Check for linearity on a column
  const_coord = positions[0].x;
  space       = atn::COLUMN;
  for (uint8_t i = 1; i < positions.size(); ++i) {
    if (positions[i].x != const_coord) {
      space = atn::INVALID_SPACE;
      break;
    }
  }
  if (space != atn::INVALID_SPACE) return space;
  // Check for linearity on a row
  const_coord = positions[0].y;
  space       = atn::ROW;
  for (uint8_t i = 1; i < positions.size(); ++i) {
    if (positions[i].y != const_coord) {
      space = atn::INVALID_SPACE;
      break;
    }
  }
  return space;
}

#endif  // _SRC_UTILS_CPP_