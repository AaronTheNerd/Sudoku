#include "generator.h"

#include "initial/get_generator.h"

atn::Generator::Generator(InitialGeneratorType type)
    : _board(), _initial_generator(get_generator(type)) {}

atn::BoardPtr atn::Generator::get_sudoku(const DifficultyRange& difficulty) {
  this->_board = this->_initial_generator->generate();
  return this->_board;
}
