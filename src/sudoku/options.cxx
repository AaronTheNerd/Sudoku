#include "options.h"

#include <bit>

atn::Options::Options(uint16_t bitset) : _bitset(bitset) {}

bool atn::Options::includes(atn::Value option) const {
  return (this->_bitset & (1 << option.value())) != 0;
}

void atn::Options::set(atn::Value option) {
  this->_bitset |= (1 << option.value());
}

void atn::Options::clear(atn::Value option) {
  this->_bitset &= ~(1 << option.value());
}

void atn::Options::clear_all() { this->_bitset = 0u; }

uint atn::Options::count() const { return std::popcount(this->_bitset); }
