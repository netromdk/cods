#include <array>
#include <vector>
#include <utility> // move

#include "gtest/gtest.h"

#include "cods/Vector.h"
using namespace cods;

TEST(Vector, instantiate) {
  Vector<int> vec;
  Vector<int, 3> vec2;
  Vector<int, 3, 10> vec3;
}

TEST(Vector, copyCtor) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  decltype(vec) vec2(vec);
  EXPECT_TRUE(vec == vec2);
}

TEST(Vector, moveCtor) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  decltype(vec) temp(vec);

  decltype(vec) vec2(std::move(vec));
  EXPECT_TRUE(vec.isEmpty());
  EXPECT_TRUE(vec2 == temp);
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

TEST(Vector, appendVector) {
  Vector<int> vec, vec2;
  vec2 << 1 << 2 << 3;

  vec.append(vec2);
  EXPECT_EQ(vec, vec2);

  vec.clear();
  vec << vec2;
  EXPECT_EQ(vec, vec2);
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

TEST(Vector, insertIterator) {
  Vector<int> vec;
  auto it1 = vec.insert(vec.begin(), 1);
  auto it2 = vec.insert(it1, 2);
  vec.insert(it2, 3);
  EXPECT_EQ(vec[0], 3);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 1);
  EXPECT_EQ(vec.size(), 3);
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

TEST(Vector, reserve) {
  Vector<int, 1, 2> vec;
  vec.append(1);
  vec.append(2);
  vec.append(3);
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec.capacity(), 4);

  vec.reserve(10);
  EXPECT_EQ(vec.capacity(), 10);

  vec.reserve(3);
  EXPECT_EQ(vec.capacity(), 10);
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

TEST(Vector, contains) {
  Vector<int> vec;
  EXPECT_FALSE(vec.contains(1));

  vec << 1 << 2 << 3;
  EXPECT_TRUE(vec.contains(1));
  EXPECT_FALSE(vec.contains(4));
}

TEST(Vector, streamOperator) {
  Vector<int> vec;
  vec << 1 << 2 << 3;
  EXPECT_EQ(vec.size(), 3);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(Vector, equalsOperator) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  decltype(vec) vec2;
  vec2 << 1 << 2 << 3;
  EXPECT_TRUE(vec == vec2);

  decltype(vec) vec3;
  EXPECT_FALSE(vec == vec3);

  decltype(vec) vec4;
  vec4 << 3 << 2 << 1;
  EXPECT_FALSE(vec == vec4);
}

TEST(Vector, notEqualsOperator) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  decltype(vec) vec2;
  vec2 << 1 << 2 << 3;
  EXPECT_FALSE(vec != vec2);

  decltype(vec) vec3;
  EXPECT_TRUE(vec != vec3);

  decltype(vec) vec4;
  vec4 << 3 << 2 << 1;
  EXPECT_TRUE(vec != vec4);
}

TEST(Vector, hash) {
  Vector<int> vec;
  vec << 1 << 2 << 3;
  auto h = std::hash<decltype(vec)>()(vec);

  decltype(vec) vec2;
  vec2 << 3 << 2 << 1;
  auto h2 = std::hash<decltype(vec2)>()(vec2);

  EXPECT_NE(h, h2);
}

TEST(Vector, iterator) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  int i = 0;
  for (const auto &elm : vec) {
    EXPECT_EQ(vec[i], elm);
    i++;
  }
}

TEST(Vector, refAssign) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  EXPECT_EQ(vec[0], 1);

  vec[0] = 42;
  EXPECT_EQ(vec[0], 42);
}

TEST(Vector, indexOf) {
  Vector<int> vec;
  vec << 1 << 2 << 3;

  EXPECT_EQ(vec.indexOf(1), 0);
  EXPECT_EQ(vec.indexOf(3), 2);
  EXPECT_EQ(vec.indexOf(30), -1);
  EXPECT_EQ(vec.indexOf(2, 1), 1);
  EXPECT_EQ(vec.indexOf(2, 2), -1);
}

TEST(Vector, lastIndexOf) {
  Vector<int> vec;
  vec << 1 << 2 << 2 << 3 << 1;

  EXPECT_EQ(vec.lastIndexOf(1), 4);
  EXPECT_EQ(vec.lastIndexOf(3), 3);
  EXPECT_EQ(vec.lastIndexOf(30), -1);
  EXPECT_EQ(vec.lastIndexOf(2, 0), -1);
  EXPECT_EQ(vec.lastIndexOf(2, 1), 1);
  EXPECT_EQ(vec.lastIndexOf(2, 2), 2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
