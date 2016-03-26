#ifndef CODS_VECTOR_H
#define CODS_VECTOR_H

#include <vector>
#include <iterator>
#include <type_traits> // conditional
#include <initializer_list>

#include "cods/Global.h"
#include "cods/Utility.h"

CODS_BEGIN_NAMESPACE

/// Implementation of a container class similar to the std::vector.
template <typename T,        ///< Item type.
          int INIT_CAP = 64> ///< Initial capacity size.
class Vector {
  /// Const and non-const iterator class.
  template <bool IS_CONST = true>
  class _Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    using PtrType = typename std::conditional<IS_CONST, const Vector*, Vector*>::type;
    using ValueType = typename std::conditional<IS_CONST, const T&, T&>::type;

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

  /// Create empty vector with no capacity.
  Vector();

  /// Create vector with initializer list.
  Vector(std::initializer_list<T> args);

  /// Copy-constructor.
  Vector(const Vector &other);

  /// Move-constructor.
  Vector(Vector &&other);

  /// Create vector filled with \p size elements of value \p val.
  Vector(int size, T val);

  /// Create vector from the values of raw array \p values.
  Vector(int size, T *values);

  /// Create vector from iterator range.
  template <typename Iter>
  Vector(Iter first, Iter last);

  ~Vector();

  bool isEmpty() const;
  int size() const;
  int capacity() const;

  T &at(int pos);
  const T &at(int pos) const;

  /// Insert value at the end.
  void append(const T &val);

  /// Insert values at the end.
  void append(const Vector &vals);

  /// Insert value at the beginning.
  void prepend(const T &val);

  void insert(int pos, const T &value);
  Iterator insert(Iterator before, const T &value);

  bool contains(const T &val) const;

  int indexOf(const T &value, int from = 0) const;
  int lastIndexOf(const T &value, int from = -1) const;

  void print() const;

  void clear();

  void reserve(int capacity);
  void shrinkToFit();

  void remove(const T &val);
  void removeFirst();
  void removeLast();
  void removeAt(int pos);

  T takeFirst();
  T takeLast();
  T takeAt(int pos);

  /// Erase iterator and return iterator to next value or \p end().
  Iterator erase(Iterator pos);

  Iterator begin();
  ConstIterator begin() const;
  ConstIterator cbegin() const;

  Iterator end();
  ConstIterator end() const;
  ConstIterator cend() const;

  std::vector<T> toStdVector() const;

  T &operator[](int pos);
  const T &operator[](int pos) const;

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

  bool operator==(const Vector &other) const;
  bool operator!=(const Vector &other) const;

  Vector &operator=(const Vector &other);
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
  T *data;
};

#include "cods/Vector.hpp"

CODS_END_NAMESPACE

/// Define hashing of the Vector class.
namespace std {
  template <typename T>
  struct hash<CODS_NAMESPACE::Vector<T>> {
    std::size_t operator()(const CODS_NAMESPACE::Vector<T> &vec) const {
      std::size_t res = 0;
      auto size = vec.size();
      for (decltype(size) i = 0; i < size; i++) {
        res ^= (std::hash<T>()(vec[i]) << i);
      }
      return res;
    }
  };
}

#endif // CODS_VECTOR_H
