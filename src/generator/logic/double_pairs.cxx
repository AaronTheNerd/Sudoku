#include "double_pairs.h"

#include "clear_options.h"
#include "macro_command.h"

atn::DoublePairs::DoublePairs(atn::BoardPtr board)
    : Technique(board), view(board) {
  this->find_next_move();
}

void atn::DoublePairs::find_next_move() {
  for (atn::BoxIndex i{0}; i < 3; ++i) {
    if (auto column_move = this->search_box_group(i, atn::Line::COLUMN)) {
      this->_next_move = column_move;
      return;
    }
    if (auto row_move = this->search_box_group(i, atn::Line::ROW)) {
      this->_next_move = row_move;
      return;
    }
  }
}

std::optional<atn::NextMove> atn::DoublePairs::search_box_group(
    BoxIndex index, Line line) const {
  std::vector<Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto value : values) {
    if (auto next_move = this->search_box_group_at_value(index, line, value)) {
      return next_move;
    }
  }
  return std::nullopt;
}

std::optional<atn::NextMove> atn::DoublePairs::search_box_group_at_value(
    BoxIndex index, Line line, Value value) const {
  std::array<std::bitset<3>, 3> box_bitsets =
      this->get_all_bitsets(index, line, value);
  std::optional<BoxIndex> optional_excluded_index =
      this->excluded_index(box_bitsets);
  if (!optional_excluded_index.has_value()) return std::nullopt;
  BoxIndex excluded_index = optional_excluded_index.value();
  if (!this->technique_applicable(box_bitsets, excluded_index))
    return std::nullopt;
  BoxIndex change_index =
      this->get_change_index(box_bitsets[excluded_index.value()]);
  return this->calculate_changes(index, line, value, excluded_index,
                                 change_index);
}

std::array<std::bitset<3>, 3> atn::DoublePairs::get_all_bitsets(
    BoxIndex index, Line line, Value value) const {
  return {this->view.box_bitset(value, line, Index::from_boxes(index, 0)),
          this->view.box_bitset(value, line, Index::from_boxes(index, 1)),
          this->view.box_bitset(value, line, Index::from_boxes(index, 2))};
}

std::optional<atn::BoxIndex> atn::DoublePairs::excluded_index(
    std::array<std::bitset<3>, 3> bitsets) const {
  for (BoxIndex index{0}; index < 3; ++index) {
    if (bitsets[index.value()].count() == 1) {
      return index;
    }
  }
  return std::nullopt;
}

bool atn::DoublePairs::technique_applicable(
    std::array<std::bitset<3>, 3> bitsets, BoxIndex excluded_index) const {
  BoxIndex index_1 = (excluded_index.value() + 1) % 3;
  BoxIndex index_2 = (excluded_index.value() + 2) % 3;
  auto bitset_1 = bitsets[index_1.value()];
  auto bitset_2 = bitsets[index_2.value()];
  auto excluded_bitset = bitsets[excluded_index.value()];
  bool has_double_pair = (bitset_1 & bitset_2).count() >= 2;
  bool has_changes_if_applied =
      ((bitset_1 | bitset_2) & excluded_bitset).count() == 1;
  return has_double_pair && has_changes_if_applied;
}

atn::BoxIndex atn::DoublePairs::get_change_index(
    std::bitset<3> excluded_bitset) const {
  for (BoxIndex i{0}; i < 3; ++i) {
    if (excluded_bitset.test(i.value())) {
      return i;
    }
  }
}

atn::NextMove atn::DoublePairs::calculate_changes(BoxIndex box_index, Line line,
                                                  Value value,
                                                  BoxIndex excluded_index,
                                                  BoxIndex change_index) const {
  if (line == atn::Line::ROW) {
    return this->calculate_changes_row(box_index, value, excluded_index,
                                       change_index);
  }
  return this->calculate_changes_column(box_index, value, excluded_index,
                                        change_index);
}

atn::NextMove atn::DoublePairs::calculate_changes_row(BoxIndex box_y,
                                                      Value value,
                                                      BoxIndex exclude_inside_y,
                                                      BoxIndex box_x) const {
  MacroCommand command;
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
  return {this->get_technique_from_exclude(exclude_inside_y),
          std::make_shared<MacroCommand>(command)};
}

atn::NextMove atn::DoublePairs::calculate_changes_column(
    BoxIndex box_x, Value value, BoxIndex exclude_inside_x,
    BoxIndex box_y) const {
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
  return {this->get_technique_from_exclude(exclude_inside_x),
          std::make_shared<MacroCommand>(command)};
}

atn::TechniqueEnum atn::DoublePairs::get_technique_from_exclude(
    BoxIndex exclude_index) const {
  if (exclude_index == 2) {
    return TechniqueEnum::MULTIPLE_LINES;
  }
  return TechniqueEnum::DOUBLE_PAIRS;
}
