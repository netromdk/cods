#include "gtest/gtest.h"

#include "cods/Set.h"
using namespace cods;

TEST(Set, instantiate) {
  Set<int> set;
}

TEST(Set, isEmpty) {
  Set<int> set;
  EXPECT_TRUE(set.isEmpty());
}

TEST(Set, size) {
  Set<int> set;
  EXPECT_EQ(set.size(), 0);
}

TEST(Set, insert) {
  Set<int> set;
  set.insert(1);
  set.insert(1);
  EXPECT_EQ(set.size(), 1); // No duplicates.
}

TEST(Set, remove) {
  Set<int> set;
  EXPECT_FALSE(set.remove(1));
  set.insert(1);
  EXPECT_FALSE(set.isEmpty());

  EXPECT_TRUE(set.remove(1));
  EXPECT_TRUE(set.isEmpty());
}

TEST(Set, toVector) {
  Set<int> set;
  set.insert(1);
  set.insert(2);
  set.insert(3);

  auto vec = set.toVector();
  ASSERT_EQ(vec.size(), set.size());
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);

  auto vec2 = set.values();
  EXPECT_EQ(vec, vec2);
}

TEST(Set, streamOperator) {
  Set<int> set;
  set << 1 << 1 << 1;
  EXPECT_EQ(set.size(), 1);

  auto vec = set.toVector();
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec[0], 1);
}

TEST(Set, clear) {
  Set<int> set;
  set << 1 << 2 << 3;
  EXPECT_EQ(set.size(), 3);

  set.clear();
  EXPECT_TRUE(set.isEmpty());
}

TEST(Set, contains) {
  Set<int> set;
  set << 1 << 2 << 3;
  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(2));
  EXPECT_TRUE(set.contains(3));
  EXPECT_FALSE(set.contains(4));

  EXPECT_TRUE(set.contains(set));

  Set<int> set2;
  set << 1 << 2;
  EXPECT_TRUE(set.contains(set2));
  EXPECT_FALSE(set2.contains(set));
}

TEST(Set, reserve) {
  Set<int> set;
  set.reserve(100);
  EXPECT_EQ(set.capacity(), 100);
}

TEST(Set, shrinkToFit) {
  Set<int> set;
  set.reserve(100);
  EXPECT_EQ(set.capacity(), 100);

  set << 1 << 2 << 3;
  set.shrinkToFit();
  EXPECT_EQ(set.capacity(), 3);
}

TEST(Set, iterator) {
  Set<int> set;
  set << 1 << 2 << 3;

  auto vec = set.toVector();

  int i = 0;
  for (const auto &elm : set) {
    EXPECT_EQ(elm, vec[i]);
    i++;
  }
}

TEST(Set, insertIterator) {
  Set<int> set;
  set << 10 << 20 << 30;
  auto it = set.insert(1);
  auto it2 = set.insert(1);
  EXPECT_EQ(set.size(), 4);
  EXPECT_EQ(it, it2);
  EXPECT_EQ(*it, 1);
}

TEST(Set, erase) {
  Set<int> set;
  set << 1 << 2 << 3;

  auto it = set.erase(set.begin());
  EXPECT_EQ(set.size(), 2);

  it = set.erase(it);
  EXPECT_EQ(set.size(), 1);

  it = set.erase(it);
  EXPECT_EQ(set.size(), 0);

  it = set.erase(it);
  EXPECT_EQ(it, set.end());
}

TEST(Set, find) {
  Set<int> set;
  set << 1 << 2 << 3;

  auto it = set.find(1);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 1);

  it = set.find(2);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 2);

  it = set.find(3);
  EXPECT_NE(it, set.end());
  EXPECT_EQ(*it, 3);

  it = set.find(42);
  EXPECT_EQ(it, set.end());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
