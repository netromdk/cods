#ifndef CODS_STACK_H
#define CODS_STACK_H

#include "cods/Vector.h"

namespace cods {

/// Implementation of a stack container extending Vector.
template <typename T> ///< Item type.
class Stack : public Vector<T> {
public:
  Stack();

  void push(const T &value);
  T pop();

  T &top();
  const T &top() const;
};

#include "cods/Stack.hpp"

} // namespace cods

#endif // CODS_STACK_H
