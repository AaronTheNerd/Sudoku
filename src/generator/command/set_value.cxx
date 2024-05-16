#include "set_value.h"

atn::generator::command::SetValue::SetValue(atn::sudoku::CellPtr cell,
                                            atn::sudoku::Value value)
    : _cell(cell), _value(value) {}

void atn::generator::command::SetValue::apply() {
  this->_cell->set(this->_value);
}

void atn::generator::command::SetValue::undo() { this->_cell->unset(); }