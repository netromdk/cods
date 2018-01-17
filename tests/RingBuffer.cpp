#include "gtest/gtest.h"

#include "cods/RingBuffer.h"
using namespace cods;

TEST(RingBuffer, instantiate)
{
  RingBuffer<int, 3> buf;
}

TEST(RingBuffer, copyCtor)
{
  RingBuffer<int, 3> buf;
  buf.insert(1);
  buf.insert(2);
  buf.insert(3);

  decltype(buf) buf2(buf);
  EXPECT_TRUE(buf == buf2);
}

TEST(RingBuffer, moveCtor)
{
  RingBuffer<int, 3> buf;
  buf.insert(1);
  buf.insert(2);
  buf.insert(3);

  decltype(buf) temp(buf);

  decltype(buf) buf2(std::move(buf));
  EXPECT_TRUE(buf.isEmpty());
  EXPECT_TRUE(buf2 == temp);
}

TEST(RingBuffer, size)
{
  RingBuffer<int, 3> buf;
  EXPECT_EQ(buf.size(), 0);
}

TEST(RingBuffer, capacity)
{
  RingBuffer<int, 3> buf;
  EXPECT_EQ(buf.capacity(), 3);
}

TEST(RingBuffer, isEmpty)
{
  RingBuffer<int, 3> buf;
  EXPECT_TRUE(buf.isEmpty());
}

TEST(RingBuffer, isFull)
{
  RingBuffer<int, 3> buf;
  EXPECT_FALSE(buf.isFull());
}

TEST(RingBuffer, insert)
{
  RingBuffer<int, 3> buf;
  buf.insert(1);
  buf.insert(2);
  ASSERT_EQ(buf.size(), 2);
  ASSERT_FALSE(buf.isEmpty());
  ASSERT_FALSE(buf.isFull());
  EXPECT_EQ(buf.at(0), 1);
  EXPECT_EQ(buf.at(1), 2);

  buf.insert(3);
  ASSERT_EQ(buf.size(), 3);
  ASSERT_FALSE(buf.isEmpty());
  ASSERT_TRUE(buf.isFull());
  EXPECT_EQ(buf.at(2), 3);

  buf.insert(4);
  ASSERT_EQ(buf.size(), 3);
  ASSERT_FALSE(buf.isEmpty());
  ASSERT_TRUE(buf.isFull());
  EXPECT_EQ(buf.at(0), 2);
  EXPECT_EQ(buf.at(1), 3);
  EXPECT_EQ(buf.at(2), 4);
}

TEST(RingBuffer, removeAt)
{
  RingBuffer<int, 3> buf;
  buf.insert(1);
  buf.insert(2);
  ASSERT_EQ(buf.size(), 2);
  ASSERT_FALSE(buf.isEmpty());

  buf.removeAt(0);
  ASSERT_EQ(buf.size(), 1);
  ASSERT_FALSE(buf.isEmpty());
  EXPECT_EQ(buf[0], 2);

  buf.removeAt(0);
  ASSERT_EQ(buf.size(), 0);
  ASSERT_TRUE(buf.isEmpty());
}

TEST(RingBuffer, at)
{
  RingBuffer<int, 3> buf;
  buf.insert(1);
  buf.insert(2);
  buf.insert(3);

  EXPECT_EQ(buf.at(0), 1);
  EXPECT_EQ(buf.at(1), 2);
  EXPECT_EQ(buf.at(2), 3);

  EXPECT_EQ(buf[0], buf.at(0));
  EXPECT_EQ(buf[1], buf.at(1));
  EXPECT_EQ(buf[2], buf.at(2));
}

TEST(RingBuffer, toVector)
{
  RingBuffer<int, 3> buf;
  buf.insert(1);
  buf.insert(2);
  buf.insert(3);

  const auto vec = buf.toVector();
  ASSERT_EQ(vec.size(), buf.size());
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
}

TEST(RingBuffer, iterate)
{
  RingBuffer<int, 3> buf;
  buf.insert(0);
  buf.insert(1);
  buf.insert(2);

  int i = 0;
  for (const auto value : buf) {
    EXPECT_EQ(buf[i], value);
    i++;
  }
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
