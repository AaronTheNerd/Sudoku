#include "double_pairs.h"

using namespace atn::generator::logic;

atn::generator::logic::DoublePairs::DoublePairs(BoardPtr board)
    : _next_move(std::nullopt), _board(board) {}

std::optional<NextMove> atn::generator::logic::DoublePairs::get_next_move() {
  return std::nullopt;
}
