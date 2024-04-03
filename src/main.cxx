#include <iostream>

#include "config.h"
#include "value.h"

int main(int argc, char* argv[]) {
  std::cout << "Program Version " << SudokuGenerator_VERSION_MAJOR << "." << SudokuGenerator_VERSION_MINOR << std::endl;
  atn::sudoku::Value value{10};
  return 0;
}