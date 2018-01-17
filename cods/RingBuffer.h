#ifndef CODS_RING_BUFFER_H
#define CODS_RING_BUFFER_H

#include "cods/Vector.h"

#include <algorithm>
#include <iterator>

namespace cods {

/// Implementation of a ring buffer with a fixed capacity.
template <typename T, ///< Item type.
          int CAP>    ///< Buffer capacity.
class RingBuffer {
public:
  RingBuffer();
  RingBuffer(const RingBuffer &other) = default;
  RingBuffer(RingBuffer &&other) = default;

  int size() const;
  int capacity() const;

  bool isEmpty() const;
  bool isFull() const;

  void insert(const T &value);

  void removeAt(int pos);

  T &at(int pos);
  const T &at(int pos) const;

  T &operator[](int pos);
  const T &operator[](int pos) const;

  bool operator==(const RingBuffer &other) const;
  bool operator!=(const RingBuffer &other) const;

  Vector<T, CAP> toVector() const;

  typename Vector<T, CAP>::Iterator begin();
  typename Vector<T, CAP>::ConstIterator begin() const;
  typename Vector<T, CAP>::ConstIterator cbegin() const;

  typename Vector<T, CAP>::Iterator end();
  typename Vector<T, CAP>::ConstIterator end() const;
  typename Vector<T, CAP>::ConstIterator cend() const;

private:
  Vector<T, CAP> vec;
};

#include "cods/RingBuffer.hpp"

} // namespace cods

template <typename T, int CAP>
inline std::ostream &operator<<(std::ostream &os, const cods::RingBuffer<T, CAP> &buf)
{
  return os << buf.toVector();
}

#endif // CODS_RING_BUFFER_H
