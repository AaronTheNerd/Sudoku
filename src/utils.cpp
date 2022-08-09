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

bool atn::utils::in_same_block(const std::vector<atn::Pos>& positions, uint8_t T) {
  uint8_t block_x, block_y;
  if (positions.size() == 0) return false;
  block_x = positions[0].x / T;
  block_y = positions[0].y / T;
  for (uint8_t i = 1; i < positions.size(); ++i) {
    if (block_x != positions[i].x / T || block_y != positions[i].y / T)
      return false;
  }
  return true;
}

#endif  // _SRC_UTILS_CPP_