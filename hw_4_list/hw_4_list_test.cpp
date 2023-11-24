// Copyright 2023 <fleurs>

#include <gtest/gtest.h>

#include "hw_4_list.h"

TEST(ListTest, 1DefaultConstructor) {
  bmstu::list<int> my_list;
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, 1PushBackAndSize) {
  bmstu::list<int> my_list = {};
  my_list.push_back(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, 1PushFrontAndSize) {
  bmstu::list<int> my_list;
  my_list.push_front(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, 1Clear) {
  bmstu::list<int> my_list;
  my_list.push_back(42);
  my_list.clear();
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, 1Iterators) {
  bmstu::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  auto it = my_list.begin();
  ASSERT_EQ(*it, 1);

  ++it;
  ASSERT_EQ(*it, 2);

  it++;
  ASSERT_EQ(*it, 3);
}

TEST(ListTest, 1CopyConstructor) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy(original);
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, DefaultConstructor) {
  bmstu::list<int> my_list;
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, PushBackAndSize) {
  bmstu::list<int> my_list;
  my_list.push_back(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, PushFrontAndSize) {
  bmstu::list<int> my_list;
  my_list.push_front(42);
  ASSERT_EQ(my_list.size(), 1);
  ASSERT_FALSE(my_list.empty());
}

TEST(ListTest, Clear) {
  bmstu::list<int> my_list;
  my_list.push_back(42);
  my_list.clear();
  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(my_list.empty());
}

TEST(ListTest, Iterators) {
  bmstu::list<int> my_list;
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  auto it = my_list.begin();
  ASSERT_EQ(*it, 1);

  ++it;
  ASSERT_EQ(*it, 2);

  it++;
  ASSERT_EQ(*it, 3);
}

TEST(ListTest, CopyConstructor) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy(original);
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, MoveConstructor) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> moved(std::move(original));
  ASSERT_EQ(moved.size(), 1);
  ASSERT_EQ(moved[0], 42);
  ASSERT_EQ(original.size(), 0);
  ASSERT_TRUE(original.empty());
}

TEST(ListTest, CopyAssignment) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy;
  copy = original;
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, MoveAssignment) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> moved;
  moved = std::move(original);
  ASSERT_EQ(moved.size(), 1);
  ASSERT_EQ(moved[0], 42);
  ASSERT_EQ(original.size(), 0);
  ASSERT_TRUE(original.empty());
}

TEST(ListTest, Swap) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(3);
  list2.push_back(4);

  list1.swap(list2);

  ASSERT_EQ(list1.size(), 2);
  ASSERT_EQ(list1[0], 3);
  ASSERT_EQ(list1[1], 4);

  ASSERT_EQ(list2.size(), 2);
  ASSERT_EQ(list2[0], 1);
  ASSERT_EQ(list2[1], 2);
}

TEST(ListTest, Equality) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  ASSERT_TRUE(list1 == list2);

  list2.push_back(3);
  ASSERT_FALSE(list1 == list2);
}

TEST(ListTest, Inequality) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  ASSERT_FALSE(list1 != list2);

  list2.push_back(3);
  ASSERT_TRUE(list1 != list2);
}

TEST(ListTest, LessThan) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);
  list2.push_back(3);

  ASSERT_TRUE(list1 < list2);
}

TEST(ListTest, GreaterThan) {
  bmstu::list<int> list1;
  list1.push_back(1);
  list1.push_back(2);
  list1.push_back(3);

  bmstu::list<int> list2;
  list2.push_back(1);
  list2.push_back(2);

  ASSERT_TRUE(list1 > list2);
}

TEST(ListTest, InsertTest) {
  // Создаем список
  bmstu::list<int> my_list;

  // Вставляем элементы в список
  my_list.push_back(1);
  my_list.push_back(2);
  my_list.push_back(3);

  // Вставляем элемент в середину списка
  auto it = my_list.begin();
  ++it;
  my_list.insert(it, 10);

  // Проверяем, что элементы вставлены верно
  EXPECT_EQ(my_list.size(), 4);
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 10);
  EXPECT_EQ(my_list[2], 2);
  EXPECT_EQ(my_list[3], 3);
}

TEST(ListTest, InitializerListTest) {
  // Инициализируем список с использованием initializer list
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Проверяем, что элементы в списке соответствуют ожидаемым значениям
  EXPECT_EQ(my_list.size(), 5);
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 2);
  EXPECT_EQ(my_list[2], 3);
  EXPECT_EQ(my_list[3], 4);
  EXPECT_EQ(my_list[4], 5);
}

TEST(ListTest, OutputOperatorTest) {
  // Инициализируем список
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Подготавливаем поток для вывода
  std::ostringstream oss;

  // Используем оператор вывода для записи списка в поток
  oss << my_list;

  // Проверяем, что результат соответствует ожидаемой строке
  EXPECT_EQ(oss.str(), "[ 1, 2, 3, 4, 5 ]");
}

TEST(ListTest, SubscriptOperatorTest) {
  // Инициализируем список
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Проверяем, что оператор [] возвращает ожидаемые значения
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 2);
  EXPECT_EQ(my_list[2], 3);
  EXPECT_EQ(my_list[3], 4);
  EXPECT_EQ(my_list[4], 5);
}

/// TODO : move, swap in header, test for move constructors.
