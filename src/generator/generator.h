#pragma once

#include "board.h"
#include "difficulty.hpp"
#include "initial/get_generator.h"

namespace atn {

class Generator {
 public:
  Generator(InitialGeneratorType = InitialGeneratorType::RECURSIVE);

  BoardPtr get_sudoku(const DifficultyRange&);

 private:
  BoardPtr _board;
  InitialGeneratorPtr _initial_generator;
};

}  // namespace atn
