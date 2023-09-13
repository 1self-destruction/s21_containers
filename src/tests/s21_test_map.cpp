#ifndef S21_TEST_MAP_CPP
#define S21_TEST_MAP_CPP

#include "s21_test_containers.h"

TEST(mapTest, defaultConstructor) {
  s21::map<int, int> m1;
  EXPECT_EQ(m1.size(), 0);
}

TEST(mapTest, initializerListConstructor) {
  s21::map<int, int> m1 = {std::make_pair(0, 0), std::make_pair(1, 1),
                           std::make_pair(2, 2)};
  EXPECT_EQ(m1.size(), 3);
}

TEST(mapTest, copyConstructor) {
  s21::map<int, int> m1 = {std::make_pair(0, 0), std::make_pair(1, 1),
                           std::make_pair(2, 2)};
  s21::map<int, int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(mapTest, moveConstructor) {
  s21::map<int, int> m1 = {std::make_pair(0, 0), std::make_pair(1, 1),
                           std::make_pair(2, 2)};
  s21::map<int, int> m2(std::move(m1));
  EXPECT_EQ(m1.size(), 0);
  EXPECT_EQ(m2.size(), 3);
}

TEST(mapTest, operatorEqual) {
  s21::map<int, int> m1 = {std::make_pair(0, 0), std::make_pair(1, 1),
                           std::make_pair(2, 2)};
  s21::map<int, int> m2 = m1;
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(mapTest, at) {
  s21::map<int, int> m1 = {std::make_pair(0, 0), std::make_pair(1, 109),
                           std::make_pair(2, 2)};
  EXPECT_EQ(m1.at(1), 109);
}

TEST(mapTest, operatorAt) {
  s21::map<int, int> m1 = {std::make_pair(0, 0), std::make_pair(1, 109),
                           std::make_pair(2, 2)};
  EXPECT_EQ(m1[1], 109);
}

TEST(mapTest, begin) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 2)};
  s21::map<int, int>::iterator mbegin = m1.begin();
  EXPECT_EQ(mbegin.current->pair.second, 20);
}

TEST(mapTest, end) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  s21::map<int, int>::iterator mend = m1.end();
  --mend;
  EXPECT_EQ(mend.current->pair.second, 26);
}

TEST(mapTest, constBegin) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 2)};
  s21::map<int, int>::const_iterator mconstbegin = m1.const_begin();
  EXPECT_EQ(mconstbegin.current->pair.second, 20);
}

TEST(mapTest, constEnd) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  s21::map<int, int>::const_iterator mconstend = m1.const_end();
  --mconstend;
  EXPECT_EQ(mconstend.current->pair.second, 26);
}

TEST(mapTest, empty) {
  s21::map<int, int> m1;
  EXPECT_TRUE(m1.empty());
}

TEST(mapTest, size) {
  s21::map<int, int> m1 = {std::make_pair(0, 20)};
  EXPECT_EQ(m1.size(), 1);
}


TEST(mapTest, maxSize) {
  s21::map<int, int> m1;
  std::map<int, int> m2;
  EXPECT_GT(m1.max_size(), m2.max_size());
} //Макс сайз s21 контейнера больше чем у std 18446744073709551615 < 230584300921369395

TEST(mapTest, clear) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  EXPECT_EQ(m1.size(), 3);
  m1.clear();
  EXPECT_EQ(m1.size(), 0);
}

TEST(mapTest, insert) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  auto p = std::make_pair(3, 37);
  m1.insert(p);
  EXPECT_EQ(m1[3], 37);
}

TEST(mapTest, insertKeyAndObj) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  m1.insert(3, 37);
  EXPECT_EQ(m1[3], 37);
  m1.insert(3, 42);
  EXPECT_FALSE(m1[3] == 42);
}

TEST(mapTest, insertOrAssign) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  m1.insert_or_assign(3, 37);
  EXPECT_EQ(m1[3], 37);
  m1.insert_or_assign(3, 42);
  EXPECT_EQ(m1[3], 42);
}

TEST(mapTest, erase) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  m1.erase(m1.begin());
  auto mbegin = m1.begin();
  EXPECT_EQ(mbegin.current->pair.second, 109);
}

TEST(mapTest, swap) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  s21::map<int, int> m2 = {std::make_pair(0, 40), std::make_pair(1, 228),
                           std::make_pair(2, 1337)};

  m1.swap(m2);
  EXPECT_EQ(m1[0], 40);
  EXPECT_EQ(m2[1], 109);
}

TEST(mapTest, merge) {
  s21::map<int, int> m1 = {std::make_pair(0, 20), std::make_pair(1, 109),
                           std::make_pair(2, 26)};
  s21::map<int, int> m2 = {std::make_pair(3, 40), std::make_pair(4, 228),
                           std::make_pair(5, 1337)};
  m1.merge(m2);
  EXPECT_EQ(m1[3], 40);
  EXPECT_EQ(m1.size(), 6);
}

TEST(mapTest, contains) {
  s21::map<int, int> m1;
  EXPECT_FALSE(m1.contains(86));
}

#endif  // S21_TEST_MAP_CPP