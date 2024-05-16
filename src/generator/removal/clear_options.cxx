#include "clear_options.h"

atn::generator::removal::ClearOptions::ClearOptions(
    atn::sudoku::CellPtr cell, std::vector<atn::sudoku::Value> options)
    : _cell(cell), _options(options) {}

void atn::generator::removal::ClearOptions::apply() {
  for (auto it = this->_options.begin(); it != this->_options.end(); ++it) {
    this->_cell->clear_option(*it);
  }
}

void atn::generator::removal::ClearOptions::undo() {
  for (auto it = this->_options.begin(); it != this->_options.end(); ++it) {
    this->_cell->set_option(*it);
  }
}
