#pragma once

#include <array>
#include <bitset>

#include "board.h"
#include "value.h"

namespace atn {

enum class Line : uint { ROW = 0, COLUMN = 3 * 9 };

class LineBoxView {
 public:
  LineBoxView(atn::BoardPtr);

  uint count_boxes(atn::Value, atn::Line, atn::Index) const;
  std::bitset<3> box_bitset(atn::Value, atn::Line, atn::Index) const;

 private:
  void initialize_view(atn::BoardPtr);
  void add_cell_options(atn::CellPtr);
  void add_option(atn::Position, atn::Value);
  size_t line_offset(atn::Line, atn::Index) const;

  std::array<std::bitset<3 * 18>, 9> _lines;
};

}  // namespace atn
