#include <iostream>

#include "config.h"
#include "difficulty.hpp"
#include "generator.h"

int main(int argc, char* argv[]) {
  std::cout << "Program Version " << SudokuGenerator_VERSION_MAJOR << "."
            << SudokuGenerator_VERSION_MINOR << std::endl;
  atn::Generator gen{};
  gen.get_sudoku(atn::difficulty::beginner);
  return 0;
}