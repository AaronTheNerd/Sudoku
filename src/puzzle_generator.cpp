// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_PUZZLE_GENERATOR_CPP_
#define _SRC_PUZZLE_GENERATOR_CPP_

#include "puzzle_generator.h"

template<size_t T>
void atn::SudokuPuzzleGenerator<T>::init() {
  size_t attempts = this->difficulty;
  std::uniform_int_distribution<size_t> distribution(0, T * T - 1);
  auto random_pos = std::bind(distribution, this->rng);
  atn::Sudoku<T> backup_board, solve_board;
  while (attempts > 0) {

    // Get random cell which is not set
    size_t x, y;
    uint8_t val;
    do {
      x = random_pos();
      y = random_pos();
      val = this->puzzle.get_cell({x, y}).value;
    } while (val == atn::UNSET);

    // Prepare backups
    backup_board = solve_board = this->puzzle;

    // Unset cell
    this->puzzle.set_cell({x, y}, atn::UNSET);
    this->puzzle.fix_options();

    // Check that the puzzle does not have multiple soltutions
    for (uint8_t i = 1; i <= T * T; ++i) {
      if (i != val) {
        bool valid = this->puzzle.set_cell({x, y}, i);
        if (!valid) continue;
        // Solve
        bool solved = false;
        if (solved) {
          this->puzzle = backup_board;
        } else {
          this->puzzle.set_cell({x, y}, atn::UNSET);
          this->puzzle.fix_options();
        }
      }
    }

  }
}

template<size_t T>
atn::SudokuPuzzleGenerator<T>::SudokuPuzzleGenerator(
    atn::DIFFICULTY difficulty, unsigned seed, atn::Sudoku<T> solution):
  difficulty(difficulty), seed(seed), rng(this->seed), puzzle(solution) {
  this->init();
}

template<size_t T>
atn::Sudoku<T> atn::SudokuPuzzleGenerator<T>::get_puzzle() const {
  return this->solution;
}

#endif // _SRC_PUZZLE_GENERATOR_CPP_
