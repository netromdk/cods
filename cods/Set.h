#ifndef CODS_SET_H
#define CODS_SET_H

#include "cods/Global.h"
#include "cods/HashMap.h"

CODS_BEGIN_NAMESPACE

/// Implementation of Set container where there can be no duplicate values.
template <typename T>
class Set {
public:
  Set();

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  // TODO: return iterator when implemented.
  void insert(const T &value);

  /// Returns true if a value was removed.
  bool remove(const T &value);

  Vector<T> values() const;
  Vector<T> toVector() const;

  Set &operator<<(const T &value);

private:
  // Only lookup on key is used, the bool is irrelevant.
  HashMap<T, bool> map;
};

#include "cods/Set.hpp"

CODS_END_NAMESPACE

#endif // CODS_SET_H
