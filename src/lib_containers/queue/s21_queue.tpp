#ifndef S21_QUEUE_TPP
#define S21_QUEUE_TPP

namespace s21 {
template <typename value_type>
queue<value_type>::queue() {
  head = nullptr;
  tail = nullptr;
  size_ = 0;
}

template <typename value_type>
queue<value_type>::queue(const queue& q) {
  head = nullptr;
  tail = nullptr;
  size_ = 0;
  node<value_type>* current = q.head;
  while (current) {
    push(current->data);
    current = current->pNext;
  }
}

template <typename value_type>
queue<value_type>::queue(queue&& q) {
  head = q.head;
  tail = q.tail;
  size_ = q.size_;
  q.head = nullptr;
  q.tail = nullptr;
  q.size_ = 0;
}

template <typename value_type>
queue<value_type>::queue(std::initializer_list<value_type> const& items) {
  head = nullptr;
  tail = nullptr;
  size_ = 0;
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    push(*iter);
  }
}

template <typename value_type>
queue<value_type>::~queue() {
  while (head != nullptr) {
    node<value_type>* tmp = head;
    head = head->pNext;
    delete tmp;
  }
  size_ = 0;
}

template <typename value_type>
queue<value_type>& queue<value_type>::operator=(queue&& q) noexcept {
  if (*this != q) {
    head = q.head;
    tail = q.tail;
    size_ = q.size_;
    q.head = nullptr;
    q.tail = nullptr;
    q.size_ = 0;
  }
  return *this;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::front() {
  return head->data;
}

template <typename value_type>
typename queue<value_type>::const_reference queue<value_type>::back() {
  return tail->data;
}

template <typename value_type>
void queue<value_type>::push(value_type data) {
  if (size_ == 0) {
    head = new node<value_type>(nullptr, nullptr, data);
    tail = head;
  } else {
    tail = new node<value_type>(nullptr, tail, data);
    tail->pPrev->pNext = tail;
  }
  size_++;
}

template <typename value_type>
void queue<value_type>::pop() {
  node<value_type>* tmp = head;
  head = head->pNext;
  delete tmp;
  size_--;
}

template <typename value_type>
void queue<value_type>::swap(queue& other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(size_, other.size_);
}

template <typename value_type>
typename queue<value_type>::size_type queue<value_type>::size() {
  return size_;
}

template <typename value_type>
bool queue<value_type>::empty() {
  if (size_ == 0) return true;
  return false;
}

template <typename value_type>
value_type queue<value_type>::operator[](int index) {
  if (index < (int)size_ && index >= 0) {
    node<value_type>* current = head;
    int counter = 0;
    while (current != tail) {
      if (index == counter) return current->data;
      current = current->pNext;
      counter++;
    }
  }
  throw CustomException("Error!");
}
}  // namespace s21

#endif  // S21_QUEUE_TPP