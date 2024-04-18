
#include "test_utils.h"

atn::sudoku::Board atn::test_utils::generate_board(
    std::vector<std::vector<uint8_t>> input) {
  atn::sudoku::Board board{};
  for (uint y = 0; y < 9; ++y) {
    for (uint x = 0; x < 9; ++x) {
      atn::sudoku::Position pos{x, y};
      atn::sudoku::Value value{input[y][x]};
      board.get(pos)->set(value);
    }
  }
  return board;
}

bool atn::test_utils::cell_group_eq(atn::sudoku::CellGroup group,
                                    std::vector<uint8_t> test) {
  if (group.size() != test.size()) return false;
  for (uint index{0}; index < group.size(); ++index) {
    if (group[index]->get() != atn::sudoku::Value{test[index]}) return false;
  }
  return true;
}
