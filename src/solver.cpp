// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_SOLVER_CPP_
#define _INCLUDE_SOLVER_CPP_

#include <algorithm> // std::sort
#include "solver.h"

template<size_t T>
bool atn::fill_known(
    atn::Sudoku<T>& board,
    std::vector<atn::Cell<T>>& empty_cells) {
  while (empty_cells.size() != 0
      && empty_cells[0].options.count() == 1
      && board.validate()) {
    for (size_t i = 0; i < T * T; ++i) {
      if (empty_cells[0].options[i]) {
        bool valid = board.set(empty_cells[0].pos, i + 1);
        if (valid) break;
        else return true;
      }
    }
    empty_cells = board.get_empty_cells();
    std::sort(
        empty_cells.begin(),
        empty_cells.end(),
        atn::Cell<T>::compare_options);
  }
  return false;
}

#endif // _INCLUDE_SOLVER_CPP_
