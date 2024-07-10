#include "single_position.h"

#include <algorithm>
#include <unordered_map>

#include "clear_options.h"
#include "set_value.h"

using namespace atn::generator::logic;
using namespace atn::generator::command;

atn::generator::logic::SinglePosition::SinglePosition(BoardPtr board)
    : Technique(board) {
  this->find_next_move();
}

void atn::generator::logic::SinglePosition::find_next_move() {
  if (auto row_next_move = this->search_all_rows()) {
    this->_next_move = row_next_move;
  } else if (auto column_next_move = this->search_all_columns()) {
    this->_next_move = column_next_move;
  } else if (auto box_next_move = this->search_all_boxes()) {
    this->_next_move = box_next_move;
  }
}

std::optional<NextMove> atn::generator::logic::SinglePosition::search_all_rows()
    const {
  for (Index y{0}; y < 9u; ++y) {
    CellGroup row = this->_board->row(y);
    if (auto result = this->search_group(row)) {
      return this->calculate_changes(*result);
    }
  }
  return std::nullopt;
}

std::optional<NextMove>
atn::generator::logic::SinglePosition::search_all_columns() const {
  for (Index x{0}; x < 9u; ++x) {
    CellGroup column = this->_board->column(x);
    if (auto result = this->search_group(column)) {
      return this->calculate_changes(*result);
    }
  }
  return std::nullopt;
}

std::optional<NextMove>
atn::generator::logic::SinglePosition::search_all_boxes() const {
  for (BoxIndex x{0}; x < 3u; ++x) {
    for (BoxIndex y{0}; y < 3u; ++y) {
      CellGroup box = this->_board->box(x, y);
      if (auto result = this->search_group(box)) {
        return this->calculate_changes(*result);
      }
    }
  }
  return std::nullopt;
}

std::optional<GroupSearchResult>
atn::generator::logic::SinglePosition::search_group(
    const CellGroup& group) const {
  std::unordered_map<Value, std::vector<CellPtr>, ValueHash> value_cells{
      {1, {}}, {2, {}}, {3, {}}, {4, {}}, {5, {}},
      {6, {}}, {7, {}}, {8, {}}, {9, {}}};
  std::vector<Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto it = group.begin(); it != group.end(); ++it) {
    CellPtr cell = *it;
    for (auto value : values) {
      if (cell->has_option(value)) {
        value_cells[value].push_back(cell);
      }
    }
  }
  for (auto value : values) {
    auto positions = value_cells[value];
    if (positions.size() == 1) {
      return {{positions[0], value}};
    }
  }
  return std::nullopt;
}

NextMove atn::generator::logic::SinglePosition::calculate_changes(
    GroupSearchResult result) const {
  CellPtr cell = result.cell;
  MacroCommand command = this->calculate_aoe_changes(cell, result.value);
  command.push(std::make_shared<SetValue>(cell, result.value));
  std::vector<Value> values{1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<Value> clear_options;
  std::copy_if(values.begin(), values.end(), std::back_inserter(clear_options),
               [cell](Value v) { return cell->has_option(v); });
  command.push(std::make_shared<ClearOptions>(cell, clear_options));
  return {TechniqueEnum::SINGLE_POSITION,
          std::make_shared<MacroCommand>(command)};
}

MacroCommand atn::generator::logic::SinglePosition::calculate_aoe_changes(
    CellPtr original_cell, Value set_value) const {
  MacroCommand command;
  CellGroup aoe = this->_board->area_of_effect(original_cell->position());
  for (auto& cell : aoe) {
    if (cell->has_option(set_value)) {
      command.push(
          std::make_shared<ClearOptions>(cell, std::vector{set_value}));
    }
  }
  return command;
}
