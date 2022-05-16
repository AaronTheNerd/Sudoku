// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_PUZZLE_GENERATOR_CPP_
#define _SRC_PUZZLE_GENERATOR_CPP_

#include <functional> // std::bind
#include "puzzle_generator.h"

template<uint8_t T>
void atn::SudokuPuzzleGenerator<T>::init() {
  uint8_t attempts = this->difficulty;
  std::uniform_int_distribution<uint8_t> distribution(0, T * T - 1);
  auto random_pos = std::bind(distribution, this->rng);
  atn::Sudoku<T> backup_board, solve_board;
  while (attempts > 0) {

    // Get random cell which is not set
    uint8_t x, y;
    uint8_t val;
    do {
      x = random_pos();
      y = random_pos();
      val = this->puzzle.get({x, y}).value;
    } while (val == atn::UNSET);

    // Prepare backups
    backup_board = solve_board = this->puzzle;

    // Unset cell
    this->puzzle.set({x, y}, atn::UNSET);

    // Check that the puzzle does not have multiple soltutions
    for (uint8_t i = 1; i <= T * T; ++i) {
      if (i != val) {
        bool valid = this->puzzle.set({x, y}, i);
        if (!valid) continue;
        // Solve
        bool solved = false;
        if (solved) {
          this->puzzle = backup_board;
        } else {
          this->puzzle.set({x, y}, atn::UNSET);
        }
      }
    }
    attempts += 1;
  }
}

template<uint8_t T>
atn::SudokuPuzzleGenerator<T>::SudokuPuzzleGenerator(
    atn::DIFFICULTY difficulty, unsigned seed, atn::Sudoku<T> solution):
  difficulty(difficulty), seed(seed), rng(this->seed), puzzle(solution) {
  this->init();
}

template<uint8_t T>
atn::Sudoku<T> atn::SudokuPuzzleGenerator<T>::get_puzzle() const {
  return this->puzzle;
}

#endif // _SRC_PUZZLE_GENERATOR_CPP_
