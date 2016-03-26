#include <cassert>
#include <cstring>  // memcpy
#include <utility>  // swap
#include <iostream> // cout, endl

template <typename T, int INIT_CAP>
template <bool IS_CONST>
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::_Iterator(PtrType vec, int pos)
  : vec(vec), pos_(pos)
{ }

template <typename T, int INIT_CAP>
template <bool IS_CONST>
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::_Iterator(const _Iterator<false> &other)
  : vec(other.vec), pos_(other.pos_)
{ }

template <typename T, int INIT_CAP>
template <bool IS_CONST>
typename Vector<T, INIT_CAP>::template _Iterator<IS_CONST>::ValueType
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator*() {
  return (*vec)[pos_];
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
typename Vector<T, INIT_CAP>::template _Iterator<IS_CONST>::PtrType
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator->() {
  return &(*vec)[pos_];
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
typename Vector<T, INIT_CAP>::template _Iterator<IS_CONST>&
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator++() {
  ++pos_;
  return *this;
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
typename Vector<T, INIT_CAP>::template _Iterator<IS_CONST>
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator++(int) {
  return ++_Iterator(vec, pos_);
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
typename Vector<T, INIT_CAP>::template _Iterator<IS_CONST>&
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator--() {
  --pos_;
  return *this;
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
typename Vector<T, INIT_CAP>::template _Iterator<IS_CONST>
Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator--(int) {
  return --_Iterator(vec, pos_);
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
bool Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator==(const _Iterator &other) const {
  return pos() == other.pos();
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
bool Vector<T, INIT_CAP>::_Iterator<IS_CONST>::operator!=(const _Iterator &other) const {
  return !(*this == other);
}

template <typename T, int INIT_CAP>
template <bool IS_CONST>
int Vector<T, INIT_CAP>::_Iterator<IS_CONST>::pos() const {
  return pos_;
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::Vector() : items(0), cap(0), data(nullptr) { }

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::Vector(std::initializer_list<T> args) : Vector() {
  reserve(args.size());
  for (const auto &elm : args) {
    append(elm);
  }
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::Vector(const Vector &other) : Vector() {
  std::cout << "COPY CTOR\n";
  alloc(other.size());
  for (const auto &elm : other) {
    // Don't check capacity because we just allocated all. Will speed up a lot.
    _append(elm, false);
  }
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::Vector(Vector &&other) : Vector() {
  std::cout << "MOVE CTOR\n";
  *this = std::move(other);
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::Vector(int size, T val) : Vector() {
  std::cout << "size,val CTOR\n";
  alloc(size);
  for (decltype(size) i = 0; i < size; i++) {
    _append(val, false);
  }
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::Vector(int size, T *values) : Vector() {
  std::cout << "size,*values CTOR\n";
  alloc(size);
  for (decltype(size) i = 0; i < size; i++) {
    _append(values[i], false);
  }
}

template <typename T, int INIT_CAP>
template <typename Iter>
Vector<T, INIT_CAP>::Vector(Iter first, Iter last) : Vector() {
  std::cout << "first,last CTOR\n";
  for (; first != last; first++) {
    append(*first);
  }
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP>::~Vector() {
  clear();
}

template <typename T, int INIT_CAP>
bool Vector<T, INIT_CAP>::isEmpty() const {
  return items == 0;
}

template <typename T, int INIT_CAP>
int Vector<T, INIT_CAP>::size() const {
  return items;
}

template <typename T, int INIT_CAP>
int Vector<T, INIT_CAP>::capacity() const {
  return cap;
}

template <typename T, int INIT_CAP>
T &Vector<T, INIT_CAP>::at(int pos) {
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  return data[pos];
}

template <typename T, int INIT_CAP>
const T &Vector<T, INIT_CAP>::at(int pos) const {
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  return data[pos];
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::append(const T &val) {
  _append(val);
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::append(const Vector &vals) {
  for (const auto &val : vals) {
    append(val);
  }
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::prepend(const T &val) {
  insert(0, val);
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::insert(int pos, const T &value) {
  checkAlloc();
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  shiftLeft(pos); // Effectively moving right.
  data[pos] = value;
  items++;
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::Iterator
Vector<T, INIT_CAP>::insert(Iterator before, const T &value) {
  int pos = before.pos();
  insert(pos, value);
  return createIterator(pos);
}

template <typename T, int INIT_CAP>
bool Vector<T, INIT_CAP>::contains(const T &val) const {
  for (decltype(items) i = 0; i < items; i++) {
    if (data[i] == val) {
      return true;
    }
  }
  return false;
}

template <typename T, int INIT_CAP>
int Vector<T, INIT_CAP>::indexOf(const T &value, int from) const {
  assert(from >= 0 && from < items && "'from' out of bounds!");
  for (decltype(items) i = from; i < items; i++) {
    if (data[i] == value) {
      return i;
    }
  }
  return -1;
}

template <typename T, int INIT_CAP>
int Vector<T, INIT_CAP>::lastIndexOf(const T &value, int from) const {
  assert(from >= -1 && from < items && "'from' out of bounds!");
  if (from == -1) from = items - 1;
  for (decltype(items) i = from; i >= 0; i--) {
    if (data[i] == value) {
      return i;
    }
  }
  return -1;
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::print() const {
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

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::clear() {
  if (data) {
    delete[] data;
    data = nullptr;
  }
  items = cap = 0;
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::reserve(int cap_) {
  if (cap >= cap_) return;
  alloc(cap_);
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::shrinkToFit() {
  if (items == cap) return;
  alloc(items);
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::remove(const T &val) {
  removeFrom(val);
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::removeAt(int pos) {
  assert(pos >= 0 && pos < cap && "Position out of bounds!");
  data[pos] = T();
  items--;
  shiftRight(pos); // Effectively moving left.
}

template <typename T, int INIT_CAP>
T Vector<T, INIT_CAP>::takeFirst() {
  return takeAt(0);
}

template <typename T, int INIT_CAP>
T Vector<T, INIT_CAP>::takeLast() {
  return takeAt(size() - 1);
}

template <typename T, int INIT_CAP>
T Vector<T, INIT_CAP>::takeAt(int pos) {
  auto value = at(pos);
  removeAt(pos);
  return value;
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::Iterator
Vector<T, INIT_CAP>::erase(Iterator pos) {
  removeAt(pos.pos());
  return createIterator(pos.pos());
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::Iterator
Vector<T, INIT_CAP>::begin() {
  return createIterator(0);
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::ConstIterator
Vector<T, INIT_CAP>::begin() const {
  return createIterator(0);
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::ConstIterator
Vector<T, INIT_CAP>::cbegin() const {
  return createIterator(0);
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::Iterator
Vector<T, INIT_CAP>::end() {
  return createIterator(size());
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::ConstIterator
Vector<T, INIT_CAP>::end() const {
  return createIterator(size());
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::ConstIterator
Vector<T, INIT_CAP>::cend() const {
  return createIterator(size());
}

template <typename T, int INIT_CAP>
T &Vector<T, INIT_CAP>::operator[](int pos) {
  return at(pos);
}

template <typename T, int INIT_CAP>
const T &Vector<T, INIT_CAP>::operator[](int pos) const {
  return at(pos);
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP> &Vector<T, INIT_CAP>::operator<<(const T &value) {
  append(value);
  return *this;
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP> &Vector<T, INIT_CAP>::operator<<(const Vector &values) {
  append(values);
  return *this;
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP> &Vector<T, INIT_CAP>::operator+=(const T &value) {
  append(value);
  return *this;
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP> &Vector<T, INIT_CAP>::operator+=(const Vector &values) {
  append(values);
  return *this;
}

template <typename T, int INIT_CAP>
Vector<T, INIT_CAP> Vector<T, INIT_CAP>::operator+(const Vector &values) {
  append(values);
  return *this;
}

template <typename T, int INIT_CAP>
bool Vector<T, INIT_CAP>::operator==(const Vector &other) const {
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

template <typename T, int INIT_CAP>
bool Vector<T, INIT_CAP>::operator!=(const Vector &other) const {
  return !(*this == other);
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::Vector&
Vector<T, INIT_CAP>::operator=(const Vector &other) {
  clear();
  auto size = other.size();
  for (decltype(size) i = 0; i < size; i++) {
    append(other[i]);
  }
  return *this;
}

template <typename T, int INIT_CAP>
typename Vector<T, INIT_CAP>::Vector&
Vector<T, INIT_CAP>::operator=(Vector &&other) {
  clear();

  data = other.data;
  items = other.items;
  cap = other.cap;

  // Nullify original container.
  other.data = nullptr;
  other.items = other.cap = 0;
  return *this;
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::fillDefault(T *ptr, int n) {
  for (decltype(n) i = 0; i < n; i++) {
    ptr[i] = T();
  }
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::alloc(int size) {
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

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::checkAlloc() {
  if (items != cap) return;
  alloc(cap == 0 ? INIT_CAP : cap * 2);
}

/// Appends value but only checks capacity if check is set.
/** This saves processing time when appending very many items. */
template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::_append(const T &val, bool check) {
  if (check) {
    checkAlloc();
  }
  data[items++] = val;
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::shiftRight(int pos) {
  for (decltype(pos) i = pos; i < items; i++) {
    std::swap(data[i], data[i+1]);
  }
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::shiftLeft(int pos) {
  for (decltype(pos) i = items; i >= pos; i--) {
    std::swap(data[i], data[i+1]);
  }
}

template <typename T, int INIT_CAP>
void Vector<T, INIT_CAP>::removeFrom(const T &val, int pos) {
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

template <typename T, int INIT_CAP>
inline typename Vector<T, INIT_CAP>::Iterator
Vector<T, INIT_CAP>::createIterator(int pos) {
  return Iterator(this, pos);
}

template <typename T, int INIT_CAP>
inline typename Vector<T, INIT_CAP>::ConstIterator
Vector<T, INIT_CAP>::createIterator(int pos) const {
  return ConstIterator(this, pos);
}
