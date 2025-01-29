#include "cell_group.h"

#include <algorithm>

atn::CellGroup::CellGroup(): _vector() {}

void atn::CellGroup::insert(atn::CellPtr cell) {
  if (this->includes(cell)) return;
  this->_vector.push_back(cell);
}

atn::CellGroup::const_iterator atn::CellGroup::find(atn::CellPtr cell) const {
  return std::find(this->_vector.begin(), this->_vector.end(), cell);
}

bool atn::CellGroup::includes(atn::CellPtr cell) const {
  return this->find(cell) != this->end();
}

void atn::CellGroup::erase(atn::CellPtr cell) {
  if (!this->includes(cell)) return;
  this->_vector.erase(this->find(cell));
}

size_t atn::CellGroup::size() const {
  return this->_vector.size();
}

atn::CellGroup::const_iterator atn::CellGroup::begin() const {
  return this->_vector.begin();
}

atn::CellGroup::const_iterator atn::CellGroup::end() const {
  return this->_vector.end();
}

atn::CellGroup atn::CellGroup::operator||(const atn::CellGroup& rhs) {
  atn::CellGroup result;
  for (auto it = this->_vector.begin(); it != this->_vector.end(); ++it) {
    result.insert(*it);
  }
  for (auto it = rhs._vector.begin(); it != rhs._vector.end(); ++it) {
    result.insert(*it);
  }
  return result;
}

atn::CellGroup atn::CellGroup::operator&&(const atn::CellGroup& rhs) {
  atn::CellGroup result;
  for (auto it = this->_vector.begin(); it != this->_vector.end(); ++it) {
    if (rhs.includes(*it)) {
      result.insert(*it);
    }
  }
  return result;
}

atn::CellPtr& atn::CellGroup::operator[](const size_t index) {
  return this->_vector[index];
}
