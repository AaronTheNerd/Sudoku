#include "validate.h"

#include <algorithm>
#include <unordered_set>

#include "cell_group.h"

namespace {

bool valid_cell_group(atn::CellGroup group) {
  std::unordered_set<atn::Value, atn::ValueHash> set{};
  for (uint index{0}; index < 9u; ++index) {
    atn::CellPtr cell = group[index];
    if (!cell->is_set()) continue;
    atn::Value value = cell->get();
    if (set.contains(value)) return false;
    set.insert(value);
  }
  return true;
}

bool valid_rows(atn::BoardPtr board) {
  for (uint index{0}; index < 9u; ++index) {
    atn::CellGroup group = board->row(index);
    if (!valid_cell_group(group)) return false;
  }
  return true;
}

bool valid_columns(atn::BoardPtr board) {
  for (uint index{0}; index < 9u; ++index) {
    atn::CellGroup group = board->column(index);
    if (!valid_cell_group(group)) return false;
  }
  return true;
}

bool valid_boxes(atn::BoardPtr board) {
  for (uint x{0}; x < 3u; ++x) {
    for (uint y{0}; y < 3u; ++y) {
      atn::CellGroup group = board->box(x, y);
      if (!valid_cell_group(group)) return false;
    }
  }
  return true;
}

}  // namespace

bool atn::validate(atn::BoardPtr board) {
  return valid_rows(board) && valid_columns(board) && valid_boxes(board);
}