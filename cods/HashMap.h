#ifndef CODS_HASH_MAP_H
#define CODS_HASH_MAP_H

#include "cods/Global.h"
#include "cods/Vector.h"

#include <cstddef> // size_t

CODS_BEGIN_NAMESPACE

/// Implementation of a hash-table-based dictionary.
template <typename Key,      ///< Key type.
          typename T,        ///< Item type.
          int INIT_CAP = 64, ///< Initial capacity size.
          int CAP_MULT = 2>  ///< Capacity multiplier.
class HashMap {
  class Bucket {
  public:
    Bucket(const Key &key, const T &value);

    void setValue(const T &value);
    void addValue(const T &value);

    const Key &key() const;
    T &value();
    const T &value() const;
    const Vector<T> &values() const;

  private:
    Key key_;
    Vector<T> values_;
  };

public:
  /// Create empty map with maximum capacity.
  HashMap();

  /// Copy-constructor.
  HashMap(const HashMap &other);

  /// Move-constructor.
  HashMap(HashMap &&other);

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  void insert(const Key &key, const T &value);
  void insertMulti(const Key &key, const T &value);

  void remove(const Key &key);

  Key key(const T &value) const;
  Key key(const T &value, const Key &defaultKey) const;

  Vector<Key> keys() const;

  T value(const Key &key) const;

  /// If \p key is not contained then \p defaultValue is returned.
  T value(const Key &key, const T &defaultValue) const;

  Vector<T> values() const;
  Vector<T> values(const Key &key) const;

  bool contains(const Key &key) const;

  void clear();

  void reserve(int capacity);
  void shrinkToFit();

  /// Returns reference to value pointed to by \p key.
  /** If it doesn't exist then a default-constructed value will be inserted with the \p key and a
      reference return to it. */
  T &operator[](const Key &key);

  T operator[](const Key &key) const;

  bool operator==(const HashMap &other) const;
  bool operator!=(const HashMap &other) const;

private:
  std::size_t hashIndex(const Key &key) const;
  void checkRehash();
  void _insert(const Key &key, const T &value, bool multi = false);

  Vector<Bucket*, INIT_CAP, CAP_MULT> buckets;
  int items;
};

#include "cods/HashMap.hpp"

CODS_END_NAMESPACE

#endif // CODS_HASH_MAP_H
