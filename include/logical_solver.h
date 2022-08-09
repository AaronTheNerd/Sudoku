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

struct StepDifficulty {
  uint16_t bonus;
  uint16_t per_uses;
};

template <uint8_t T>
atn::LogicalTechniquePtr<T> get_next_move(atn::Sudoku<T>&);

template <uint8_t T>
LogicalSolverResults<T> logical_solve(atn::Sudoku<T>&);

// Constant variable

static const std::unordered_map<LOGICAL_TECHNIQUE, StepDifficulty>
    TECHNIQUE_DIFFICULTY = {{SINGLE_CANDIDATE, {0, 100}},
        {SINGLE_POSITION, {0, 100}}, {CANDIDATE_LINES, {150, 200}},
        {DOUBLE_PAIRS, {250, 250}}, {MULTIPLE_LINES, {300, 400}},
        {NAKED_PAIR, {250, 500}}, {HIDDEN_PAIR, {300, 1200}},
        {NAKED_TRIPLE, {600, 1400}}, {HIDDEN_TRIPLE, {800, 1600}},
        {X_WING, {1200, 1600}}, {FORCING_CHAINS, {2100, 2100}},
        {NAKED_QUAD, {1000, 4000}}, {HIDDEN_QUAD, {2000, 5000}},
        {SWORDFISH, {2000, 6000}}};


}  // namespace atn

#include "../src/logical_solver.cpp"

#endif  // _INCLUDE_LOGICAL_SOLVER_H_
