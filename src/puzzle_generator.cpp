// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_PUZZLE_GENERATOR_CPP_
#define _SRC_PUZZLE_GENERATOR_CPP_

#include "puzzle_generator.h"
#include <functional>  // std::bind
#include "solver.h"

template <uint8_t T>
void atn::SudokuPuzzleGenerator<T>::init() {
  uint8_t attempts = this->difficulty;
  std::uniform_int_distribution<uint8_t> distribution(0, T * T - 1);
  auto random_coord = std::bind(distribution, this->rng);
  atn::Pos curr_pos;
  atn::Sudoku<T> backup_board, solve_board;
  while (attempts != 0) {
    // Get random cell which is not set
    uint8_t x, y;
    uint8_t value;
    do {
      x = random_coord();
      y = random_coord();
      curr_pos = {x, y};
      value = this->puzzle.get(curr_pos).value;
    } while (value == atn::UNSET);

    // Prepare backups
    solve_board = this->puzzle;
    // Unset cell
    solve_board.set(curr_pos, atn::UNSET);

    // Check that the puzzle does not have multiple soltutions
    bool safe_to_remove = true;
    for (uint8_t i = 1; i <= T * T; ++i) {
      if (i != value && solve_board.get(curr_pos).options[i - 1]) {
        bool valid = solve_board.set(curr_pos, i);
        if (!valid) {
          solve_board.set(curr_pos, atn::UNSET);
          continue;
        }
        bool solved = atn::solve(solve_board);
        if (solved) {
          this->puzzle.set(curr_pos, value);
          safe_to_remove = false;
          attempts -= 1;
          break;
        }
      }
    }
    if (safe_to_remove) this->puzzle.set(curr_pos, atn::UNSET);
  }
}

template <uint8_t T>
atn::SudokuPuzzleGenerator<T>::SudokuPuzzleGenerator(atn::DIFFICULTY difficulty,
                                                     unsigned seed,
                                                     atn::Sudoku<T> solution)
    : difficulty(difficulty), seed(seed), rng(this->seed), puzzle(solution) {
  this->init();
}

template <uint8_t T>
atn::Sudoku<T> atn::SudokuPuzzleGenerator<T>::get_puzzle() const {
  return this->puzzle;
}

#endif  // _SRC_PUZZLE_GENERATOR_CPP_
