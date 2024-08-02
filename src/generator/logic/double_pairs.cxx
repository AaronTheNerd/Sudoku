#include "double_pairs.h"

using namespace atn::sudoku;
using namespace atn::generator::logic;

atn::generator::logic::DoublePairs::DoublePairs(BoardPtr board)
    : Technique(board) {
  this->find_next_move();
}

void atn::generator::logic::DoublePairs::find_next_move() {
  
}
