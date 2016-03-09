#include <array>
#include <vector>

#include "gtest/gtest.h"

#include "cods/Vector.h"
using namespace cods;

TEST(Vector, instantiate) {
  Vector<int> vec;
  Vector<int, 3> vec2;
  Vector<int, 3, 10> vec3;
}

TEST(Vector, ctor1) {
  Vector<int> vec;
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(Vector, ctor2) {
  int amount = 3, value = 9;
  Vector<int> vec(amount, value);
  EXPECT_EQ(vec.size(), amount);

  // Initial capacity becomes the size.
  EXPECT_EQ(vec.capacity(), amount);

  for (int i = 0; i < amount; i++) {
    EXPECT_EQ(vec[i], value);
  }
}

TEST(Vector, ctor3) {
  constexpr int amount = 3;
  std::array<int, amount> arr{{1, 3, 5}};

  Vector<int> vec(amount, arr.data());
  EXPECT_EQ(vec.size(), amount);
  EXPECT_EQ(vec.capacity(), amount);

  for (int i = 0; i < amount; i++) {
    EXPECT_EQ(vec[i], arr[i]);
  }
}

TEST(Vector, ctor4) {
  std::vector<int> svec{1, 3, 5};

  Vector<int, 3, 3> vec(svec.begin(), svec.end());
  EXPECT_EQ(vec.size(), svec.size());
  EXPECT_EQ(vec.capacity(), svec.size());

  for (int i = 0; i < svec.size(); i++) {
    EXPECT_EQ(vec[i], svec[i]);
  }
}

TEST(Vector, append) {
  Vector<int, 2, 2> vec;
  vec.append(1);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec.capacity(), 2);

  vec.append(2);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.capacity(), 2);

  vec.append(3);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec.size(), 3);

  // Went from size 2->3 so capacity is changed from 2->4 because the multiplier is 2.
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(Vector, prepend) {
  Vector<int, 2, 2> vec;
  vec.prepend(1);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec.capacity(), 2);

  vec.prepend(2);
  EXPECT_EQ(vec[0], 2);
  EXPECT_EQ(vec[1], 1);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.capacity(), 2);

  vec.prepend(3);
  EXPECT_EQ(vec[0], 3);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 1);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(Vector, insert) {
  Vector<int, 2, 2> vec;
  vec.insert(0, 1);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec.size(), 1);
  EXPECT_EQ(vec.capacity(), 2);

  vec.insert(1, 2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec.capacity(), 2);

  vec.insert(1, 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec[2], 2);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 4);
}

TEST(Vector, clear) {
  Vector<int> vec;
  vec.append(1);
  vec.append(2);
  vec.append(3);
  EXPECT_EQ(vec.size(), 3);

  vec.clear();
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 0);
}

TEST(Vector, shrinkToFit) {
  Vector<int, 1, 2> vec;
  vec.append(1);
  vec.append(2);
  vec.append(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 4);

  vec.shrinkToFit();
  EXPECT_EQ(vec.capacity(), vec.size());
}

TEST(Vector, remove) {
  Vector<int> vec;
  vec.append(1);
  vec.append(2);
  vec.append(3);

  vec.remove(2);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec.size(), 2);

  vec.remove(1);
  EXPECT_EQ(vec[0], 3);
  EXPECT_EQ(vec.size(), 1);
}

TEST(Vector, removeAt) {
  Vector<int> vec;
  vec.append(1);
  vec.append(2);
  vec.append(3);

  vec.removeAt(1);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 3);
  EXPECT_EQ(vec.size(), 2);

  vec.removeAt(0);
  EXPECT_EQ(vec[0], 3);
  EXPECT_EQ(vec.size(), 1);
}

TEST(Vector, isEmpty) {
  Vector<int> vec;
  EXPECT_TRUE(vec.isEmpty());

  vec.append(1);
  EXPECT_FALSE(vec.isEmpty());

  vec.clear();
  EXPECT_TRUE(vec.isEmpty());
}

TEST(Vector, streamOperator) {
  Vector<int> vec;
  vec << 1 << 2 << 3;
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
