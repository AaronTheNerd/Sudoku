#pragma once

#include <vector>
#include <unordered_set>

#include "cell.h"

namespace atn {

class CellGroup {
 public:
  CellGroup();
  using const_iterator = std::vector<CellPtr>::const_iterator;

  void insert(CellPtr);

  const_iterator find(CellPtr) const;
  bool includes(CellPtr) const;
  void erase(CellPtr);
  size_t size() const;
  const_iterator begin() const;
  const_iterator end() const;

  CellGroup operator||(const CellGroup&);
  CellGroup operator&&(const CellGroup&);
  CellPtr& operator[](const size_t);
 private:
  std::vector<CellPtr> _vector;
};

}  // namespace atn