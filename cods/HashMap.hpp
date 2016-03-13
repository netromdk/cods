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
T HashMap<Key, T, INIT_CAP, CAP_MULT>::value(const Key &key) const {
  return buckets[hashIndex(key)]->value();
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
  Vector<T> res;
  for (const auto *bucket : buckets) {
    if (bucket && bucket->key() == key) {
      res << bucket->values();
    }
  }
  return res;
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
  Vector<int> del;
  int i = 0;
  for (const auto *bucket : buckets) {
    if (!bucket) {
      del << i++;
    }
  }

  for (const auto &idx : del) {
    buckets.removeAt(idx);
  }

  buckets.shrinkToFit();
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
