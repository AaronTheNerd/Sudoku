#include "board.h"

#include <sstream>
#include <unordered_set>

atn::Board::Board(Board::Private) : _board() { this->initialize_board(); }

atn::BoardPtr atn::Board::create() {
  return std::make_shared<Board>(Board::Private());
}

atn::BoardPtr atn::Board::get_ptr() { return this->shared_from_this(); }

atn::CellPtr atn::Board::get(const Position& pos) const {
  return this->_board[pos.y().value()][pos.x().value()];
}

atn::CellGroup atn::Board::board() const {
  CellGroup group;
  for (Index y{0}; y < 9; ++y) {
    for (Index x{0}; x < 9; ++x) {
      group.push_back(this->get({x, y}));
    }
  }
  return group;
}

atn::CellGroup atn::Board::row(Index y) const {
  CellGroup group;
  for (Index x{0}; x < 9; ++x) {
    group.push_back(this->get({x, y}));
  }
  return group;
}

atn::CellGroup atn::Board::column(Index x) const {
  CellGroup group;
  for (Index y{0}; y < 9; ++y) {
    group.push_back(this->get({x, y}));
  }
  return group;
}

atn::CellGroup atn::Board::box(BoxIndex box_x, BoxIndex box_y) const {
  CellGroup group;
  for (BoxIndex y{0}; y < 3; ++y) {
    for (BoxIndex x{0}; x < 3; ++x) {
      group.push_back(this->get(
          {Index::from_boxes(box_x, x), Index::from_boxes(box_y, y)}));
    }
  }
  return group;
}

atn::CellGroup atn::Board::area_of_effect(Position position) const {
  CellGroup group;
  std::unordered_set<Position, PositionHash> visited_positions;
  visited_positions.insert(position);
  CellGroup current_group;
  current_group = this->row(position.y());
  for (uint index{0}; index < current_group.size(); ++index) {
    CellPtr cell = current_group[index];
    if (visited_positions.contains(cell->position())) {
      continue;
    }
    visited_positions.insert(cell->position());
    group.push_back(cell);
  }
  current_group = this->column(position.x());
  for (uint index{0}; index < current_group.size(); ++index) {
    CellPtr cell = current_group[index];
    if (visited_positions.contains(cell->position())) {
      continue;
    }
    visited_positions.insert(cell->position());
    group.push_back(cell);
  }
  current_group = this->box(atn::BoxIndex::index_in_board(position.x()),
                            atn::BoxIndex::index_in_board(position.y()));
  for (uint index{0}; index < current_group.size(); ++index) {
    CellPtr cell = current_group[index];
    if (visited_positions.contains(cell->position())) {
      continue;
    }
    visited_positions.insert(cell->position());
    group.push_back(cell);
  }
  return group;
}

void atn::Board::initialize_board() {
  for (uint8_t y{0}; y < 9u; ++y) {
    for (uint8_t x{0}; x < 9u; ++x) {
      this->_board[y][x] = std::make_shared<Cell>(Position{x, y});
    }
  }
}
