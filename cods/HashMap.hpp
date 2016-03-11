#include <iostream>   // cout, endl
#include <functional> // hash

template <typename Key, typename T>
HashMap<Key, T>::HashMap() { }

template <typename Key, typename T>
void HashMap<Key, T>::insert(const Key &key, const T &value) {
  valuePairs << ValuePair(key, value);
  int index = valuePairs.size() - 1;
  auto hash = std::hash<Key>()(key);
  indexPairs << IndexPair(hash, index);
}

template <typename Key, typename T>
T HashMap<Key, T>::value(const Key &key) const {
  auto hash = std::hash<Key>()(key);
  for (int i = 0; i < indexPairs.size(); i++) {
    const auto &ip = indexPairs[i];
    if (ip.first == hash) {
      return valuePairs[ip.second].second;
    }
  }
  return T();
}
