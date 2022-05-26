// Written by Aaron Barge
// Copyright 2022

#define GAME_SIZE 3

#include <chrono>                // std::chrono
#include <iostream>              // std::cout, std::endl
#include "puzzle_generator.h"    // atn::SudokuPuzzleGenerator
#include "solution_generator.h"  // atn::SudokuSolutionGenerator
#include "sudoku.h"              // atn::Sudoku

int main(int argc, char** argv) {
  // Instantiate variables for Sudoku Generation
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> ms_duration = end - start;
  atn::DIFFICULTY difficulty = atn::VERY_EASY;

  // Start generating valid Sudoku board
  start = std::chrono::high_resolution_clock::now();
  atn::SudokuSolutionGenerator<GAME_SIZE> generator;
  end = std::chrono::high_resolution_clock::now();

  // Get the seed
  unsigned seed = generator.get_seed();

  // Get the generated solution
  atn::Sudoku<GAME_SIZE> solution = generator.get_solution();

  // Record seed
  std::cout << "Seed: " << seed << std::endl;

  // Record execution time of solution
  ms_duration = end - start;
  std::cout << "Solution generated in " << ms_duration.count() << "ms"
            << std::endl;

  // Display Sudoku solution
  std::cout << "Solution:" << std::endl;
  std::cout << solution.to_str() << "\n\n\n\n\n\n" << std::endl;

  // Start generating Sudoku puzzle
  start = std::chrono::high_resolution_clock::now();
  atn::SudokuPuzzleGenerator<GAME_SIZE> puzzle_generator(
      difficulty, seed, solution);
  end = std::chrono::high_resolution_clock::now();

  // Get generated Sudoku puzzle
  atn::Sudoku<GAME_SIZE> puzzle = puzzle_generator.get_puzzle();

  // Record execution time of puzzle
  ms_duration = end - start;
  std::cout << "Puzzle generated in " << ms_duration.count() << "ms"
            << std::endl;

  // Display Sudoku puzzle
  std::cout << "Puzzle:" << std::endl;
  std::cout << puzzle.to_str() << std::endl;

  return 0;
}
