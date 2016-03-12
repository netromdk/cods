#include <functional> // hash

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
HashMap<Key, T, INIT_CAP, CAP_MULT>::HashMap()
  : buckets(INIT_CAP, defaultValue()), items(0)
{ }

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
void HashMap<Key, T, INIT_CAP, CAP_MULT>::insert(const Key &key, const T &value) {
  checkRehash();
  buckets[hashIndex(key)] = Value(key, value, true);
  items++;
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
T HashMap<Key, T, INIT_CAP, CAP_MULT>::value(const Key &key) const {
  return std::get<1>(buckets[hashIndex(key)]);
}

template <typename Key, typename T, int INIT_CAP, int CAP_MULT>
typename HashMap<Key, T, INIT_CAP, CAP_MULT>::Value
HashMap<Key, T, INIT_CAP, CAP_MULT>::defaultValue() const {
  return Value(Key(), T(), false);
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
  buckets.append(defaultValue());

  auto size = buckets.size();
  for (decltype(size) i = 0; i < size; i++) {
    auto &value = buckets[i];
    if (std::get<2>(value)) {
      buckets[hashIndex(std::get<0>(value))] = value;
      buckets[i] = defaultValue(); // Clear old index.
    }
  }
}
