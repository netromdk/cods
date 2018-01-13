#include "gtest/gtest.h"

#include "cods/Deque.h"
using namespace cods;

TEST(Deque, instantiate)
{
  Deque<int> deque;
}

TEST(Deque, pushBack)
{
  Deque<int> deque;
  deque.pushBack(1);
  deque.pushBack(2);

  ASSERT_EQ(deque.size(), 2);
  EXPECT_EQ(deque[0], 1);
  EXPECT_EQ(deque[1], 2);
}

TEST(Deque, pushFront)
{
  Deque<int> deque;
  deque.pushFront(1);
  deque.pushFront(2);

  ASSERT_EQ(deque.size(), 2);
  EXPECT_EQ(deque[0], 2);
  EXPECT_EQ(deque[1], 1);
}

TEST(Deque, popBack)
{
  Deque<int> deque;
  deque.pushBack(1);
  deque.pushBack(2);

  EXPECT_EQ(deque.popBack(), 2);
  ASSERT_EQ(deque.size(), 1);
  EXPECT_EQ(deque[0], 1);
}

TEST(Deque, popFront)
{
  Deque<int> deque;
  deque.pushBack(1);
  deque.pushBack(2);

  EXPECT_EQ(deque.popFront(), 1);
  ASSERT_EQ(deque.size(), 1);
  EXPECT_EQ(deque[0], 2);
}

TEST(Deque, back)
{
  Deque<int> deque;
  deque.pushBack(1);
  deque.pushBack(2);

  EXPECT_EQ(deque.back(), 2);
}

TEST(Deque, front)
{
  Deque<int> deque;
  deque.pushBack(1);
  deque.pushBack(2);

  EXPECT_EQ(deque.front(), 1);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
