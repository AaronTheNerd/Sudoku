#pragma once

#include <optional>
#include <unordered_map>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn {

enum class LineTestEnum { COLUMN, ROW, NONE };

class CandidateLines : public Technique {
 public:
  CandidateLines(BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_box(CellGroup) const;
  std::unordered_map<Value, CellGroup, ValueHash> map_options_to_cells(
      CellGroup) const;
  LineTestEnum test_line(CellGroup) const;
  CellGroup find_affected_cells(LineTestEnum, CellGroup, Value) const;
  CellGroup get_cell_group(LineTestEnum, CellGroup) const;
  CellGroup remove_cells(CellGroup, CellGroup) const;
  NextMove calculate_changes(CellGroup, Value) const;
};

}  // namespace atn
