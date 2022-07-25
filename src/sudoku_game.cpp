// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_SUDOKU_GAME_CPP_
#define _SRC_SUDOKU_GAME_CPP_

#include "sudoku_game.h"
#include <sstream>  // std::stringstream

template <uint8_t T>
atn::SudokuGame<T>::SudokuGame()
    : difficulty(atn::SOLUTION),
      seed(std::chrono::system_clock::now().time_since_epoch().count()),
      _solution_generator(this->seed),
      solution(this->_solution_generator.get_solution()),
      _puzzle_generator(this->difficulty, this->seed, this->solution),
      puzzle(this->_puzzle_generator.get_puzzle()),
      difficulty_score(this->_puzzle_generator.get_difficulty_score()) {}

template <uint8_t T>
atn::SudokuGame<T>::SudokuGame(atn::DIFFICULTY difficulty)
    : difficulty(difficulty),
      seed(std::chrono::system_clock::now().time_since_epoch().count()),
      _solution_generator(this->seed),
      solution(this->_solution_generator.get_solution()),
      _puzzle_generator(this->difficulty, this->seed, this->solution),
      puzzle(this->_puzzle_generator.get_puzzle()),
      difficulty_score(this->_puzzle_generator.get_difficulty_score()) {}

template <uint8_t T>
atn::SudokuGame<T>::SudokuGame(atn::DIFFICULTY difficulty, uint32_t seed)
    : difficulty(difficulty),
      seed(seed),
      _solution_generator(this->seed),
      solution(this->_solution_generator.get_solution()),
      _puzzle_generator(this->difficulty, this->seed, this->solution),
      puzzle(this->_puzzle_generator.get_puzzle()),
      difficulty_score(this->_puzzle_generator.get_difficulty_score()) {}

template <uint8_t T>
atn::DIFFICULTY atn::SudokuGame<T>::get_difficulty() const {
  return this->difficulty;
}

template <uint8_t T>
uint32_t atn::SudokuGame<T>::get_seed() const {
  return this->seed;
}

template <uint8_t T>
atn::Sudoku<T> atn::SudokuGame<T>::get_solution() const {
  return this->solution;
}

template <uint8_t T>
atn::Sudoku<T> atn::SudokuGame<T>::get_puzzle() const {
  return this->puzzle;
}

template <uint8_t T>
uint16_t atn::SudokuGame<T>::get_difficulty_score() const {
  return this->difficulty_score;
}

#endif  // _SRC_SUDOKU_GAME_CPP_
