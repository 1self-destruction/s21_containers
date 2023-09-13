#ifndef S21_MAP_H
#define S21_MAP_H

#include <vector>

#include "../common_joints.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = size_t;

  template <typename K1, typename T1>
  class MapIterator {
   public:
    using key_type = K1;
    using mapped_type = T1;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;

    MapIterator() {}
    MapIterator(node_pair<key_type, mapped_type>* current,
                map<key_type, mapped_type>* ptr_map)
        : current(current), ptr_map(ptr_map) {}
    value_type operator*() { return current->pair; }
    MapIterator operator++();
    MapIterator operator--() {
      node_pair<key_type, mapped_type>* ans = current;
      node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
      if (current == nullptr) {
        while (cur->right != nullptr) cur = cur->right;
        current = cur;
      } else {
        while (cur != nullptr) {
          if (cur->pair.first < current->pair.first) {
            ans = cur;
            cur = cur->right;
          } else {
            cur = cur->left;
          }
        }
        current = ans;
      }
      return *this;
    }
    bool operator==(MapIterator<key_type, mapped_type> comparable_iter) {
      if (current->pair.first == comparable_iter.current->pair.first)
        return true;
      return false;
    }
    bool operator!=(MapIterator<key_type, mapped_type> comparable_iter) {
      if (current->pair.first != comparable_iter.current->pair.first)
        return true;
      return false;
    }

    node_pair<key_type, mapped_type>* current;
    map<key_type, mapped_type>* ptr_map;
  };

  template <typename K2, typename T2>
  class MapConstIterator {
   public:
    using key_type = K2;
    using mapped_type = T2;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;

    MapConstIterator() {}
    MapConstIterator(const node_pair<key_type, mapped_type>* current,
                     map<key_type, mapped_type>* ptr_map)
        : current(current), ptr_map(ptr_map) {}
    value_type operator*() { return current->pair; }
    MapConstIterator operator++() {
      const node_pair<key_type, mapped_type>* ans = current;
      const node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
      while (cur != nullptr) {
        if (cur->pair.first > current->pair.first) {
          ans = cur;
          cur = cur->left;
        } else {
          cur = cur->right;
        }
      }
      current = ans;
      return *this;
    }
    MapConstIterator operator--() {
      const node_pair<key_type, mapped_type>* ans = current;
      const node_pair<key_type, mapped_type>* cur = ptr_map->get_root();
      if (current == nullptr) {
        while (cur->right != nullptr) cur = cur->right;
        current = cur;
      } else {
        while (cur != nullptr) {
          if (cur->pair.first < current->pair.first) {
            ans = cur;
            cur = cur->right;
          } else {
            cur = cur->left;
          }
        }
        current = ans;
      }
      return *this;
    }
    bool operator==(MapConstIterator<key_type, mapped_type> comparable_iter) {
      if (current->pair.first == comparable_iter.current->pair.first)
        return true;
      return false;
    }
    bool operator!=(MapConstIterator<key_type, mapped_type> comparable_iter) {
      if (current->pair.first != comparable_iter.current->pair.first)
        return true;
      return false;
    }

    const node_pair<key_type, mapped_type>* current;
    map<key_type, mapped_type>* ptr_map;
  };

  using iterator = MapIterator<key_type, mapped_type>;
  using const_iterator = MapConstIterator<key_type, mapped_type>;

  map();
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(map&& m);

  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  iterator begin();
  iterator end();

  const_iterator const_begin();
  const_iterator const_end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const key_type& key);

  void balanced_tree();

 private:
  node_pair<key_type, mapped_type>* root;
  size_type size_;

  void copy_map(node_pair<key_type, mapped_type>* current_from,
                node_pair<key_type, mapped_type>*& current_to);
  void clear_recursive(node_pair<key_type, mapped_type>* current);
  node_pair<key_type, mapped_type>* get_root();
  void from_tree_to_array(std::vector<node_pair<key_type, mapped_type>>& vec,
                          node_pair<key_type, mapped_type>* current,
                          node_pair<key_type, mapped_type>* erasable_element);
  void balanced_tree_recursive(
      std::vector<node_pair<key_type, mapped_type>> vec);
};
}  // namespace s21
#include "s21_map.tpp"

#endif  // S21_MAP_H