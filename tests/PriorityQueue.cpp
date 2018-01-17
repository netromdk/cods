#include "gtest/gtest.h"

#include <string>

#include "cods/PriorityQueue.h"
using namespace cods;

TEST(PriorityQueue, instantiate)
{
  PriorityQueue<int> queue;
}

TEST(PriorityQueue, copyCtor)
{
  PriorityQueue<int> queue;
  queue.insert(1, 0);
  queue.insert(2, 1);
  queue.insert(3, 2);

  decltype(queue) queue2(queue);
  EXPECT_TRUE(queue == queue2);
}

TEST(PriorityQueue, moveCtor)
{
  PriorityQueue<int> queue;
  queue.insert(1, 0);
  queue.insert(2, 1);
  queue.insert(3, 2);

  decltype(queue) temp(queue);

  decltype(queue) queue2(std::move(queue));
  EXPECT_TRUE(queue.isEmpty());
  EXPECT_TRUE(queue2 == temp);
}

TEST(PriorityQueue, size)
{
  PriorityQueue<int> queue;
  EXPECT_EQ(queue.size(), 0);
}

TEST(PriorityQueue, isEmpty)
{
  PriorityQueue<int> queue;
  EXPECT_TRUE(queue.isEmpty());
}

TEST(PriorityQueue, insert)
{
  PriorityQueue<int> queue;
  queue.insert(10, 1);
  queue.insert(20, 2);
  queue.insert(30, 3);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.size(), 3);
}

TEST(PriorityQueue, peekHigh)
{
  PriorityQueue<int> queue;
  queue.insert(10, 1);
  queue.insert(20, 2);
  queue.insert(30, 3);
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);
  EXPECT_EQ(queue.peekHigh(), 30);
}

TEST(PriorityQueue, peekLow)
{
  PriorityQueue<int> queue;
  queue.insert(10, 1);
  queue.insert(20, 2);
  queue.insert(30, 3);
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);
  EXPECT_EQ(queue.peekLow(), 10);
}

TEST(PriorityQueue, popHigh)
{
  PriorityQueue<int> queue;
  EXPECT_EQ(queue.popHigh(), int());

  queue.insert(10, 1);
  queue.insert(20, 2);
  queue.insert(30, 3);
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.popHigh(), 30);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.popHigh(), 20);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.popHigh(), 10);
  EXPECT_EQ(queue.size(), 0);
}

TEST(PriorityQueue, popHighSamePriority)
{
  PriorityQueue<int> queue;
  EXPECT_EQ(queue.popHigh(), int());

  queue.insert(10, 3);
  queue.insert(20, 3);
  queue.insert(30, 3);
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.popHigh(), 10);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.popHigh(), 20);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.popHigh(), 30);
  EXPECT_EQ(queue.size(), 0);
}

TEST(PriorityQueue, popLow)
{
  PriorityQueue<int> queue;
  EXPECT_EQ(queue.popLow(), int());

  queue.insert(10, 1);
  queue.insert(20, 2);
  queue.insert(30, 3);
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.popLow(), 10);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.popLow(), 20);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.popLow(), 30);
  EXPECT_EQ(queue.size(), 0);
}

TEST(PriorityQueue, popLowSamePriority)
{
  PriorityQueue<int> queue;
  EXPECT_EQ(queue.popLow(), int());

  queue.insert(10, 1);
  queue.insert(20, 1);
  queue.insert(30, 1);
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.popLow(), 10);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.popLow(), 20);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.popLow(), 30);
  EXPECT_EQ(queue.size(), 0);
}

TEST(PriorityQueue, stringPriorityType)
{
  PriorityQueue<int, std::string> queue;
  EXPECT_EQ(queue.popHigh(), int());

  queue.insert(10, "a");
  queue.insert(20, "aa");
  queue.insert(30, "aaa");
  ASSERT_FALSE(queue.isEmpty());
  ASSERT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.popHigh(), 30);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.popLow(), 10);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.popHigh(), 20);
  EXPECT_EQ(queue.size(), 0);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
