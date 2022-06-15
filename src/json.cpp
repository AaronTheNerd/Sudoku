// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_JSON_CPP_
#define _SRC_JSON_CPP_

#define TAB_WIDTH 2

#include "json.h"
#include <stdexcept>      // std::invalid_argument
#include <sstream>        // std::stringstream

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
  return atn::difficulty_to_string_map.at(difficulty);
}

atn::DIFFICULTY string_to_difficulty(const std::string difficulty_string) {
  for (auto it = atn::difficulty_to_string_map.begin();
       it != atn::difficulty_to_string_map.end(); ++it) {
    if (it->second == difficulty_string) return it->first;
  }
  throw std::invalid_argument("Unrecognized difficulty: \"" + difficulty_string + "\"");
}

}  // namespace

template <uint8_t T>
std::string atn::json::to_json(const atn::SudokuGame<T>& game) {
  std::stringstream ss;
  ss << "{";
  ss << "\n" << std::string(TAB_WIDTH, ' ') << "\"seed\": " << game.get_seed() << ",";
  ss << "\n"
     << std::string(TAB_WIDTH, ' ') << "\"difficulty\": \""
     << difficulty_to_string(game.get_difficulty()) << "\",";
  ss << "\n" << std::string(TAB_WIDTH, ' ') << "\"difficulty_score\": " << game.get_difficulty_score() << ",";
  ss << "\n" << board_to_json(game.get_solution(), "solution", 1) << ",";
  ss << "\n" << board_to_json(game.get_puzzle(), "puzzle", 1);
  ss << "\n}";
  return ss.str();
}

template <uint8_t T>
atn::Sudoku<T> atn::json::from_json(const std::string json) {}

#endif  // _SRC_JSON_CPP_