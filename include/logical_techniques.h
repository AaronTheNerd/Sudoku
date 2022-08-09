// Written by Aaron Barge
// Copyright 2022

#ifndef _INCLUDE_LOGICAL_TECHNIQUES_H_
#define _INCLUDE_LOGICAL_TECHNIQUES_H_

#include <cstddef>        // uint8_t, uint16_t
#include <memory>         // std::shared_ptr
#include <unordered_map>  // std::unordered_map
#include <vector>         // std::vector
#include "sudoku.h"

namespace atn {

// Enumerations

enum LOGICAL_TECHNIQUE : uint8_t {
  SINGLE_CANDIDATE = 0,
  SINGLE_POSITION,
  CANDIDATE_LINES,
  DOUBLE_PAIRS,
  MULTIPLE_LINES,
  NAKED_PAIR,
  HIDDEN_PAIR,
  NAKED_TRIPLE,
  HIDDEN_TRIPLE,
  X_WING,
  FORCING_CHAINS,
  NAKED_QUAD,
  HIDDEN_QUAD,
  SWORDFISH,
  LAST_TECHNIQUE,
  INVALID_TECHNIQUE
};

// Structs

template <uint8_t T>
struct LogicalTechnique {
  bool valid = false;
  LOGICAL_TECHNIQUE technique;
  virtual void apply(atn::Sudoku<T> &) const = 0;

 protected:
  LogicalTechnique(bool, LOGICAL_TECHNIQUE);
};

/*
 * This technique is used when there is one option
 * for a value at a specific position
 */
template <uint8_t T>
struct SingleCandidate : public LogicalTechnique<T> {
  atn::Pos pos;
  uint8_t value;
  SingleCandidate(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

/*
 * This technique is used when there is one possible
 * position for a specific value in a row, column, or block
 */
template <uint8_t T>
struct SinglePosition : public LogicalTechnique<T> {
  atn::Pos pos;
  uint8_t value;
  SinglePosition(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

/*
 * This technique is used when all positions of a specific
 * value in a block lie on the same line
 */
template <uint8_t T>
struct CandidateLines : public LogicalTechnique<T> {
  std::vector<atn::Pos> positions;
  uint8_t value;
  BOARD_SPACE line;
  CandidateLines(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct DoublePairs : public LogicalTechnique<T> {
  BOARD_SPACE line;
  uint8_t block_x;
  uint8_t block_y;
  uint8_t coord_to_keep;
  DoublePairs(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct MultipleLines : public LogicalTechnique<T> {
  // I'll be honest idk what this one is
  MultipleLines(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

/*
 * This technique is used when there are some x number of positions
 * which only contain x unique options in some constrained space
 */
template <uint8_t T, uint8_t N>
struct NakedValueSubset : public LogicalTechnique<T> {
  BOARD_SPACE space;
  std::vector<atn::Pos> positions;
  std::vector<uint8_t> values;
  NakedValueSubset(const atn::Sudoku<T> &, const LOGICAL_TECHNIQUE);
  void apply(atn::Sudoku<T> &) const;

 private:
  void findRowSubset(const atn::Sudoku<T> &);
  void findColumnSubset(const atn::Sudoku<T> &);
  void findBlockSubset(const atn::Sudoku<T> &);
  void applyRowSubset(atn::Sudoku<T> &) const;
  void applyColumnSubset(atn::Sudoku<T> &) const;
  void applyBlockSubset(atn::Sudoku<T> &) const;

 protected:
  void getNextCombination(
      std::vector<uint8_t> &, const std::vector<atn::Pos>) const;
};

template <uint8_t T, uint8_t N>
struct HiddenValueSubset : public NakedValueSubset<T, N> {
  HiddenValueSubset(const atn::Sudoku<T> &, const LOGICAL_TECHNIQUE);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct NakedPair : public NakedValueSubset<T, 2> {
  NakedPair(const atn::Sudoku<T> &);
};

template <uint8_t T>
struct HiddenPair : public HiddenValueSubset<T, 2> {
  HiddenPair(const atn::Sudoku<T> &);
};

template <uint8_t T>
struct NakedTriple : public NakedValueSubset<T, 3> {
  NakedTriple(const atn::Sudoku<T> &);
};

template <uint8_t T>
struct HiddenTriple : public HiddenValueSubset<T, 3> {
  HiddenTriple(const atn::Sudoku<T> &);
};

template <uint8_t T>
struct XWing : public LogicalTechnique<T> {
  BOARD_SPACE line;
  uint8_t line1_coord, line2_coord;
  XWing(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct ForcingChains : public LogicalTechnique<T> {
  std::vector<SingleCandidate<T>> invariables;
  ForcingChains(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct NakedQuad : public NakedValueSubset<T, 4> {
  NakedQuad(const atn::Sudoku<T> &);
};

template <uint8_t T>
struct HiddenQuad : public HiddenValueSubset<T, 4> {
  HiddenQuad(const atn::Sudoku<T> &);
};

template <uint8_t T>
struct Swordfish : public LogicalTechnique<T> {
  BOARD_SPACE line;
  std::vector<atn::Pos> verticies;
  Swordfish(const atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

// Typedefs

template <uint8_t T>
using LogicalTechniquePtr = std::shared_ptr<LogicalTechnique<T>>;

// Functions

template <uint8_t T>
LogicalTechniquePtr<T> generate_ptr(
    const atn::Sudoku<T> &, const atn::LOGICAL_TECHNIQUE);

}  // namespace atn

#include "../src/logical_techniques.cpp"

#endif  // _INCLUDE_LOGICAL_TECHNIQUES_H_
