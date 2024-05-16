#include "set_value.h"

atn::generator::removal::SetValue::SetValue(atn::sudoku::CellPtr cell,
                                            atn::sudoku::Value value)
    : _cell(cell), _value(value) {}

void atn::generator::removal::SetValue::apply() {
  this->_cell->set(this->_value);
}

void atn::generator::removal::SetValue::undo() { this->_cell->unset(); }