#ifndef S21_LIST_TPP
#define S21_LIST_TPP

namespace s21 {
template <typename T>
list<T>::list() : head(nullptr), tail(nullptr), len(0) {}

template <typename T>
list<T>::list(size_type n) : head{nullptr}, tail{nullptr}, len{0} {
  for (size_type i = 0; i < n; ++i) {
    this->push_back(0);
  }
}

template <typename T>
list<T>::list(std::initializer_list<value_type> const &items)
    : head{nullptr}, tail{nullptr}, len{0} {
  for (auto item : items) {
    this->push_back(item);
  }
}

template <typename T>
list<T>::list(const list &other) {
  head = nullptr;
  tail = nullptr;
  len = 0;
  node<value_type> *current = other.head;
  while (current) {
    push_back(current->data);
    current = current->pNext;
  }
}

template <typename T>
list<T>::list(list<T> &&other)
    : head{other.head}, tail{other.tail}, len{other.len} {
  other.head = nullptr;
  other.tail = nullptr;
  other.len = 0;
}

template <typename T>
list<T>::~list() {
  this->clear();
}

template <typename T>
list<T> &list<T>::operator=(list &&other) noexcept {
  head = other.head;
  tail = other.tail;
  len = other.len;
  other.head = nullptr;
  other.tail = nullptr;
  other.len = 0;
}

template <typename T>
typename list<T>::const_reference list<T>::front() {
  return head->data;
}

template <typename T>
typename list<T>::const_reference list<T>::back() {
  return tail->data;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  return iterator{head, this};
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  return iterator{nullptr, this};
}

template <typename T>
bool list<T>::empty() {
  return len == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() {
  return len;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void list<T>::clear() {
  while (!this->empty()) {
    this->pop_front();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  node<value_type> *current =
      new node<value_type>{pos.current, pos.current->pPrev, value};
  if (pos.current->pPrev) {
    pos.current->pPrev->pNext = current;
  } else {
    head = current;
  }
  pos.current->pPrev = current;
  ++len;
  return iterator{current, this};
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.current->pPrev) {
    pos.current->pPrev->pNext = pos.current->pNext;
  } else {
    head = pos.current->pNext;
  }
  if (pos.current->pNext) {
    pos.current->pNext->pPrev = pos.current->pPrev;
  } else {
    tail = pos.current->pPrev;
  }
  delete pos.current;
  --len;
}

template <typename T>
void list<T>::push_back(const T &value) {
  if (len == 0) {
    head = new node<value_type>(nullptr, nullptr, value);
    tail = head;
  } else {
    tail = new node<value_type>(nullptr, tail, value);
    tail->pPrev->pNext = tail;
  }
  len++;
}

template <typename T>
void list<T>::pop_back() {
  if (tail == nullptr) {
    return;
  }
  node<value_type> *new_tail = tail->pPrev;
  if (new_tail != nullptr) {
    new_tail->pNext = nullptr;
  } else {
    head = nullptr;
  }

  delete tail;
  tail = new_tail;
  --len;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  node<value_type> *current = new node<value_type>{head, nullptr, value};
  if (head) {
    head->pPrev = current;
  } else {
    tail = current;
  }
  head = current;
  ++len;
}

template <typename T>
void list<T>::pop_front() {
  node<value_type> *old_head = head;
  head = head->pNext;
  if (head) {
    head->pPrev = nullptr;
  } else {
    tail = nullptr;
  }
  delete old_head;
  --len;
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(head, other.head);
  std::swap(tail, other.tail);
  std::swap(len, other.len);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this == &other) {
    return;
  }
  this->splice(begin(), other);
}

template <typename T>
void list<T>::splice(iterator pos, list &other) {
  if (this == &other || other.empty()) {
    return;
  }

  node<value_type> *first = other.head;
  node<value_type> *last = other.tail;

  if (pos.current->pPrev) {
    pos.current->pPrev->pNext = first;
  } else {
    head = first;
  }
  last->pNext = pos.current;
  pos.current->pPrev = last;

  len += other.len;

  other.head = nullptr;
  other.tail = nullptr;
  other.len = 0;
}

template <typename T>
void list<T>::reverse() {
  node<value_type> *current = head;
  while (current) {
    std::swap(current->pPrev, current->pNext);
    current = current->pPrev;
  }
  std::swap(head, tail);
}

template <typename T>
void list<T>::unique() {
  if (this->empty()) {
    return;
  }
  node<value_type> *current = head;
  while (current->pNext) {
    if (current->data == current->pNext->data) {
      node<value_type> *tmp = current->pNext;
      current->pNext = tmp->pNext;
      if (tmp->pNext) {
        tmp->pNext->pPrev = current;
      } else {
        tail = current;
      }
      delete tmp;
      --len;
    } else {
      current = current->pNext;
    }
  }
}

template <typename T>
void list<T>::sort() {
  node<value_type> *current = head;
  value_type *array = new value_type[len];
  int k = 0;
  while (current) {
    array[k] = current->data;
    current = current->pNext;
    k++;
  }

  for (int i = 0; i < (int)len; i++) {
    for (int j = i + 1; j < (int)len; j++) {
      if (array[i] > array[j]) {
        value_type tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
      }
    }
  }

  node<value_type> *current2 = head;
  int l = 0;
  while (current2) {
    current2->data = array[l];
    current2 = current2->pNext;
    l++;
  }

  delete[] array;
}
}  // namespace s21

#endif  // S21_LIST_TPP