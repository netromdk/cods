#ifndef CODS_PAIR_H
#define CODS_PAIR_H

#include <utility> // swap, pair

namespace cods {

/// Implementation of a pair of two values.
template <typename T1, ///< First type.
          typename T2> ///< Second type.
class Pair {
public:
  /// Std compatibility.
  //@{
  using first_type = T1;
  using second_type = T2;
  //@}

  /// Create pair with default-constructed \p first and \p second.
  constexpr Pair();

  /// Create pair with \p first = v1 and \p second = v2.
  constexpr Pair(const T1 &v1, const T2 &v2);

  /// Create pair from \p std::pair.
  constexpr Pair(const std::pair<T1, T2> &pair);

  /// Swap values of \p this with \p other.
  void swap(Pair &other);

  Pair &operator=(const Pair &other) = default;

  constexpr bool operator==(const Pair &other) const;
  constexpr bool operator!=(const Pair &other) const;
  constexpr bool operator<(const Pair &other) const;
  constexpr bool operator<=(const Pair &other) const;
  constexpr bool operator>(const Pair &other) const;
  constexpr bool operator>=(const Pair &other) const;

  T1 first;
  T2 second;
};

template <typename T1, typename T2>
inline constexpr Pair<T1, T2> makePair(const T1 &v1, const T2 &v2);

template <typename T1, typename T2>
inline constexpr Pair<T1, T2> makePair(const std::pair<T1, T2> &pair);

#include "cods/Pair.hpp"

} // namespace cods

template <typename T1, typename T2>
inline std::ostream &operator<<(std::ostream &os, const cods::Pair<T1, T2> &pair)
{
  return os << "(" << pair.first << ", " << pair.second << ")";
}

#endif // CODS_PAIR_H
