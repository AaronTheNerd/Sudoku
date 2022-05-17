// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_SUDOKU_CPP_
#define _SRC_SUDOKU_CPP_

#include <sstream> // std::stringstream
#include "sudoku.h"

template<uint8_t T>
atn::Cell<T>::Cell(): value(atn::UNSET), pos({0, 0}), options() {
  this->options.set();
}

template<uint8_t T>
atn::Cell<T>::Cell(atn::Pos pos): value(atn::UNSET), pos(pos), options() {
  this->options.set();
}

template<uint8_t T>
bool atn::Cell<T>::invalid() const {
  return this->options.count() == 0 && this->value == atn::UNSET;
}

template<uint8_t T>
bool atn::Cell<T>::compare_options(const atn::Cell<T>& c1, const atn::Cell<T>& c2) {
  return c1.options.count() < c2.options.count();
}

template<uint8_t T>
void atn::Sudoku<T>::initialize_cell_width() {
  std::string max_cell = std::to_string(T * T);
  this->cell_width = max_cell.size() + 1;
}

template<uint8_t T>
void atn::Sudoku<T>::initialize_blank_board() {
  for (uint8_t y = 0; y < T * T; ++y) {
    for (uint8_t x = 0; x < T * T; ++x) {
      this->board[x][y] = atn::Cell<T>({x, y});
    }
  }
}

template<uint8_t T>
bool atn::Sudoku<T>::propogate_block(atn::Pos p, uint8_t val) {
  uint8_t block_x = p.x / T;
  uint8_t block_y = p.y / T;
  for (uint8_t y = 0; y < T; ++y) {
    for (uint8_t x = 0; x < T; ++x) {
      this->board[block_x * T + x][block_y * T + y].options.reset(val - 1);
      if (this->board[block_x * T + x][block_y * T + y].invalid())
        return false;
    }
  }
  return true;
}

template<uint8_t T>
bool atn::Sudoku<T>::propogate(atn::Pos p, uint8_t val) {
  for (uint8_t i = 0; i < T * T; ++i) {
    this->board[p.x][i].options.reset(val - 1);
    if (this->board[p.x][i].invalid())
      return false;
    this->board[i][p.y].options.reset(val - 1);
    if (this->board[i][p.y].invalid())
      return false;
  }
  return this->propogate_block(p, val);
}

template<uint8_t T>
bool atn::Sudoku<T>::validate_row() const {
  std::bitset<T * T> row_options;
  std::bitset<T * T> row_contains;
  for (uint8_t y = 0; y < T * T; ++y) {
    row_options.reset();
    row_contains.reset();
    for (uint8_t x = 0; x < T * T; ++x) {
      if (this->board[x][y].value != atn::UNSET) {
        row_contains.set(this->board[x][y].value - 1);
      } else {
        row_options |= this->board[x][y].options;
      }
    }
    for (uint8_t i = 0; i < T * T; ++i) {
      if (!row_contains[i] && !row_options[i])
        return false;
    }
  }
  return true;
}

template<uint8_t T>
bool atn::Sudoku<T>::validate_column() const {
  std::bitset<T * T> column_options;
  std::bitset<T * T> column_contains;
  for (uint8_t x = 0; x < T * T; ++x) {
    column_options.reset();
    column_contains.reset();
    for (uint8_t y = 0; y < T * T; ++y) {
      if (this->board[x][y].value != atn::UNSET) {
        column_contains.set(this->board[x][y].value - 1);
      } else {
        column_options |= this->board[x][y].options;
      }
    }
    for (uint8_t i = 0; i < T * T; ++i) {
      if (!column_contains[i] && !column_options[i])
        return false;
    }
  }
  return true;
}

template<uint8_t T>
bool atn::Sudoku<T>::validate_block() const {
  std::bitset<T * T> block_options;
  std::bitset<T * T> block_contains;
  for (uint8_t i = 0; i < T * T; ++i) {
    uint8_t block_x = i / T;
    uint8_t block_y = i % T;
    block_options.reset();
    block_contains.reset();
    for (uint8_t y = 0; y < T; ++y) {
      for (uint8_t x = 0; x < T; ++x) {
        if (this->board[block_x * T + x][block_y * T + y].value != atn::UNSET) {
        block_contains.set(this->board[block_x * T + x][block_y * T + y].value - 1);
      } else {
        block_options |= this->board[block_x * T + x][block_y * T + y].options;
      }
      }
    }
  }
  return true;
}

template<uint8_t T>
std::bitset<T * T> atn::Sudoku<T>::contains_row_column(atn::Pos pos) {
  std::bitset<T * T> contains;
  uint8_t value;
  for (uint8_t i = 0; i < T * T; ++i) {
    value = this->get({pos.x, i}).value;
    if (value != atn::UNSET) {
      contains.set(value - 1);
    }
    value = this->get({i, pos.y}).value;
    if (value != atn::UNSET) {
      contains.set(value - 1);
    }
  }
  return contains;
}

template<uint8_t T>
std::bitset<T * T> atn::Sudoku<T>::contains_block(uint8_t x_block, uint8_t y_block) {
  std::bitset<T * T> contains_block;
  uint8_t value;
  for (uint8_t x = 0; x < T; ++x) {
    for (uint8_t y = 0; y < T; ++y) {
      value = this->get({x_block * T + x, y_block * T + y}).value;
      if (value != atn::UNSET) {
        contains_block.set(value - 1);
      }
    }
  }
  return contains_block;
}

template<uint8_t T>
atn::Sudoku<T>::Sudoku(): cell_width(0), board() {
  this->initialize_cell_width();
  this->initialize_blank_board();
}

template<uint8_t T>
atn::Cell<T>& atn::Sudoku<T>::at(atn::Pos pos) {
  return this->board[pos.x][pos.y];
}

template<uint8_t T>
atn::Cell<T> atn::Sudoku<T>::get(atn::Pos pos) const {
  return this->board[pos.x][pos.y];
}

template<uint8_t T>
bool atn::Sudoku<T>::set(atn::Pos pos, uint8_t val) {
  this->board[pos.x][pos.y].value = val;
  if (val != atn::UNSET) {
    this->board[pos.x][pos.y].options.reset();
    return this->propogate(pos, val);
  } else {
    this->fix_options();
    return true;
  }
}

template<uint8_t T>
void atn::Sudoku<T>::unset(atn::Pos pos) {
  this->board[pos.x][pos.y].value = atn::UNSET;
  this->board[pos.x][pos.y].options.reset();
}

template<uint8_t T>
void atn::Sudoku<T>::fix_options() {
  for (uint8_t x = 0; x < T * T; ++x) {
    for (uint8_t y = 0; y < T * T; ++y) {
      atn::Cell<T>& cell = this->at({x, y});
      cell.options.reset();
      if (cell.value == atn::UNSET) {
        cell.options |= this->contains_row_column(cell.pos).flip();
        cell.options |= this->contains_block(x / T, y / T).flip();
      }
    }
  }
}

template<uint8_t T>
std::vector<atn::Cell<T>> atn::Sudoku<T>::get_empty_cells() {
  std::vector<atn::Cell<T>> empty_cells;
  for (uint8_t x = 0; x < T * T; ++x) {
    for (uint8_t y = 0; y < T * T; ++y) {
      atn::Cell<T> cell = this->at({x, y});
      if (cell.value == atn::UNSET) empty_cells.emplace_back(cell);
    }
  }
  return empty_cells;
}

template<uint8_t T>
bool atn::Sudoku<T>::validate() const {
  if (!this->validate_row()) return false;
  if (!this->validate_column()) return false;
  if (!this->validate_block()) return false;
  return true;
}

template<uint8_t T>
std::string atn::Sudoku<T>::to_str() const {
  std::stringstream ss;
  ss << std::string(this->cell_width + 1, ' ');
  for (uint8_t x = 1; x <= T * T; ++x) {
    std::string col_indicator = std::to_string(x);
    ss << col_indicator
        << std::string(this->cell_width - col_indicator.size(), ' ');
  }
  ss << "\n\n";
  for (uint8_t y = 0; y < T * T; ++y) {
    std::string row_indicator = std::to_string(y + 1);
    ss << row_indicator
        << std::string(this->cell_width - row_indicator.size() + 1, ' ');
    for (uint8_t x = 0; x < T * T; ++x) {
      uint8_t cell_val = this->get({x, y}).value;
      std::string cell_str = std::to_string(cell_val);
      if (cell_val == atn::UNSET)
        ss << std::string(this->cell_width - 1, ' ');
      else ss << cell_str
          << std::string(this->cell_width - cell_str.size() - 1, ' ');
      if ((x + 1) % T == 0 && x + 1 != T * T) ss << "|";
      else ss << " ";
    }
    ss << "\n";
    if ((y + 1) % T == 0 && y + 1 != T * T) {
      ss << std::string(this->cell_width + 1, ' ');
      for (uint8_t i = 0; i < T; ++i) {
        ss << std::string(T * this->cell_width - 1, '-');
        if (i + 1 != T)
          ss << "+";
      }
      ss << "\n";
    }
  }
  return ss.str();
}

#endif // _SRC_SUDOKU_CPP_
