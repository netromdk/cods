#ifndef CODS_VECTOR_H
#define CODS_VECTOR_H

#include <cassert>
#include <cstring> // memcpy
#include <initializer_list>
#include <iostream> // cout, endl
#include <iterator>
#include <type_traits> // conditional
#include <utility>     // swap
#include <vector>

#include "cods/Utility.h"

namespace cods {

/// Container class similar to \p std::vector.
/** The template typename \p T denotes the element type of the container and the initial capacity is
    set to \p INIT_CAP. */
template <typename T, int INIT_CAP = 64>
class Vector {
  /// Const and non-const iterator class.
  template <bool IS_CONST = true>
  class _Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    using PtrType = typename std::conditional<IS_CONST, const Vector *, Vector *>::type;
    using ValueType = typename std::conditional<IS_CONST, const T &, T &>::type;

  public:
    _Iterator(PtrType vec, int pos);

    /// Conversion from non-const to const iterator.
    _Iterator(const _Iterator<false> &other);

    ValueType operator*();
    PtrType operator->();

    _Iterator &operator++();
    _Iterator operator++(int);

    _Iterator &operator--();
    _Iterator operator--(int);

    _Iterator operator+(int) const;
    _Iterator &operator+=(int);

    int operator-(const _Iterator &other) const;
    _Iterator operator-(int pos) const;

    bool operator==(const _Iterator &other) const;
    bool operator!=(const _Iterator &other) const;

    bool operator<(const _Iterator &other) const;
    bool operator<=(const _Iterator &other) const;

    bool operator>(const _Iterator &other) const;
    bool operator>=(const _Iterator &other) const;

    int pos() const;

  private:
    PtrType vec;
    int pos_;
  };

public:
  using Iterator = _Iterator<false>;
  using ConstIterator = _Iterator<true>;

  /// Create empty vector with no capacity.
  Vector();

  /// Create vector with initializer list.
  Vector(std::initializer_list<T> args);

  /// Copy-constructor.
  Vector(const Vector &other);

  /// Move-constructor.
  Vector(Vector &&other);

  /// Create vector filled with \p size elements of \p value.
  Vector(int size, T value);

  /// Create vector from the values of raw array \p values.
  Vector(int size, T *values);

  /// Create vector from iterator range.
  template <typename Iter>
  Vector(Iter first, Iter last);

  ~Vector();

  /// Returns \p true if vector has size \p 0, otherwise \p false.
  bool isEmpty() const;

  /// Returns the number of elements in the vector.
  int size() const;

  /// Returns the number of elements the vector can contain.
  int capacity() const;

  /// Returns the element at \p pos.
  //@{
  T &at(int pos);
  const T &at(int pos) const;
  //@}

  /// Insert \p value at the end.
  void append(const T &value);

  /// Insert \p values at the end.
  void append(const Vector &values);

  /// Insert \p value at the beginning.
  void prepend(const T &value);

  /// Insert \p value at \p pos.
  void insert(int pos, const T &value);

  /// Insert \p value before iterator \p before.
  Iterator insert(Iterator before, const T &value);

  /// Check if vector contains \p value.
  bool contains(const T &value) const;

  /// Returns the first index of \p value found in the vector starting at \p from.
  /** If nothing is found then it returns \p -1. */
  int indexOf(const T &value, int from = 0) const;

  /// Returns the last index of \p value found starting from \p from.
  /** If nothing is found then it returns \p -1. */
  int lastIndexOf(const T &value, int from = -1) const;

  /// Print vector to stdout.
  void print() const;

  /// Clear and empty vector.
  void clear();

  /// Reserve room for \p capacity elements.
  void reserve(int capacity);

  /// Shrink vector capacity to match the number of elements it contains.
  void shrinkToFit();

  /// Remove \p value from vector
  void remove(const T &value);

  /// Remove first element from vector.
  void removeFirst();

  /// Remove last element from vector.
  void removeLast();

  /// Remove element at \p pos from vector.
  void removeAt(int pos);

  /// Remove first element from vector and return it.
  /** Assumes vector is not empty! */
  T takeFirst();

  /// Remove last element from vector and return it.
  /** Assumes vector is not empty! */
  T takeLast();

  /// Remove element at \p pos from vector and return it.
  /** Assumes vector is not empty! */
  T takeAt(int pos);

  /// Erase iterator and return iterator to next value or \p end().
  Iterator erase(Iterator pos);

  /// Returns iterator to beginning of vector.
  //@{
  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;
  //@}

  /// Returns iterator to end of vector.
  //@{
  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;
  //@}

  /// Returns pointer to internal data.
  //@{
  T *data();
  const T *data() const;
  const T *constData() const;
  //@}

  /// Returns \p std::vector<T> of elements of the vector.
  std::vector<T> toStdVector() const;

  /// Access element at \p pos.
  //@{
  T &operator[](int pos);
  const T &operator[](int pos) const;
  //@}

  /// Append value to the vector.
  Vector &operator<<(const T &value);

  /// Append values to the vector.
  Vector &operator<<(const Vector &values);

  /// Append value to the vector.
  Vector &operator+=(const T &value);

  /// Append values to the vector.
  Vector &operator+=(const Vector &other);

  /// Returns vector with the values of this vector appended the ones from \p other.
  Vector operator+(const Vector &other);

  /// Returns \p true if all values are equal to those in \p other and in the same order.
  bool operator==(const Vector &other) const;

  /// Returns \p true if all values are not equal to those in \p other or are not in the same order.
  bool operator!=(const Vector &other) const;

  /// Copy-assigns \p other to \p this.
  Vector &operator=(const Vector &other);

  /// Move-assigns \p other to \p this.
  Vector &operator=(Vector &&other);

private:
  void fillDefault(T *ptr, int n);
  void alloc(int size);
  void checkAlloc();

  /// Appends value but only checks capacity if check is set.
  /** This saves processing time when appending very many items. */
  void _append(const T &val, bool check = true);

  void shiftRight(int pos);
  void shiftLeft(int pos);

  void removeFrom(const T &val, int pos = 0);

  inline Iterator createIterator(int pos);
  inline ConstIterator createIterator(int pos) const;

  int items, cap;
  T *data_;
};

#include "cods/Vector.hpp"

} // namespace cods

/// Define hashing of the Vector class.
namespace std {

template <typename T>
struct hash<cods::Vector<T>> {
  std::size_t operator()(const cods::Vector<T> &vec) const
  {
    std::size_t res = 0;
    auto size = vec.size();
    for (decltype(size) i = 0; i < size; i++) {
      res ^= (std::hash<T>()(vec[i]) << i);
    }
    return res;
  }
};

} // namespace std

#endif // CODS_VECTOR_H
