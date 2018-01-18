#include "gtest/gtest.h"

#include <vector>

#include "cods/Vector.h"
using namespace cods;

static constexpr int _10_MIL = 10 * 1000 * 1000;
static constexpr int _10_THOU = 10 * 1000;

TEST(Vector, construct10Mil)
{
  Vector<int> vec(_10_MIL, 42);
  EXPECT_EQ(vec.size(), _10_MIL);
  EXPECT_EQ(vec.capacity(), _10_MIL);
}

TEST(StdVector, construct10Mil)
{
  std::vector<int> vec(_10_MIL, 42);
  EXPECT_EQ(vec.size(), std::size_t(_10_MIL));
  EXPECT_EQ(vec.capacity(), std::size_t(_10_MIL));
}

TEST(Vector, append10Mil)
{
  Vector<int> vec;
  for (int i = 0; i < _10_MIL; i++) {
    vec.append(i);
  }
  EXPECT_EQ(vec.size(), _10_MIL);
}

TEST(StdVector, append10Mil)
{
  std::vector<int> vec;
  for (int i = 0; i < _10_MIL; i++) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), std::size_t(_10_MIL));
}

TEST(Vector, prepend10Thou)
{
  Vector<int> vec;
  for (int i = 0; i < _10_THOU; i++) {
    vec.prepend(i);
  }
  ASSERT_EQ(vec.size(), _10_THOU);
  for (int j = 0, i = _10_THOU - 1; i >= 0; j++, i--) {
    ASSERT_EQ(vec[j], i);
  }
}

TEST(StdVector, prepend10Thou)
{
  std::vector<int> vec;
  for (int i = 0; i < _10_THOU; i++) {
    vec.insert(vec.begin(), i);
  }
  ASSERT_EQ(vec.size(), std::size_t(_10_THOU));
  for (int j = 0, i = _10_THOU - 1; i >= 0; j++, i--) {
    ASSERT_EQ(vec[j], i);
  }
}

TEST(Vector, removeLast10Mil)
{
  Vector<int> vec(_10_MIL, 42);
  ASSERT_EQ(vec.size(), _10_MIL);
  for (int i = 0; i < _10_MIL; i++) {
    vec.removeLast();
  }
  EXPECT_EQ(vec.size(), 0);
}

TEST(StdVector, removeLast10Mil)
{
  std::vector<int> vec(_10_MIL, 42);
  ASSERT_EQ(vec.size(), std::size_t(_10_MIL));
  for (int i = 0; i < _10_MIL; i++) {
    vec.erase(vec.end() - 1);
  }
  EXPECT_EQ(vec.size(), std::size_t(0));
}

TEST(Vector, removeFirst10Thou)
{
  Vector<int> vec(_10_THOU, 42);
  ASSERT_EQ(vec.size(), _10_THOU);
  for (int i = 0; i < _10_THOU; i++) {
    vec.removeFirst();
  }
  EXPECT_EQ(vec.size(), 0);
}

TEST(StdVector, removeFirst10Thou)
{
  std::vector<int> vec(_10_THOU, 42);
  ASSERT_EQ(vec.size(), std::size_t(_10_THOU));
  for (int i = 0; i < _10_THOU; i++) {
    vec.erase(vec.begin());
  }
  EXPECT_EQ(vec.size(), std::size_t(0));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
