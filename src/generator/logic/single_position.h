#pragma once

#include <optional>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn::generator::logic {

struct GroupSearchResult {
  atn::sudoku::CellPtr cell;
  atn::sudoku::Value value;
};

class SinglePosition : public Technique {
 public:
  SinglePosition(atn::sudoku::BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_all_rows() const;
  std::optional<NextMove> search_all_columns() const;
  std::optional<NextMove> search_all_boxes() const;
  std::optional<GroupSearchResult> search_group(
      const atn::sudoku::CellGroup&) const;
  NextMove calculate_changes(GroupSearchResult) const;
  atn::generator::command::MacroCommand calculate_aoe_changes(
      atn::sudoku::CellPtr, atn::sudoku::Value) const;
};

}  // namespace atn::generator::logic
