#ifndef S21_SET_TPP
#define S21_SET_TPP

namespace s21 {
template <typename value_type>
set<value_type>::set() : root(nullptr), size_(0) {}

template <typename value_type>
set<value_type>::set(std::initializer_list<value_type> const& items) {
  root = nullptr;
  size_ = 0;
  for (auto iter = items.begin(); iter != items.end(); ++iter) {
    insert(*iter);
  }
}

template <typename value_type>
set<value_type>::set(const set& s) {
  size_ = s.size_;
  root = new node<value_type>(nullptr, nullptr, s.root->data);
  copy_set(s.root, root);
}

template <typename value_type>
set<value_type>::set(set&& s) {
  size_ = s.size_;
  root = s.root;
  s.size_ = 0;
  s.root = nullptr;
}

template <typename value_type>
set<value_type>::~set() {
  clear();
}

template <typename value_type>
typename set<value_type>::iterator set<value_type>::begin() {
  node<value_type>* current = root;
  while (current->pPrev) {
    current = current->pPrev;
  }
  iterator iter(current, this);
  return iter;
}

template <typename value_type>
typename set<value_type>::iterator set<value_type>::end() {
  iterator iter(nullptr, this);
  return iter;
}

template <typename value_type>
typename set<value_type>::const_iterator set<value_type>::const_begin() {
  node<value_type>* current = root;
  while (current->pPrev != nullptr) {
    current = current->pPrev;
  }
  const_iterator iter(current, this);
  return iter;
}

template <typename value_type>
typename set<value_type>::const_iterator set<value_type>::const_end() {
  const_iterator iter(nullptr, this);
  return iter;
}

template <typename value_type>
std::pair<typename set<value_type>::iterator, bool> set<value_type>::insert(
    const_reference value) {
  node<value_type>* current = root;
  while (current != nullptr) {
    if (value < current->data) {
      if (!current->pPrev) {
        current->pPrev = new node<value_type>(nullptr, nullptr, value);
        size_++;
        iterator iter(current->pPrev, this);
        return std::make_pair(iter, true);
      }
      current = current->pPrev;
    } else if (value > current->data) {
      if (!current->pNext) {
        current->pNext = new node<value_type>(nullptr, nullptr, value);
        size_++;
        iterator iter(current->pNext, this);
        return std::make_pair(iter, true);
      }
      current = current->pNext;
    } else {
      iterator iter(current, this);
      return std::make_pair(iter, false);
    }
  }
  root = new node<value_type>(nullptr, nullptr, value);
  size_++;
  iterator iter(root, this);
  return std::make_pair(iter, true);
}

template <typename value_type>
void set<value_type>::clear() {
  clear_recursive(root);
  root = nullptr;
  size_ = 0;
}

template <typename value_type>
bool set<value_type>::empty() {
  if (size_ == 0) return true;
  return false;
}

template <typename value_type>
typename set<value_type>::size_type set<value_type>::size() {
  return size_;
}

template <typename value_type>
typename set<value_type>::size_type set<value_type>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename value_type>
void set<value_type>::erase(iterator pos) {
  std::vector<node<value_type>> vec;
  from_tree_to_array(vec, root, pos.current);
  clear();
  balanced_tree_recursive(vec);
}

template <typename value_type>
void set<value_type>::swap(set& other) {
  std::swap(root, other.root);
  std::swap(size_, other.size_);
}

template <typename value_type>
void set<value_type>::merge(set& other) {
  std::vector<node<value_type>> vec;
  from_tree_to_array(vec, get_root(), nullptr);
  from_tree_to_array(vec, other.get_root(), nullptr);
  clear();
  balanced_tree_recursive(vec);
  vec.clear();
  from_tree_to_array(vec, get_root(), nullptr);
  clear();
  balanced_tree_recursive(vec);
}

template <typename value_type>
typename set<value_type>::iterator set<value_type>::find(const key_type& key) {
  node<value_type>* current = root;
  while (current) {
    if (key > current->data)
      current = current->pNext;
    else if (key < current->data)
      current = current->pPrev;
    else
      break;
  }
  iterator iter(current, this);
  return iter;
}

template <typename value_type>
bool set<value_type>::contains(const key_type& key) {
  node<value_type>* current = root;
  while (current) {
    if (key > current->data)
      current = current->pNext;
    else if (key < current->data)
      current = current->pPrev;
    else
      return true;
  }
  return false;
}

template <typename value_type>
void set<value_type>::balanced_tree() {
  std::vector<node<value_type>> vec;
  from_tree_to_array(vec, root, nullptr);
  clear();
  balanced_tree_recursive(vec);
}

template <typename value_type>
void set<value_type>::from_tree_to_array(std::vector<node<value_type>>& vec,
                                         node<value_type>* current,
                                         node<value_type>* erasable_element) {
  if (current->pPrev != nullptr) {
    from_tree_to_array(vec, current->pPrev, erasable_element);
  }
  if (erasable_element != nullptr) {
    if (current->data != erasable_element->data) {
      vec.push_back(*current);
    }
  } else {
    vec.push_back(*current);
  }
  if (current->pNext != nullptr) {
    from_tree_to_array(vec, current->pNext, erasable_element);
  }
}

template <typename value_type>
void set<value_type>::balanced_tree_recursive(
    std::vector<node<value_type>> vec) {
  if (vec.size() == 1) {
    insert(vec[0].data);
  } else if (vec.size() == 2) {
    insert(vec[0].data);
    insert(vec[1].data);
  } else {
    int middle = (vec.size() - 1) / 2;
    insert(vec[middle].data);
    std::vector<node<value_type>> vec1;
    for (int i = 0; i < middle; i++) {
      vec1.push_back(vec[i]);
    }
    balanced_tree_recursive(vec1);
    std::vector<node<value_type>> vec2;
    for (size_type i = middle + 1; i < vec.size(); i++) {
      vec2.push_back(vec[i]);
    }
    balanced_tree_recursive(vec2);
  }
}

template <typename value_type>
void set<value_type>::clear_recursive(node<value_type>* current) {
  if (current != nullptr) {
    if (current->pPrev != nullptr) {
      clear_recursive(current->pPrev);
    }
    if (current->pNext != nullptr) {
      clear_recursive(current->pNext);
    }
    delete current;
  }
}

template <typename value_type>
node<value_type>* set<value_type>::get_root() {
  return root;
}

template <typename value_type>
void set<value_type>::copy_set(node<value_type>* current_from,
                               node<value_type>* current_to) {
  if (current_from->pPrev != nullptr) {
    current_to->pPrev =
        new node<value_type>(nullptr, nullptr, current_from->pPrev->data);
    copy_set(current_from->pPrev, current_to->pPrev);
  }
  if (current_from->pNext != nullptr) {
    current_to->pNext =
        new node<value_type>(nullptr, nullptr, current_from->pNext->data);
    copy_set(current_from->pNext, current_to->pNext);
  }
}
}  // namespace s21

#endif  // S21_SET_TPP