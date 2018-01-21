template <typename T1, typename T2>
constexpr Pair<T1, T2>::Pair() : first(), second()
{
}

template <typename T1, typename T2>
constexpr Pair<T1, T2>::Pair(const T1 &v1, const T2 &v2) : first(v1), second(v2)
{
}

template <typename T1, typename T2>
constexpr Pair<T1, T2>::Pair(const std::pair<T1, T2> &pair) : Pair(pair.first, pair.second)
{
}

template <typename T1, typename T2>
void Pair<T1, T2>::swap(Pair<T1, T2> &other)
{
  std::swap(first, other.first);
  std::swap(second, other.second);
}

template <typename T1, typename T2>
constexpr bool Pair<T1, T2>::operator==(const Pair<T1, T2> &other) const
{
  return first == other.first && second == other.second;
}

template <typename T1, typename T2>
constexpr bool Pair<T1, T2>::operator!=(const Pair<T1, T2> &other) const
{
  return !(*this == other);
}

template <typename T1, typename T2>
constexpr bool Pair<T1, T2>::operator<(const Pair<T1, T2> &other) const
{
  return first < other.first && second < other.second;
}

template <typename T1, typename T2>
constexpr bool Pair<T1, T2>::operator<=(const Pair<T1, T2> &other) const
{
  return !(other < *this);
}

template <typename T1, typename T2>
constexpr bool Pair<T1, T2>::operator>(const Pair<T1, T2> &other) const
{
  return first > other.first && second > other.second;
}

template <typename T1, typename T2>
constexpr bool Pair<T1, T2>::operator>=(const Pair<T1, T2> &other) const
{
  return !(other > *this);
}

template <typename T1, typename T2>
inline constexpr Pair<T1, T2> makePair(const T1 &v1, const T2 &v2)
{
  return {v1, v2};
}

template <typename T1, typename T2>
inline constexpr Pair<T1, T2> makePair(const std::pair<T1, T2> &pair)
{
  return {pair};
}
