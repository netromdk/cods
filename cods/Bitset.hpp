template <int B>
Bitset<B>::Bitset() : vec(intsNeeded(B) + 1, uint64_t(0))
{
  static_assert(B > 0, "Bitset size must be positive!");
}

template <int B>
Bitset<B>::Bitset(const uint64_t num) : Bitset()
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

  const auto n = intsNeeded(pos);
  return (vec[n] >> (pos - n * sizeof(uint64_t) * 8)) & 1U;
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
  const auto n = intsNeeded(pos);
  uint64_t x = (on ? 1 : 0);
  vec[n] = vec[n] ^ ((-x ^ vec[n]) & (1UL << (pos - n * sizeof(uint64_t) * 8)));
}

template <int B>
void Bitset<B>::reset()
{
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
  for (int pos = 0; pos < B; pos++) {
    flip(pos);
  }
}

template <int B>
void Bitset<B>::flip(int pos)
{
  set(pos, !test(pos));
}

template <int B>
bool Bitset<B>::all() const
{
  for (int pos = 0; pos < B; pos++) {
    if (!test(pos)) {
      return false;
    }
  }

  return true;
}

template <int B>
bool Bitset<B>::any() const
{
  for (int pos = 0; pos < B; pos++) {
    if (test(pos)) {
      return true;
    }
  }

  return false;
}

template <int B>
bool Bitset<B>::none() const
{
  for (int pos = 0; pos < B; pos++) {
    if (test(pos)) {
      return false;
    }
  }

  return true;
}

template <int B>
int Bitset<B>::count() const
{
  int res = 0;
  for (int pos = 0; pos < B; pos++) {
    if (test(pos)) {
      res++;
    }
  }

  return res;
}

template <int B>
bool Bitset<B>::operator==(const Bitset<B> &other) const
{
  for (int pos = 0; pos < B; pos++) {
    if (test(pos) != other.test(pos)) {
      return false;
    }
  }
  return true;
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
  for (int pos = 0; pos < B; pos++) {
    res.set(pos, res.test(pos) && other.test(pos));
  }
  return res;
}

template <int B>
Bitset<B> Bitset<B>::operator|(const Bitset<B> &other) const
{
  Bitset<B> res = *this;
  for (int pos = 0; pos < B; pos++) {
    res.set(pos, res.test(pos) || other.test(pos));
  }
  return res;
}

template <int B>
Bitset<B> Bitset<B>::operator^(const Bitset<B> &other) const
{
  Bitset<B> res = *this;
  for (int pos = 0; pos < B; pos++) {
    res.set(pos, res.test(pos) != other.test(pos));
  }
  return res;
}

template <int B>
std::string Bitset<B>::toString(const char zero, const char one) const
{
  using namespace std;
  ostringstream ss;
  for (int pos = 0; pos < B; pos++) {
    ss << (test(pos) ? one : zero);
  }
  auto s = ss.str();
  std::reverse(s.begin(), s.end());
  return s;
}

template <int B>
uint64_t Bitset<B>::toNum() const
{
  uint64_t res = 0;
  for (int pos = 0; pos < B; pos++) {
    if (test(pos)) {
      res += std::pow(2, pos);
    }
  }
  return res;
}

template <int B>
void Bitset<B>::print() const
{
  std::cout << toString() << std::endl;
}

template <int B>
int Bitset<B>::intsNeeded(int bits) const
{
  if (bits == 0) return 0;
  const auto amount = static_cast<double>(bits) / (static_cast<double>(sizeof(uint64_t)) * 8.0);
  return static_cast<int>(std::ceil(amount)) - 1;
}

template <int B>
bool Bitset<B>::checkPos(int pos) const
{
  const bool within = intsNeeded(pos) <= intsNeeded(B);
  assert(within && "Position not within bounds!");
  return within;
}
