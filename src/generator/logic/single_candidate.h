#pragma once

#include <exception>
#include <string>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn::generator::logic {

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

class SingleCandidate : public Technique {
 public:
  SingleCandidate(BoardPtr);
  std::optional<NextMove> get_next_move();

 private:
  void find_next_move();
  void calculate_changes(CellPtr);
  Value calculate_set_value(CellPtr) const;
  MacroCommand calculate_aoe_changes(CellPtr, Value) const;

  std::optional<NextMove> _next_move;
  BoardPtr _board;
};

class MissingOption : public std::exception {
 public:
  MissingOption(Position) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn::generator::logic
