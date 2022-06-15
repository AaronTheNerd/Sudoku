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

enum BOARD_SPACE : uint8_t { ROW, COLUMN, BLOCK };

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
  INVALID
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

template <uint8_t T>
struct SingleCandidate : public LogicalTechnique<T> {
  atn::Pos pos;
  uint8_t value;
  SingleCandidate(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct SinglePosition : public LogicalTechnique<T> {
  atn::Pos pos;
  uint8_t value;
  SinglePosition(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct CandidateLines : public LogicalTechnique<T> {
  atn::Pos pos;
  uint8_t value;
  BOARD_SPACE line;
  CandidateLines(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct DoublePairs : public LogicalTechnique<T> {
  BOARD_SPACE line;
  uint8_t block_x;
  uint8_t block_y;
  uint8_t coord_to_keep;
  DoublePairs(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct MultipleLines : public LogicalTechnique<T> {
  // I'll be honest idk what this one is
  MultipleLines(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T, uint8_t N>
struct NakedValueSubset : public LogicalTechnique<T> {
  BOARD_SPACE space;
  std::array<atn::Pos, N> positions;
  std::array<uint8_t, N> values;
  NakedValueSubset(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T, uint8_t N>
struct HiddenValueSubset : public NakedValueSubset<T, N> {
  HiddenValueSubset(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct NakedPair : public NakedValueSubset<T, 2> {
  NakedPair(atn::Sudoku<T> &);
};

template <uint8_t T>
struct HiddenPair : public HiddenValueSubset<T, 2> {
  HiddenPair(atn::Sudoku<T> &);
};

template <uint8_t T>
struct NakedTriple : public NakedValueSubset<T, 3> {
  NakedTriple(atn::Sudoku<T> &);
};

template <uint8_t T>
struct HiddenTriple : public HiddenValueSubset<T, 3> {
  HiddenTriple(atn::Sudoku<T> &);
};

template <uint8_t T>
struct XWing : public LogicalTechnique<T> {
  BOARD_SPACE line;
  uint8_t line1_coord, line2_coord;
  XWing(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct ForcingChains : public LogicalTechnique<T> {
  std::vector<SingleCandidate<T>> invariables;
  ForcingChains(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

template <uint8_t T>
struct NakedQuad : public NakedValueSubset<T, 4> {
  NakedQuad(atn::Sudoku<T> &);
};

template <uint8_t T>
struct HiddenQuad : public HiddenValueSubset<T, 4> {
  HiddenQuad(atn::Sudoku<T> &);
};

template <uint8_t T>
struct Swordfish : public LogicalTechnique<T> {
  BOARD_SPACE line;
  std::vector<atn::Pos> verticies;
  Swordfish(atn::Sudoku<T> &);
  void apply(atn::Sudoku<T> &) const;
};

struct StepDifficulty {
  uint16_t bonus;
  uint16_t per_uses;
};

// Constant variable

static const std::unordered_map<LOGICAL_TECHNIQUE, StepDifficulty>
    TECHNIQUE_DIFFICULTY = {{SINGLE_CANDIDATE, {0, 100}},
        {SINGLE_POSITION, {0, 100}}, {CANDIDATE_LINES, {150, 200}},
        {DOUBLE_PAIRS, {250, 250}}, {MULTIPLE_LINES, {300, 400}},
        {NAKED_PAIR, {250, 500}}, {HIDDEN_PAIR, {300, 1200}},
        {NAKED_TRIPLE, {600, 1400}}, {HIDDEN_TRIPLE, {800, 1600}},
        {X_WING, {1200, 1600}}, {FORCING_CHAINS, {2100, 2100}},
        {NAKED_QUAD, {1000, 4000}}, {HIDDEN_QUAD, {2000, 5000}},
        {SWORDFISH, {2000, 6000}}};

// Typedefs

template <uint8_t T>
using LogicalTechniquePtr = std::shared_ptr<LogicalTechnique<T>>;

// Functions

template <uint8_t T>
LogicalTechniquePtr<T> generate_ptr(atn::Sudoku<T> &, LOGICAL_TECHNIQUE);

}  // namespace atn

#include "../src/logical_techniques.cpp"

#endif  // _INCLUDE_LOGICAL_TECHNIQUES_H_
