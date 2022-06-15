// Written by Aaron Barge
// Copyright 2022

#ifndef _SRC_LOGICAL_TECHNIQUES_CPP_
#define _SRC_LOGICAL_TECHNIQUES_CPP_

#include "logical_techniques.h"
#include <array>  // std::array

namespace {}  // namespace

template <uint8_t T>
atn::LogicalTechnique<T>::LogicalTechnique(
    bool valid, LOGICAL_TECHNIQUE technique)
    : valid(valid), technique(technique) {}

template <uint8_t T>
atn::SingleCandidate<T>::SingleCandidate(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, SINGLE_CANDIDATE),
      pos(),
      value(atn::UNSET) {
  atn::Cell<T> curr_cell;
  for (uint8_t x = 0; x < T * T; ++x) {
    for (uint8_t y = 0; y < T * T; ++y) {
      curr_cell = puzzle.at({x, y});
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
atn::SinglePosition<T>::SinglePosition(atn::Sudoku<T>& puzzle)
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
      column_cell = puzzle.at({i, j});
      row_cell    = puzzle.at({j, i});
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
          column_cell = puzzle.at({i, j});
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
          row_cell = puzzle.at({j, i});
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
atn::CandidateLines<T>::CandidateLines(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, CANDIDATE_LINES),
      pos(),
      value(atn::UNSET),
      line(ROW) {}

template <uint8_t T>
void atn::CandidateLines<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::DoublePairs<T>::DoublePairs(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, DOUBLE_PAIRS),
      line(ROW),
      block_x(0),
      block_y(0),
      coord_to_keep(0) {}

template <uint8_t T>
void atn::DoublePairs<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::MultipleLines<T>::MultipleLines(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, MULTIPLE_LINES) {}

template <uint8_t T>
void atn::MultipleLines<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T, uint8_t N>
atn::NakedValueSubset<T, N>::NakedValueSubset(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, INVALID),
      space(ROW),
      positions(),
      values() {}

template <uint8_t T, uint8_t N>
void atn::NakedValueSubset<T, N>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T, uint8_t N>
atn::HiddenValueSubset<T, N>::HiddenValueSubset(atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, N>(puzzle) {}

template <uint8_t T, uint8_t N>
void atn::HiddenValueSubset<T, N>::apply(atn::Sudoku<T>&) const {}

template <uint8_t T>
atn::NakedPair<T>::NakedPair(atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, 2>(puzzle) {
  this->technique = NAKED_PAIR;
}

template <uint8_t T>
atn::HiddenPair<T>::HiddenPair(atn::Sudoku<T>& puzzle)
    : atn::HiddenValueSubset<T, 2>(puzzle) {
  this->technique = HIDDEN_PAIR;
}

template <uint8_t T>
atn::NakedTriple<T>::NakedTriple(atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, 3>(puzzle) {
  this->technique = NAKED_TRIPLE;
}

template <uint8_t T>
atn::HiddenTriple<T>::HiddenTriple(atn::Sudoku<T>& puzzle)
    : atn::HiddenValueSubset<T, 3>(puzzle) {
  this->technique = HIDDEN_TRIPLE;
}

template <uint8_t T>
atn::XWing<T>::XWing(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, X_WING),
      line(ROW),
      line1_coord(0),
      line2_coord(0) {}

template <uint8_t T>
void atn::XWing<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::ForcingChains<T>::ForcingChains(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, FORCING_CHAINS), invariables() {}

template <uint8_t T>
void atn::ForcingChains<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::NakedQuad<T>::NakedQuad(atn::Sudoku<T>& puzzle)
    : atn::NakedValueSubset<T, 4>(puzzle) {
  this->technique = NAKED_QUAD;
}

template <uint8_t T>
atn::HiddenQuad<T>::HiddenQuad(atn::Sudoku<T>& puzzle)
    : atn::HiddenValueSubset<T, 4>(puzzle) {
  this->technique = HIDDEN_QUAD;
}

template <uint8_t T>
atn::Swordfish<T>::Swordfish(atn::Sudoku<T>& puzzle)
    : atn::LogicalTechnique<T>(false, SWORDFISH), line(ROW), verticies() {}

template <uint8_t T>
void atn::Swordfish<T>::apply(atn::Sudoku<T>& puzzle) const {}

template <uint8_t T>
atn::LogicalTechniquePtr<T> atn::generate_ptr(
    atn::Sudoku<T>& puzzle, LOGICAL_TECHNIQUE technique) {
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
  }
}

#endif  // _SRC_LOGICAL_TECHNIQUES_CPP_