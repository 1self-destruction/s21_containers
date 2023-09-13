#ifndef S21_SET_H
#define S21_SET_H

#include <vector>

#include "../common_joints.h"

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = key_type;
  using size_type = size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  template <typename T1>
  class SetIterator {
   public:
    using value_type = T1;
    using reference = value_type&;
    using const_reference = const value_type&;

    node<value_type>* current;
    set<value_type>* ptr_set;

    SetIterator() {}
    SetIterator(node<value_type>* current, set<value_type>* ptr_set)
        : current(current), ptr_set(ptr_set) {}
    value_type operator*() { return current->data; }
    SetIterator operator++() {
      node<value_type>* ans = current;
      node<value_type>* cur = ptr_set->get_root();
      while (cur) {
        if (cur->data > current->data) {
          ans = cur;
          cur = cur->pPrev;
        } else {
          cur = cur->pNext;
        }
      }
      current = ans;
      return *this;
    }
    SetIterator operator--() {
      node<value_type>* ans = current;
      node<value_type>* cur = ptr_set->get_root();
      if (current == nullptr) {
        while (cur->pNext != nullptr) cur = cur->pNext;
        current = cur;
      } else {
        while (cur != nullptr) {
          if (cur->data < current->data) {
            ans = cur;
            cur = cur->pNext;
          } else {
            cur = cur->pPrev;
          }
        }
        current = ans;
      }
      return *this;
    }
    bool operator==(SetIterator<value_type> comparable_iter) {
      if (current->data == comparable_iter.current->data) return true;
      return false;
    }
    bool operator!=(SetIterator<value_type> comparable_iter) {
      if (current->data != comparable_iter.current->data) return true;
      return false;
    }
  };

  template <typename T2>
  class SetConstIterator {
   public:
    using value_type_ = T2;
    using reference = value_type&;
    using const_reference = const value_type&;

    const node<value_type>* current;
    set<value_type>* ptr_set;
    SetConstIterator() {}
    SetConstIterator(const node<value_type>* current, set<value_type>* ptr_set)
        : current(current), ptr_set(ptr_set) {}
    value_type operator*() { return current->data; }
    SetConstIterator operator++() {
      const node<value_type>* ans = current;
      const node<value_type>* cur = ptr_set->get_root();
      while (cur != nullptr) {
        if (cur->data > current->data) {
          ans = cur;
          cur = cur->pPrev;
        } else {
          cur = cur->pNext;
        }
      }
      current = ans;
      return *this;
    }
    SetConstIterator operator--() {
      const node<value_type>* ans = current;
      const node<value_type>* cur = ptr_set->get_root();
      if (current == nullptr) {
        while (cur->pNext != nullptr) cur = cur->pNext;
        current = cur;
      } else {
        while (cur != nullptr) {
          if (cur->data < current->data) {
            ans = cur;
            cur = cur->pNext;
          } else {
            cur = cur->pPrev;
          }
        }
        current = ans;
      }
      return *this;
    }
    bool operator==(SetConstIterator<value_type> comparable_iter) {
      if (current->data == comparable_iter.current->data) return true;
      return false;
    }
    bool operator!=(SetConstIterator<value_type> comparable_iter) {
      if (current->data != comparable_iter.current->data) return true;
      return false;
    }
  };

  using iterator = SetIterator<value_type>;
  using const_iterator = SetConstIterator<value_type>;

  set();
  set(std::initializer_list<value_type> const& items);
  set(const set& s);
  set(set&& s);
  ~set();

  iterator begin();
  iterator end();

  const_iterator const_begin();
  const_iterator const_end();

  bool empty();
  size_type size();
  size_type max_size();

  std::pair<iterator, bool> insert(const_reference value);
  void clear();
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const key_type& key);
  bool contains(const key_type& key);

  void balanced_tree();
  node<value_type>* get_root();

 private:
  node<value_type>* root;
  size_type size_;

  void clear_recursive(node<value_type>* current);
  void copy_set(node<value_type>* current_from, node<value_type>* current_to);
  void from_tree_to_array(std::vector<node<value_type>>& vec,
                          node<value_type>* current,
                          node<value_type>* erasable_element);
  void balanced_tree_recursive(std::vector<node<value_type>> vec);
};
}  // namespace s21
#include "s21_set.tpp"

#endif  // S21_SET_H