#ifndef CODS_BITSET_H
#define CODS_BITSET_H

#include "cods/Vector.h"

#include <algorithm> // reverse
#include <cassert>
#include <cmath> // ceil, pow
#include <cstdint>
#include <iostream> // cout, endl
#include <sstream>  // ostringstream
#include <string>

namespace cods {

/// Implementation of a bitset a fixed size of bits, B.
template <int B>
class Bitset {
public:
  /// Create bitset with all zeroes.
  Bitset();

  /// Create bitset with bits from \p num.
  Bitset(const uint64_t num);

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
  uint64_t toNum() const;

  void print() const;

private:
  /// Calculates the amount of bytes needed to represent \p bites when using type \p uint64_t.
  int intsNeeded(int bits) const;

  /// Checks \p pos in bits is within the bounds of this container.
  bool checkPos(int pos) const;

  Vector<uint64_t, 1> vec;
};

#include "cods/Bitset.hpp"

} // namespace cods

#endif // CODS_BITSET_H
