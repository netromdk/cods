#include "gtest/gtest.h"

#include "cods/HashMap.h"
using namespace cods;

TEST(HashMap, instantiate) {
  HashMap<std::string, int> map;
}

TEST(HashMap, insertAndGet) {
  HashMap<std::string, int> map;
  std::string key = "hello";
  int value = 42;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);
}

TEST(HashMap, insertThriceRehash) {
  HashMap<std::string, int, 2> map;
  std::string key = "hello";
  int value = 42;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);

  key = "world";
  value = 90;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);

  key = "!";
  value = 123;
  map.insert(key, value);
  EXPECT_EQ(map.value(key), value);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
