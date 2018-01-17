template <int B>
Bitset<B>::Bitset() : vec(indexFromBits(B) + 1, NumType(0))
{
  static_assert(B > 0, "Bitset size must be positive!");
}

template <int B>
Bitset<B>::Bitset(const NumType num) : Bitset()
{
  vec[0] = num;
}

template <int B>
Bitset<B>::Bitset(const std::string &str, const char zero, const char one) : Bitset()
{
  assert(str.size() <= B && "String requires more bits!");
  int pos = 0;
  for (auto it = str.rbegin(); it != str.rend(); ++it, ++pos) {
    const auto ch = *it;
    assert((ch == zero || ch == one) && "Must contain only valid zero/one values!");
    set(pos, ch == one);
  }
}

template <int B>
int Bitset<B>::size() const
{
  return B;
}

template <int B>
bool Bitset<B>::test(int pos) const
{
  if (!checkPos(pos)) {
    return false;
  }

  const auto n = indexFromBits(pos);
  return (vec[n] >> (pos - n * BITS_PER_NUM)) & NumType(1);
}

template <int B>
bool Bitset<B>::operator[](int pos) const
{
  return test(pos);
}

template <int B>
void Bitset<B>::set(int pos, bool on)
{
  if (!checkPos(pos)) {
    return;
  }

  // Set bit at \p pos to be 1 if \p on and 0 otherwise.
  const auto n = indexFromBits(pos);
  NumType x = (on ? 1 : 0);
  vec[n] = vec[n] ^ ((-x ^ vec[n]) & (NumType(1) << (pos - n * BITS_PER_NUM)));
}

template <int B>
void Bitset<B>::reset()
{
  // It's more efficient setting the number of integers to zero than all bits to zero.
  for (int i = 0; i < vec.size(); i++) {
    vec[i] = 0;
  }
}

template <int B>
void Bitset<B>::reset(int pos)
{
  set(pos, false);
}

template <int B>
void Bitset<B>::flip()
{
  invokeOnAll([this](int pos) {
    flip(pos);
    return true;
  });
}

template <int B>
void Bitset<B>::flip(int pos)
{
  set(pos, !test(pos));
}

template <int B>
bool Bitset<B>::all() const
{
  return invokeOnAll([this](int pos) { return test(pos); });
}

template <int B>
bool Bitset<B>::any() const
{
  return breakOnFirst([this](int pos) { return test(pos); });
}

template <int B>
bool Bitset<B>::none() const
{
  return !breakOnFirst([this](int pos) { return test(pos); });
}

template <int B>
int Bitset<B>::count() const
{
  int res = 0;
  invokeOnAll([this, &res](int pos) {
    if (test(pos)) {
      res++;
    }
    return true;
  });
  return res;
}

template <int B>
bool Bitset<B>::operator==(const Bitset<B> &other) const
{
  return invokeOnAll([this, &other](int pos) { return test(pos) == other.test(pos); });
}

template <int B>
bool Bitset<B>::operator!=(const Bitset<B> &other) const
{
  return !(*this == other);
}

template <int B>
Bitset<B> Bitset<B>::operator&(const Bitset<B> &other) const
{
  Bitset<B> res = *this;
  invokeOnAll([&res, &other](int pos) {
    res.set(pos, res.test(pos) && other.test(pos));
    return true;
  });
  return res;
}

template <int B>
Bitset<B> Bitset<B>::operator|(const Bitset<B> &other) const
{
  Bitset<B> res = *this;
  invokeOnAll([&res, &other](int pos) {
    res.set(pos, res.test(pos) || other.test(pos));
    return true;
  });
  return res;
}

template <int B>
Bitset<B> Bitset<B>::operator^(const Bitset<B> &other) const
{
  Bitset<B> res = *this;
  invokeOnAll([&res, &other](int pos) {
    res.set(pos, res.test(pos) != other.test(pos));
    return true;
  });
  return res;
}

template <int B>
std::string Bitset<B>::toString(const char zero, const char one) const
{
  using namespace std;

  ostringstream ss;
  invokeOnAll([this, &ss, zero, one](int pos) {
    ss << (test(pos) ? one : zero);
    return true;
  });

  auto s = ss.str();
  std::reverse(s.begin(), s.end());
  return s;
}

template <int B>
typename Bitset<B>::NumType Bitset<B>::toNum() const
{
  NumType res = 0;
  invokeOnAll([this, &res](int pos) {
    if (test(pos)) {
      res += std::pow(2, pos);
    }
    return true;
  });
  return res;
}

template <int B>
int Bitset<B>::indexFromBits(int bits) const
{
  if (bits == 0) return 0;
  const auto amount = static_cast<double>(bits) / (static_cast<double>(BITS_PER_NUM));
  return static_cast<int>(std::ceil(amount)) - 1;
}

template <int B>
bool Bitset<B>::checkPos(int pos) const
{
  const bool within = pos < B;
  assert(within && "Position not within bounds!");
  return within;
}

template <int B>
bool Bitset<B>::invokeOnAll(const std::function<bool(int)> &func) const
{
  for (int pos = 0; pos < B; pos++) {
    if (!func(pos)) {
      return false;
    }
  }
  return true;
}

template <int B>
bool Bitset<B>::breakOnFirst(const std::function<bool(int)> &func) const
{
  for (int pos = 0; pos < B; pos++) {
    if (func(pos)) {
      return true;
    }
  }
  return false;
}
