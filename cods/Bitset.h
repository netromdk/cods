#ifndef CODS_BITSET_H
#define CODS_BITSET_H

#include "cods/Vector.h"

#include <algorithm> // reverse
#include <cassert>
#include <cmath> // ceil, pow
#include <cstdint>
#include <functional>
#include <iostream> // cout, endl
#include <sstream>  // ostringstream
#include <string>

namespace cods {

/// Implementation of a bitset a fixed size of bits, B.
template <int B>
class Bitset {
public:
  /// Type used for dividing up the bits into.
  using NumType = uint64_t;

  /// Bits per number.
  static constexpr int BITS_PER_NUM = sizeof(NumType) * 8;

  /// Create bitset with all zeroes.
  Bitset();

  /// Create bitset with bits from \p num.
  Bitset(const NumType num);

  /// Create bitset with bits from \p str.
  /** It must contain only \p zero and \p one characters. */
  Bitset(const std::string &str, const char zero = '0', const char one = '1');

  /// Size in bits.
  int size() const;

  bool test(int pos) const;
  bool operator[](int pos) const;

  void set(int pos, bool on);

  /// Reset all values to \p false.
  void reset();

  /// Reset value at \p pos to \p false.
  void reset(int pos);

  /// Flip all values.
  void flip();

  /// Flip value at \p pos.
  void flip(int pos);

  /// Checks if all bits are \p true.
  bool all() const;

  /// Checks if any bits are \p true.
  bool any() const;

  /// Checks if no bits are \p true.
  bool none() const;

  /// Amount of bits that is \p true.
  int count() const;

  bool operator==(const Bitset<B> &other) const;
  bool operator!=(const Bitset<B> &other) const;

  /// Returns the bitwise AND of \p and \p other.
  Bitset<B> operator&(const Bitset<B> &other) const;

  /// Returns the bitwise OR of \p and \p other.
  Bitset<B> operator|(const Bitset<B> &other) const;

  /// Returns the bitwise XOR of \p and \p other.
  Bitset<B> operator^(const Bitset<B> &other) const;

  /// Create string from bitset using \p zero and \p one.
  std::string toString(const char zero = '0', const char one = '1') const;

  /// Converts bitset into the number it represents.
  NumType toNum() const;

private:
  /// Returns the index of the \p NumType that contains the \p bits as position.
  int indexFromBits(int bits) const;

  /// Checks \p pos in bits is within the bounds of this container.
  bool checkPos(int pos) const;

  /// Call \p func on all bits, or until returning false.
  bool invokeOnAll(const std::function<bool(int)> &func) const;

  /// Call \p func on all bits, or until returning true.
  bool breakOnFirst(const std::function<bool(int)> &func) const;

  Vector<NumType, 1> vec;
};

#include "cods/Bitset.hpp"

} // namespace cods

template <int B>
inline std::ostream &operator<<(std::ostream &os, const cods::Bitset<B> &bs)
{
  return os << "\"" << bs.toString() << "\"";
}

#endif // CODS_BITSET_H
