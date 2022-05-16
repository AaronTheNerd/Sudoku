// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_SOLUTION_GENERATOR_CPP_
#define _SRC_SOLUTION_GENERATOR_CPP_

#include <algorithm> // std::shuffle, std::sort
#include <iostream> // std::cout, std::endl
#include <chrono> // std::chrono
#include "solution_generator.h"
#include "solver.h"

template<uint8_t T>
void atn::SudokuSolutionGenerator<T>::init() {

  // Generate a list of cell values
  std::array<uint8_t, T * T> possible_values;
  for (uint8_t i = 0; i < T * T; ++i)
    possible_values[i] = i + 1;

  // Place permutations of list on diagonal of Sudoku board
  for (uint8_t i = 0; i < T; ++i) {
    std::shuffle(possible_values.begin(), possible_values.end(), this->rng);
    for (uint8_t j = 0; j < T * T; ++j) {
      this->solution.set(
          {i * T + j / T, i * T + (j % T)},
          possible_values[j]);
    }
  }

  // Fill the rest of the cells
  atn::GeneratorResults<T> result = this->fill(this->solution);

  // Save results of generator if did not fail
  if (result.failed) {
    std::cout << "Sudoku Generation Failed" << std::endl;
    exit(-1);
  }
  this->solution = result.result;
}

template<uint8_t T>
atn::GeneratorResults<T> atn::SudokuSolutionGenerator<T>::fill(
    atn::Sudoku<T> curr_board) {

  // Reject invalid Sudoku boards
  if (!curr_board.validate()) return {true, curr_board};

  // Sort empty cells based on number of options
  std::vector<atn::Cell<T>> empty_cells = curr_board.get_empty_cells();
  std::sort(
      empty_cells.begin(),
      empty_cells.end(),
      atn::Cell<T>::compare_options);

  // Approve Sudoku boards with no empty cells
  if (empty_cells.size() == 0) return {false, curr_board};

  // Place cells which only have one option
  if (empty_cells[0].options.count() == 1) {

    bool failed = atn::fill_known(curr_board, empty_cells);

    // Reject invalid Sudoku boards
    if (failed || !curr_board.validate()) return {true, curr_board};

    // Approve Sudoku boards which have no empty cells
    if (empty_cells.size() == 0) return {false, curr_board};
  }

  // Store original board for backtracking
  atn::Sudoku<T> original_board = curr_board;

  empty_cells = curr_board.get_empty_cells();
  std::sort(
      empty_cells.begin(),
      empty_cells.end(),
      atn::Cell<T>::compare_options);

  // Recursive Step
  for (uint8_t j = 0; j < T * T; ++j) {
    if (empty_cells[0].options[j]) {
      bool valid = curr_board.set(empty_cells[0].pos, j + 1);
      //std::cout << curr_board.to_str() << std::endl;
      if (!valid) {
        curr_board = original_board;
      } else {
        atn::GeneratorResults<T> result = this->fill(curr_board);
        if (!result.failed) return result;
        else curr_board = original_board;
      }
    }
  }
  return {true, original_board};
}

template<uint8_t T>
atn::SudokuSolutionGenerator<T>::SudokuSolutionGenerator(): 
    seed(std::chrono::system_clock::now().time_since_epoch().count()),
    rng(this->seed),
    solution() {
  this->init();
}

template<uint8_t T>
atn::SudokuSolutionGenerator<T>::SudokuSolutionGenerator(unsigned seed):
    seed(seed),
    rng(this->seed),
    solution() {
  this->init();
}

template<uint8_t T>
unsigned atn::SudokuSolutionGenerator<T>::get_seed() const {
  return this->seed;
}

template<uint8_t T>
atn::Sudoku<T> atn::SudokuSolutionGenerator<T>::get_solution() const {
  return this->solution;
}

#endif // _SRC_SOLUTION_GENERATOR_CPP_
