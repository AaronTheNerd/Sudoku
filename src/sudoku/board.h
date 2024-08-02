#pragma once

#include <array>
#include <memory>

namespace atn {
class Board;
typedef std::shared_ptr<Board> BoardPtr;
}  // namespace atn

#include "cell.h"
#include "cell_group.h"
#include "position.h"

namespace atn {

class Board : public std::enable_shared_from_this<Board> {
 private:
  struct Private {
    explicit Private() = default;
  };

 public:
  Board(Private);
  static BoardPtr create();
  BoardPtr get_ptr();

  CellPtr get(const Position&) const;

  CellGroup board() const;
  CellGroup row(Index) const;
  CellGroup column(Index) const;
  CellGroup box(BoxIndex, BoxIndex) const;
  CellGroup area_of_effect(Position) const;

 private:
  void initialize_board();

  std::array<std::array<CellPtr, 9>, 9> _board;
};

}  // namespace atn