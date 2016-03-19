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

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
