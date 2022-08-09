// Written by Aaron Barge
// Copyright 2022

#include "../unittest.h"
#include "logical_solver.h"
#include "sudoku.h"

void test_candidate_lines() {
  TEST_INIT();
  // Import the board state from json
  std::array<std::array<uint8_t, 3 * 3>, 3 * 3> board{
    // clang-format off
      {{0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 3, 0, 0, 0, 0, 0, 0},
        {5, 0, 7, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 4, 0, 0, 0, 0, 0}}
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
    ASSERT(ptr->technique == atn::CANDIDATE_LINES);
  }
  // Test that the sudoku board is correctly changed after calling apply()
  TEST_CASE("apply()") {
    for (uint8_t x = 0; x < 6; ++x) {
      ASSERT(puzzle.get({x, 1}).options.count() == 9);
    }
    for (uint8_t x = 0; x < 8; ++x) {
      ASSERT(puzzle.get({x, 1}).options[3] == true);
    }
    ptr->apply(puzzle);
    for (uint8_t x = 0; x < 6; ++x) {
      ASSERT(puzzle.get({x, 1}).options.count() == 8);
      ASSERT(puzzle.get({x, 1}).options[3] == false);
    }
    for (uint8_t x = 6; x < 8; ++x) {
      ASSERT(puzzle.get({x, 1}).options[3] == true);
    }
  }
}
