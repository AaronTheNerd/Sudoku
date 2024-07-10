#pragma once

#include <optional>
#include <unordered_map>

#include "board.h"
#include "macro_command.h"
#include "technique.h"

namespace atn::generator::logic {

using namespace atn::sudoku;
using namespace atn::generator::logic;
using namespace atn::generator::command;

enum class LineTestEnum { COLUMN, ROW, NONE };

class CandidateLines : public Technique {
 public:
  CandidateLines(BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_box(CellGroup) const;
  std::unordered_map<Value, std::vector<CellPtr>, ValueHash>
      map_options_to_cells(CellGroup) const;
  LineTestEnum test_line(std::vector<CellPtr>) const;
  std::vector<CellPtr> find_affected_cells(LineTestEnum, std::vector<CellPtr>,
                                           Value) const;
  CellGroup get_cell_group(LineTestEnum, std::vector<CellPtr>) const;
  NextMove calculate_changes(std::vector<CellPtr>, Value) const;
};

}  // namespace atn::generator::logic
