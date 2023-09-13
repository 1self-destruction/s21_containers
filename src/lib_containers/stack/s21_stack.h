#ifndef S21_STACK_H
#define S21_STACK_H

#include "../common_joints.h"

namespace s21 {
template <typename T>
class stack {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  stack();
  stack(const stack& s);
  stack(stack&& s);
  stack(std::initializer_list<value_type> const& items);
  ~stack();
  stack& operator=(stack&& s) noexcept;

  const_reference top();
  void push(const_reference data);
  void pop();
  bool empty();
  size_type size();
  void swap(stack& other);
  void clear();
  value_type operator[](int i);

 private:
  node<value_type>* head;
  size_type size_;

  value_type get_element(int i);
};
}  // namespace s21
#include "s21_stack.tpp"

#endif  // S21_STACK_H