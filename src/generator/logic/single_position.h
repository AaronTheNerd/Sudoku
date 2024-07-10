#pragma once

#include <optional>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn::generator::logic {

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

struct GroupSearchResult {
  CellPtr cell;
  Value value;
};

class SinglePosition : public Technique {
 public:
  SinglePosition(BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_all_rows() const;
  std::optional<NextMove> search_all_columns() const;
  std::optional<NextMove> search_all_boxes() const;
  std::optional<GroupSearchResult> search_group(const CellGroup&) const;
  NextMove calculate_changes(GroupSearchResult) const;
  MacroCommand calculate_aoe_changes(CellPtr, Value) const;
};

}  // namespace atn::generator::logic
