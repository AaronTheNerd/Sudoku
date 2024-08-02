#include "technique.h"

atn::Technique::Technique(atn::BoardPtr board)
    : _next_move(std::nullopt), _board(board) {}

std::optional<atn::NextMove> atn::Technique::get_next_move() const {
  return this->_next_move;
}
