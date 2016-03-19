#include <functional> // hash

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::Bucket(const Key &key, const T &value) : key_(key) {
  setValue(value);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::setValue(const T &value) {
  if (values_.size() == 0) {
    values_ << value;
  }
  else {
    values_[0] = value;
  }
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::addValue(const T &value) {
  values_.prepend(value);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
const Key &HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::key() const {
  return key_;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
T &HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::value() {
  return values_[0];
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
const T &HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::value() const {
  return values_[0];
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
const Vector<T> &HashMap<Key, T, INIT_CAP, CAP_MULT>::Bucket::values() const {
  return values_;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::_Iterator(PtrType vec, int pos)
  : vec(vec), pos_(pos)
{ }

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::_Iterator(const _Iterator<false> &other)
  : vec(other.vec), pos_(other.pos_)
{ }

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>::ValueType
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::value() const {
  return (*vec)[pos_]->value();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>::ValueType
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::operator*() {
  return value();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>::KeyType
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::key() const {
  return (*vec)[pos_]->key();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>&
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::operator++() {
  auto cap = vec->capacity();
  for (;;) {
    ++pos_;
    if (pos_ == cap || (*vec)[pos_]) break;
  }
  return *this;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::operator++(int) {
  _Iterator it(vec, pos_);
  ++it;
  return it;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>&
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::operator--() {
  for (;;) {
    --pos_;
    if (pos_ < 0 || (*vec)[pos_]) break;
  }
  return *this;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::template _Iterator<IS_CONST>
HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::operator--(int) {
  _Iterator it(vec, pos_);
  --it;
  return it;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
bool HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::
operator==(const _Iterator &other) const {
  return pos() == other.pos();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
bool HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::
operator!=(const _Iterator &other) const {
  return !(*this == other);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
template <bool IS_CONST>
int HashMap<Key, T, INIT_CAP, CAP_MULT>::_Iterator<IS_CONST>::pos() const {
  return pos_;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
HashMap<Key, T, INIT_CAP, CAP_MULT>::HashMap()
  : buckets(), items(0)
{
  for (int i = 0; i < INIT_CAP; i++) {
    buckets << nullptr;
  }
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
HashMap<Key, T, INIT_CAP, CAP_MULT>::HashMap(const HashMap &other)
  : buckets(other.buckets), items(other.items)
{ }

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
HashMap<Key, T, INIT_CAP, CAP_MULT>::HashMap(HashMap &&other)
  : buckets(std::move(other.buckets)), items(other.items)
{
  // Clear the other instance.
  other.items = 0;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
bool HashMap<Key, T, INIT_CAP, CAP_MULT>::isEmpty() const {
  return items == 0;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
int HashMap<Key, T, INIT_CAP, CAP_MULT>::size() const {
  return items;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
int HashMap<Key, T, INIT_CAP, CAP_MULT>::capacity() const {
  return buckets.capacity();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
int HashMap<Key, T, INIT_CAP, CAP_MULT>::count() const {
  return size();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
int HashMap<Key, T, INIT_CAP, CAP_MULT>::count(const Key &key) const {
  return buckets[hashIndex(key)]->values().size();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::insert(const Key &key, const T &value) {
  _insert(key, value);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::insertMulti(const Key &key, const T &value) {
  _insert(key, value, true);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::remove(const Key &key) {
  if (contains(key)) {
    buckets[hashIndex(key)] = nullptr;
    items--;
  }
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
Key HashMap<Key, T, INIT_CAP, CAP_MULT>::key(const T &value, const Key &defaultKey) const {
  for (const auto *bucket : buckets) {
    if (bucket && bucket->values().contains(value)) {
      return bucket->key();
    }
  }
  return defaultKey;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
Vector<Key> HashMap<Key, T, INIT_CAP, CAP_MULT>::keys() const {
  Vector<Key> res;
  for (const auto *bucket : buckets) {
    if (bucket) {
      res << bucket->key();
    }
  }
  return res;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
T HashMap<Key, T, INIT_CAP, CAP_MULT>::value(const Key &key,
                                             const T &defaultValue) const {
  if (!contains(key)) {
    return defaultValue;
  }
  return buckets[hashIndex(key)]->value();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
Vector<T> HashMap<Key, T, INIT_CAP, CAP_MULT>::values() const {
  Vector<T> res;
  for (const auto *bucket : buckets) {
    if (bucket) {
      res << bucket->values();
    }
  }
  return res;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
Vector<T> HashMap<Key, T, INIT_CAP, CAP_MULT>::values(const Key &key) const {
  return buckets[hashIndex(key)]->values();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
bool HashMap<Key, T, INIT_CAP, CAP_MULT>::contains(const Key &key) const {
  return buckets[hashIndex(key)];
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::clear() {
  buckets.clear();
  items = 0;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::reserve(int cap_) {
  buckets.reserve(cap_);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::shrinkToFit() {
  // Remove any unused buckets so the vector can shrink as much as possible.
  buckets.remove(nullptr);
  buckets.shrinkToFit();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::Iterator
HashMap<Key, T, INIT_CAP, CAP_MULT>::begin() {
  Iterator it(&buckets, -1);
  ++it;
  return it;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::ConstIterator
HashMap<Key, T, INIT_CAP, CAP_MULT>::begin() const {
  ConstIterator it(&buckets, -1);
  ++it;
  return it;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::ConstIterator
HashMap<Key, T, INIT_CAP, CAP_MULT>::cbegin() const {
  ConstIterator it(&buckets, -1);
  ++it;
  return it;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::Iterator
HashMap<Key, T, INIT_CAP, CAP_MULT>::end() {
  return Iterator(&buckets, capacity());
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::ConstIterator
HashMap<Key, T, INIT_CAP, CAP_MULT>::end() const {
  return ConstIterator(&buckets, capacity());
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::ConstIterator
HashMap<Key, T, INIT_CAP, CAP_MULT>::cend() const {
  return ConstIterator(&buckets, capacity());
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
T &HashMap<Key, T, INIT_CAP, CAP_MULT>::operator[](const Key &key) {
  if (!contains(key)) {
    insert(key, T());
  }
  return buckets[hashIndex(key)]->value();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
T HashMap<Key, T, INIT_CAP, CAP_MULT>::operator[](const Key &key) const {
  return value(key);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
bool HashMap<Key, T, INIT_CAP, CAP_MULT>::operator==(const HashMap &other) const {
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

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
bool HashMap<Key, T, INIT_CAP, CAP_MULT>::operator!=(const HashMap &other) const {
  return !(*this == other);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
std::size_t HashMap<Key, T, INIT_CAP, CAP_MULT>::hashIndex(const Key &key) const {
  return std::hash<Key>()(key) % buckets.size();
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::checkRehash() {
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

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::_insert(const Key &key, const T &value, bool multi) {
  // If there is a collision on a key then either override or prepend if multi mode. Otherwise, if
  // the keys are different then make room for the new one and rehash.
  for (;;) {
    auto *bucket = buckets[hashIndex(key)];
    if (!bucket) break;

    if (bucket->key() == key) {
      if (!multi) {
        bucket->setValue(value);
      }
      else {
        bucket->addValue(value);
        items++;
      }
      return;
    }

    buckets.append(nullptr);
  }

  checkRehash();
  buckets[hashIndex(key)] = new Bucket(key, value);
  items++;
}
