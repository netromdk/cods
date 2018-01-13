template <typename T>
Stack<T>::Stack() : Stack<T>::Vector()
{
}

template <typename T>
void Stack<T>::push(const T &value)
{
  Stack<T>::prepend(value);
}

template <typename T>
T Stack<T>::pop()
{
  return Stack<T>::takeFirst();
}

template <typename T>
T &Stack<T>::top()
{
  return *Stack<T>::begin();
}

template <typename T>
const T &Stack<T>::top() const
{
  return *Stack<T>::cbegin();
}
