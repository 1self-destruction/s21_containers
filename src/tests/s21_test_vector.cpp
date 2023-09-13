#ifndef S21_TEST_VECTOR_CPP
#define S21_TEST_VECTOR_CPP

#include "s21_test_containers.h"

TEST(vectorTest, defaultConstructor) {
  s21::vector<int> x;
  EXPECT_EQ(0, x.size());
}

TEST(vectorTest, parameterizedConstructor) {
  s21::vector<int> x(5);
  EXPECT_EQ(5, x.size());
}

TEST(vectorTest, initializerListConstructor) {
  s21::vector<int> x = {1, 2, 3};
  EXPECT_EQ(x.size(), 3);
}

TEST(vectorTest, copyConstructor) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y(x);
  EXPECT_EQ(y.size(), 3);
  EXPECT_EQ(x.size(), 3);
}

TEST(vectorTest, moveConstructor) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y(std::move(x));
  EXPECT_EQ(y.size(), 3);
  EXPECT_EQ(x.size(), 0);
}

TEST(vectorTest, operatorEqual) {
  s21::vector<int> x = {1, 2, 3};
  s21::vector<int> y = x;
  EXPECT_EQ(y.size(), 3);
  EXPECT_EQ(x.size(), 3);
}

TEST(vectorTest, at) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_THROW(v.at(3), CustomException);
  EXPECT_EQ(v.at(0), 1);
}

TEST(vectorTest, operatorAccessesElement) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_THROW(v[3], CustomException);
  EXPECT_EQ(v[0], 1);
}

TEST(vectorTest, front) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.front(), 1);
}

TEST(vectorTest, back) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.back(), 3);
}

TEST(vectorTest, data) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(v.data()[1], 2);
}

TEST(vectorTest, begin) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(*v.begin(), 1);
}

TEST(vectorTest, end) {
  s21::vector<int> v = {1, 2, 3};
  EXPECT_EQ(*(v.end() - 1), 3);
}

TEST(vectorTest, empty) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(vectorTest, size) {
  s21::vector<int> x(5);
  EXPECT_EQ(x.size(), 5);
}

TEST(vectorTest, capacity) {
  s21::vector<char> x = {'D', 'e', 'n'};
  EXPECT_EQ(3, x.capacity());
}

TEST(vectorTest, reserve) {
  s21::vector<int> v = {1, 2, 3};
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
}

TEST(vectorTest, shrinkToFit) {
  s21::vector<int> v = {1, 2, 3};
  v.reserve(10);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 3);
}

TEST(vectorTest, clear) {
  s21::vector<int> v{1, 2, 3};
  v.clear();
  EXPECT_TRUE(v.empty());
}

TEST(vectorTest, insert) {
  s21::vector<int> v = {1, 2, 3};
  v.insert(v.end(), 15);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.at(3), 15);
}

TEST(vectorTest, erase) {
  s21::vector<int> v = {1, 2, 3};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v.at(0), 2);
}

TEST(vectorTest, pushBack) {
  s21::vector<int> v = {1, 2, 3};
  v.push_back(16);
  EXPECT_EQ(v.size(), 4);
  EXPECT_EQ(v.at(3), 16);
}

TEST(vectorTest, popBack) {
  s21::vector<int> v = {1, 2, 3};
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(*(v.end() - 1), 2);
}

TEST(vectorTest, swap) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};
  v1.swap(v2);
  EXPECT_EQ(v1.at(0), 4);
  EXPECT_EQ(v2.at(2), 3);
}

#endif  // S21_TEST_VECTOR_CPP