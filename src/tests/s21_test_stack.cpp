#ifndef S21_TEST_STACK_CPP
#define S21_TEST_STACK_CPP

#include "s21_test_containers.h"

TEST(stackTest, defaultConstructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.size() == 0);
}

TEST(stackTest, copyConstructor) {
  s21::stack<int> s1;
  s1.push(1);
  s21::stack<int> s2(s1);
  EXPECT_EQ(s2.size(), 1);
}

TEST(stackTest, moveConstructor) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2(std::move(s1));
  EXPECT_EQ(s1.size(), 0);
  EXPECT_EQ(s2.size(), 3);
}

TEST(stackTest, initializerListConstructor) {
  s21::stack<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
}

TEST(stackTest, operatorEqual) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2 = s1;
  EXPECT_EQ(s2.size(), 3);
}

TEST(stackTest, top) {
  s21::stack<int> s = {1, 2, 3};
  EXPECT_EQ(s.top(), 1);
}

TEST(stackTest, push) {
  s21::stack<int> s;
  EXPECT_EQ(s.size(), 0);
  s.push(1);
  EXPECT_EQ(s.size(), 1);
}

TEST(stackTest, pop) {
  s21::stack<int> s = {1};
  EXPECT_EQ(s.size(), 1);
  s.pop();
  EXPECT_EQ(s.size(), 0);
}

TEST(stackTest, empty) {
  s21::stack<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  s.clear();
  EXPECT_TRUE(s.empty());
}

TEST(stackTest, size) {
  s21::stack<int> s1 = {1, 2, 3, 4};
  EXPECT_EQ(s1.size(), 4);
}

TEST(stackTest, swap) {
  s21::stack<int> s1 = {1, 2, 3};
  s21::stack<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.top(), 4);
  EXPECT_EQ(s2.top(), 1);
}

#endif  // S21_TEST_STACK_CPP