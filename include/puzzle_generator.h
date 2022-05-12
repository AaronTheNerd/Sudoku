// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_PUZZLE_GENERATOR_H_
#define _INCLUDE_PUZZLE_GENERATOR_H_

#include <cstddef> // size_t
#include "sudoku.h"

namespace atn {

template<size_t T>
class SudokuPuzzleGenerator {
 private:
  DIFFICULTY difficulty;
  Sudoku<T> puzzle;
 public:
  SudokuGenerator(DIFFICULTY, Sudoku<T>);
  Sudoku<T> get_puzzle() const;
};

} // namespace atn

#include "../src/generator.cpp"

#endif // _INCLUDE_PUZZLE_GENERATOR_H_
