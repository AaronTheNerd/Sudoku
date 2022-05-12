// Written by Aaron Barge
// Copyright 2022

#define GAME_SIZE 3

#include <chrono> // std::chrono
#include <iostream> // std::cout, std::endl
#include "generator.h"
//#include "puzzle_generator.h"
#include "sudoku.h"


int main(int argc, char** argv) {
  // Instantiate variables for Sudoku Generation
  auto start = std::chrono::high_resolution_clock::now();
  auto end = std::chrono::high_resolution_clock::now();
  atn::DIFFICULTY difficulty = atn::EASY;

  // Start generating valid Sudoku board
  start = std::chrono::high_resolution_clock::now();
  atn::SudokuGenerator<GAME_SIZE> generator;
  end = std::chrono::high_resolution_clock::now();

  // Get the generated solution
  atn::Sudoku<GAME_SIZE> solution = generator.get_solution();

  // Record execution time of solution
  std::chrono::duration<double, std::milli> ms_duration = end - start;
  std::cout << "Generated in " << ms_duration.count() << "ms" << std::endl;

  // Start generating Sudoku puzzle
  //atn::SudokuPuzzleGenerator<GAME_SIZE> puzzle_generator(difficulty, solution);

  // Record seed
  std::cout << "Seed: " << generator.get_seed() << std::endl;

  // Get generated Sudoku puzzle
  //atn::Sudoku<GAME_SIZE> game = puzzle_generator.get_puzzle();

  // Display Sudoku puzzle
  //std::cout << "Puzzle:" << std::endl; 
  //std::cout << game.to_str() << std::endl;

  // Display Sudoku solution
  std::cout << "\n\n\n\n\nSolution:" << std::endl;
  std::cout << solution.to_str() << std::endl;
  return 0;
}
