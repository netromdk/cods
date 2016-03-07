#include <cassert>
#include <cstring> // memcpy
#include <utility> // swap

#include "cods/Global.h"
#include "cods/Utility.h"

CODS_BEGIN_NAMESPACE

/// Implementation of a container class similar to the std::vector.
template <typename T,        ///< Item type.
          int INIT_CAP = 64, ///< Initial capacity size.
          int CAP_MULT = 2>  ///< Capacity multiplier.
class Vector {
public:
  /// Create empty vector with no capacity.
  Vector() : items(0), cap(0), data(nullptr) { }

  /// Create vector filled with \p size elements of value \p val.
  Vector(int size, T val) : Vector() {
    alloc(size);
    for (decltype(size) i = 0; i < size; i++) {
      // Don't check capacity because we just allocated all. Will speed up a lot.
      _append(val, false);
    }
  }

  /// Create vector from the values of raw array \p values.
  Vector(int size, T *values) : Vector() {
    alloc(size);
    for (decltype(size) i = 0; i < size; i++) {
      _append(values[i], false);
    }
  }

  /// Create vector from iterator range.
  template <typename Iterator>
  Vector(Iterator first, Iterator last) : Vector() {
    for (; first != last; first++) {
      append(*first);
    }
  }

  ~Vector() {
    clear();
  }

  bool isEmpty() const {
    return items == 0;
  }

  int size() const {
    return items;
  }

  int capacity() const {
    return cap;
  }

  /// Insert value at the end.
  void append(const T &val) {
    _append(val);
  }

  /// Insert value at the beginning.
  void prepend(const T &val) {
    insert(0, val);
  }

  void insert(int pos, const T &val) {
    assert(pos >= 0 && pos < cap && "Position out of bounds!");
    checkAlloc();
    shiftLeft(pos); // Effectively moving right.
    data[pos] = val;
    items++;
  }

  void print() const {
    cout << "[ ";
    if (isEmpty()) {
      cout << "empty";
    }
    for (decltype(cap) i = 0; i < cap; i++) {
      cout << convert(data[i]);
      if (i < cap - 1) {
        cout << ", ";
      }
    }
    cout << " ]" << endl;
  }

  void clear() {
    if (data) {
      delete[] data;
      data = nullptr;
    }
    items = cap = 0;
  }

  void shrinkToFit() {
    if (items == cap) return;
    alloc(items);
  }

  T operator[](int pos) {
    assert(pos >= 0 && pos < cap && "Position out of bounds!");
    return data[pos];
  }

  const T &operator[](int pos) const {
    assert(pos >= 0 && pos < cap && "Position out of bounds!");
    return data[pos];
  }

  void remove(const T &val) {
    removeFrom(val);
  }

  void removeAt(int pos) {
    assert(pos >= 0 && pos < cap && "Position out of bounds!");
    data[pos] = T();
    items--;
    shiftRight(pos); // Effectively moving left.
  }

private:
  void fillDefault(T *ptr, int n) {
    for (decltype(n) i = 0; i < n; i++) {
      ptr[i] = T();
    }
  }

  void alloc(int size) {
    auto newCap = size;
    auto *newData = new T[newCap];
    if (newCap > cap) {
      fillDefault(newData, newCap);
    }
    if (items > 0) {
      memcpy(newData, data, items * sizeof(T));
      delete[] data;
    }
    data = newData;
    cap = newCap;
  }

  void checkAlloc() {
    if (items != cap) return;
    alloc(cap == 0 ? INIT_CAP : cap * CAP_MULT);
  }

  /// Appends value but only checks capacity if check is set.
  /** This saves processing time when appending very many items. */
  void _append(const T &val, bool check = true) {
    if (check) {
      checkAlloc();
    }
    data[items++] = val;
  }

  void shiftRight(int pos) {
    for (decltype(pos) i = pos; i < items; i++) {
      std::swap(data[i], data[i+1]);
    }
  }

  void shiftLeft(int pos) {
    for (decltype(pos) i = items; i >= pos; i--) {
      std::swap(data[i], data[i+1]);
    }
  }

  void removeFrom(const T &val, int pos = 0) {
    for (decltype(pos) i = pos; i < items; i++) {
      auto &item = data[i];
      if (item == val) {
        item = T(); // Clear.
        items--;
        shiftRight(i); // Effectively moving left.
        removeFrom(val, i);
        break;
      }
    }
  }

  int items, cap;
  T *data;
};

CODS_END_NAMESPACE
