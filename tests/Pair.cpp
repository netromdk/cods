#include "gtest/gtest.h"

#include <utility>

#include "cods/Pair.h"
using namespace cods;

TEST(Pair, instantiate)
{
  Pair<int, int> p1(1, 2);
  Pair<float, int> p2(1.0f, 2);
  Pair<int, double> p3(1, 2.0);
}

TEST(Pair, first)
{
  Pair<int, int> p1(1, 2);
  EXPECT_EQ(p1.first, 1);

  Pair<int, int> p2;
  EXPECT_EQ(p2.first, int());
}

TEST(Pair, second)
{
  Pair<int, int> p1(1, 2);
  EXPECT_EQ(p1.second, 2);

  Pair<int, int> p2;
  EXPECT_EQ(p2.second, int());
}

TEST(Pair, makePair)
{
  const auto p = makePair(1, 2);
  EXPECT_EQ(p.first, 1);
  EXPECT_EQ(p.second, 2);
}

TEST(Pair, constexpr)
{
  constexpr Pair<int, int> p1(1, 2);
  static_assert(p1.first == 1, "p1.first is not 1!");
  static_assert(p1.second == 2, "p1.second is not 2!");

  constexpr auto p2 = makePair(1, 2);
  static_assert(p2.first == 1, "p2.first is not 1!");
  static_assert(p2.second == 2, "p2.second is not 2!");
}

TEST(Pair, operatorEquals)
{
  const auto p1 = makePair(1, 2);
  const auto p2 = makePair(10, 20);
  EXPECT_EQ(p1, p1);
  EXPECT_FALSE(p1 == p2);
}

TEST(Pair, operatorNotEquals)
{
  const auto p1 = makePair(1, 2);
  const auto p2 = makePair(10, 20);
  EXPECT_NE(p1, p2);
  EXPECT_TRUE(p1 != p2);
}

TEST(Pair, operatorLessThan)
{
  const auto p1 = makePair(1, 2);
  const auto p2 = makePair(10, 20);
  EXPECT_TRUE(p1 < p2);
}

TEST(Pair, operatorLessThanEquals)
{
  const auto p1 = makePair(1, 2);
  const auto p2 = makePair(10, 20);
  EXPECT_TRUE(p1 <= p2);

  const auto p3 = makePair(10, 20);
  const auto p4 = makePair(10, 20);
  EXPECT_TRUE(p3 <= p4);
}

TEST(Pair, operatorGreaterThan)
{
  const auto p1 = makePair(100, 200);
  const auto p2 = makePair(10, 20);
  EXPECT_TRUE(p1 > p2);
}

TEST(Pair, operatorGreaterThanEquals)
{
  const auto p1 = makePair(100, 200);
  const auto p2 = makePair(10, 20);
  EXPECT_TRUE(p1 >= p2);

  const auto p3 = makePair(10, 20);
  const auto p4 = makePair(10, 20);
  EXPECT_TRUE(p3 >= p4);
}

TEST(Pair, operatorAssign)
{
  auto p = makePair(1, 2);
  const auto p2 = makePair(10, 20);
  auto &ref = (p = p2);
  EXPECT_EQ(ref, p2);
  EXPECT_EQ(ref, p);
}

TEST(Pair, swap)
{
  auto p1 = makePair(1, 2);
  auto p2 = makePair(10, 20);
  p1.swap(p2);
  EXPECT_EQ(p1.first, 10);
  EXPECT_EQ(p1.second, 20);
  EXPECT_EQ(p2.first, 1);
  EXPECT_EQ(p2.second, 2);
}

TEST(Pair, fromStdPair)
{
  const Pair<int, int> p1(std::make_pair(1, 2));
  EXPECT_EQ(p1, makePair(1, 2));

  const auto p2 = makePair(std::make_pair(1, 2));
  EXPECT_EQ(p2, makePair(1, 2));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
