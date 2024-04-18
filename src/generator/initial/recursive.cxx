#include "recursive.h"

#include <algorithm>
#include <iterator>

atn::sudoku::Board atn::generator::Recursive::generate() {
  this->clear_board();
  if (this->add_value(0)) {
    return this->_board;
  }
  throw atn::generator::GenerationFailedException{};
}

atn::generator::Recursive::Recursive()
    : _board(), _factory(this->_board), _rng() {}

void atn::generator::Recursive::clear_board() {
  for (uint index{0}; index < 81u; ++index) {
    atn::sudoku::Position position = this->get_position(index);
    this->_board.get(position).unset();
  }
}

bool atn::generator::Recursive::add_value(uint board_index) {
  if (board_index >= 81u) {
    return true;
  }
  atn::sudoku::Position position = this->get_position(board_index);
  std::vector<atn::sudoku::Value> values = this->get_shuffled_values();
  for (uint index{0}; index < values.size(); ++index) {
    atn::sudoku::Value value = values[index];
    if (this->safe_to_add(value, position)) {
      atn::sudoku::Cell& cell = this->_board.get(position);
      cell.set(value);
      if (this->add_value(board_index + 1)) {
        return true;
      }
      cell.unset();
    }
  }
  return false;
}

atn::sudoku::Position atn::generator::Recursive::get_position(
    uint board_index) const {
  return atn::sudoku::Position{board_index % 9u, board_index / 9u};
}

std::vector<atn::sudoku::Value>
atn::generator::Recursive::get_shuffled_values() {
  std::vector<atn::sudoku::Value> values;
  std::copy(this->_values.begin(), this->_values.end(),
            std::back_inserter(values));
  std::shuffle(values.begin(), values.end(), this->_rng);
  return values;
}

bool atn::generator::Recursive::safe_to_add(
    atn::sudoku::Value value, atn::sudoku::Position position) const {
  atn::sudoku::CellGroup row = this->_factory.row(position.y());
  if (this->cell_group_contains(row, value)) {
    return false;
  }
  atn::sudoku::CellGroup column = this->_factory.column(position.x());
  if (this->cell_group_contains(column, value)) {
    return false;
  }
  atn::sudoku::CellGroup box = this->_factory.box(position.x() / 3, position.y() / 3);
  if (this->cell_group_contains(box, value)) {
    return false;
  }
  return true;
}

atn::sudoku::Value value_from_cell_ptr(atn::sudoku::CellPtr cell) {
  return cell->get();
}

bool atn::generator::Recursive::cell_group_contains(
    atn::sudoku::CellGroup cell_group, atn::sudoku::Value value) const {
  std::vector<atn::sudoku::Value> values;
  values.resize(cell_group.size());
  std::transform(cell_group.begin(), cell_group.end(), values.begin(),
                 value_from_cell_ptr);
  return std::find(values.begin(), values.end(), value) != std::end(values);
}

atn::generator::GenerationFailedException::
    GenerationFailedException() noexcept {
  this->message = "Initial board generation failed";
}

const char* atn::generator::GenerationFailedException::what() const noexcept {
  return this->message.c_str();
}
