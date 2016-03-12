#include <cassert>
#include <cstring>  // memcpy
#include <utility>  // swap
#include <iostream> // cout, endl

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT>::Vector() : items(0), cap(0), data(nullptr) { }

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT>::Vector(const Vector &other) : Vector() {
  auto size = other.size();
  alloc(size);
  for (decltype(size) i = 0; i < size; i++) {
    // Don't check capacity because we just allocated all. Will speed up a lot.
    _append(other[i], false);
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT>::Vector(Vector &&other) : Vector() {
  data = other.data;
  items = other.items;
  cap = other.cap;

  // Nullify original container.
  other.data = nullptr;
  other.items = other.cap = 0;
}

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT>::Vector(int size, T val) : Vector() {
  alloc(size);
  for (decltype(size) i = 0; i < size; i++) {
    _append(val, false);
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT>::Vector(int size, T *values) : Vector() {
  alloc(size);
  for (decltype(size) i = 0; i < size; i++) {
    _append(values[i], false);
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
template <typename Iterator>
Vector<T, INIT_CAP, CAP_MULT>::Vector(Iterator first, Iterator last) : Vector() {
  for (; first != last; first++) {
    append(*first);
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT>::~Vector() {
  clear();
}

template <typename T, int INIT_CAP, int CAP_MULT>
bool Vector<T, INIT_CAP, CAP_MULT>::isEmpty() const {
  return items == 0;
}

template <typename T, int INIT_CAP, int CAP_MULT>
int Vector<T, INIT_CAP, CAP_MULT>::size() const {
  return items;
}

template <typename T, int INIT_CAP, int CAP_MULT>
int Vector<T, INIT_CAP, CAP_MULT>::capacity() const {
  return cap;
}

/// Insert value at the end.
template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::append(const T &val) {
  _append(val);
}

/// Insert value at the beginning.
template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::prepend(const T &val) {
  insert(0, val);
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::insert(int pos, const T &val) {
  checkAlloc();
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  shiftLeft(pos); // Effectively moving right.
  data[pos] = val;
  items++;
}

template <typename T, int INIT_CAP, int CAP_MULT>
bool Vector<T, INIT_CAP, CAP_MULT>::contains(const T &val) const {
  for (decltype(items) i = 0; i < items; i++) {
    if (data[i] == val) {
      return true;
    }
  }
  return false;
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::print() const {
  using namespace std;
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

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::clear() {
  if (data) {
    delete[] data;
    data = nullptr;
  }
  items = cap = 0;
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::reserve(int cap_) {
  if (cap >= cap_) return;
  alloc(cap_);
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::shrinkToFit() {
  if (items == cap) return;
  alloc(items);
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::remove(const T &val) {
  removeFrom(val);
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::removeAt(int pos) {
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  data[pos] = T();
  items--;
  shiftRight(pos); // Effectively moving left.
}

template <typename T, int INIT_CAP, int CAP_MULT>
T &Vector<T, INIT_CAP, CAP_MULT>::operator[](int pos) {
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  return data[pos];
}

template <typename T, int INIT_CAP, int CAP_MULT>
const T &Vector<T, INIT_CAP, CAP_MULT>::operator[](int pos) const {
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  return data[pos];
}

template <typename T, int INIT_CAP, int CAP_MULT>
Vector<T, INIT_CAP, CAP_MULT> &Vector<T, INIT_CAP, CAP_MULT>::operator<<(const T &value) {
  append(value);
  return *this;
}

template <typename T, int INIT_CAP, int CAP_MULT>
bool Vector<T, INIT_CAP, CAP_MULT>::operator==(const Vector &other) const {
  if (items != other.size()) {
    return false;
  }
  for (decltype(items) i = 0; i < items; i++) {
    if (data[i] != other[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, int INIT_CAP, int CAP_MULT>
bool Vector<T, INIT_CAP, CAP_MULT>::operator!=(const Vector &other) const {
  return !(*this == other);
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::fillDefault(T *ptr, int n) {
  for (decltype(n) i = 0; i < n; i++) {
    ptr[i] = T();
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::alloc(int size) {
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

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::checkAlloc() {
  if (items != cap) return;
  alloc(cap == 0 ? INIT_CAP : cap * CAP_MULT);
}

/// Appends value but only checks capacity if check is set.
/** This saves processing time when appending very many items. */
template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::_append(const T &val, bool check) {
  if (check) {
    checkAlloc();
  }
  data[items++] = val;
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::shiftRight(int pos) {
  for (decltype(pos) i = pos; i < items; i++) {
    std::swap(data[i], data[i+1]);
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::shiftLeft(int pos) {
  for (decltype(pos) i = items; i >= pos; i--) {
    std::swap(data[i], data[i+1]);
  }
}

template <typename T, int INIT_CAP, int CAP_MULT>
void Vector<T, INIT_CAP, CAP_MULT>::removeFrom(const T &val, int pos) {
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
