// Copyright 2023 <fleurs>

#include <gtest/gtest.h>

#include "hw_4_list.h"

TEST(ListTest, 1DefaultListTest) {
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

TEST(ListTest, 1CopyListTest) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy(original);
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, DefaultListTest) {
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

TEST(ListTest, CopyListTest) {
  bmstu::list<int> original;
  original.push_back(42);

  bmstu::list<int> copy(original);
  ASSERT_EQ(copy.size(), 1);
  ASSERT_EQ(copy[0], 42);
}

TEST(ListTest, MoveListTest) {
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

TEST(ListTest, OutputListTestTest) {
  // Инициализируем список
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Подготавливаем поток для вывода
  std::ostringstream oss;

  // Используем оператор вывода для записи списка в поток
  oss << my_list;

  // Проверяем, что результат соответствует ожидаемой строке
  EXPECT_EQ(oss.str(), "[ 1, 2, 3, 4, 5 ]");
}

TEST(ListTest, SubscriptListTestTest) {
  // Инициализируем список
  bmstu::list<int> my_list = {1, 2, 3, 4, 5};

  // Проверяем, что оператор [] возвращает ожидаемые значения
  EXPECT_EQ(my_list[0], 1);
  EXPECT_EQ(my_list[1], 2);
  EXPECT_EQ(my_list[2], 3);
  EXPECT_EQ(my_list[3], 4);
  EXPECT_EQ(my_list[4], 5);
}

TEST(ListTest, Default) {
  bmstu::list<int> my_list;
  auto it_b = my_list.begin();
  auto it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(it_b == it_e);

  --it_b;
  --it_e;
  ASSERT_TRUE(it_b == it_e);
}

TEST(ListTest, IList) {
  bmstu::list<int> my_list({0, 1, 2, 3, 4});
  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 5);
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 4; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, Copy) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int>::iterator it_b_1 = my_list_1.begin();
  bmstu::list<int>::iterator it_e_1 = my_list_1.end();

  bmstu::list<int> my_list_2(my_list_1);
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 5);
  ASSERT_EQ(my_list_2.size(), 5);
  for (int a = 0; it_b_2 != it_e_2; ++it_b_1, ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_1 == a);
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_1[a] == my_list_2[a]);
  }

  --it_e_1;
  --it_e_2;
  it_b_1 = my_list_1.begin() - 1;
  it_b_2 = my_list_2.begin() - 1;
  for (int a = 4; it_b_2 != it_e_2; --it_e_1, --it_e_2, --a) {
    ASSERT_TRUE(*it_e_1 == a);
    ASSERT_TRUE(*it_e_2 == a);
    ASSERT_TRUE(my_list_1[a] == my_list_2[a]);
  }
}

TEST(ListTest, Move) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int> my_list_2(std::move(my_list_1));
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 0);
  ASSERT_EQ(my_list_2.size(), 5);
  for (int a = 0; it_b_2 != it_e_2; ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_2[a] == a);
  }
}

TEST(ListTest, push_back) {
  bmstu::list<int> my_list({0, 1, 2, 3, 4});

  my_list.push_back(5);

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 6);
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 5; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, push_front) {
  bmstu::list<int> my_list({1, 2, 3, 4, 5});

  my_list.push_front(0);

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 6);
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 5; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, clear) {
  bmstu::list<int> my_list({1, 2, 3, 4, 5});

  my_list.clear();

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();

  ASSERT_EQ(my_list.size(), 0);
  ASSERT_TRUE(it_b == it_e);

  --it_b;
  --it_e;
  ASSERT_TRUE(it_b == it_e);
}

TEST(ListTest, swap) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int> my_list_2({7, 8, 9});

  my_list_1.swap(my_list_2);

  bmstu::list<int>::iterator it_b_1 = my_list_1.begin();
  bmstu::list<int>::iterator it_e_1 = my_list_1.end();
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 3);
  ASSERT_EQ(my_list_2.size(), 5);

  for (int a = 7; it_b_1 != it_e_1; ++it_b_1, ++a) {
    ASSERT_TRUE(*it_b_1 == a);
    ASSERT_TRUE(my_list_1[a - 7] == a);
  }

  --it_e_1;
  it_b_1 = my_list_1.begin() - 1;
  for (int a = 9; it_b_1 != it_e_1; --it_e_1, --a) {
    ASSERT_TRUE(*it_e_1 == a);
    ASSERT_TRUE(my_list_1[a - 7] == a);
  }

  for (int a = 0; it_b_2 != it_e_2; ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_2[a] == a);
  }

  --it_e_2;
  it_b_2 = my_list_2.begin() - 1;
  for (int a = 4; it_b_2 != it_e_2; --it_e_2, --a) {
    ASSERT_TRUE(*it_e_2 == a);
    ASSERT_TRUE(my_list_2[a] == a);
  }
}

TEST(ListTest, Index) {
  bmstu::list<int> my_list({0, 1, 2, 0, 4});
  my_list[3] = 3;

  ASSERT_EQ(my_list.size(), 5);

  bmstu::list<int>::iterator it_b = my_list.begin();
  bmstu::list<int>::iterator it_e = my_list.end();
  for (int a = 0; it_b != it_e; ++it_b, ++a) {
    ASSERT_TRUE(*it_b == a);
    ASSERT_TRUE(my_list[a] == a);
  }

  --it_e;
  it_b = my_list.begin() - 1;
  for (int a = 4; it_b != it_e; --it_e, --a) {
    ASSERT_TRUE(*it_e == a);
    ASSERT_TRUE(my_list[a] == a);
  }
}

TEST(ListTest, EQs) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4, 5, 6});
  bmstu::list<int> my_list_2({0, 1, 2, 3, 4, 5, 6});
  bmstu::list<int> my_list_3({0, 1, 2, 3, 4, 5, 7});
  bmstu::list<int> my_list_4({1, 2, 3, 4, 5, 7, 8});
  bmstu::list<int> my_list_5({1, 1, 2, 3, 4, 5, 7});

  ASSERT_TRUE(my_list_1 == my_list_2);
  ASSERT_FALSE(my_list_1 == my_list_3);
  ASSERT_TRUE(my_list_1 != my_list_3);
  ASSERT_FALSE(my_list_1 != my_list_2);
  ASSERT_TRUE(my_list_1 < my_list_4);
  ASSERT_TRUE(my_list_4 > my_list_1);
  ASSERT_TRUE(my_list_1 <= my_list_5);
  ASSERT_TRUE(my_list_5 >= my_list_1);
}

TEST(ListTest, LeftShift) {
  bmstu::list<int> my_list({0, 1, 2, 3, 4, 5, 6});
  std::stringstream ss;
  ss << my_list;
  ASSERT_STREQ(ss.str().c_str(), "[ 0, 1, 2, 3, 4, 5, 6 ]");
}

TEST(ListTest, IteratorsHard) {
  bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
  bmstu::list<int>::iterator it_b_1 = my_list_1.begin() + 1;
  bmstu::list<int>::iterator it_e_1 = my_list_1.end() - 1;

  bmstu::list<int> my_list_2(it_b_1, it_e_1);
  bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
  bmstu::list<int>::iterator it_e_2 = my_list_2.end();

  ASSERT_EQ(my_list_1.size(), 5);
  ASSERT_EQ(my_list_2.size(), 3);
  for (int a = 1; it_b_2 != it_e_2; ++it_b_2, ++a) {
    ASSERT_TRUE(*it_b_2 == a);
    ASSERT_TRUE(my_list_2[a - 1] == a);
  }

  --it_e_2;
  it_b_2 = my_list_2.begin() - 1;
  for (int a = 3; it_b_2 != it_e_2; --it_e_2, --a) {
    ASSERT_TRUE(*it_e_2 == a);
    ASSERT_TRUE(my_list_2[a - 1] == a);
  }
}
