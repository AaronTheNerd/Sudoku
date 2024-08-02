#include "set_value.h"

atn::SetValue::SetValue(CellPtr cell, Value value)
    : _cell(cell), _value(value) {}

void atn::SetValue::apply() { this->_cell->set(this->_value); }

void atn::SetValue::undo() { this->_cell->unset(); }