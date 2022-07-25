// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_LOGICAL_SOLVER_CPP_
#define _SRC_LOGICAL_SOLVER_CPP_

#include "logical_solver.h"
#include <vector>  // std::vector

namespace {

uint16_t calculate_difficulty_score(const atn::TechniqueCounts steps_to_solve) {
  uint16_t difficulty_score = 0;
  for (auto it = steps_to_solve.begin(); it != steps_to_solve.end(); ++it) {
    difficulty_score +=
        (it->second > 0) * atn::TECHNIQUE_DIFFICULTY.at(it->first).bonus;
    difficulty_score +=
        it->second * atn::TECHNIQUE_DIFFICULTY.at(it->first).per_uses;
  }
  return difficulty_score;
}

}  // namespace

template <uint8_t T>
atn::LogicalTechniquePtr<T> atn::get_next_move(atn::Sudoku<T>& puzzle) {
  atn::LogicalTechniquePtr<T> technique;
  for (LOGICAL_TECHNIQUE i = SINGLE_CANDIDATE; i != LAST_TECHNIQUE;
       i = static_cast<LOGICAL_TECHNIQUE>((uint8_t)i + 1)) {
    technique = atn::generate_ptr(puzzle, i);
    if (technique == nullptr) break;
    if (technique->valid) {
      return technique;
    }
  }
  return nullptr;
}

template <uint8_t T>
atn::LogicalSolverResults<T> atn::logical_solve(atn::Sudoku<T>& puzzle) {
  std::vector<atn::Cell<T>> empty_cells = puzzle.get_empty_cells();
  atn::LogicalTechniquePtr<T> technique;
  atn::TechniqueCounts counts;
  while (empty_cells.size() != 0 && puzzle.validate()) {
    technique = atn::get_next_move<T>(puzzle);
    if (technique != nullptr) {
      auto result = counts.insert({technique->technique, 1});
      if (result.second) result.first->second++;
      technique->apply(puzzle);
    } else {
      return {false, 0};
    }
    empty_cells = puzzle.get_empty_cells();
  }
  return {puzzle.validate() && empty_cells.size() == 0,
      calculate_difficulty_score(counts)};
}

#endif  // _SRC_LOGICAL_SOLVER_CPP_