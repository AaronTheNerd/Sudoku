#include "validate.h"

#include <algorithm>
#include <unordered_set>

#include "cell_group.h"

namespace {

bool valid_cell_group(atn::sudoku::CellGroup group) {
  std::unordered_set<atn::sudoku::Value, atn::sudoku::ValueHash> set{};
  for (auto it = group.begin(); it != group.end(); ++it) {
    atn::sudoku::CellPtr cell = *it;
    if (!cell->is_set()) continue;
    atn::sudoku::Value value = cell->get();
    if (set.contains(value)) return false;
    set.insert(value);
  }
  return true;
}

bool valid_rows(atn::sudoku::BoardPtr board) {
  for (uint index{0}; index < 9u; ++index) {
    atn::sudoku::CellGroup group = board->row(index);
    if (!valid_cell_group(group)) return false;
  }
  return true;
}

bool valid_columns(atn::sudoku::BoardPtr board) {
  for (uint index{0}; index < 9u; ++index) {
    atn::sudoku::CellGroup group = board->column(index);
    if (!valid_cell_group(group)) return false;
  }
  return true;
}

bool valid_boxes(atn::sudoku::BoardPtr board) {
  for (uint x{0}; x < 3u; ++x) {
    for (uint y{0}; y < 3u; ++y) {
      atn::sudoku::CellGroup group = board->box(x, y);
      if (!valid_cell_group(group)) return false;
    }
  }
  return true;
}

}  // namespace

bool atn::sudoku::validate(atn::sudoku::BoardPtr board) {
  return valid_rows(board) && valid_columns(board) && valid_boxes(board);
}