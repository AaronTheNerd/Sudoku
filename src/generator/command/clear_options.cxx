#include "clear_options.h"

atn::ClearOptions::ClearOptions(CellPtr cell, std::vector<Value> options)
    : _cell(cell), _options(options) {}

void atn::ClearOptions::apply() {
  for (auto it = this->_options.begin(); it != this->_options.end(); ++it) {
    this->_cell->clear_option(*it);
  }
}

void atn::ClearOptions::undo() {
  for (auto it = this->_options.begin(); it != this->_options.end(); ++it) {
    this->_cell->set_option(*it);
  }
}
