// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_PUZZLE_GENERATOR_CPP_
#define _SRC_PUZZLE_GENERATOR_CPP_

#include "puzzle_generator.h"
#include <functional>  // std::bind
#include "logical_solver.h"
#include "solver.h"

template <uint8_t T>
void atn::SudokuPuzzleGenerator<T>::init() {
  if (this->difficulty == SOLUTION) return;
  uint8_t attempts = 2;
  std::uniform_int_distribution<uint8_t> distribution(0, T * T - 1);
  auto random_coord = std::bind(distribution, this->rng);
  atn::Pos curr_pos;
  atn::Sudoku<T> solve_board;
  while (attempts != 0 && this->difficulty_score < this->difficulty) {
    // Get random cell which is not set
    uint8_t x, y;
    uint8_t value;
    do {
      x        = random_coord();
      y        = random_coord();
      curr_pos = {x, y};
      value    = this->puzzle.get(curr_pos).value;
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
          solve_board.unset(curr_pos);
          continue;
        }
        valid = atn::solve(solve_board);
        if (valid) {
          safe_to_remove = false;
          attempts -= 1;
          break;
        }
      }
    }
    if (safe_to_remove) {
      this->puzzle.unset(curr_pos);
      solve_board = this->puzzle;
      atn::LogicalSolverResults<T> results = atn::logical_solve(solve_board);
      if (!results.valid) { // Could not solve the puzzle logically
        this->puzzle.set(curr_pos, value);
        attempts -= 1;
      } else {
        this->difficulty_score = results.difficulty_score;
      }
    }
  }
}

template <uint8_t T>
atn::SudokuPuzzleGenerator<T>::SudokuPuzzleGenerator(
    atn::DIFFICULTY difficulty, unsigned seed, atn::Sudoku<T> solution)
    : difficulty(difficulty),
      seed(seed),
      rng(this->seed),
      puzzle(solution),
      difficulty_score(0) {
  this->init();
}

template <uint8_t T>
atn::Sudoku<T> atn::SudokuPuzzleGenerator<T>::get_puzzle() const {
  return this->puzzle;
}

template <uint8_t T>
uint16_t atn::SudokuPuzzleGenerator<T>::get_difficulty_score() const {
  return this->difficulty_score;
}

#endif  // _SRC_PUZZLE_GENERATOR_CPP_
