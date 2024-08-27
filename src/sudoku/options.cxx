#include "options.h"

#include <bit>

atn::Options::Options(std::bitset<9> bitset) : _bitset(bitset) {}

bool atn::Options::includes(atn::Value option) const {
  return this->_bitset.test(option.value() - 1);
}

void atn::Options::set(atn::Value option) {
  this->_bitset.set(option.value() - 1);
}

void atn::Options::clear(atn::Value option) {
  this->_bitset.reset(option.value() - 1);
}

void atn::Options::clear_all() { this->_bitset.reset(); }

uint atn::Options::count() const { return this->_bitset.count(); }

std::bitset<9> atn::Options::bitset() const { return this->_bitset; }
