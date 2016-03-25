#ifndef CODS_QUEUE_H
#define CODS_QUEUE_H

#include "cods/Global.h"
#include "cods/Vector.h"

CODS_BEGIN_NAMESPACE

/// Implementation of a queue container using Vector internally.
template <typename T> ///< Item type.
class Queue {
public:
  Queue();

  bool isEmpty() const;
  int size() const;

  void enqueue(const T &value);
  T dequeue();

  T &head();
  const T &head() const;

private:
  Vector<T> data;
};

#include "cods/Queue.hpp"

CODS_END_NAMESPACE

#endif // CODS_QUEUE_H
