#pragma once

#include <optional>

#include "board.h"
#include "line_box_view.h"
#include "technique.h"

namespace atn {

class DoublePairs : public Technique {
 public:
  DoublePairs(BoardPtr);

 private:
  void find_next_move();
  std::optional<NextMove> search_box_group(BoxIndex, Line) const;
  std::optional<NextMove> search_box_group_at_value(BoxIndex, Line,
                                                    Value) const;
  std::array<std::bitset<3>, 3> get_all_bitsets(BoxIndex, Line, Value) const;
  std::optional<BoxIndex> excluded_index(std::array<std::bitset<3>, 3>) const;
  bool technique_applicable(std::array<std::bitset<3>, 3>, BoxIndex) const;
  BoxIndex get_change_index(std::bitset<3>) const;
  NextMove calculate_changes(BoxIndex, Line, Value, BoxIndex, BoxIndex) const;
  NextMove calculate_changes_row(BoxIndex, Value, BoxIndex, BoxIndex) const;
  NextMove calculate_changes_column(BoxIndex, Value, BoxIndex, BoxIndex) const;
  
  LineBoxView view;
};

}  // namespace atn
