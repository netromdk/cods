template <typename T, typename P>
PriorityQueue<T, P>::PriorityQueue() : size_(0), high(), low()
{
}

template <typename T, typename P>
PriorityQueue<T, P>::PriorityQueue(PriorityQueue &&other) : PriorityQueue()
{
  *this = std::move(other);
}

template <typename T, typename P>
int PriorityQueue<T, P>::size() const
{
  return size_;
}

template <typename T, typename P>
bool PriorityQueue<T, P>::isEmpty() const
{
  return size_ == 0;
}

template <typename T, typename P>
void PriorityQueue<T, P>::insert(const T &value, const P &priority)
{
  auto &vec = map[priority];
  vec << value;

  // Initialize both on first insertion.
  if (isEmpty()) {
    high = low = priority;
  }
  else {
    high = std::max(high, priority);
    low = std::min(low, priority);
  }

  size_++;
}

template <typename T, typename P>
T PriorityQueue<T, P>::popHigh()
{
  return pop(Priority::HIGH);
}

template <typename T, typename P>
T PriorityQueue<T, P>::popLow()
{
  return pop(Priority::LOW);
}

template <typename T, typename P>
T &PriorityQueue<T, P>::peekHigh()
{
  assert(!isEmpty() && "Container is empty!");
  return map[high].at(0);
}

template <typename T, typename P>
const T &PriorityQueue<T, P>::peekHigh() const
{
  assert(!isEmpty() && "Container is empty!");
  return map[high].at(0);
}

template <typename T, typename P>
T &PriorityQueue<T, P>::peekLow()
{
  assert(!isEmpty() && "Container is empty!");
  return map[low].at(0);
}

template <typename T, typename P>
const T &PriorityQueue<T, P>::peekLow() const
{
  assert(!isEmpty() && "Container is empty!");
  return map[low].at(0);
}

template <typename T, typename P>
bool PriorityQueue<T, P>::operator==(const PriorityQueue &other) const
{
  return map == other.map;
}

template <typename T, typename P>
bool PriorityQueue<T, P>::operator!=(const PriorityQueue &other) const
{
  return !(*this == other);
}

template <typename T, typename P>
PriorityQueue<T, P> &PriorityQueue<T, P>::operator=(const PriorityQueue &other)
{
  map = other.map;
  size_ = other.size_;
  high = other.high;
  low = other.low;
  return *this;
}

template <typename T, typename P>
PriorityQueue<T, P> &PriorityQueue<T, P>::operator=(PriorityQueue &&other)
{
  map = other.map;
  size_ = other.size_;
  high = other.high;
  low = other.low;

  // Nullify original container.
  other.map.clear();
  other.size_ = 0;
  other.high = T();
  other.low = T();
  return *this;
}

template <typename T, typename P>
T PriorityQueue<T, P>::pop(Priority priority)
{
  if (isEmpty()) {
    return {};
  }

  const auto priv = (priority == Priority::HIGH ? high : low);
  assert(map.contains(priv) && "Priority not found in queue!");

  auto &vec = map[priv];
  const auto value = vec.takeFirst();
  size_--;

  // If no more elements are contained for the priority then remove and find next highest/lowest
  // priority.
  if (vec.isEmpty()) {
    map.remove(priv);

    if (!isEmpty()) {
      auto keys = map.keys();
      std::sort(keys.begin(), keys.end());

      if (priority == Priority::HIGH) {
        high = keys.takeLast();
      }
      else {
        low = keys.takeFirst();
      }

      assert(low <= high && "Lowest priority > highest priority!");
    }
  }

  return value;
}
