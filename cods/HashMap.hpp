#include <functional> // hash

template <typename Key, typename T, int INIT_CAP>
HashMap<Key, T, INIT_CAP>::Bucket::Bucket(const Key &key, const T &value) : key_(key) {
  setValue(value);
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::Bucket::setValue(const T &value) {
  if (values_.size() == 0) {
    values_ << value;
  }
  else {
    values_[0] = value;
  }
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::Bucket::addValue(const T &value) {
  values_.prepend(value);
}

template <typename Key, typename T, int INIT_CAP>
const Key &HashMap<Key, T, INIT_CAP>::Bucket::key() const {
  return key_;
}

template <typename Key, typename T, int INIT_CAP>
T &HashMap<Key, T, INIT_CAP>::Bucket::value() {
  return values_[0];
}

template <typename Key, typename T, int INIT_CAP>
const T &HashMap<Key, T, INIT_CAP>::Bucket::value() const {
  return values_[0];
}

template <typename Key, typename T, int INIT_CAP>
const Vector<T> &HashMap<Key, T, INIT_CAP>::Bucket::values() const {
  return values_;
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::_Iterator(PtrType vec, int pos)
  : vec(vec), pos_(pos)
{ }

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::_Iterator(const _Iterator<false> &other)
  : vec(other.vec), pos_(other.pos_)
{ }

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>::ValueType
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::value() const {
  return (*vec)[pos_]->value();
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>::ValueType
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::operator*() {
  return value();
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>::KeyType
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::key() const {
  return (*vec)[pos_]->key();
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>&
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::operator++() {
  auto cap = vec->capacity();
  do {
    ++pos_;
  } while (pos_ < cap && !(*vec)[pos_]);
  return *this;
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::operator++(int) {
  return ++_Iterator(vec, pos_);
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>&
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::operator--() {
  do {
    --pos_;
  } while (pos_ >= 0 && !(*vec)[pos_]);
  return *this;
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP>::template _Iterator<IS_CONST>
HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::operator--(int) {
  return --_Iterator(vec, pos_);
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
bool HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::
operator==(const _Iterator &other) const {
  return pos() == other.pos();
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
bool HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::
operator!=(const _Iterator &other) const {
  return !(*this == other);
}

template <typename Key, typename T, int INIT_CAP>
template <bool IS_CONST>
int HashMap<Key, T, INIT_CAP>::_Iterator<IS_CONST>::pos() const {
  return pos_;
}

template <typename Key, typename T, int INIT_CAP>
HashMap<Key, T, INIT_CAP>::HashMap()
  : buckets(), items(0)
{
  buckets.reserve(INIT_CAP);
  for (int i = 0; i < INIT_CAP; i++) {
    buckets << nullptr;
  }
}

template <typename Key, typename T, int INIT_CAP>
HashMap<Key, T, INIT_CAP>::HashMap(const HashMap &other)
  : buckets(other.buckets), items(other.items)
{ }

template <typename Key, typename T, int INIT_CAP>
HashMap<Key, T, INIT_CAP>::HashMap(HashMap &&other)
  : buckets(std::move(other.buckets)), items(other.items)
{
  // Clear the other instance.
  other.items = 0;
}

template <typename Key, typename T, int INIT_CAP>
bool HashMap<Key, T, INIT_CAP>::isEmpty() const {
  return items == 0;
}

template <typename Key, typename T, int INIT_CAP>
int HashMap<Key, T, INIT_CAP>::size() const {
  return items;
}

template <typename Key, typename T, int INIT_CAP>
int HashMap<Key, T, INIT_CAP>::capacity() const {
  return buckets.capacity();
}

template <typename Key, typename T, int INIT_CAP>
int HashMap<Key, T, INIT_CAP>::count() const {
  return size();
}

template <typename Key, typename T, int INIT_CAP>
int HashMap<Key, T, INIT_CAP>::count(const Key &key) const {
  return buckets[hashIndex(key)]->values().size();
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::insert(const Key &key, const T &value) {
  return _insert(key, value);
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::insertMulti(const Key &key, const T &value) {
  return _insert(key, value, true);
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::remove(const Key &key) {
  if (contains(key)) {
    buckets[hashIndex(key)] = nullptr;
    items--;
  }
}

template <typename Key, typename T, int INIT_CAP>
Key HashMap<Key, T, INIT_CAP>::key(const T &value, const Key &defaultKey) const {
  for (const auto *bucket : buckets) {
    if (bucket && bucket->values().contains(value)) {
      return bucket->key();
    }
  }
  return defaultKey;
}

template <typename Key, typename T, int INIT_CAP>
Vector<Key> HashMap<Key, T, INIT_CAP>::keys() const {
  Vector<Key> res;
  for (const auto *bucket : buckets) {
    if (bucket) {
      res << bucket->key();
    }
  }
  return res;
}

template <typename Key, typename T, int INIT_CAP>
T HashMap<Key, T, INIT_CAP>::value(const Key &key,
                                             const T &defaultValue) const {
  if (!contains(key)) {
    return defaultValue;
  }
  return buckets[hashIndex(key)]->value();
}

template <typename Key, typename T, int INIT_CAP>
Vector<T> HashMap<Key, T, INIT_CAP>::values() const {
  Vector<T> res;
  for (const auto *bucket : buckets) {
    if (bucket) {
      res << bucket->values();
    }
  }
  return res;
}

template <typename Key, typename T, int INIT_CAP>
Vector<T> HashMap<Key, T, INIT_CAP>::values(const Key &key) const {
  return buckets[hashIndex(key)]->values();
}

template <typename Key, typename T, int INIT_CAP>
bool HashMap<Key, T, INIT_CAP>::contains(const Key &key) const {
  return buckets[hashIndex(key)];
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::clear() {
  buckets.clear();
  items = 0;
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::reserve(int cap_) {
  buckets.reserve(cap_);
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::shrinkToFit() {
  // Remove any unused buckets so the vector can shrink as much as possible.
  buckets.remove(nullptr);
  buckets.shrinkToFit();
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::erase(Iterator pos) {
  if (pos == end()) {
    return end();
  }
  remove(pos.key());
  return ++pos;
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::begin() {
  // Start at -1 to find the first item. ++ will continue until an item is found.
  return ++createIterator(-1);
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::ConstIterator
HashMap<Key, T, INIT_CAP>::begin() const {
  return ++createIterator(-1);
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::ConstIterator
HashMap<Key, T, INIT_CAP>::cbegin() const {
  return ++createIterator(-1);
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::end() {
  return createIterator(capacity());
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::ConstIterator
HashMap<Key, T, INIT_CAP>::end() const {
  return createIterator(capacity());
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::ConstIterator
HashMap<Key, T, INIT_CAP>::cend() const {
  return createIterator(capacity());
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::find(const Key &key) {
  if (!contains(key)) {
    return end();
  }
  return createIterator(hashIndex(key));
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::ConstIterator
HashMap<Key, T, INIT_CAP>::find(const Key &key) const {
  return find(key);
}

template <typename Key, typename T, int INIT_CAP>
T &HashMap<Key, T, INIT_CAP>::operator[](const Key &key) {
  if (!contains(key)) {
    insert(key, T());
  }
  return buckets[hashIndex(key)]->value();
}

template <typename Key, typename T, int INIT_CAP>
T HashMap<Key, T, INIT_CAP>::operator[](const Key &key) const {
  return value(key);
}

template <typename Key, typename T, int INIT_CAP>
bool HashMap<Key, T, INIT_CAP>::operator==(const HashMap &other) const {
  auto ourKeys = keys();
  auto theirKeys = other.keys();
  if (ourKeys.size() != theirKeys.size()) {
    return false;
  }

  for (const auto &key : ourKeys) {
    if (!theirKeys.contains(key)) {
      return false;
    }
  }

  auto ourValues = values();
  auto theirValues = other.values();
  if (ourValues.size() != theirValues.size()) {
    return false;
  }

  for (const auto &value : ourValues) {
    if (!theirValues.contains(value)) {
      return false;
    }
  }
  return true;
}

template <typename Key, typename T, int INIT_CAP>
bool HashMap<Key, T, INIT_CAP>::operator!=(const HashMap &other) const {
  return !(*this == other);
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::HashMap&
HashMap<Key, T, INIT_CAP>::operator=(const HashMap &other) {
  buckets.reserve(other.size());
  for (const auto &key : other.keys()) {
    insert(key, other[key]);
  }
  return *this;
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::HashMap&
HashMap<Key, T, INIT_CAP>::operator=(HashMap &&other) {
  buckets = std::move(other.buckets);
  items = other.items;
  other.items = 0;
  return *this;
}

template <typename Key, typename T, int INIT_CAP>
std::size_t HashMap<Key, T, INIT_CAP>::hashIndex(const Key &key) const {
  return std::hash<Key>()(key) % buckets.size();
}

template <typename Key, typename T, int INIT_CAP>
void HashMap<Key, T, INIT_CAP>::checkRehash() {
  // If next item fits then stop.
  if (items + 1 <= buckets.capacity()) {
    return;
  }

  // Force growing!
  buckets.append(nullptr);

  int i = 0;
  for (auto *bucket : buckets) {
    if (bucket) {
      buckets[hashIndex(bucket->key())] = bucket;
      buckets[i] = nullptr; // Clear old index.
    }
    i++;
  }
}

template <typename Key, typename T, int INIT_CAP>
typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::_insert(const Key &key, const T &value, bool multi) {
  // If there is a collision on a key then either override or prepend if multi mode. Otherwise, if
  // the keys are different then make room for the new one and rehash.
  for (;;) {
    auto idx = hashIndex(key);
    auto *bucket = buckets[idx];
    if (!bucket) break;

    if (bucket->key() == key) {
      if (!multi) {
        bucket->setValue(value);
      }
      else {
        bucket->addValue(value);
        items++;
      }
      return createIterator(idx);
    }

    buckets.append(nullptr);
  }

  checkRehash();
  auto idx = hashIndex(key);
  buckets[idx] = new Bucket(key, value);
  items++;
  return createIterator(idx);
}

template <typename Key, typename T, int INIT_CAP>
inline typename HashMap<Key, T, INIT_CAP>::Iterator
HashMap<Key, T, INIT_CAP>::createIterator(int pos) {
  return Iterator(&buckets, pos);
}

template <typename Key, typename T, int INIT_CAP>
inline typename HashMap<Key, T, INIT_CAP>::ConstIterator
HashMap<Key, T, INIT_CAP>::createIterator(int pos) const {
  return ConstIterator(&buckets, pos);
}
