#pragma once

#include <memory>

#include "options.h"
#include "position.h"
#include "value.h"

namespace atn {

class Cell {
 public:
  Cell(Position = {0, 0});
  Cell(Position, Value);

  Position position() const;
  bool is_set() const;
  void set(Value);
  Value unset();
  Value get() const;
  bool has_option(Value) const;
  void set_option(Value);
  void clear_option(Value);
  void clear_all_options();
  uint count_options() const;

 private:
  Position _position;
  Value _value;
  Options _options;
};

typedef std::shared_ptr<Cell> CellPtr;

}  // namespace atn