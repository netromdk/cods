#ifndef CODS_HASH_MAP_H
#define CODS_HASH_MAP_H

#include "cods/Vector.h"

#include <utility> // pair
#include <cstddef> // size_t
#include <functional> // hash
#include <initializer_list>

namespace cods {

/// Implementation of a hash-table-based dictionary.
template <typename Key,      ///< Key type.
          typename T,        ///< Item type.
          int INIT_CAP = 64> ///< Initial capacity size.
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

  template <bool IS_CONST = true>
  class _Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    using PtrType =
      typename std::conditional<IS_CONST, const Vector<Bucket*>*, Vector<Bucket*>*>::type;
    using KeyType = const Key&;
    using ValueType = typename std::conditional<IS_CONST, const T&, T&>::type;

  public:
    _Iterator(PtrType vec, int pos);

    /// Conversion from non-const to const iterator.
    _Iterator(const _Iterator<false> &other);

    ValueType value() const;
    ValueType operator*();

    KeyType key() const;

    _Iterator &operator++(); // prefix
    _Iterator operator++(int); // postfix

    _Iterator &operator--();
    _Iterator operator--(int);

    bool operator==(const _Iterator &other) const;
    bool operator!=(const _Iterator &other) const;

    int pos() const;

  private:
    PtrType vec;
    int pos_;
  };

public:
  using Iterator = _Iterator<false>;
  using ConstIterator = _Iterator<true>;

  /// Create empty map with maximum capacity.
  HashMap();

  /// Create map with initializer list.
  HashMap(std::initializer_list<std::pair<Key, T>> args);

  /// Copy-constructor.
  HashMap(const HashMap &other);

  /// Move-constructor.
  HashMap(HashMap &&other);

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  int count() const;
  int count(const Key &key) const;

  Iterator insert(const Key &key, const T &value);
  Iterator insertMulti(const Key &key, const T &value);

  void remove(const Key &key);

  Key key(const T &value, const Key &defaultKey = Key()) const;
  Vector<Key> keys() const;

  T value(const Key &key, const T &defaultValue = T()) const;
  Vector<T> values() const;
  Vector<T> values(const Key &key) const;

  bool contains(const Key &key) const;

  void clear();

  void reserve(int capacity);
  void shrinkToFit();

  Iterator erase(Iterator pos);

  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;

  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;

  Iterator find(const Key &key);
  ConstIterator find(const Key &key) const;

  /// Returns reference to value pointed to by \p key.
  /** If it doesn't exist then a default-constructed value will be inserted with the \p key and a
      reference return to it. */
  T &operator[](const Key &key);

  T operator[](const Key &key) const;

  bool operator==(const HashMap &other) const;
  bool operator!=(const HashMap &other) const;

  HashMap &operator=(const HashMap &other);
  HashMap &operator=(HashMap &&other);

private:
  std::size_t hashIndex(const Key &key) const;
  void checkRehash();
  Iterator _insert(const Key &key, const T &value, bool multi = false);

  inline Iterator createIterator(int pos);
  inline ConstIterator createIterator(int pos) const;

  Vector<Bucket*> buckets;
  int items;
};

#include "cods/HashMap.hpp"

} // cods

#endif // CODS_HASH_MAP_H
