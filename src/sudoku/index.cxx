#include "index.h"

#include <sstream>

atn::Index::Index(uint8_t index) : _index(index) {}

bool atn::Index::operator==(const atn::Index& rhs) const {
  return this->_index == rhs._index;
}

bool atn::Index::operator!=(const atn::Index& rhs) const {
  return this->_index != rhs._index;
}

bool atn::Index::operator<(const atn::Index& rhs) const {
  return this->_index < rhs._index;
}

atn::Index& atn::Index::operator++() {
  this->_index += 1;
  return *this;
}

uint8_t atn::Index::value() const {
  if (this->is_invalid()) {
    throw atn::InvalidIndexValueException{this->_index};
  }
  return this->_index;
}

bool atn::Index::is_invalid() const { return this->_index >= 9u; }

std::string atn::Index::to_string() const {
  std::stringstream ss;
  ss << (int)this->_index;
  return ss.str();
}

atn::BoxIndex::BoxIndex(uint8_t index) : Index(index) {}

bool atn::BoxIndex::is_invalid() const { return this->_index >= 3u; }

atn::BoxIndex atn::BoxIndex::index_in_box(atn::Index index) {
  return atn::BoxIndex{index.value() % 3};
}

atn::BoxIndex atn::BoxIndex::index_in_board(atn::Index index) {
  return atn::BoxIndex{index.value() / 3};
}

atn::InvalidIndexValueException::InvalidIndexValueException(
    uint8_t index) noexcept {
  std::stringstream ss;
  ss << "Invalid index received: " << (int)index;
  this->message = ss.str();
}

const char* atn::InvalidIndexValueException::what() const noexcept {
  return this->message.c_str();
}
