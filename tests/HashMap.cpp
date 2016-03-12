#include "gtest/gtest.h"

#include "cods/HashMap.h"
using namespace cods;

TEST(HashMap, instantiate) {
  HashMap<std::string, int> map;
  HashMap<std::string, int, 10> map2;
  HashMap<std::string, int, 12, 20> map3;
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
  HashMap<int, int, 1, 2> map;
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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
