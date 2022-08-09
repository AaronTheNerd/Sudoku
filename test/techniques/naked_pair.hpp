// Written by Aaron Barge
// Copyright 2022

#include "../unittest.h"
#include "logical_solver.h"
#include "sudoku.h"

void test_naked_pair() {
  TEST_INIT();
  // Import the board state from json
  std::array<std::array<uint8_t, 3 * 3>, 3 * 3> board{
      // clang-format off
      {{0, 6, 0, 0, 0, 0, 0, 0, 0},
        {0, 7, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 0, 0, 0, 0, 0, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 5, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0}}
      // clang-format on
  };
  atn::Sudoku<3> puzzle(board);
  puzzle.fix_options();
  // Call atn::get_next_move()
  atn::LogicalTechniquePtr<3> ptr = atn::get_next_move(puzzle);
  // Test that the returned pointer is not a nullptr
  TEST_CASE("Not a nullptr") { ASSERT(ptr->valid); }
  // Test that the returned pointer is the correct technique
  TEST_CASE("Correct Technique") { ASSERT(ptr->technique == atn::NAKED_PAIR); }
  // Test that the sudoku board is correctly changed after calling apply()
  TEST_CASE("apply()") {
    ASSERT(puzzle.get({2, 1}).options == 0b000011110);
    ASSERT(puzzle.get({5, 1}).options == 0b000011110);
    ASSERT(puzzle.get({6, 1}).options == 0b000001010);
    ASSERT(puzzle.get({8, 1}).options == 0b000001010);
    ASSERT(puzzle.get({6, 0}).options == 0b111101010);
    ASSERT(puzzle.get({7, 0}).options == 0b111101010);
    ASSERT(puzzle.get({7, 2}).options == 0b111101010);
    ASSERT(puzzle.get({8, 2}).options == 0b111101010);
    ptr->apply(puzzle);
    ASSERT(puzzle.get({2, 1}).options == 0b000010100);
    ASSERT(puzzle.get({5, 1}).options == 0b000010100);
    ASSERT(puzzle.get({6, 1}).options == 0b000001010);
    ASSERT(puzzle.get({8, 1}).options == 0b000001010);
    ASSERT(puzzle.get({6, 0}).options == 0b111100000);
    ASSERT(puzzle.get({7, 0}).options == 0b111100000);
    ASSERT(puzzle.get({7, 2}).options == 0b111100000);
    ASSERT(puzzle.get({8, 2}).options == 0b111100000);
  }
}
