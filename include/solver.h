// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SOLVER_H_
#define _INCLUDE_SOLVER_H_

#include <cstddef> // size_t
#include <vector> // std::vector
#include "sudoku.h"

namespace atn {

template<size_t T>
bool fill_known(atn::Sudoku<T>&, std::vector<atn::Cell<T>>&);

} // namespace atn

#include "../src/solver.cpp"

#endif // _INCLUDE_SOLVER_H_
