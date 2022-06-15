// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SUDOKU_GAME_H_
#define _INCLUDE_SUDOKU_GAME_H_

#include "puzzle_generator.h"
#include "solution_generator.h"
#include "sudoku.h"

namespace atn {

template <uint8_t T>
class SudokuGame {
 private:
  atn::DIFFICULTY difficulty;
  uint32_t seed;
  atn::SudokuSolutionGenerator<T> _solution_generator;
  atn::Sudoku<T> solution;
  atn::SudokuPuzzleGenerator<T> _puzzle_generator;
  atn::Sudoku<T> puzzle;
  uint16_t difficulty_score;

 public:
  SudokuGame();
  SudokuGame(atn::DIFFICULTY);
  SudokuGame(atn::DIFFICULTY, uint32_t);

  atn::DIFFICULTY get_difficulty() const;
  uint32_t get_seed() const;
  atn::Sudoku<T> get_solution() const;
  atn::Sudoku<T> get_puzzle() const;
  uint16_t get_difficulty_score() const;

  std::string to_str() const;
};

}  // namespace atn

#include "../src/sudoku_game.cpp"

#endif  // _INCLUDE_SUDOKU_GAME_H_
