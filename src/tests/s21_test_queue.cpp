#ifndef S21_TEST_QUEUE_CPP
#define S21_TEST_QUEUE_CPP

#include "s21_test_containers.h"

TEST(queueTest, defaultConstructor) {
  s21::queue<int> q1;
  EXPECT_EQ(q1.size(), 0);
}

TEST(queueTest, initializerListConstructor) {
  s21::queue<int> q1 = {1, 2, 3, 4};
  EXPECT_EQ(q1[0], 1);
}

TEST(queueTest, copyConstructor) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.size(), 3);
}

TEST(queueTest, moveConstuctor) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2(std::move(q1));
  EXPECT_EQ(q1.size(), 0);
  EXPECT_EQ(q2.size(), 3);
}

TEST(queueTest, operatorEqual) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = q1;
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q1.size(), 3);
}

TEST(queueTest, front) {
  s21::queue<int> q1 = {1, 2, 3};
  EXPECT_EQ(q1.front(), 1);
}

TEST(queueTest, back) {
  s21::queue<int> q1 = {1, 2, 3};
  EXPECT_EQ(q1.back(), 3);
}

TEST(queueTest, empty) {
  s21::queue<int> q1;
  EXPECT_EQ(q1.empty(), true);
  q1.push(3);
  EXPECT_EQ(q1.empty(), false);
}

TEST(queueTest, size) {
  s21::queue<int> q1 = {1, 2, 3};
  EXPECT_EQ(q1.size(), 3);
}

TEST(queueTest, push) {
  s21::queue<int> q1;
  EXPECT_EQ(q1.size(), 0);
  q1.push(3);
  EXPECT_EQ(q1.size(), 1);
}

TEST(queueTest, pop) {
  s21::queue<int> q1 = {1, 2, 3};
  EXPECT_EQ(q1.size(), 3);
  q1.pop();
  EXPECT_EQ(q1.size(), 2);
}

TEST(queueTest, swap) {
  s21::queue<int> q1 = {1, 2, 3};
  s21::queue<int> q2 = {4, 5, 6};
  q1.swap(q2);
  EXPECT_EQ(q1.front(), 4);
  EXPECT_EQ(q2.front(), 1);
}

#endif  // S21_TEST_QUEUE_CPP