// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SOLUTION_GENERATOR_H_
#define _INCLUDE_SOLUTION_GENERATOR_H_

#include <cstddef> // uint8_t
#include <random> // std::default_random_engine, std::uniform_int_distribution
#include <vector> // std::vector
#include "sudoku.h"

namespace atn {

template<uint8_t T>
struct GeneratorResults {
  bool failed;
  Sudoku<T> result;
};

template<uint8_t T>
class SudokuSolutionGenerator {
 private:
  unsigned seed;
  std::default_random_engine rng;
  Sudoku<T> solution;
  void init();
  GeneratorResults<T> fill(Sudoku<T>&);
 public:
  SudokuSolutionGenerator();
  SudokuSolutionGenerator(unsigned);
  unsigned get_seed() const;
  Sudoku<T> get_solution() const;
};

} // namespace atn

#include "../src/solution_generator.cpp"

#endif // _INCLUDE_SOLUTION_GENERATOR_H_
