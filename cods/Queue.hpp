template <typename T>
Queue<T>::Queue() : Queue<T>::Vector()
{
}

template <typename T>
void Queue<T>::enqueue(const T &value)
{
  Queue<T>::append(value);
}

template <typename T>
T Queue<T>::dequeue()
{
  return Queue<T>::takeFirst();
}

template <typename T>
T &Queue<T>::head()
{
  return *Queue<T>::begin();
}

template <typename T>
const T &Queue<T>::head() const
{
  return *Queue<T>::cbegin();
}
