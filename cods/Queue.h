#ifndef CODS_QUEUE_H
#define CODS_QUEUE_H

#include "cods/Vector.h"

namespace cods {

/// Implementation of a queue container extending Vector.
template <typename T> ///< Item type.
class Queue : public Vector<T> {
public:
  Queue();

  void enqueue(const T &value);
  T dequeue();

  T &head();
  const T &head() const;
};

#include "cods/Queue.hpp"

} // namespace cods

#endif // CODS_QUEUE_H
