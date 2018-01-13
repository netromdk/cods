template <typename T>
Deque<T>::Deque() : Deque<T>::Vector()
{
}

template <typename T>
void Deque<T>::pushBack(const T &value)
{
  Deque<T>::append(value);
}

template <typename T>
void Deque<T>::pushFront(const T &value)
{
  Deque<T>::prepend(value);
}

template <typename T>
T Deque<T>::popBack()
{
  return Deque<T>::takeLast();
}

template <typename T>
T Deque<T>::popFront()
{
  return Deque<T>::takeFirst();
}

template <typename T>
T &Deque<T>::back()
{
  return *(--Deque<T>::end());
}

template <typename T>
const T &Deque<T>::back() const
{
  return *(--Deque<T>::cend());
}

template <typename T>
T &Deque<T>::front()
{
  return *Deque<T>::begin();
}

template <typename T>
const T &Deque<T>::front() const
{
  return *Deque<T>::cbegin();
}
