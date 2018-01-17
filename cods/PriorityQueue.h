#ifndef CODS_PRIORITY_QUEUE_H
#define CODS_PRIORITY_QUEUE_H

#include <algorithm> // max, min, sort
#include <cassert>
#include <utility>

#include "cods/HashMap.h"
#include "cods/Vector.h"

namespace cods {

/// Implementation of a priority queue where each element has an integer priority.
/** The priority type must be comparable, hashable, and have an ordering. */
template <typename T,       ///< Item type.
          typename P = int> ///< Priority type.
class PriorityQueue {
public:
  PriorityQueue();
  PriorityQueue(const PriorityQueue &other) = default;
  PriorityQueue(PriorityQueue &&other);

  int size() const;
  bool isEmpty() const;

  void insert(const T &value, const P &priority);

  T popHigh();
  T popLow();

  /// Peeking assumes that the container is not empty!
  //@{
  T &peekHigh();
  const T &peekHigh() const;

  T &peekLow();
  const T &peekLow() const;
  //@}

  bool operator==(const PriorityQueue &other) const;
  bool operator!=(const PriorityQueue &other) const;

  PriorityQueue &operator=(const PriorityQueue &other);
  PriorityQueue &operator=(PriorityQueue &&other);

private:
  enum class Priority { HIGH, LOW };
  T pop(Priority priority);

  /// Maps priority to a vector of values so multiple values can have the same priority.
  HashMap<P, Vector<T>> map;

  int size_; ///< Total amount of elements in the container.
  P high;    ///< Highest priority in the container.
  P low;     ///< Lowest priority in the container.
};

#include "cods/PriorityQueue.hpp"

} // namespace cods

template <typename T, typename P>
inline std::ostream &operator<<(std::ostream &os, const cods::PriorityQueue<T, P> &queue)
{
  os << "[";
  auto copy = queue;
  while (!copy.isEmpty()) {
    os << copy.popLow();
    if (copy.size() >= 1) {
      os << ", ";
    }
  }
  return os << "]";
}

#endif // CODS_PRIORITY_QUEUE_H
