#include "technique.h"

using namespace atn::generator::logic;
using namespace atn::sudoku;

atn::generator::logic::Technique::Technique(BoardPtr board)
    : _next_move(std::nullopt), _board(board) {}

std::optional<NextMove> atn::generator::logic::Technique::get_next_move()
    const {
  return this->_next_move;
}
