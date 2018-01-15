#include "gtest/gtest.h"

#include "cods/Stack.h"
using namespace cods;

TEST(Stack, instantiate)
{
  Stack<int> stack;
}

TEST(Stack, push)
{
  Stack<int> stack;
  stack.push(42);
  stack.push(21);
  EXPECT_EQ(stack.size(), 2);
}

TEST(Stack, pop)
{
  Stack<int> stack;
  stack.push(1);
  stack.push(2);
  stack.push(3);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 3);

  EXPECT_EQ(stack.pop(), 3);
  EXPECT_EQ(stack.size(), 2);

  EXPECT_EQ(stack.pop(), 2);
  EXPECT_EQ(stack.size(), 1);

  EXPECT_EQ(stack.pop(), 1);
  EXPECT_EQ(stack.size(), 0);
  EXPECT_TRUE(stack.isEmpty());
}

TEST(Stack, top)
{
  Stack<int> stack;
  stack.push(42);
  EXPECT_EQ(stack.size(), 1);

  EXPECT_EQ(stack.top(), 42);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 1);

  EXPECT_EQ(stack.top(), 42);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 1);

  auto &value = stack.top();
  value = 21;

  EXPECT_EQ(stack.top(), 21);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 1);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
