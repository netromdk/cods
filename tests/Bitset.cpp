#include "gtest/gtest.h"

#include <bitset>

#include "cods/Bitset.h"
using namespace cods;

TEST(Bitset, instantiate)
{
  Bitset<12> bs;
}

TEST(Bitset, copyCtor)
{
  Bitset<4> bs("1010");
  decltype(bs) bs2(bs);
  EXPECT_TRUE(bs == bs2);
}

TEST(Bitset, moveCtor)
{
  Bitset<4> bs("1010");
  decltype(bs) temp(bs);

  decltype(bs) bs2(std::move(bs));
  EXPECT_TRUE(bs2 == temp);
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

TEST(Bitset, flipFirstBitOfSecondNum)
{
  Bitset<100> bs;
  EXPECT_FALSE(bs.test(0));
  bs.flip(64);
  EXPECT_TRUE(bs.test(64));

  // The first bit was flipped because indexFromBits(64) returned 0 instead of 1 earlier!
  EXPECT_FALSE(bs.test(0));
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

TEST(Bitset, operatorAnd)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1 & bs2, Bitset<4>("0010"));
}

TEST(Bitset, operatorAndAssign)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  auto &ref = bs1 &= bs2;
  EXPECT_EQ(ref, Bitset<4>("0010"));
  EXPECT_EQ(ref, bs1);
}

TEST(Bitset, operatorOr)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1 | bs2, Bitset<4>("0111"));
}

TEST(Bitset, operatorOrAssign)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  auto &ref = bs1 |= bs2;
  EXPECT_EQ(ref, Bitset<4>("0111"));
  EXPECT_EQ(ref, bs1);
}

TEST(Bitset, operatorXor)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  EXPECT_EQ(bs1 ^ bs2, Bitset<4>("0101"));
}

TEST(Bitset, operatorXorAssign)
{
  Bitset<4> bs1("0110");
  Bitset<4> bs2("0011");
  auto &ref = bs1 ^= bs2;
  EXPECT_EQ(ref, Bitset<4>("0101"));
  EXPECT_EQ(ref, bs1);
}

TEST(Bitset, operatorNot)
{
  Bitset<4> bs("0110");
  EXPECT_EQ(~bs, Bitset<4>("1001"));
}

TEST(Bitset, operatorShiftRight)
{
  Bitset<4> bs("1110");
  EXPECT_EQ(bs >> 0, Bitset<4>("1110"));
  EXPECT_EQ(bs >> 1, Bitset<4>("0111"));
  EXPECT_EQ(bs >> 2, Bitset<4>("0011"));
  EXPECT_EQ(bs >> 3, Bitset<4>("0001"));

  Bitset<1> bs2("1");
  EXPECT_EQ(bs2 >> 1, Bitset<1>("0"));
  EXPECT_EQ(bs2 >> 2, Bitset<1>("0"));

  Bitset<100> bs3;
  bs3.flip(99); // 10000...0
  EXPECT_FALSE(bs3.test(0));
  auto res = bs3 >> 99;
  EXPECT_TRUE(res.test(0));
}

TEST(Bitset, operatorShiftRightAssign)
{
  Bitset<4> bs("1110");
  auto &ref = bs >>= 2;
  EXPECT_EQ(ref, Bitset<4>("0011"));
  EXPECT_EQ(ref, bs);
}

TEST(Bitset, operatorShiftLeft)
{
  Bitset<4> bs("0111");
  EXPECT_EQ(bs << 0, Bitset<4>("0111"));
  EXPECT_EQ(bs << 1, Bitset<4>("1110"));
  EXPECT_EQ(bs << 2, Bitset<4>("1100"));
  EXPECT_EQ(bs << 3, Bitset<4>("1000"));

  Bitset<100> bs2;
  bs2.flip(0); // 00...01
  EXPECT_TRUE(bs2.test(0));
  auto res = bs2 << 99; // 100...0
  EXPECT_FALSE(res.test(0));
  EXPECT_TRUE(res.test(99));
}

TEST(Bitset, operatorShiftLeftAssign)
{
  Bitset<4> bs("0111");
  auto &ref = bs <<= 2;
  EXPECT_EQ(ref, Bitset<4>("1100"));
  EXPECT_EQ(ref, bs);
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

TEST(Bitset, stdBitsetCompare)
{
  const auto num = 0xFEEDFACE;
  const auto bits = sizeof(num) * 8;
  Bitset<bits> bs(num);
  std::bitset<bits> bs2(num);
  EXPECT_EQ(bs.toString(), bs2.to_string());
  EXPECT_EQ(bs.toNum(), num);
  EXPECT_EQ(bs.toNum(), bs2.to_ullong());
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
