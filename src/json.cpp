// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_JSON_CPP_
#define _SRC_JSON_CPP_

#define TAB_WIDTH 2

#include "json.h"
#include <sstream>  // std::stringstream

namespace {

template <uint8_t T>
std::string board_to_json(
    const atn::Sudoku<T>& board, std::string name, uint8_t indentation) {
  std::stringstream ss;
  ss << std::string(TAB_WIDTH * indentation, ' ') << "\"" << name << "\": [";
  for (uint8_t y = 0; y < T * T; ++y) {
    if (y != 0) ss << ",";
    ss << "\n" << std::string(TAB_WIDTH * (indentation + 1), ' ') << "[";
    for (uint8_t x = 0; x < T * T; ++x) {
      if (x != 0) ss << ", ";
      ss << std::to_string(board.get({x, y}).value);
    }
    ss << "]";
  }
  ss << "\n" << std::string(TAB_WIDTH * indentation, ' ') << "]";
  return ss.str();
}

std::string difficulty_to_string(const atn::DIFFICULTY difficulty) {
  switch (difficulty) {
    case atn::SOLUTION:
      return "Solution";
    case atn::VERY_EASY:
      return "Very Easy";
    case atn::EASY:
      return "Easy";
    case atn::MEDIUM:
      return "Medium";
    case atn::HARD:
      return "Hard";
    case atn::KILLER:
      return "Killer";
    case atn::EVIL:
      return "EVIL";
  }
  return "INVALID";
}

}  // namespace

template <uint8_t T>
std::string atn::json::to_json(uint32_t seed, atn::DIFFICULTY difficulty,
    const atn::Sudoku<T>& solution, const atn::Sudoku<T>& puzzle) {
  std::stringstream ss;
  ss << "{";
  ss << "\n" << std::string(TAB_WIDTH, ' ') << "\"seed\": " << seed << ",";
  ss << "\n"
     << std::string(TAB_WIDTH, ' ') << "\"difficulty\": \""
     << difficulty_to_string(difficulty) << "\",";
  ss << "\n" << board_to_json(solution, "solution", 1) << ",";
  ss << "\n" << board_to_json(puzzle, "puzzle", 1);
  ss << "\n}";
  return ss.str();
}

template <uint8_t T>
atn::Sudoku<T> atn::json::from_json(const std::string json) {}

#endif  // _SRC_JSON_CPP_