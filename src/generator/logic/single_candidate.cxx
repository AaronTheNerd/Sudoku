#include "single_candidate.h"

#include "clear_options.h"
#include "macro_command.h"
#include "set_value.h"
#include "sstream"

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

atn::generator::logic::SingleCandidate::SingleCandidate(BoardPtr board)
    : Technique(board) {
  this->find_next_move();
}

void atn::generator::logic::SingleCandidate::find_next_move() {
  CellGroup board = this->_board->board();
  for (auto it = board.begin(); it != board.end(); ++it) {
    CellPtr cell = *it;
    if (cell->count_options() == 1) {
      this->calculate_changes(cell);
      return;
    }
  }
}

void atn::generator::logic::SingleCandidate::calculate_changes(CellPtr cell) {
  Value set_value = this->calculate_set_value(cell);
  MacroCommand command = this->calculate_aoe_changes(cell, set_value);
  command.push(std::make_shared<SetValue>(cell, set_value));
  command.push(std::make_shared<ClearOptions>(cell, std::vector{set_value}));
  this->_next_move = {TechniqueEnum::SINGLE_CANDIDATE,
                      std::make_shared<MacroCommand>(command)};
}

Value atn::generator::logic::SingleCandidate::calculate_set_value(
    CellPtr cell) const {
  std::vector<Value> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (const auto& value : values) {
    if (cell->has_option(value)) {
      return value;
    }
  }
  throw MissingOption{cell->position()};
}

MacroCommand atn::generator::logic::SingleCandidate::calculate_aoe_changes(
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

atn::generator::logic::MissingOption::MissingOption(
    atn::sudoku::Position pos) noexcept {
  std::stringstream ss;
  ss << "Cell at position " << pos.to_string()
     << " is missing any valid options";
  this->message = ss.str();
}

const char* atn::generator::logic::MissingOption::what() const noexcept {
  return this->message.c_str();
}
