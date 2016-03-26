#ifndef CODS_QUEUE_H
#define CODS_QUEUE_H

#include "cods/Global.h"
#include "cods/Vector.h"

CODS_BEGIN_NAMESPACE

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

CODS_END_NAMESPACE

#endif // CODS_QUEUE_H
