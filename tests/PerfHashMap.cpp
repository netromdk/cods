#include "gtest/gtest.h"

#include <unordered_map>

#include "cods/HashMap.h"
using namespace cods;

static constexpr int _1_MIL = 1 * 1000 * 1000;

TEST(HashMap, construct1M)
{
  HashMap<int, int> map;
  for (int i = 0; i < _1_MIL; i++) {
    map.insert(i, i);
  }
  EXPECT_EQ(map.size(), _1_MIL);
}

TEST(StdUnorderedMap, construct1M)
{
  std::unordered_map<int, int> map;
  for (int i = 0; i < _1_MIL; i++) {
    map.insert({i, i});
  }
  EXPECT_EQ(map.size(), std::size_t(_1_MIL));
}

TEST(HashMap, remove1M)
{
  HashMap<int, int> map;
  for (int i = 0; i < _1_MIL; i++) {
    map.insert(i, i);
  }
  ASSERT_EQ(map.size(), _1_MIL);
  for (auto it = map.begin(); it != map.end();) {
    it = map.erase(it);
  }
  EXPECT_TRUE(map.isEmpty());
}

TEST(StdUnorderedMap, remove1M)
{
  std::unordered_map<int, int> map;
  for (int i = 0; i < _1_MIL; i++) {
    map.insert({i, i});
  }
  ASSERT_EQ(map.size(), std::size_t(_1_MIL));
  for (auto it = map.begin(); it != map.end();) {
    it = map.erase(it);
  }
  EXPECT_TRUE(map.empty());
}

TEST(HashMap, find1M)
{
  HashMap<int, int> map;
  for (int i = 0; i < _1_MIL; i++) {
    map.insert(i, i);
  }
  ASSERT_EQ(map.size(), _1_MIL);
  for (int i = 0; i < _1_MIL; i++) {
    auto it = map.find(i);
    ASSERT_NE(it, map.end());
    ASSERT_EQ(it.key(), i);
    ASSERT_EQ(it.value(), i);
  }
}

TEST(StdUnorderedMap, find1M)
{
  std::unordered_map<int, int> map;
  for (int i = 0; i < _1_MIL; i++) {
    map.insert({i, i});
  }
  ASSERT_EQ(map.size(), std::size_t(_1_MIL));
  for (int i = 0; i < _1_MIL; i++) {
    auto it = map.find(i);
    ASSERT_NE(it, map.end());
    ASSERT_EQ(it->first, i);
    ASSERT_EQ(it->second, i);
  }
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return (RUN_ALL_TESTS());
}
