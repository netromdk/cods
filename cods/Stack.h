#ifndef CODS_STACK_H
#define CODS_STACK_H

#include "cods/Global.h"
#include "cods/Vector.h"

CODS_BEGIN_NAMESPACE

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

CODS_END_NAMESPACE

#endif // CODS_STACK_H
