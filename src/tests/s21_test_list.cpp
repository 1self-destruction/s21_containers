#ifndef S21_TEST_LIST_CPP
#define S21_TEST_LIST_CPP

#include "s21_test_containers.h"

TEST(listTest, defaultConstructor) {
  s21::list<char> x;
  EXPECT_EQ(0, x.size());
}

TEST(listTest, parameterizedConstructor) {
  s21::list<char> x(5);
  EXPECT_EQ(5, x.size());
}

TEST(listTest, initializerListConstructor) {
  s21::list<int> x = {1, 2, 3};
  EXPECT_EQ(3, x.size());
}

TEST(listTest, copyConstructor) {
  s21::list<int> x = {1, 2, 3};
  s21::list<int> y(x);
  EXPECT_EQ(3, y.size());
  EXPECT_EQ(3, x.size());
}

TEST(listTest, moveConstructor) {
  s21::list<int> x = {1, 2, 3};
  s21::list<int> y(std::move(x));
  EXPECT_EQ(3, y.size());
  EXPECT_EQ(0, x.size());
}

TEST(listTest, operatorEqual) {
  s21::list<int> x = {1, 2, 3};
  s21::list<int> y = x;
  EXPECT_EQ(3, y.size());
  EXPECT_EQ(3, x.size());
}

TEST(listTest, front) {
  s21::list<int> x = {1, 2, 3};
  EXPECT_EQ(1, x.front());
}

TEST(listTest, back) {
  s21::list<int> x = {1, 2, 3};
  EXPECT_EQ(3, x.back());
}

TEST(listTest, begin) {
  s21::list<int> x = {1, 2, 3};
  EXPECT_EQ(1, *x.begin());
}

TEST(listTest, end) {
  s21::list<int> x = {1, 2, 3};
  EXPECT_EQ(3, *(--x.end()));
}

TEST(listTest, empty) {
  s21::list<int> x;
  EXPECT_EQ(true, x.empty());
  x.push_back(1);
  EXPECT_EQ(false, x.empty());
}

TEST(listTest, size) {
  s21::list<int> x;
  EXPECT_EQ(0, x.size());
  x.push_back(1);
  EXPECT_EQ(1, x.size());
}

TEST(listTest, clear) {
  s21::list<int> x = {1, 2, 3};
  EXPECT_EQ(3, x.size());
  x.clear();
  EXPECT_EQ(0, x.size());
}

TEST(listTest, insert) {
  s21::list<int> x = {1, 2, 3};
  x.insert(x.begin(), 16);
  EXPECT_EQ(16, x.front());
}

TEST(listTest, erase) {
  s21::list<int> x = {1, 2, 3};
  x.erase(x.begin());
  EXPECT_EQ(2, x.front());
}

TEST(listTest, pushBack) {
  s21::list<int> x = {2};
  x.push_back(1);
  EXPECT_EQ(x.back(), 1);
}

TEST(listTest, popBack) {
  s21::list<int> x = {1, 2};
  x.pop_back();
  EXPECT_EQ(x.back(), 1);
}

TEST(listTest, pushFront) {
  s21::list<int> x = {2};
  x.push_front(1);
  EXPECT_EQ(x.front(), 1);
}

TEST(listTest, popFront) {
  s21::list<int> x = {1, 2};
  x.pop_front();
  EXPECT_EQ(x.front(), 2);
}

TEST(listTest, swap) {
  s21::list<int> x = {1, 2};
  s21::list<int> y = {3, 4};
  x.swap(y);
  EXPECT_EQ(x.front(), 3);
  EXPECT_EQ(y.front(), 1);
}

TEST(listTest, merge) {
  s21::list<int> x = {1};
  s21::list<int> y = {2};
  x.merge(y);
  EXPECT_EQ(x.front(), 2);
  EXPECT_EQ(x.back(), 1);
}

TEST(listTest, splice) {
  s21::list<int> x = {1, 2, 3, 4, 5};
  s21::list<int> y = {10, 20, 30, 40, 50};
  x.splice(x.begin(), y);
  EXPECT_EQ(x.front(), 10);
  EXPECT_EQ(x.size(), 10);
}

TEST(listTest, unique) {
  s21::list<int> x = {4, 4, 1, 1};
  x.unique();
  EXPECT_EQ(x.front(), 4);
  EXPECT_EQ(x.back(), 1);
}

TEST(listTest, reverse) {
  s21::list<int> x = {4, 1};
  x.reverse();
  EXPECT_EQ(x.front(), 1);
  EXPECT_EQ(x.back(), 4);
}

TEST(listTest, sort) {
  s21::list<int> x = {4, 1, 9, 17, 3, 2};
  x.sort();
  EXPECT_EQ(x.front(), 1);
  EXPECT_EQ(x.back(), 17);
}

#endif  // S21_TEST_LIST_CPP