#ifndef CODS_VECTOR_H
#define CODS_VECTOR_H

#include <iterator>

#include "cods/Global.h"
#include "cods/Utility.h"

CODS_BEGIN_NAMESPACE

/// Implementation of a container class similar to the std::vector.
template <typename T,        ///< Item type.
          int INIT_CAP = 64, ///< Initial capacity size.
          int CAP_MULT = 2>  ///< Capacity multiplier.
class Vector {
public:
  /// Iterator for Vector.
  class Iterator : public std::iterator<std::output_iterator_tag, T> {
  public:
    Iterator(Vector *vec, int pos);

    T &operator*();
    T *operator->();
    Iterator &operator++();
    Iterator operator++(int i);

    friend bool operator==(Iterator lhs, Iterator rhs) {
      return lhs.pos == rhs.pos;
    }

    friend bool operator!=(Iterator lhs, Iterator rhs) {
      return !(lhs == rhs);
    }

  private:
    Vector *vec;
    int pos;
  };

  /// Create empty vector with no capacity.
  Vector();

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

  /// Insert value at the end.
  void append(const T &val);

  /// Insert value at the beginning.
  void prepend(const T &val);

  void insert(int pos, const T &val);

  bool contains(const T &val) const;

  void print() const;

  void clear();

  void reserve(int capacity);
  void shrinkToFit();

  void remove(const T &val);
  void removeAt(int pos);

  Iterator begin();
  Iterator begin() const;
  Iterator cbegin() const;

  Iterator end();
  Iterator end() const;
  Iterator cend() const;

  T &operator[](int pos);
  const T &operator[](int pos) const;

  /// Append value to the vector.
  Vector &operator<<(const T &value);

  bool operator==(const Vector &other) const;
  bool operator!=(const Vector &other) const;

  Vector &operator=(const Vector &other);

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

  int items, cap;
  T *data;
};

#include "cods/Vector.hpp"

CODS_END_NAMESPACE

/// Define hashing of the Vector class.
namespace std {
  template <typename T>
  struct hash<cods::Vector<T>> {
    std::size_t operator()(const cods::Vector<T> &vec) const {
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
