#include "line_box_view.h"

#include <cassert>

atn::LineBoxView::LineBoxView(BoardPtr board) : _lines() {
  this->initialize_view(board);
}

uint atn::LineBoxView::count_boxes(Value value, Line line, Index index) const {
  return this->box_bitset(value, line, index).count();
}

std::bitset<3> atn::LineBoxView::box_bitset(atn::Value value, atn::Line line,
                                            atn::Index index) const {
  size_t line_offset = this->line_offset(line, index);
  std::bitset<3 * 18> mask = 7ull;
  return std::bitset<3>(
      ((this->_lines[value.value() - 1] >> line_offset) & mask).to_ulong());
}

void atn::LineBoxView::initialize_view(BoardPtr board) {
  for (auto cell : board->board()) {
    if (cell->is_set()) continue;
    this->add_cell_options(cell);
  }
}

void atn::LineBoxView::add_cell_options(atn::CellPtr cell) {
  std::vector<atn::Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto value : values) {
    if (!cell->has_option(value)) continue;
    this->add_option(cell->position(), value);
  }
}

void atn::LineBoxView::add_option(atn::Position position, atn::Value option) {
  atn::BoxIndex box_x = atn::BoxIndex::index_in_board(position.x());
  atn::BoxIndex box_y = atn::BoxIndex::index_in_board(position.y());
  this->_lines[option.value() - 1].set(
      this->line_offset(atn::Line::ROW, position.y()) + box_x.value());
  this->_lines[option.value() - 1].set(
      this->line_offset(atn::Line::COLUMN, position.x()) + box_y.value());
}

size_t atn::LineBoxView::line_offset(atn::Line line, atn::Index index) const {
  return (uint)line + (3 * index.value());
}
