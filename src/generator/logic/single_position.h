#pragma once

#include <optional>

#include "board.h"
#include "cell_group.h"
#include "technique.h"
#include "macro_command.h"

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
  SinglePosition(Board);
  std::optional<NextMove> get_next_move();

 private:
  void find_next_move();
  std::optional<NextMove> search_all_rows() const;
  std::optional<NextMove> search_all_columns() const;
  std::optional<NextMove> search_all_boxes() const;
  std::optional<GroupSearchResult> search_group(const CellGroup&) const;
  NextMove calculate_changes(GroupSearchResult) const;
  MacroCommand calculate_aoe_changes(CellPtr, Value) const;

  std::optional<NextMove> _next_move;
  CellGroupFactory _factory;
};

}  // namespace atn::generator::logic
