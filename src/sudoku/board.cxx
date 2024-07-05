#include "board.h"

#include <unordered_set>

atn::sudoku::Board::Board(Board::Private) : _board() {
  this->initialize_board();
}

atn::sudoku::BoardPtr atn::sudoku::Board::create() {
  return std::make_shared<Board>(Board::Private());
}

atn::sudoku::BoardPtr atn::sudoku::Board::get_ptr() {
  return this->shared_from_this();
}

atn::sudoku::CellPtr atn::sudoku::Board::get(
    const atn::sudoku::Position& pos) const {
  return this->_board[pos.y()][pos.x()];
}

atn::sudoku::CellGroup atn::sudoku::Board::board() const {
  CellGroup group;
  for (uint y{0}; y < 9; ++y) {
    for (uint x{0}; x < 9; ++x) {
      atn::sudoku::Position position{x, y};
      group.push_back(this->get(position));
    }
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::row(uint y) const {
  CellGroup group;
  for (uint x{0}; x < 9; ++x) {
    atn::sudoku::Position position{x, y};
    group.push_back(this->get(position));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::column(uint x) const {
  CellGroup group;
  for (uint y{0}; y < 9; ++y) {
    atn::sudoku::Position position{x, y};
    group.push_back(this->get(position));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::box(uint box_x, uint box_y) const {
  CellGroup group;
  for (uint y{0}; y < 3; ++y) {
    for (uint x{0}; x < 3; ++x) {
      atn::sudoku::Position position{3 * box_x + x, 3 * box_y + y};
      group.push_back(this->get(position));
    }
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::area_of_effect(
    Position position) const {
  CellGroup group;
  std::unordered_set<Position, PositionHash> visited_positions;
  visited_positions.insert(position);
  CellGroup current_group;
  current_group = this->row(position.y());
  for (uint index{0}; index < current_group.size(); ++index) {
    atn::sudoku::CellPtr cell = current_group[index];
    if (visited_positions.contains(cell->position())) {
      continue;
    }
    visited_positions.insert(cell->position());
    group.push_back(cell);
  }
  current_group = this->column(position.x());
  for (uint index{0}; index < current_group.size(); ++index) {
    atn::sudoku::CellPtr cell = current_group[index];
    if (visited_positions.contains(cell->position())) {
      continue;
    }
    visited_positions.insert(cell->position());
    group.push_back(cell);
  }
  current_group = this->box(position.x() / 3, position.y() / 3);
  for (uint index{0}; index < current_group.size(); ++index) {
    atn::sudoku::CellPtr cell = current_group[index];
    if (visited_positions.contains(cell->position())) {
      continue;
    }
    visited_positions.insert(cell->position());
    group.push_back(cell);
  }
  return group;
}

void atn::sudoku::Board::initialize_board() {
  for (uint y{0}; y < 9u; ++y) {
    for (uint x{0}; x < 9u; ++x) {
      this->_board[y][x] =
          std::make_shared<atn::sudoku::Cell>(atn::sudoku::Position{x, y});
    }
  }
}
