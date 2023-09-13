#ifndef S21_TEST_SET_CPP
#define S21_TEST_SET_CPP

#include "s21_test_containers.h"

TEST(setTest, defaultConstructor) {
  s21::set<int> s1;
  EXPECT_EQ(s1.size(), 0);
}

TEST(setTest, initializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.contains(1), 1);
}

TEST(setTest, copyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s2.size(), 3);
}

TEST(setTest, moveConstuctor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s1.size(), 0);
}

TEST(setTest, operatorEqual) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = s1;
  EXPECT_EQ(s2.contains(3), 1);
}

TEST(setTest, begin) {
  s21::set<int> s1 = {1, 2, 3};
  EXPECT_EQ(*s1.begin(), 1);
}

TEST(setTest, end) {
  s21::set<int> s1 = {1, 2, 3};
  EXPECT_EQ(*(--s1.end()), 3);
}

TEST(setTest, constBegin) {
  s21::set<int> s1 = {1, 2, 3};
  EXPECT_EQ(*s1.const_begin(), 1);
}

TEST(setTest, constEnd) {
  s21::set<int> s1 = {1, 2, 3};
  EXPECT_EQ(*(--s1.const_end()), 3);
}

TEST(setTest, empty) {
  s21::set<int> s1;
  EXPECT_EQ(s1.empty(), true);
  s1.insert(4);
  EXPECT_EQ(s1.empty(), false);
}

TEST(setTest, size) {
  s21::set<int> s1;
  EXPECT_EQ(s1.size(), 0);
  s1.insert(4);
  s1.insert(7);
  EXPECT_EQ(s1.size(), 2);
}

TEST(setTest, clear) {
  s21::set<int> s1 = {8, 20, 5, 6, 3};
  s1.clear();
  EXPECT_EQ(s1.contains(6), false);
  EXPECT_EQ(s1.size(), 0);
}

TEST(setTest, insert) {
  s21::set<int> s1;
  s1.insert(4);
  EXPECT_EQ(s1.contains(4), 1);
  EXPECT_EQ(s1.contains(3), 0);
}

TEST(setTest, swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.contains(4), true);
  EXPECT_EQ(s2.contains(1), true);
}

TEST(setTest, erase) {
  s21::set<int> s1 = {1, 2, 3};
  auto iter = s1.begin();
  s1.erase(iter);
  EXPECT_EQ(s1.begin().current->data, 2);
}

TEST(setTest, merge) {
  s21::set<int> s1 = {1, 3, 5};
  s21::set<int> s2 = {2, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.contains(2), true);
}

TEST(setTest, find) {
  s21::set<int> s1 = {1, 3, 5};
  auto iter = s1.begin();
  ++iter;
  EXPECT_TRUE(s1.find(3) == iter);
}

TEST(setTest, contains) {
  s21::set<int> s1 = {1, 3, 5};
  EXPECT_TRUE(s1.contains(1) == true);
}

TEST(setTest, maxSize) {
  s21::set<int> s1;
  std::set<int> s2;
  EXPECT_GT(s1.max_size(), s2.max_size());
} //Макс сайз s21 контейнера больше чем у std 18446744073709551615 < 230584300921369395

TEST(setTest, eraseNonExistentElement) {
  s21::set<int> s1 = {1, 2, 3};
  auto iter = s1.begin();
  s1.erase(iter);
  EXPECT_EQ(s1.size(), 2);
  EXPECT_FALSE(s1.contains(1));
}
#endif  // S21_TEST_SET_CPP