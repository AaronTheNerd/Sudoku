#pragma once

#include <optional>
#include <unordered_map>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn::generator::logic {

enum class LineTestEnum { COLUMN, ROW, NONE };

class CandidateLines : public Technique {
 public:
  CandidateLines(atn::sudoku::BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_box(atn::sudoku::CellGroup) const;
  std::unordered_map<atn::sudoku::Value, atn::sudoku::CellGroup,
                     atn::sudoku::ValueHash>
      map_options_to_cells(atn::sudoku::CellGroup) const;
  LineTestEnum test_line(atn::sudoku::CellGroup) const;
  atn::sudoku::CellGroup find_affected_cells(LineTestEnum,
                                             atn::sudoku::CellGroup,
                                             atn::sudoku::Value) const;
  atn::sudoku::CellGroup get_cell_group(LineTestEnum,
                                        atn::sudoku::CellGroup) const;
  NextMove calculate_changes(atn::sudoku::CellGroup, atn::sudoku::Value) const;
};

}  // namespace atn::generator::logic
