#ifndef S21_VECTOR_TPP
#define S21_VECTOR_TPP

namespace s21 {
template <typename T>
vector<T>::vector() : m_data(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : m_data(new value_type[n]), m_size(n), m_capacity(n) {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items) {
  m_data = new value_type[items.size()];
  m_size = items.size();
  m_capacity = items.size();
  std::copy(items.begin(), items.end(), m_data);
}

template <typename T>
vector<T>::vector(const vector &v) {
  m_data = new value_type[v.m_size];
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  std::copy(v.m_data, v.m_data + v.m_size, m_data);
}

template <typename T>
vector<T>::vector(vector &&v) noexcept {
  m_data = v.m_data;
  m_size = v.m_size;
  m_capacity = v.m_capacity;
  v.m_data = nullptr;
  v.m_size = 0;
  v.m_capacity = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] m_data;
  m_data = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &&v) {
  if (this != &v) {
    delete[] m_data;
    m_data = v.m_data;
    m_size = v.m_size;
    m_capacity = v.m_capacity;
    v.m_data = nullptr;
    v.m_size = 0;
    v.m_capacity = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= m_size) {
    throw CustomException("s21::vector::at - out_of_range");
  }
  return m_data[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= m_size) {
    throw CustomException("s21::vector::at - out_of_range");
  }
  return m_data[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  return m_data[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  return m_data[m_size - 1];
}

template <typename T>
T *vector<T>::data() {
  return m_data;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return m_data;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return m_data + m_size;
}

template <typename T>
bool vector<T>::empty() {
  return m_size == 0;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() {
  return m_size;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > m_capacity) {
    value_type *new_data = new value_type[size];
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() {
  return m_capacity;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (m_size != m_capacity) {
    value_type *new_data = new value_type[m_size];
    std::copy(m_data, m_data + m_size, new_data);
    delete[] m_data;
    m_data = new_data;
    m_capacity = m_size;
  }
}

template <typename T>
void vector<T>::clear() {
  delete[] m_data;
  m_data = nullptr;
  m_size = 0;
  m_capacity = 0;
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type index = pos - m_data;
  if (m_size == m_capacity) {
    reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    pos = m_data + index;
  }
  std::copy_backward(pos, m_data + m_size, m_data + m_size + 1);
  *pos = value;
  ++m_size;
  return m_data + index;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  std::copy(pos + 1, m_data + m_size, pos);
  --m_size;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (m_size == m_capacity) {
    reserve(m_capacity == 0 ? 1 : m_capacity * 2);
  }
  *(m_data + m_size) = value;
  ++m_size;
}

template <typename T>
void vector<T>::pop_back() {
  --m_size;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(m_data, other.m_data);
  std::swap(m_size, other.m_size);
  std::swap(m_capacity, other.m_capacity);
}
}  // namespace s21
#endif  // S21_VECTOR_TPP