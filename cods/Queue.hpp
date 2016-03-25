template <typename T>
Queue<T>::Queue() : data() { }

template <typename T>
bool Queue<T>::isEmpty() const {
  return data.isEmpty();
}

template <typename T>
int Queue<T>::size() const {
  return data.size();
}

template <typename T>
void Queue<T>::enqueue(const T &value) {
  data << value;
}

template <typename T>
T Queue<T>::dequeue() {
  auto it = data.begin();
  auto value = *it;
  data.erase(it);
  return value;
}

template <typename T>
T &Queue<T>::head() {
  return *data.begin();
}

template <typename T>
const T &Queue<T>::head() const {
  return *data.cbegin();
}
