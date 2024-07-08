#include "board.h"

#include <sstream>
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
  return this->_board[pos.y().value()][pos.x().value()];
}

atn::sudoku::CellGroup atn::sudoku::Board::board() const {
  CellGroup group;
  for (atn::sudoku::Index y{0}; y < 9; ++y) {
    for (atn::sudoku::Index x{0}; x < 9; ++x) {
      group.push_back(this->get({x, y}));
    }
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::row(atn::sudoku::Index y) const {
  CellGroup group;
  for (atn::sudoku::Index x{0}; x < 9; ++x) {
    group.push_back(this->get({x, y}));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::column(atn::sudoku::Index x) const {
  CellGroup group;
  for (atn::sudoku::Index y{0}; y < 9; ++y) {
    group.push_back(this->get({x, y}));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::Board::box(
    atn::sudoku::BoxIndex box_x, atn::sudoku::BoxIndex box_y) const {
  CellGroup group;
  for (atn::sudoku::BoxIndex y{0}; y < 3; ++y) {
    for (atn::sudoku::BoxIndex x{0}; x < 3; ++x) {
      group.push_back(this->get(
          {3 * box_x.value() + x.value(), 3 * box_y.value() + y.value()}));
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
  current_group = this->box(position.x().value() / 3, position.y().value() / 3);
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
  for (uint8_t y{0}; y < 9u; ++y) {
    for (uint8_t x{0}; x < 9u; ++x) {
      this->_board[y][x] =
          std::make_shared<atn::sudoku::Cell>(atn::sudoku::Position{x, y});
    }
  }
}

