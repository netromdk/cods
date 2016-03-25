#include "gtest/gtest.h"

#include "cods/HashMap.h"
using namespace cods;

TEST(HashMap, instantiate) {
  HashMap<std::string, int> map;
  HashMap<std::string, int, 10> map2;
}

TEST(HashMap, copyCtor) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);

  decltype(map) map2(map);
  EXPECT_TRUE(map == map2);
}

TEST(HashMap, moveCtor) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);

  decltype(map) temp(map);

  decltype(map) map2(std::move(map));
  EXPECT_TRUE(map.isEmpty());
  EXPECT_TRUE(map2 == temp);
}

TEST(HashMap, insertAndGet) {
  HashMap<std::string, int> map;
  std::string key = "hello";
  int value = 42;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);
  EXPECT_EQ(map.size(), 1);
}

TEST(HashMap, insertThriceRehash) {
  HashMap<std::string, int, 2> map;
  std::string key = "hello";
  int value = 42;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map.capacity(), 2);

  key = "world";
  value = 90;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);
  EXPECT_EQ(map.size(), 2);
  EXPECT_EQ(map.capacity(), 2);

  // Insert will increase capacity 2->4 and rehash all values.
  key = "!";
  value = 123;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.capacity(), 4);
}

TEST(HashMap, isEmpty) {
  HashMap<int, int> map;
  EXPECT_TRUE(map.isEmpty());

  map.insert(1, 1);
  EXPECT_FALSE(map.isEmpty());

  map.clear();
  EXPECT_TRUE(map.isEmpty());
}

TEST(HashMap, clear) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.size(), 3);

  map.clear();
  EXPECT_EQ(map.size(), 0);
  EXPECT_EQ(map.capacity(), 0);
}

TEST(HashMap, contains) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_TRUE(map.contains(1));
  EXPECT_TRUE(map.contains(2));
  EXPECT_TRUE(map.contains(3));
  EXPECT_FALSE(map.contains(4));
}

TEST(HashMap, getDefaultValue) {
  HashMap<int, int> map;
  EXPECT_FALSE(map.contains(1));
  EXPECT_EQ(map.value(1, 42), 42);
}

TEST(HashMap, remove) {
  HashMap<int, int> map;
  map.insert(1, 42);
  EXPECT_EQ(map.size(), 1);

  map.remove(1);
  EXPECT_FALSE(map.contains(1));
  EXPECT_TRUE(map.isEmpty());
}

TEST(HashMap, key) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.key(1), 3);
  EXPECT_EQ(map.key(20, 42), 42);
}

TEST(HashMap, keys) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.size(), 3);

  auto keys = map.keys();
  EXPECT_EQ(keys.size(), map.size());
  EXPECT_EQ(keys[0], 1);
  EXPECT_EQ(keys[1], 2);
  EXPECT_EQ(keys[2], 3);
}

TEST(HashMap, values) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.size(), 3);

  auto values = map.values();
  EXPECT_EQ(values.size(), map.size());
  EXPECT_EQ(values[0], 3);
  EXPECT_EQ(values[1], 2);
  EXPECT_EQ(values[2], 1);
}

TEST(HashMap, reserve) {
  HashMap<int, int, 1> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.capacity(), 4);

  map.reserve(10);
  EXPECT_EQ(map.capacity(), 10);

  map.reserve(3);
  EXPECT_EQ(map.capacity(), 10);
}

TEST(HashMap, shrinkToFit) {
  HashMap<int, int, 2> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.capacity(), 4);

  map.shrinkToFit();
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map.capacity(), 3);
}

TEST(HashMap, squareBracketsOperator) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  EXPECT_EQ(map[1], 3);
  EXPECT_EQ(map[2], 2);
  EXPECT_EQ(map[3], 1);

  // Get default value when nonexistent, and it inserts the key.
  EXPECT_FALSE(map.contains(42));
  EXPECT_EQ(map[42], int());
  EXPECT_TRUE(map.contains(42));

  // Set values via reference.
  map[42] = 10;
  EXPECT_EQ(map[42], 10);
}

TEST(HashMap, equalsOperator) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);

  decltype(map) map2;
  map2.insert(1, 3);
  map2.insert(2, 2);
  map2.insert(3, 1);
  EXPECT_TRUE(map == map2);

  decltype(map) map3;
  EXPECT_FALSE(map == map3);
}

TEST(HashMap, notEqualsOperator) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);

  decltype(map) map2;
  map2.insert(1, 3);
  map2.insert(2, 2);
  map2.insert(3, 1);
  EXPECT_FALSE(map != map2);

  decltype(map) map3;
  EXPECT_TRUE(map != map3);
}

TEST(HashMap, insertCollision) {
  HashMap<int, int> map;
  map.insert(1, 1);
  map.insert(1, 2);
  map.insert(1, 42);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[1], 42);
}

TEST(HashMap, insertVectorKey) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  HashMap<decltype(vec), int> map;
  map.insert(vec, 42);
  EXPECT_EQ(map.size(), 1);
  EXPECT_EQ(map[vec], 42);
}

TEST(HashMap, insertMulti) {
  HashMap<int, int> map;
  map.insertMulti(1, 1);
  map.insertMulti(1, 2);
  map.insertMulti(1, 42);
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], 42);
}

TEST(HashMap, multiValues) {
  HashMap<int, int> map;
  map.insertMulti(1, 1);
  map.insertMulti(1, 2);
  map.insertMulti(1, 42);
  EXPECT_EQ(map.size(), 3);

  Vector<int> vec;
  vec << 42 << 2 << 1;
  EXPECT_EQ(map.values(1), vec);

  map.insert(2, 23);
  EXPECT_EQ(map.size(), 4);

  vec << 23;
  EXPECT_EQ(map.values(), vec);
}

TEST(HashMap, count) {
  HashMap<int, int> map;
  map.insert(1, 3);
  map.insert(2, 2);
  map.insert(3, 1);
  map.insertMulti(1, 4);
  EXPECT_EQ(map.size(), map.count());
  EXPECT_EQ(map.count(1), 2);
}

TEST(HashMap, iterator) {
  HashMap<int, int> map;
  map.insert(10, 1);
  map.insert(20, 2);
  map.insert(30, 3);

  int i = 10;
  for (const auto &elm : map) {
    EXPECT_EQ(elm, map[i]);
    i += 10;
  }

  for (auto it = map.begin(); it != map.end(); ++it) {
    EXPECT_EQ(*it, it.value());
    EXPECT_EQ(it.value(), map[it.key()]);
  }

  auto it = map.begin();
  EXPECT_EQ(*it, 1);
  *it = 42;
  EXPECT_EQ(*it, 42);

  // Testing bidirectional functionality.
  EXPECT_EQ(*--map.end(), 3);
  EXPECT_EQ(*--(--map.end()), 2);
  EXPECT_EQ(*++(--(--map.end())), 3);
}

TEST(HashMap, find) {
  HashMap<int, int> map;
  map.insert(10, 1);
  map.insert(20, 2);
  map.insert(30, 3);
  EXPECT_EQ(map.find(42), map.end());
  EXPECT_EQ(*map.find(20), 2);
}

TEST(HashMap, insertIteartor) {
  HashMap<int, int> map;
  auto it = map.insert(1, 1);
  EXPECT_EQ(*it, 1);

  it = map.insert(2, 2);
  EXPECT_EQ(*it, 2);

  it = map.insert(3, 3);
  EXPECT_EQ(*it, 3);

  it = map.insertMulti(3, 42);
  EXPECT_EQ(*it, 42);
}

TEST(HashMap, erase) {
  HashMap<int, int> map;
  map.insert(1, 1);
  map.insert(2, 2);
  map.insert(3, 3);

  auto it = map.erase(map.begin());
  EXPECT_EQ(map.size(), 2);
  EXPECT_NE(it, map.end());

  it = map.erase(it);
  EXPECT_EQ(map.size(), 1);
  EXPECT_NE(it, map.end());

  it = map.erase(it);
  EXPECT_EQ(map.size(), 0);
  EXPECT_EQ(it, map.end());
}

TEST(HashMap, assignment) {
  HashMap<int, int> map;
  map.insert(1, 1);
  map.insert(2, 2);
  map.insert(3, 3);

  HashMap<int, int> map2;
  map2 = map;
  EXPECT_EQ(map, map2);
}

TEST(HashMap, moveAssignment) {
  HashMap<int, int> map;
  map.insert(1, 1);
  map.insert(2, 2);
  map.insert(3, 3);

  auto tmp = map;

  HashMap<int, int> map2;
  map2 = std::move(map);
  EXPECT_TRUE(map.isEmpty());
  EXPECT_EQ(map2, tmp);
}

TEST(HashMap, initializerList) {
  HashMap<int, int> map({std::make_pair(1, 1), std::make_pair(2, 2), std::make_pair(3, 3)});
  EXPECT_EQ(map.size(), 3);
  EXPECT_EQ(map[1], 1);
  EXPECT_EQ(map[2], 2);
  EXPECT_EQ(map[3], 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
