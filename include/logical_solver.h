// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_LOGICAL_SOLVER_H_
#define _INCLUDE_LOGICAL_SOLVER_H_

#include <cstddef>  // uint8_t, uint16_t
#include "logical_techniques.h"
#include "sudoku.h"

namespace atn {

typedef std::unordered_map<LOGICAL_TECHNIQUE, uint8_t> TechniqueCounts;

template <uint8_t T>
struct LogicalSolverResults {
  bool valid;
  uint16_t difficulty_score;
};

template <uint8_t T>
atn::LogicalTechniquePtr<T> get_next_move(atn::Sudoku<T>&);

template <uint8_t T>
LogicalSolverResults<T> logical_solve(atn::Sudoku<T>&);

}  // namespace atn

#include "../src/logical_solver.cpp"

#endif  // _INCLUDE_LOGICAL_SOLVER_H_
