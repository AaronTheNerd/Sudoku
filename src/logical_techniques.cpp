// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_LOGICAL_TECHNIQUES_CPP_
#define _SRC_LOGICAL_TECHNIQUES_CPP_

#include "logical_techniques.h"
#include <algorithm>  // std::find
#include <array>      // std::array
#include <iostream>
#include <unordered_map>  // std::unordered_map
#include "utils.h"

namespace {}  // namespace

template <uint8_t T>
atn::LogicalTechnique<T>::LogicalTechnique(
    bool valid, LOGICAL_TECHNIQUE technique)
    : valid(valid), technique(technique) {}

template <uint8_t T>
atn::SingleCandidate<T>::SingleCandidate(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, SINGLE_CANDIDATE),
      pos(),
      value(atn::UNSET) {
  atn::Cell<T> curr_cell;
  for (uint8_t x = 0; x < T * T; ++x) {
    for (uint8_t y = 0; y < T * T; ++y) {
      curr_cell = puzzle.get({x, y});
      if (curr_cell.options.count() == 1 && curr_cell.value == atn::UNSET) {
        this->valid = true;
        for (uint8_t value = 1; value <= T * T; ++value) {
          if (curr_cell.options[value - 1]) {
            this->value = value;
            break;
          }
        }
        this->pos   = curr_cell.pos;
        this->valid = true;
        return;
      }
    }
  }
}

template <uint8_t T>
void atn::SingleCandidate<T>::apply(atn::Sudoku<T>& puzzle) const {
  puzzle.set(this->pos, this->value);
}

template <uint8_t T>
atn::SinglePosition<T>::SinglePosition(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, SINGLE_POSITION),
      pos(),
      value(atn::UNSET) {
  std::array<uint8_t, T * T> row_option_counts;
  std::array<uint8_t, T * T> column_option_counts;
  atn::Cell<T> row_cell, column_cell;
  for (uint8_t i = 0; i < T * T; ++i) {
    row_option_counts.fill(0);
    column_option_counts.fill(0);
    for (uint8_t j = 0; j < T * T; ++j) {
      column_cell = puzzle.get({i, j});
      row_cell    = puzzle.get({j, i});
      for (uint8_t value = 1; value <= T * T; ++value) {
        if (row_cell.options[value - 1] && row_cell.value == atn::UNSET)
          row_option_counts[value - 1]++;
        if (column_cell.options[value - 1] && column_cell.value == atn::UNSET)
          column_option_counts[value - 1]++;
      }
    }
    for (uint8_t value = 1; value <= T * T; ++value) {
      if (column_option_counts[value - 1] == 1) {
        this->valid = true;
        for (uint8_t j = 0; j < T * T; ++j) {
          column_cell = puzzle.get({i, j});
          if (column_cell.options[value - 1]) {
            this->pos   = column_cell.pos;
            this->value = value;
            return;
          }
        }
        return;
      }
      if (row_option_counts[value - 1] == 1) {
        this->valid = true;
        for (uint8_t j = 0; j < T * T; ++j) {
          row_cell = puzzle.get({j, i});
          if (row_cell.options[value - 1]) {
            this->pos   = row_cell.pos;
            this->value = value;
            return;
          }
        }
        return;
      }
    }
  }
}

template <uint8_t T>
void atn::SinglePosition<T>::apply(atn::Sudoku<T>& puzzle) const {
  puzzle.set(this->pos, this->value);
}

template <uint8_t T>
atn::CandidateLines<T>::CandidateLines(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, CANDIDATE_LINES),
      positions(),
      value(atn::UNSET),
      line(ROW) {
  uint8_t block_x, block_y, x, y;
  Pos curr_pos;
  Cell<T> curr_cell;
  std::vector<Pos> positions;
  std::unordered_map<uint8_t, std::vector<Pos>> valid_positions_of_option;
  for (uint8_t block_it = 0; block_it < T * T; ++block_it) {
    block_x                   = block_it / T;
    block_y                   = block_it % T;
    valid_positions_of_option = {};
    for (uint8_t it = 0; it < T * T; ++it) {
      x         = it / T;
      y         = it % T;
      curr_pos  = {block_x * T + x, block_y * T + y};
      curr_cell = puzzle.get(curr_pos);
      for (uint8_t value = 1; value <= T * T; ++value) {
        if (curr_cell.value == atn::UNSET && curr_cell.options[value - 1]) {
          valid_positions_of_option[value].emplace_back(curr_pos);
        }
      }
    }
    atn::BOARD_SPACE space;
    for (const auto& [value, positions] : valid_positions_of_option) {
      space = atn::utils::on_same_line(positions);
      if (space != atn::INVALID_SPACE) {  // TODO: Check for duplicate technique
        this->valid     = true;
        this->value     = value;
        this->positions = positions;
        this->line      = space;
        return;
      }
    }
  }
}

template <uint8_t T>
void atn::CandidateLines<T>::apply(atn::Sudoku<T>& puzzle) const {
  uint dx, dy, x0, y0;
  if (this->line == atn::ROW) {
    dx = 1;
    dy = 0;
    x0 = 0;
    y0 = this->positions[0].y;
  } else if (this->line == atn::COLUMN) {
    dx = 0;
    dy = 1;
    x0 = this->positions[0].x;
    y0 = 0;
  } else {
    return;
  }
  Pos curr_pos;
  for (uint8_t x = x0, y = y0; x < T * T && y < T * T; x += dx, y += dy) {
    curr_pos = {x, y};
    if (std::find(this->positions.begin(), this->positions.end(), curr_pos)
        == this->positions.end()) {
      puzzle.at(curr_pos).options[this->value - 1] = false;
    }
  }
}

template <uint8_t T>
atn::DoublePairs<T>::DoublePairs(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, DOUBLE_PAIRS),
      line(ROW),
      block_x(0),
      block_y(0),
      coord_to_keep(0) {}

template <uint8_t T>
void atn::DoublePairs<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::MultipleLines<T>::MultipleLines(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, MULTIPLE_LINES) {}

template <uint8_t T>
void atn::MultipleLines<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T, uint8_t N>
atn::NakedValueSubset<T, N>::NakedValueSubset(
    const atn::Sudoku<T>& puzzle, const atn::LOGICAL_TECHNIQUE technique)
    : atn::LogicalTechnique<T>(false, technique),
      space(ROW),
      positions(),
      values() {
  this->findRowSubset(puzzle);
  if (this->valid) return;
  this->findColumnSubset(puzzle);
  if (this->valid) return;
  this->findBlockSubset(puzzle);
}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::apply(atn::Sudoku<T>& puzzle) const {
  switch (this->space) {
    case ROW:
      return this->applyRowSubset(puzzle);
    case COLUMN:
      return this->applyColumnSubset(puzzle);
    case BLOCK:
      return this->applyBlockSubset(puzzle);
    default:
      throw std::runtime_error("Invalid space attempted to be applied");
  }
}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::findRowSubset(const atn::Sudoku<T>& puzzle) {
  atn::Pos curr_pos;
  uint8_t count;
  for (uint8_t y = 0; y < T * T; ++y) {
    count = 0;
    for (uint8_t x = 0; x < T * T; ++x) {
      curr_pos = {x, y};
      if (puzzle.get(curr_pos).options.count() > N) continue;
    }
  }
}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::findColumnSubset(
    const atn::Sudoku<T>& puzzle) {}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::findBlockSubset(
    const atn::Sudoku<T>& puzzle) {}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::applyRowSubset(atn::Sudoku<T>& puzzle) const {
}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::applyColumnSubset(
    atn::Sudoku<T>& puzzle) const {}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::applyBlockSubset(
    atn::Sudoku<T>& puzzle) const {}

template <uint8_t T, uint8_t N>
atn::HiddenValueSubset<T, N>::HiddenValueSubset(
    const atn::Sudoku<T>& puzzle, const atn::LOGICAL_TECHNIQUE technique)
    : atn::NakedValueSubset<T, N>(puzzle, technique) {}

template <uint8_t T, uint8_t N>
void atn::HiddenValueSubset<T, N>::apply(atn::Sudoku<T>&) const {}

template <uint8_t T>
atn::NakedPair<T>::NakedPair(const atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, 2>(puzzle, NAKED_PAIR) {}

template <uint8_t T>
atn::HiddenPair<T>::HiddenPair(const atn::Sudoku<T>& puzzle)
    : atn::HiddenValueSubset<T, 2>(puzzle, HIDDEN_PAIR) {}

template <uint8_t T>
atn::NakedTriple<T>::NakedTriple(const atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, 3>(puzzle, NAKED_TRIPLE) {}

template <uint8_t T>
atn::HiddenTriple<T>::HiddenTriple(const atn::Sudoku<T>& puzzle)
    : atn::HiddenValueSubset<T, 3>(puzzle, HIDDEN_TRIPLE) {}

template <uint8_t T>
atn::XWing<T>::XWing(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, X_WING),
      line(ROW),
      line1_coord(0),
      line2_coord(0) {}

template <uint8_t T>
void atn::XWing<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::ForcingChains<T>::ForcingChains(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, FORCING_CHAINS), invariables() {}

template <uint8_t T>
void atn::ForcingChains<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::NakedQuad<T>::NakedQuad(const atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, 4>(puzzle, NAKED_QUAD) {}

template <uint8_t T>
atn::HiddenQuad<T>::HiddenQuad(const atn::Sudoku<T>& puzzle)
    : atn::HiddenValueSubset<T, 4>(puzzle, HIDDEN_QUAD) {}

template <uint8_t T>
atn::Swordfish<T>::Swordfish(const atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, SWORDFISH), line(ROW), verticies() {}

template <uint8_t T>
void atn::Swordfish<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::LogicalTechniquePtr<T> atn::generate_ptr(
    const atn::Sudoku<T>& puzzle, const atn::LOGICAL_TECHNIQUE technique) {
  switch (technique) {
    case SINGLE_CANDIDATE:
      return std::make_shared<atn::SingleCandidate<T>>(puzzle);
    case SINGLE_POSITION:
      return std::make_shared<atn::SinglePosition<T>>(puzzle);
    case CANDIDATE_LINES:
      return std::make_shared<atn::CandidateLines<T>>(puzzle);
    case DOUBLE_PAIRS:
      return std::make_shared<atn::DoublePairs<T>>(puzzle);
    case MULTIPLE_LINES:
      return std::make_shared<atn::MultipleLines<T>>(puzzle);
    case NAKED_PAIR:
      return std::make_shared<atn::NakedPair<T>>(puzzle);
    case HIDDEN_PAIR:
      return std::make_shared<atn::HiddenPair<T>>(puzzle);
    case NAKED_TRIPLE:
      return std::make_shared<atn::NakedTriple<T>>(puzzle);
    case HIDDEN_TRIPLE:
      return std::make_shared<atn::HiddenTriple<T>>(puzzle);
    case X_WING:
      return std::make_shared<atn::XWing<T>>(puzzle);
    case FORCING_CHAINS:
      return std::make_shared<atn::ForcingChains<T>>(puzzle);
    case NAKED_QUAD:
      return std::make_shared<atn::NakedQuad<T>>(puzzle);
    case HIDDEN_QUAD:
      return std::make_shared<atn::HiddenQuad<T>>(puzzle);
    case SWORDFISH:
      return std::make_shared<atn::Swordfish<T>>(puzzle);
    default:
      throw std::invalid_argument("Unrecognized technique: " + technique);
  }
}

#endif  // _SRC_LOGICAL_TECHNIQUES_CPP_