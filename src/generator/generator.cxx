#include "generator.h"

using namespace atn::generator;

Generator::Generator() : _board() {}

atn::sudoku::Board Generator::get_sudoku(const DifficultyRange& difficulty) {
  return this->_board;
}
 