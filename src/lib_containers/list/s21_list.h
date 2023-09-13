#ifndef S21_LIST_H
#define S21_LIST_H

#include "../common_joints.h"

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

  template <typename T1>
  class ListIterator {
   public:
    using value_type = T1;
    using reference = T1 &;
    using const_reference = const T1 &;
    using pointer = T1 *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    explicit ListIterator(node<value_type> *current, list<value_type> *ptr_list)
        : current{current}, ptr_list(ptr_list) {}
    ListIterator(const ListIterator &) = default;
    ListIterator &operator=(const ListIterator &) = default;

    ListIterator &operator++() {
      if (current->pNext) {
        current = current->pNext;
        return *this;
      } else {
        throw CustomException("Error!");
      }
    }

    ListIterator &operator--() {
      if (current) {
        current = current->pPrev;
      } else {
        current = ptr_list->tail;
      }
      return *this;
    }

    reference operator*() const { return current->data; }
    pointer operator->() const { return &current->data; }

    bool operator==(const ListIterator &rhs) const {
      return current == rhs.current;
    }
    bool operator!=(const ListIterator &rhs) const { return *this != rhs; }

    node<value_type> *current;
    list<value_type> *ptr_list;
  };

  template <typename T2>
  class ListConstIterator {
   public:
    using value_type = T2;
    using reference = T2 &;
    using const_reference = const T2 &;
    using pointer = T2 *;

    explicit ListConstIterator(node<value_type> *current,
                               list<value_type> *ptr_list)
        : current{current}, ptr_list(ptr_list) {}
    ListConstIterator(const ListConstIterator &) = default;
    ListConstIterator &operator=(const ListConstIterator &) = default;

    ListConstIterator &operator++() {
      if (current->pNext) {
        current = current->pNext;
        return *this;
      } else {
        throw CustomException("Error!");
      }
    }

    ListConstIterator &operator--() {
      if (current) {
        current = current->pPrev;
      } else {
        current = ptr_list->tail;
      }
      return *this;
    }

    reference operator*() const { return current->data; }
    pointer operator->() const { return &current->data; }

    bool operator==(const ListConstIterator &rhs) const {
      return current == rhs.current;
    }
    bool operator!=(const ListConstIterator &rhs) const { return *this != rhs; }

    node<value_type> *current;
    list<value_type> *ptr_list;
  };

  using size_type = size_t;
  using iterator = ListIterator<value_type>;
  using const_iterator = ListConstIterator<value_type>;

  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const &items);
  list(const list &other);
  list(list<value_type> &&other);
  ~list();
  list &operator=(list &&other) noexcept;

  const_reference front();
  const_reference back();

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();
  void clear();

  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(iterator pos, list &other);
  void reverse();
  void unique();
  void sort();

 private:
  node<value_type> *head;
  node<value_type> *tail;
  size_type len;
};
}  // namespace s21
#include "s21_list.tpp"

#endif  // S21_LIST_H