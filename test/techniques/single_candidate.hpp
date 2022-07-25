// Written by Aaron Barge
// Copyright 2022

#include "../unittest.h"
#include "logical_solver.h"
#include "sudoku.h"

int test_single_candidate() {
  TEST_SUITE("Single Candidate") {
    // Import the board state from json
    std::array<std::array<uint8_t, 3 * 3>, 3 * 3> board{
        // clang-format off
        {{1, 2, 3, 0, 5, 6, 7, 8, 9},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0}}
        // clang-format on
    };
    atn::Sudoku<3> puzzle(board);
    puzzle.fix_options();
    // Call atn::get_next_move()
    atn::LogicalTechniquePtr<3> ptr = atn::get_next_move(puzzle);
    // Test that the returned pointer is not a nullptr
    TEST_CASE("Not a nullptr") { ASSERT(ptr->valid); }
    // Test that the returned pointer is the correct technique
    TEST_CASE("Correct Technique") {
      ASSERT(ptr->technique == atn::SINGLE_CANDIDATE);
    }
    // Test that the sudoku board is correctly changed after calling apply()
    TEST_CASE("apply()") {
      ASSERT(puzzle.get({0, 3}).value == atn::UNSET);
      ptr->apply(puzzle);
      ASSERT(puzzle.get({0, 3}).value == 4);
    }
  }
  return 0;
}
