template <typename T>
Set<T>::Set() : map() { }

template <typename T>
bool Set<T>::isEmpty() const {
  return map.isEmpty();
}

template <typename T>
int Set<T>::size() const {
  return map.size();
}

template <typename T>
int Set<T>::capacity() const {
  return map.capacity();
}

template <typename T>
void Set<T>::clear() {
  map.clear();
}

template <typename T>
void Set<T>::insert(const T &value) {
  map[value] = true;
}

template <typename T>
bool Set<T>::remove(const T &value) {
  if (map.contains(value)) {
    map.remove(value);
    return true;
  }
  return false;
}

template <typename T>
void Set<T>::reserve(int capacity) {
  map.reserve(capacity);
}

template <typename T>
void Set<T>::shrinkToFit() {
  map.shrinkToFit();
}

template <typename T>
bool Set<T>::contains(const T &value) const {
  return map.contains(value);
}

template <typename T>
bool Set<T>::contains(const Set &other) const {
  // TODO: Implement iterators and then don't use the values() call.
  for (const auto &elm : other.values()) {
    if (!contains(elm)) {
      return false;
    }
  }
  return true;
}

template <typename T>
Vector<T> Set<T>::values() const {
  return map.keys();
}

template <typename T>
Vector<T> Set<T>::toVector() const {
  return values();
}

template <typename T>
typename Set<T>::Set& Set<T>::operator<<(const T &value) {
  insert(value);
  return *this;
}
