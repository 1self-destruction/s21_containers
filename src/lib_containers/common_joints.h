#ifndef COMMON_JOINTS_H
#define COMMON_JOINTS_H

#include <stdexcept>
#include <exception>
#include <algorithm>
#include <limits>
#include <initializer_list>
#include <utility> // для std::pair

namespace s21 {
template <typename T>
class node {
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    public:
        node* pNext;
        node* pPrev;
        value_type data;

        node(node* pNext, node* pPrev, value_type data) {
            this->pNext = pNext;
            this->pPrev = pPrev;
            this->data = data;
        }
};

template <typename Key, typename T>
class node_pair {
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

  public:
    value_type pair;
    node_pair* left;
    node_pair* right;
    node_pair(value_type pair, node_pair* left, node_pair* right)
            : pair(pair), left(left), right(right) {}
};
}

class CustomException : public std::exception {
public:
    explicit CustomException(char const* msg) { message_ = msg; }
    char const* what() { return message_; }

private:
    char const* message_;
};

#endif // COMMON_JOINTS_H
