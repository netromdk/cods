#ifndef CODS_HASH_MAP_H
#define CODS_HASH_MAP_H

#include "cods/Global.h"
#include "cods/Vector.h"

#include <utility> // pair
#include <cstddef> // size_t

CODS_BEGIN_NAMESPACE

template <typename Key, typename T>
class HashMap {
  using ValuePair = std::pair<Key, T>;
  using IndexPair = std::pair<std::size_t, int>; // hash -> index

public:
  HashMap();

  void insert(const Key &key, const T &value);
  T value(const Key &key) const;

private:
  // TODO: Use a Set here instead of a Vector!
  Vector<ValuePair> valuePairs; // (key, value), ..
  Vector<IndexPair> indexPairs; // (hash, index), ..
};

#include "cods/HashMap.hpp"

CODS_END_NAMESPACE

#endif // CODS_HASH_MAP_H
