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

  private:
    IterType it;
  };

public:
  using Iterator = _Iterator<false>;
  using ConstIterator = _Iterator<true>;

  Set();

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  void clear();

  // TODO: return iterator when implemented.
  void insert(const T &value);

  /// Returns true if a value was removed.
  bool remove(const T &value);

  void reserve(int capacity);
  void shrinkToFit();

  bool contains(const T &val) const;
  bool contains(const Set &other) const;

  Vector<T> values() const;
  Vector<T> toVector() const;

  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;

  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;

  Set &operator<<(const T &value);

private:
  // Only lookup on key is used, the bool is irrelevant.
  Map map;
};

#include "cods/Set.hpp"

CODS_END_NAMESPACE

#endif // CODS_SET_H
