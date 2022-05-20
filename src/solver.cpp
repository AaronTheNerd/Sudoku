// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_SOLVER_CPP_
#define _SRC_SOLVER_CPP_

#include <algorithm> // std::sort
#include <iostream> // std::cout, std::endl
#include <sstream> // std::stringstream
#include <string.h> // std::string
#include "solver.h"

namespace {

template<uint8_t T>
std::string to_string(atn::Cell<T> cell) {
  std::stringstream ss;
  ss << "{ (";
  ss << int(cell.pos.x);
  ss << ", ";
  ss << int(cell.pos.y);
  ss << "): ";
  ss << int(cell.value);
  ss << " }";
  return ss.str();
}

template<uint8_t T>
std::string to_string(atn::SolverState<T> state) {
  std::stringstream ss;
  ss << to_string(state.placed);
  return ss.str();
}

template<uint8_t T>
void print_stack(std::vector<atn::SolverState<T>> stack, bool backtrack) {
  std::cout << "backtrack=" << backtrack << ", [";
  for (auto it = stack.begin(); it != stack.end(); ++it) {
    std::cout << to_string(*it) << ", ";
  }
  std::cout << "]" << std::endl;
}

template<uint8_t T>
atn::SolverState<T> solve_helper(
    atn::Sudoku<T>& puzzle,
    std::vector<atn::Cell<T>>& empty_cells) {

  // Instantiate variables
  atn::Cell<T> curr_cell;
  atn::SolverState<T> result;
  empty_cells = puzzle.get_empty_cells();
  std::sort(
      empty_cells.begin(),
      empty_cells.end(),
      atn::Cell<T>::compare_options);
  
  // If there are no empty cells then there is nothing to do
  if (empty_cells.size() == 0) {
    result.valid = puzzle.validate();
    return result;
  }

  // Fill all known cells
  if (empty_cells[0].options.count() == 1) {
    atn::FillResult<T> fill_result = atn::fill_known(puzzle, empty_cells);
    if (fill_result.valid) {
      result.known = fill_result.filled;
    } else {
      result.valid = false;
      return result;
    }
  }

  // If there are no empty cells then there is nothing to do
  if (empty_cells.size() == 0) {
    result.valid = puzzle.validate();
    return result;
  }

  // Find first valid option
  for (uint8_t i = 1; i <= T * T; ++i) {
    curr_cell = empty_cells[0];
    if (curr_cell.options[i - 1]) {
      bool valid = puzzle.set(curr_cell.pos, i);
      if (valid && puzzle.validate()) {
        result.placed = puzzle.get(curr_cell.pos);
        result.valid = true;
        return result;
      }
      puzzle.set(curr_cell.pos, atn::UNSET);
    }
  }

  // No valid options were found
  result.valid = false;
  return result;
}

template<uint8_t T>
void iterate_state(atn::Sudoku<T>& puzzle, atn::SolverState<T>& state) {
  uint8_t start_value;
  atn::Pos pos;
  bool valid;

  if (state.placed.value == atn::UNSET) {
    state.valid = false;
    return;
  }

  start_value = state.placed.value;
  pos = state.placed.pos;

  // Unset placed value in board
  puzzle.set(pos, atn::UNSET);

  // Find new value
  for (uint8_t i = start_value + 1; i <= T * T; ++i) {
    if (puzzle.at(pos).options[i - 1]) {
      valid = puzzle.set(pos, i);
      if (valid && puzzle.validate()) {
        state.valid = true;
        state.placed.value = i;
        return;
      }
      puzzle.set(pos, atn::UNSET);
    }
  }
  state.valid = false;
}

} // namespace anonymous

template<uint8_t T>
atn::SolverState<T>::SolverState(): valid(false), placed(), known() {}

template<uint8_t T>
atn::FillResult<T> atn::fill_known(
    atn::Sudoku<T>& board,
    std::vector<atn::Cell<T>>& empty_cells) {
  atn::Pos curr_pos;
  std::vector<atn::Cell<T>> result;
  while (empty_cells.size() != 0
      && empty_cells[0].options.count() == 1
      && board.validate()) {
    for (uint8_t i = 0; i < T * T; ++i) {
      if (empty_cells[0].options[i]) {
        curr_pos = empty_cells[0].pos;
        bool valid = board.set(empty_cells[0].pos, i + 1);
        if (valid) {
          result.emplace_back(board.get(curr_pos));
          break;
        } else {
          result.clear();
          return { false, result };
        }
      }
    }
    empty_cells = board.get_empty_cells();
    std::sort(
        empty_cells.begin(),
        empty_cells.end(),
        atn::Cell<T>::compare_options);
  }
  return { true, result };
}

template<uint8_t T>
bool atn::solve(atn::Sudoku<T>& puzzle) {

  // Instantiate variables
  std::vector<atn::Cell<T>> empty_cells;
  SolverState<T> curr_state = solve_helper(puzzle, empty_cells);
  //while (!(curr_state.valid && puzzle.validate())) iterate_state(puzzle, curr_state);
  std::vector<SolverState<T>> stack;
  stack.emplace_back(curr_state);
  bool backtrack = !(curr_state.valid && puzzle.validate());

  // Main loop
  while (empty_cells.size() > 0 && stack.size() > 0) {
    print_stack(stack, backtrack);
    //std::cout << puzzle.to_str() << "\n" << std::endl;

    if (backtrack) {
      // Pop previous state
      curr_state = stack.back();
      stack.pop_back();

      // Attempt to replace value
      iterate_state(puzzle, curr_state);
      if (!curr_state.valid) {
        for (uint8_t i = 0; i < curr_state.known.size(); ++i)
          puzzle.unset(curr_state.known[i].pos);
        puzzle.fix_options();
        continue;
      }
    } else {
      curr_state = solve_helper(puzzle, empty_cells);
      curr_state.valid &= puzzle.validate();
    }
    if (curr_state.valid) {
      backtrack = false;
      stack.emplace_back(curr_state);
    } else {
      backtrack = true;
    }
  }
  return empty_cells.size() == 0 && puzzle.validate();
}

#endif // _SRC_SOLVER_CPP_