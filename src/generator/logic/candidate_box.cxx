#include "candidate_box.h"

#include "clear_options.h"
#include "macro_command.h"

atn::CandidateBox::CandidateBox(atn::BoardPtr board)
    : Technique(board), view(board) {
  this->find_next_move();
}

void atn::CandidateBox::find_next_move() {
  for (atn::Index i{0}; i < 9; ++i) {
    if (auto column_move = this->search_line(i, atn::Line::COLUMN)) {
      this->_next_move = column_move;
      return;
    }
    if (auto row_move = this->search_line(i, atn::Line::ROW)) {
      this->_next_move = row_move;
      return;
    }
  }
}

std::optional<atn::NextMove> atn::CandidateBox::search_line(Index index,
                                                            Line line) const {
  std::vector<Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto value : values) {
    if (auto next_move = this->search_line_at_value(index, line, value)) {
      return next_move;
    }
  }
  return std::nullopt;
}

std::optional<atn::NextMove> atn::CandidateBox::search_line_at_value(
    Index index, Line line, Value value) const {
  std::bitset<3> box_bitset = this->view.box_bitset(value, line, index);
  if (box_bitset.count() != 1) {
    return std::nullopt;
  }
  BoxIndex change_index = this->get_change_index(box_bitset);
  if (!this->would_have_changes(this->get_other_bitsets(index, line, value),
                                box_bitset)) {
    return std::nullopt;
  }
  return this->calculate_changes(index, line, value, change_index);
}

std::array<std::bitset<3>, 2> atn::CandidateBox::get_other_bitsets(
    Index index, Line line, Value value) const {
  BoxIndex box_index = BoxIndex::index_in_board(index);
  BoxIndex inside_index = BoxIndex::index_in_box(index);
  return {this->view.box_bitset(
              value, line,
              Index::from_boxes(box_index, (inside_index.value() + 1) % 3)),
          this->view.box_bitset(
              value, line,
              Index::from_boxes(box_index, (inside_index.value() + 2) % 3))};
}

bool atn::CandidateBox::would_have_changes(
    std::array<std::bitset<3>, 2> other_bitsets,
    std::bitset<3> box_bitset) const {
  return ((other_bitsets[0] | other_bitsets[1]) & box_bitset).count() == 1;
}

atn::BoxIndex atn::CandidateBox::get_change_index(
    std::bitset<3> box_bitset) const {
  for (BoxIndex i{0}; i < 3; ++i) {
    if (box_bitset.test(i.value())) {
      return i;
    }
  }
}

atn::NextMove atn::CandidateBox::calculate_changes(
    Index index, Line line, Value value, BoxIndex change_index) const {
  if (line == atn::Line::ROW) {
    return this->calculate_changes_row(index, value, change_index);
  }
  return this->calculate_changes_column(index, value, change_index);
}

atn::NextMove atn::CandidateBox::calculate_changes_row(Index y, Value value,
                                                       BoxIndex box_x) const {
  MacroCommand command;
  BoxIndex box_y = BoxIndex::index_in_board(y);
  BoxIndex exclude_inside_y = BoxIndex::index_in_box(y);
  for (BoxIndex inside_y{0}; inside_y < 3; ++inside_y) {
    if (inside_y == exclude_inside_y) continue;
    for (BoxIndex inside_x{0}; inside_x < 3; ++inside_x) {
      Position position{Index::from_boxes(box_x, inside_x),
                        Index::from_boxes(box_y, inside_y)};
      CellPtr cell = this->_board->get(position);
      if (cell->has_option(value)) {
        command.push(
            std::make_shared<ClearOptions>(cell, std::vector<Value>{value}));
      }
    }
  }
  return {atn::TechniqueEnum::CANDIDATE_BOX,
          std::make_shared<MacroCommand>(command)};
}

atn::NextMove atn::CandidateBox::calculate_changes_column(
    Index x, Value value, BoxIndex box_y) const {
  BoxIndex box_x = BoxIndex::index_in_board(x);
  BoxIndex exclude_inside_x = BoxIndex::index_in_box(x);
  MacroCommand command;
  for (BoxIndex inside_x{0}; inside_x < 3; ++inside_x) {
    if (inside_x == exclude_inside_x) continue;
    for (BoxIndex inside_y{0}; inside_y < 3; ++inside_y) {
      Position position{Index::from_boxes(box_x, inside_x),
                        Index::from_boxes(box_y, inside_y)};
      CellPtr cell = this->_board->get(position);
      if (cell->has_option(value)) {
        command.push(
            std::make_shared<ClearOptions>(cell, std::vector<Value>{value}));
      }
    }
  }
  return {atn::TechniqueEnum::CANDIDATE_BOX,
          std::make_shared<MacroCommand>(command)};
}
