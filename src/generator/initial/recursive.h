#pragma once

#include <random>

#include "../initial/generator.h"

namespace atn {

class Recursive : public InitialGenerator {
 public:
  BoardPtr generate();

  Recursive();

 private:
  void clear_board();
  bool add_value(uint);
  Position get_position(uint) const;
  std::vector<Value> get_shuffled_values();
  bool safe_to_add(Value, Position) const;
  bool cell_group_contains(CellGroup, Value) const;

  BoardPtr _board;
  std::default_random_engine _rng;

 protected:
  const std::vector<Value> _values{Value{1}, Value{2}, Value{3},
                                   Value{4}, Value{5}, Value{6},
                                   Value{7}, Value{8}, Value{9}};
};

}  // namespace atn
