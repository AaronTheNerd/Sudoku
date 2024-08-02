#include "../initial/recursive.h"

#include <algorithm>
#include <iterator>

#include "../initial/exception.h"

atn::BoardPtr atn::Recursive::generate() {
  this->clear_board();
  if (this->add_value(0)) {
    return this->_board;
  }
  throw GenerationFailedException{};
}

atn::Recursive::Recursive() : _board(Board::create()), _rng() {}

void atn::Recursive::clear_board() {
  for (uint index{0}; index < 81u; ++index) {
    Position position = this->get_position(index);
    this->_board->get(position)->unset();
  }
}

bool atn::Recursive::add_value(uint board_index) {
  if (board_index >= 81u) {
    return true;
  }
  Position position = this->get_position(board_index);
  std::vector<Value> values = this->get_shuffled_values();
  for (uint index{0}; index < values.size(); ++index) {
    Value value = values[index];
    if (this->safe_to_add(value, position)) {
      CellPtr cell = this->_board->get(position);
      cell->set(value);
      cell->clear_all_options();
      if (this->add_value(board_index + 1)) {
        return true;
      }
      cell->unset();
    }
  }
  return false;
}

atn::Position atn::Recursive::get_position(uint board_index) const {
  return Position{board_index % 9u, board_index / 9u};
}

std::vector<atn::Value> atn::Recursive::get_shuffled_values() {
  std::vector<Value> values;
  std::copy(this->_values.begin(), this->_values.end(),
            std::back_inserter(values));
  std::shuffle(values.begin(), values.end(), this->_rng);
  return values;
}

bool atn::Recursive::safe_to_add(Value value, Position position) const {
  CellGroup aoe = this->_board->area_of_effect(position);
  if (this->cell_group_contains(aoe, value)) {
    return false;
  }
  return true;
}

atn::Value value_from_cell_ptr(atn::CellPtr cell) { return cell->get(); }

bool atn::Recursive::cell_group_contains(CellGroup cell_group,
                                         Value value) const {
  std::vector<Value> values;
  values.resize(cell_group.size());
  std::transform(cell_group.begin(), cell_group.end(), values.begin(),
                 value_from_cell_ptr);
  return std::find(values.begin(), values.end(), value) != std::end(values);
}
