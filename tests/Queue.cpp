#include "gtest/gtest.h"

#include "cods/Queue.h"
using namespace cods;

TEST(Queue, instantiate) {
  Queue<int> queue;
}

TEST(Queue, enqueue) {
  Queue<int> queue;
  queue.enqueue(42);
  queue.enqueue(21);
  EXPECT_EQ(queue.size(), 2);
}

TEST(Queue, dequeue) {
  Queue<int> queue;
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.size(), 3);

  EXPECT_EQ(queue.dequeue(), 1);
  EXPECT_EQ(queue.size(), 2);

  EXPECT_EQ(queue.dequeue(), 2);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.dequeue(), 3);
  EXPECT_EQ(queue.size(), 0);
  EXPECT_TRUE(queue.isEmpty());
}

TEST(Queue, head) {
  Queue<int> queue;
  queue.enqueue(42);
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.head(), 42);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.size(), 1);

  EXPECT_EQ(queue.head(), 42);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.size(), 1);

  auto &value = queue.head();
  value = 21;

  EXPECT_EQ(queue.head(), 21);
  EXPECT_FALSE(queue.isEmpty());
  EXPECT_EQ(queue.size(), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
