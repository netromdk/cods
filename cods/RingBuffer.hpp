template <typename T, int CAP>
RingBuffer<T, CAP>::RingBuffer() : vec()
{
  static_assert(CAP > 0, "Capacity must be positive!");
}

template <typename T, int CAP>
int RingBuffer<T, CAP>::size() const
{
  return vec.size();
}

template <typename T, int CAP>
int RingBuffer<T, CAP>::capacity() const
{
  return CAP;
}

template <typename T, int CAP>
bool RingBuffer<T, CAP>::isEmpty() const
{
  return vec.isEmpty();
}

template <typename T, int CAP>
bool RingBuffer<T, CAP>::isFull() const
{
  return size() == capacity();
}

template <typename T, int CAP>
void RingBuffer<T, CAP>::insert(const T &value)
{
  if (isFull()) {
    vec.removeFirst();
  }

  vec << value;
}

template <typename T, int CAP>
void RingBuffer<T, CAP>::removeAt(int pos)
{
  vec.removeAt(pos);
}

template <typename T, int CAP>
T &RingBuffer<T, CAP>::at(int pos)
{
  return vec.at(pos);
}

template <typename T, int CAP>
const T &RingBuffer<T, CAP>::at(int pos) const
{
  return vec.at(pos);
}

template <typename T, int CAP>
T &RingBuffer<T, CAP>::operator[](int pos)
{
  return vec[pos];
}

template <typename T, int CAP>
const T &RingBuffer<T, CAP>::operator[](int pos) const
{
  return vec[pos];
}

template <typename T, int CAP>
bool RingBuffer<T, CAP>::operator==(const RingBuffer &other) const
{
  return vec == other.vec;
}

template <typename T, int CAP>
bool RingBuffer<T, CAP>::operator!=(const RingBuffer &other) const
{
  return !(*this == other);
}

template <typename T, int CAP>
Vector<T, CAP> RingBuffer<T, CAP>::toVector() const
{
  return vec;
}

template <typename T, int CAP>
typename Vector<T, CAP>::Iterator RingBuffer<T, CAP>::begin()
{
  return vec.begin();
}

template <typename T, int CAP>
typename Vector<T, CAP>::ConstIterator RingBuffer<T, CAP>::begin() const
{
  return vec.begin();
}

template <typename T, int CAP>
typename Vector<T, CAP>::ConstIterator RingBuffer<T, CAP>::cbegin() const
{
  return vec.cbegin();
}

template <typename T, int CAP>
typename Vector<T, CAP>::Iterator RingBuffer<T, CAP>::end()
{
  return vec.end();
}

template <typename T, int CAP>
typename Vector<T, CAP>::ConstIterator RingBuffer<T, CAP>::end() const
{
  return vec.end();
}

template <typename T, int CAP>
typename Vector<T, CAP>::ConstIterator RingBuffer<T, CAP>::cend() const
{
  return vec.cend();
}
