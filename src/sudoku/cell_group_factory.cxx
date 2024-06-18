#include "cell_group_factory.h"

#include <unordered_set>

atn::sudoku::CellGroupFactory::CellGroupFactory(atn::sudoku::Board& board)
    : _board(board) {}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::board() const {
  CellGroup group;
  for (uint y{0}; y < 9; ++y) {
    for (uint x{0}; x < 9; ++x) {
      atn::sudoku::Position position{x, y};
      group.push_back(this->_board.get(position));
    }
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::row(uint y) const {
  CellGroup group;
  for (uint x{0}; x < 9; ++x) {
    atn::sudoku::Position position{x, y};
    group.push_back(this->_board.get(position));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::column(uint x) const {
  CellGroup group;
  for (uint y{0}; y < 9; ++y) {
    atn::sudoku::Position position{x, y};
    group.push_back(this->_board.get(position));
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::box(uint box_x,
                                                          uint box_y) const {
  CellGroup group;
  for (uint y{0}; y < 3; ++y) {
    for (uint x{0}; x < 3; ++x) {
      atn::sudoku::Position position{3 * box_x + x, 3 * box_y + y};
      group.push_back(this->_board.get(position));
    }
  }
  return group;
}

atn::sudoku::CellGroup atn::sudoku::CellGroupFactory::area_of_effect(atn::sudoku::Position position) const {
  CellGroup group;
  std::unordered_set<atn::sudoku::Position, atn::sudoku::PositionHash> visited_positions;
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