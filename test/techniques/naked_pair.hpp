// Written by Aaron Barge
// Copyright 2022

#include "../unittest.h"
#include "logical_solver.h"
#include "sudoku.h"

int test_naked_pair() {
  TEST_SUITE("Naked Pair") {
    // Import the board state from json
    std::array<std::array<uint8_t, 3 * 3>, 3 * 3> board{
        // clang-format off
        {{1, 3, 5, 0, 0, 0, 0, 0, 0},
         {0, 6, 7, 0, 0, 0, 0, 0, 0},
         {0, 8, 9, 0, 0, 0, 0, 0, 0},
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
      ASSERT(ptr->technique == atn::NAKED_PAIR);
    }
    // Test that the sudoku board is correctly changed after calling apply()
    TEST_CASE("apply()") {
      for (uint8_t x = 3; x < 9; ++x) {
        ASSERT(puzzle.get({x, 0}).options.count() == 8);
        ASSERT(puzzle.get({x, 0}).options[3] == true);
        ASSERT(puzzle.get({x, 0}).options[5] == true);
      }
      ptr->apply(puzzle);
      for (uint8_t x = 3; x < 9; ++x) {
        ASSERT(puzzle.get({x, 0}).options.count() == 6);
        ASSERT(puzzle.get({x, 0}).options[3] == false);
        ASSERT(puzzle.get({x, 0}).options[5] == false);
      }
    }
  }
  return 0;
}
