#include "generator.h"

#include "initial/get_generator.h"

using namespace atn::generator;

Generator::Generator(initial::GeneratorType type)
    : _board(), _initial_generator(initial::get_generator(type)) {}

atn::sudoku::Board Generator::get_sudoku(const DifficultyRange& difficulty) {
  this->_board = this->_initial_generator->generate();
  return this->_board;
}
