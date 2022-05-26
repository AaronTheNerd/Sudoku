// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SOLVER_H_
#define _INCLUDE_SOLVER_H_

#include <cstddef>  // uint8_t
#include <vector>   // std::vector
#include "sudoku.h"

namespace atn {

template <uint8_t T>
struct FillResult {
  bool valid;
  std::vector<Cell<T>> filled;
};

template <uint8_t T>
struct SolverState {
  bool valid = false;
  Cell<T> placed;
  std::vector<Cell<T>> known;
  SolverState();
};

template <uint8_t T>
FillResult<T> fill_known(atn::Sudoku<T>&, std::vector<atn::Cell<T>>&);

template <uint8_t T>
bool solve(atn::Sudoku<T>&);

}  // namespace atn

#include "../src/solver.cpp"

#endif  // _INCLUDE_SOLVER_H_
