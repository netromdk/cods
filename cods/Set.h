#ifndef CODS_SET_H
#define CODS_SET_H

#include "cods/Global.h"
#include "cods/HashMap.h"

CODS_BEGIN_NAMESPACE

/// Implementation of Set container where there can be no duplicate values.
template <typename T>
class Set {
  using Map = HashMap<T, bool>;

  template <bool IS_CONST = true>
  class _Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    using IterType =
      typename std::conditional<IS_CONST, typename Map::ConstIterator,
                                typename Map::Iterator>::type;
    using ValueType = const T&;

  public:
    _Iterator(IterType it);

    /// Conversion from non-const to const iterator.
    _Iterator(const _Iterator<false> &other);

    ValueType operator*() const;

    _Iterator &operator++(); // prefix
    _Iterator operator++(int); // postfix

    _Iterator &operator--();
    _Iterator operator--(int);

    bool operator==(const _Iterator &other) const;
    bool operator!=(const _Iterator &other) const;

    IterType iter() const;

  private:
    IterType it;
  };

public:
  using Iterator = _Iterator<false>;
  using ConstIterator = _Iterator<true>;

  Set();

  static Set fromVector(const Vector<T> &vector);

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  void clear();

  Iterator insert(const T &value);

  /// Returns true if a value was removed.
  bool remove(const T &value);

  void reserve(int capacity);
  void shrinkToFit();

  bool contains(const T &value) const;
  bool contains(const Set &other) const;

  /// Removes all items from this set that are not in \p other.
  Set &intersect(const Set<T> &other);

  /// Removes all items from this set that are in \p other.
  Set &subtract(const Set<T> &other);

  /// Adds each item from \p other that is not in this set.
  Set &unite(const Set<T> &other);

  Iterator find(const T &value);
  ConstIterator find(const T &value) const;

  Vector<T> values() const;
  Vector<T> toVector() const;

  Iterator erase(Iterator pos);

  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;

  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;

  Set &operator<<(const T &value);

  /// Intersection.
  Set &operator&(const Set &other);

  /// Subtraction.
  Set &operator-(const Set &other);

  /// Union.
  Set &operator+(const Set &other);

  bool operator==(const Set &other) const;
  bool operator!=(const Set &other) const;

private:
  // Only lookup on key is used, the bool is irrelevant.
  Map map;
};

#include "cods/Set.hpp"

CODS_END_NAMESPACE

#endif // CODS_SET_H
