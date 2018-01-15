#include "gtest/gtest.h"

#include "cods/Bitset.h"
using namespace cods;

TEST(Bitset, instantiate)
{
  Bitset<12> bs;
}

TEST(Bitset, size)
{
  Bitset<4> bs;
  EXPECT_EQ(bs.size(), 4);
}

TEST(Bitset, set)
{
  Bitset<2> bs;
  ASSERT_EQ(bs.size(), 2);
  EXPECT_FALSE(bs[0]);
  EXPECT_FALSE(bs[1]);

  bs.set(0, true);
  EXPECT_TRUE(bs[0]);

  bs.set(0, false);
  EXPECT_FALSE(bs[0]);

  bs.set(1, true);
  EXPECT_TRUE(bs[1]);

  Bitset<82> bs2;
  ASSERT_EQ(bs2.size(), 82);
  EXPECT_FALSE(bs2[70]);
  bs2.set(70, true);
  EXPECT_TRUE(bs2[70]);
}

TEST(Bitset, test)
{
  Bitset<4> bs("1010");
  EXPECT_FALSE(bs.test(0));
  EXPECT_TRUE(bs.test(1));
  EXPECT_FALSE(bs.test(2));
  EXPECT_TRUE(bs.test(3));

  EXPECT_EQ(bs.test(0), bs[0]);
  EXPECT_EQ(bs.test(1), bs[1]);
  EXPECT_EQ(bs.test(2), bs[2]);
  EXPECT_EQ(bs.test(3), bs[3]);
}

TEST(Bitset, numberCtor)
{
  // 00101010
  Bitset<8> bs(42);
  EXPECT_FALSE(bs[0]);
  EXPECT_TRUE(bs[1]);
  EXPECT_FALSE(bs[2]);
  EXPECT_TRUE(bs[3]);
  EXPECT_FALSE(bs[4]);
  EXPECT_TRUE(bs[5]);
  EXPECT_FALSE(bs[6]);
  EXPECT_FALSE(bs[7]);
}

TEST(Bitset, stringCtor)
{
  Bitset<8> bs("10101001");
  EXPECT_TRUE(bs[0]);
  EXPECT_FALSE(bs[1]);
  EXPECT_FALSE(bs[2]);
  EXPECT_TRUE(bs[3]);
  EXPECT_FALSE(bs[4]);
  EXPECT_TRUE(bs[5]);
  EXPECT_FALSE(bs[6]);
  EXPECT_TRUE(bs[7]);

  Bitset<4> bs2("BAAB", 'A', 'B');
  EXPECT_TRUE(bs2[0]);
  EXPECT_FALSE(bs2[1]);
  EXPECT_FALSE(bs2[2]);
  EXPECT_TRUE(bs2[3]);
}

TEST(Bitset, all)
{
  Bitset<4> bs("1111");
  EXPECT_TRUE(bs.all());

  Bitset<4> bs2("1010");
  EXPECT_FALSE(bs2.all());

  Bitset<4> bs3("0000");
  EXPECT_FALSE(bs3.all());
}

TEST(Bitset, any)
{
  Bitset<4> bs("1111");
  EXPECT_TRUE(bs.any());

  Bitset<4> bs2("1010");
  EXPECT_TRUE(bs2.any());

  Bitset<4> bs3("0000");
  EXPECT_FALSE(bs3.any());
}

TEST(Bitset, none)
{
  Bitset<4> bs("1111");
  EXPECT_FALSE(bs.none());

  Bitset<4> bs2("1010");
  EXPECT_FALSE(bs2.none());

  Bitset<4> bs3("0000");
  EXPECT_TRUE(bs3.none());
}

TEST(Bitset, count)
{
  Bitset<4> bs("1011");
  EXPECT_EQ(bs.count(), 3);

  Bitset<6> bs2("011011");
  EXPECT_EQ(bs2.count(), 4);
}

TEST(Bitset, reset)
{
  Bitset<4> bs("1101");
  bs.reset(2); // -> 1001
  EXPECT_TRUE(bs[0]);
  EXPECT_FALSE(bs[1]);
  EXPECT_FALSE(bs[2]);
  EXPECT_TRUE(bs[3]);

  // 1001 -> 0000
  bs.reset();
  EXPECT_FALSE(bs[0]);
  EXPECT_FALSE(bs[1]);
  EXPECT_FALSE(bs[2]);
  EXPECT_FALSE(bs[3]);
}

TEST(Bitset, flip)
{
  Bitset<4> bs("1101");
  bs.flip(2); // -> 1001
  EXPECT_TRUE(bs[0]);
  EXPECT_FALSE(bs[1]);
  EXPECT_FALSE(bs[2]);
  EXPECT_TRUE(bs[3]);

  // 1001 -> 0110
  bs.flip();
  EXPECT_FALSE(bs[0]);
  EXPECT_TRUE(bs[1]);
  EXPECT_TRUE(bs[2]);
  EXPECT_FALSE(bs[3]);
}

TEST(Bitset, operatorEquals)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1, bs1);
  EXPECT_FALSE(bs1 == bs2);
}

TEST(Bitset, operatorNotEquals)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_NE(bs1, bs2);
  EXPECT_TRUE(bs1 != bs2);
}

TEST(Bitset, operatorAND)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1 & bs2, Bitset<4>("0010"));
}

TEST(Bitset, operatorOR)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1 | bs2, Bitset<4>("0111"));
}

TEST(Bitset, operatorXOR)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1 ^ bs2, Bitset<4>("0101"));
}

TEST(Bitset, toString)
{
  Bitset<4> bs("1101");
  EXPECT_EQ(bs.toString(), "1101");

  Bitset<8> bs2(42);
  EXPECT_EQ(bs2.toString(), "00101010");
  EXPECT_EQ(bs2.toString('A', 'B'), "AABABABA");
}

TEST(Bitset, toNum)
{
  Bitset<4> bs("1101");
  EXPECT_EQ(bs.toNum(), 13ULL);

  Bitset<8> bs2(42);
  EXPECT_EQ(bs2.toNum(), 42ULL);
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
