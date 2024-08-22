#pragma once

#include <optional>

#include "board.h"
#include "line_box_view.h"
#include "technique.h"

namespace atn {

class CandidateBox : public Technique {
 public:
  CandidateBox(BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_line(Index, Line) const;
  std::optional<NextMove> search_line_at_value(Index, Line, Value) const;
  std::array<std::bitset<3>, 2> get_other_bitsets(Index, Line, Value) const;
  bool would_have_changes(std::array<std::bitset<3>, 2>, std::bitset<3>) const;
  BoxIndex get_change_index(std::bitset<3>) const;
  NextMove calculate_changes(Index, Line, Value, BoxIndex) const;
  NextMove calculate_changes_row(Index, Value, BoxIndex) const;
  NextMove calculate_changes_column(Index, Value, BoxIndex) const;

  LineBoxView view;
};

}  // namespace atn
