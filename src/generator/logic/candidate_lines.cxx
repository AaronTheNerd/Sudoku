#include "candidate_lines.h"

#include <algorithm>

#include "clear_options.h"

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

atn::generator::logic::CandidateLines::CandidateLines(BoardPtr board)
    : Technique(board) {
  this->find_next_move();
}

void atn::generator::logic::CandidateLines::find_next_move() {
  for (BoxIndex x{0}; x < 3; ++x) {
    for (BoxIndex y{0}; y < 3; ++y) {
      CellGroup box = this->_board->box(x, y);
      if (auto result = this->search_box(box)) {
        this->_next_move = result;
        return;
      }
    }
  }
}

std::optional<NextMove> atn::generator::logic::CandidateLines::search_box(
    CellGroup box) const {
  auto option_cells_map = this->map_options_to_cells(box);
  for (uint value{1}; value <= 9; ++value) {
    auto cells = option_cells_map.at(value);
    LineTestEnum result = this->test_line(cells);
    if (result == LineTestEnum::NONE) continue;
    auto affected_cells = this->find_affected_cells(result, cells, value);
    if (affected_cells.size() == 0) continue;
    return this->calculate_changes(affected_cells, value);
  }
  return std::nullopt;
}

std::unordered_map<Value, CellGroup, ValueHash>
atn::generator::logic::CandidateLines::map_options_to_cells(
    CellGroup box) const {
  std::unordered_map<Value, CellGroup, ValueHash> option_cells_map{
      {1, {}}, {2, {}}, {3, {}}, {4, {}}, {5, {}},
      {6, {}}, {7, {}}, {8, {}}, {9, {}}};
  for (auto it = box.begin(); it != box.end(); ++it) {
    CellPtr cell = *it;
    for (uint value{1}; value <= 9; ++value) {
      if (cell->has_option(value)) {
        option_cells_map.at(value).push_back(cell);
      }
    }
  }
  return option_cells_map;
}

LineTestEnum atn::generator::logic::CandidateLines::test_line(
    CellGroup cells) const {
  if (cells.size() < 2) return LineTestEnum::NONE;
  bool row = true, column = true;
  Position first = cells[0]->position();
  for (uint index{1}; index < cells.size(); ++index) {
    auto cell = cells[index];
    if (cell->position().x() != first.x()) {
      column = false;
    }
    if (cell->position().y() != first.y()) {
      row = false;
    }
  }
  if (column) return LineTestEnum::COLUMN;
  if (row) return LineTestEnum::ROW;
  return LineTestEnum::NONE;
}

CellGroup atn::generator::logic::CandidateLines::find_affected_cells(
    LineTestEnum line, CellGroup cells, Value value) const {
  auto cell_group = this->get_cell_group(line, cells);
  CellGroup affected_cells;
  std::copy_if(
      cell_group.begin(), cell_group.end(), std::back_inserter(affected_cells),
      [value, cells](CellPtr cell) {
        return cell->has_option(value) &&
               std::find_if(cells.begin(), cells.end(),
                            [cell](CellPtr test_cell) {
                              return cell->position() == test_cell->position();
                            }) == cells.end();
      });
  return affected_cells;
}

CellGroup atn::generator::logic::CandidateLines::get_cell_group(
    LineTestEnum line, CellGroup cells) const {
  Position pos = cells[0]->position();
  if (line == LineTestEnum::COLUMN) {
    return this->_board->column(pos.x());
  }
  if (line == LineTestEnum::ROW) {
    return this->_board->row(pos.y());
  }
  throw;
}

NextMove atn::generator::logic::CandidateLines::calculate_changes(
    CellGroup cells, Value value) const {
  MacroCommand command;
  for (auto cell : cells) {
    command.push(std::make_shared<ClearOptions>(cell, std::vector{value}));
  }
  return {TechniqueEnum::CANDIDATE_LINES,
          std::make_shared<MacroCommand>(command)};
}
