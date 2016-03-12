#ifndef CODS_HASH_MAP_H
#define CODS_HASH_MAP_H

#include "cods/Global.h"
#include "cods/Vector.h"

#include <utility> // tuple
#include <cstddef> // size_t

CODS_BEGIN_NAMESPACE

/// Implementation of a hash-table-based dictionary.
template <typename Key,      ///< Key type.
          typename T,        ///< Item type.
          int INIT_CAP = 64, ///< Initial capacity size.
          int CAP_MULT = 2>  ///< Capacity multiplier.
class HashMap {
  using Value = std::tuple<Key, T, bool>;

public:
  HashMap();

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  void insert(const Key &key, const T &value);
  void remove(const Key &key);

  T value(const Key &key) const;

  /// If \p key is not contained then \p defaultValue is returned.
  T value(const Key &key, const T &defaultValue) const;

  Vector<Key> keys() const;
  Vector<T> values() const;

  bool contains(const Key &key) const;

  void clear();

  void reserve(int capacity);
  void shrinkToFit();

private:
  Value defaultValue() const;
  std::size_t hashIndex(const Key &key) const;
  void checkRehash();

  Vector<Value, INIT_CAP, CAP_MULT> buckets;
  int items;
};

#include "cods/HashMap.hpp"

CODS_END_NAMESPACE

#endif // CODS_HASH_MAP_H
