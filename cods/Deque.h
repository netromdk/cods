#ifndef CODS_DEQUE_H
#define CODS_DEQUE_H

#include "cods/Vector.h"

namespace cods {

/// Implementation of a double-ended queue container extending Vector.
template <typename T> ///< Item type.
class Deque : public Vector<T> {
public:
  Deque();

  void pushBack(const T &value);
  void pushFront(const T &value);

  T popBack();
  T popFront();

  T &back();
  const T &back() const;

  T &front();
  const T &front() const;
};

#include "cods/Deque.hpp"

} // namespace cods

#endif // CODS_DEQUE_H
