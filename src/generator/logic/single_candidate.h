#pragma once

#include <exception>
#include <string>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn::generator::logic {

class SingleCandidate : public Technique {
 public:
  SingleCandidate(atn::sudoku::BoardPtr);

 private:
  void find_next_move();
  void calculate_changes(atn::sudoku::CellPtr);
  atn::sudoku::Value calculate_set_value(atn::sudoku::CellPtr) const;
  atn::generator::command::MacroCommand calculate_aoe_changes(
      atn::sudoku::CellPtr, atn::sudoku::Value) const;
};

class MissingOption : public std::exception {
 public:
  MissingOption(atn::sudoku::Position) noexcept;
  const char* what() const noexcept;

 private:
  std::string message;
};

}  // namespace atn::generator::logic
