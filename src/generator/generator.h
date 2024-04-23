#pragma once

#include "board.h"
#include "difficulty.hpp"
#include "initial/get_generator.h"

namespace atn::generator {

class Generator {
 public:
  Generator(initial::GeneratorType = initial::GeneratorType::RECURSIVE);

  atn::sudoku::Board get_sudoku(const atn::generator::DifficultyRange&);

 private:
  atn::sudoku::Board _board;
  initial::GeneratorPtr _initial_generator;
};

}  // namespace atn::generator
