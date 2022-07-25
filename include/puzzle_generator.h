// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_PUZZLE_GENERATOR_H_
#define _INCLUDE_PUZZLE_GENERATOR_H_

#include <cstddef>  // uint8_t
#include <random>   // std::default_random_engine
#include "sudoku.h"

namespace atn {

enum DIFFICULTY : uint16_t {
  SOLUTION  = 0,
  VERY_EASY = 4000,
  EASY      = 4900,
  MEDIUM    = 6000,
  HARD      = 7600,
  KILLER    = 10000,
  EVIL      = 18000
};

template <uint8_t T>
class SudokuPuzzleGenerator {
 private:
  DIFFICULTY difficulty;
  unsigned seed;
  std::default_random_engine rng;
  Sudoku<T> puzzle;
  uint16_t difficulty_score;
  void init();

 public:
  SudokuPuzzleGenerator(DIFFICULTY, unsigned, Sudoku<T>);
  atn::Sudoku<T> get_puzzle() const;
  uint16_t get_difficulty_score() const;
};

}  // namespace atn

#include "../src/puzzle_generator.cpp"

#endif  // _INCLUDE_PUZZLE_GENERATOR_H_
