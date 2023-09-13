#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include "../common_joints.h"

namespace s21 {
template <typename T>
class queue {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  queue();
  queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q);
  ~queue();
  queue& operator=(queue&& q) noexcept;

  const_reference& front();
  const_reference& back();
  bool empty();
  size_type size();
  void push(value_type data);
  void pop();
  void swap(queue& other);

  value_type operator[](int index);

 private:
  node<value_type>* head;
  node<value_type>* tail;
  size_type size_;
};
}  // namespace s21
#include "s21_queue.tpp"

#endif  // S21_QUEUE_H