// Copyright 2023 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_3_dummy_vector.h"

using bmstu::dummy_vector;

TEST(DummyVectorTest, null) {
  dummy_vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(DummyVectorTest, pushback) {
  dummy_vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
  a.push_back(6);
  ASSERT_EQ(a.size(), 1);
  ASSERT_EQ(a.capacity(), 1);
  a.push_back(6);
  ASSERT_EQ(a.size(), 2);
  ASSERT_EQ(a.capacity(), 2);
  a.push_back(6);
  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(a.capacity(), 4);
  a.push_back(6);
  ASSERT_EQ(a.size(), 4);
  ASSERT_EQ(a.capacity(), 4);
  a.push_back(6);
  ASSERT_EQ(a.size(), 5);
  ASSERT_EQ(a.capacity(), 8);
}

TEST(DummyVectorTest, insert) {
  bmstu::dummy_vector<int> v;
  bmstu::dummy_vector<int> v_expected{0, 666, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
  v.insert(v.begin() + 1, 666);
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(v[i], v_expected[i]);
  }
}

TEST(DummyVectorTest, lexical) {
  bmstu::dummy_vector<char> v{'1', '2', '3'};
  bmstu::dummy_vector<char> v_c{'1', '2', '3'};
  ASSERT_TRUE(v <= v_c);
  ASSERT_TRUE(v >= v_c);
  ASSERT_TRUE(v == v_c);
}

TEST(DummyVectorTest, complex) {
  bmstu::dummy_vector<int> v;
  v.push_back(23);
  ASSERT_EQ(v[0], 23);
  size_t big_number = 1;
  for (size_t i = 0; i < 10; ++i) {
    big_number *= 2;
  }
  for (size_t i = 0; i < big_number; ++i) {
    v.push_back(i);
  }
  ASSERT_EQ(v.size(), big_number + 1);
  for (size_t i = 0; i < big_number; ++i) {
    v.pop_back();
  }
  ASSERT_EQ(v.size(), 1);
}

TEST(DummyVectorTest, 1reserve) {
  bmstu::dummy_vector<int> vec;
  vec.reserve(10);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 10);
  for (size_t i = 0; i < vec.capacity(); ++i) {
    vec.push_back(i);
  }
  EXPECT_EQ(vec.size(), 10);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(DummyVectorTest, DefaultDummyVectorTest) {
  bmstu::dummy_vector<int> vec_default;
  EXPECT_EQ(vec_default.size(), 0);
  EXPECT_EQ(vec_default.capacity(), 0);
}

TEST(DummyVectorTest, DummyVectorTestWithSizeAndValue) {
  bmstu::dummy_vector<int> vec_with_size(5, 42);
  EXPECT_EQ(vec_with_size.size(), 5);
  EXPECT_EQ(vec_with_size.capacity(), 5);
  for (int value : vec_with_size) {
    EXPECT_EQ(value, 42);
  }
}

TEST(DummyVectorTest, CopyDummyVectorTest) {
  bmstu::dummy_vector<int> original(3, 7);
  bmstu::dummy_vector<int> copy(original);
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.capacity(), copy.capacity());
  EXPECT_TRUE(std::equal(original.begin(), original.end(), copy.begin()));
}

TEST(DummyVectorTest, MoveDummyVectorTest) {
  bmstu::dummy_vector<int> original(3, 7);
  bmstu::dummy_vector<int> moved(std::move(original));
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(original.capacity(), 0);
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.capacity(), 3);
  moved.push_back(4);
  ASSERT_EQ(moved.capacity(), 6);
  ASSERT_EQ(moved[3], 4);
}

TEST(DummyVectorTest, Resize) {
  bmstu::dummy_vector<int> vec;
  vec.resize(5);
  EXPECT_EQ(vec.size(), 5);
  EXPECT_EQ(vec.capacity(), 5);
}

TEST(DummyVectorTest, Reserve) {
  bmstu::dummy_vector<int> vec;
  vec.reserve(10);
  EXPECT_EQ(vec.size(), 0);
  EXPECT_EQ(vec.capacity(), 10);
}

TEST(DummyVectorTest, 1Insert) {
  bmstu::dummy_vector<int> vec = {1, 2, 3};
  auto it = vec.insert(vec.begin() + 1, 42);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[1], 42);
  EXPECT_EQ(*it, 42);
}

TEST(DummyVectorTest, PushBack) {
  bmstu::dummy_vector<int> vec = {1, 2, 3};
  vec.push_back(42);
  EXPECT_EQ(vec.size(), 4);
  EXPECT_EQ(vec[3], 42);
}

TEST(DummyVectorTest, At) {
  bmstu::dummy_vector<int> vec = {1, 2, 3};
  EXPECT_EQ(vec.at(1), 2);
}

TEST(DummyVectorTest, PopBack) {
  bmstu::dummy_vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[1], 2);
}

TEST(DummyVectorTest, Swap) {
  bmstu::dummy_vector<int> vec1 = {1, 2, 3};
  bmstu::dummy_vector<int> vec2 = {4, 5, 6};
  vec1.swap(vec2);
  EXPECT_EQ(vec1.size(), 3);
  EXPECT_EQ(vec2.size(), 3);
  EXPECT_EQ(vec1[0], 4);
  EXPECT_EQ(vec2[0], 1);
}

TEST(DummyVectorTest, Equality) {
  bmstu::dummy_vector<int> vec1 = {1, 2, 3, 4, 5};
  bmstu::dummy_vector<int> vec2 = {1, 2, 3, 4, 5};
  bmstu::dummy_vector<int> vec3 = {1, 2, 3, 4, 6};
  ASSERT_TRUE(vec1 == vec2);
  ASSERT_FALSE(vec1 == vec3);
}

TEST(DummyVectorTest, Comparison) {
  bmstu::dummy_vector<int> vec1 = {1, 2, 3, 4, 5};
  bmstu::dummy_vector<int> vec2 = {1, 2, 3, 4, 5};
  bmstu::dummy_vector<int> vec3 = {1, 2, 3, 4, 6};
  bmstu::dummy_vector<int> vec4 = {1, 2, 3};
  ASSERT_TRUE(vec1 == vec2);
  ASSERT_TRUE(vec1 < vec3);
  ASSERT_TRUE(vec4 < vec1);
  ASSERT_TRUE(vec3 > vec2);
}

TEST(DummyVectorTest, OutputDummyVectorTest) {
  bmstu::dummy_vector<int> vec = {1, 2, 3, 4, 5};
  std::stringstream ss;
  ss << vec;
  ASSERT_EQ(ss.str(), "[ 1, 2, 3, 4, 5 ]");
}

TEST(DummyVectorTest, Default) {
  bmstu::dummy_vector<int> my_vec;
  ASSERT_EQ(my_vec.size(), 0);
  ASSERT_EQ(my_vec.capacity(), 0);
}

TEST(DummyVectorTest, InList) {
  bmstu::dummy_vector my_vec({0, 1, 2});
  ASSERT_EQ(my_vec.size(), 3);
  ASSERT_EQ(my_vec.capacity(), 3);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
    ASSERT_EQ(my_vec.at(i), i);
  }
}

TEST(DummyVectorTest, Parametr) {
  bmstu::dummy_vector my_vec(4, 20);
  ASSERT_EQ(my_vec.size(), 4);
  ASSERT_EQ(my_vec.capacity(), 4);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], 20);
    ASSERT_EQ(my_vec.at(i), 20);
  }
}

TEST(DummyVectorTest, 1Copy) {
  bmstu::dummy_vector my_vec1(4, 20);
  bmstu::dummy_vector my_vec2(my_vec1);
  ASSERT_EQ(my_vec1.size(), 4);
  ASSERT_EQ(my_vec1.capacity(), 4);
  ASSERT_EQ(my_vec2.size(), my_vec1.size());
  ASSERT_EQ(my_vec2.capacity(), my_vec1.capacity());
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 20);
    ASSERT_EQ(my_vec1.at(i), 20);
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(DummyVectorTest, 1Move) {
  bmstu::dummy_vector my_vec1(4, 20);
  bmstu::dummy_vector my_vec2(std::move(my_vec1));
  ASSERT_EQ(my_vec1.size(), 0);
  ASSERT_EQ(my_vec1.capacity(), 0);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(DummyVectorTest, Copy) {
  bmstu::dummy_vector my_vec1(4, 20);
  bmstu::dummy_vector my_vec2 = my_vec1;
  ASSERT_EQ(my_vec1.size(), 4);
  ASSERT_EQ(my_vec1.capacity(), 4);
  ASSERT_EQ(my_vec2.size(), my_vec1.size());
  ASSERT_EQ(my_vec2.capacity(), my_vec1.capacity());
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 20);
    ASSERT_EQ(my_vec1.at(i), 20);
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(DummyVectorTest, Move) {
  bmstu::dummy_vector my_vec1(4, 20);
  bmstu::dummy_vector my_vec2 = std::move(my_vec1);
  ASSERT_EQ(my_vec1.size(), 0);
  ASSERT_EQ(my_vec1.capacity(), 0);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
    ASSERT_EQ(my_vec2.at(i), 20);
  }
}

TEST(DummyVectorTest, BeginAndEnd) {
  bmstu::dummy_vector my_vec({0, 1, 2, 3, 4, 5});
  bmstu::dummy_vector<int>::iterator itb = my_vec.begin();
  bmstu::dummy_vector<int>::iterator ite = my_vec.end();
  size_t n = 0;
  for (; itb != ite; ++itb) {
    ASSERT_EQ(*itb, n);
    n += 1;
  }
}

TEST(DummyVectorTest, Empty) {
  bmstu::dummy_vector<int> my_vec1;
  bmstu::dummy_vector my_vec2({1, 2, 3});
  ASSERT_TRUE(my_vec1.empty());
  ASSERT_FALSE(my_vec2.empty());
}

TEST(DummyVectorTest, clear) {
  bmstu::dummy_vector my_vec({1, 2, 3});
  my_vec.clear();
  ASSERT_EQ(my_vec.size(), 0);
  ASSERT_EQ(my_vec.capacity(), 3);
}

TEST(DummyVectorTest, SwapV1) {
  bmstu::dummy_vector my_vec1(4, 20);
  bmstu::dummy_vector my_vec2(13, 3);
  my_vec1.swap(my_vec2);
  ASSERT_EQ(my_vec1.size(), 13);
  ASSERT_EQ(my_vec1.capacity(), 13);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 3);
  }
  for (size_t i = 0; i < my_vec2.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
  }
}

TEST(DummyVectorTest, SwapV2) {
  bmstu::dummy_vector my_vec1(4, 20);
  bmstu::dummy_vector my_vec2(13, 3);
  swap(my_vec1, my_vec2);
  ASSERT_EQ(my_vec1.size(), 13);
  ASSERT_EQ(my_vec1.capacity(), 13);
  ASSERT_EQ(my_vec2.size(), 4);
  ASSERT_EQ(my_vec2.capacity(), 4);
  for (size_t i = 0; i < my_vec1.size(); ++i) {
    ASSERT_EQ(my_vec1[i], 3);
  }
  for (size_t i = 0; i < my_vec2.size(); ++i) {
    ASSERT_EQ(my_vec2[i], 20);
  }
}

TEST(DummyVectorTest, resize) {
  bmstu::dummy_vector my_vec(5, 20);
  my_vec.resize(4);
  ASSERT_EQ(my_vec.size(), 4);
  ASSERT_EQ(my_vec.capacity(), 5);

  my_vec.resize(7);
  ASSERT_EQ(my_vec.size(), 7);
  ASSERT_EQ(my_vec.capacity(), 10);

  my_vec.resize(21);
  ASSERT_EQ(my_vec.size(), 21);
  ASSERT_EQ(my_vec.capacity(), 21);
}

TEST(DummyVectorTest, reserve) {
  bmstu::dummy_vector my_vec(5, 20);
  my_vec.reserve(21);
  ASSERT_EQ(my_vec.size(), 5);
  ASSERT_EQ(my_vec.capacity(), 21);
}

TEST(DummyVectorTest, Insert) {
  bmstu::dummy_vector my_vec = {0, 1, 2, 4, 5, 6};
  bmstu::dummy_vector<int>::iterator it = my_vec.begin() + 3;
  my_vec.insert(it, 3);
  ASSERT_EQ(my_vec.size(), 7);
  ASSERT_EQ(my_vec.capacity(), 12);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
  }
}

TEST(DummyVectorTest, Push_Pop_back) {
  bmstu::dummy_vector my_vec = {0, 1, 2, 3, 4, 5, 6};
  my_vec.push_back(7);
  ASSERT_EQ(my_vec.size(), 8);
  ASSERT_EQ(my_vec.capacity(), 14);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
  }
  my_vec.pop_back();
  ASSERT_EQ(my_vec.size(), 7);
  ASSERT_EQ(my_vec.capacity(), 14);
  for (size_t i = 0; i < my_vec.size(); ++i) {
    ASSERT_EQ(my_vec[i], i);
  }
}

TEST(DummyVectorTest, EQs) {
  bmstu::dummy_vector my_vec1 = {0, 1, 2, 3, 4, 5, 6};
  bmstu::dummy_vector my_vec2 = {0, 1, 2, 3, 4, 5, 6};
  bmstu::dummy_vector my_vec3 = {0, 1, 2, 3, 4, 5, 7};
  bmstu::dummy_vector my_vec4 = {1, 2, 3, 4, 5, 7, 8};
  bmstu::dummy_vector my_vec5 = {1, 1, 2, 3, 4, 5, 7};
  ASSERT_TRUE(my_vec1 == my_vec2);
  ASSERT_FALSE(my_vec1 == my_vec3);
  ASSERT_TRUE(my_vec1 != my_vec3);
  ASSERT_FALSE(my_vec1 != my_vec2);
  ASSERT_TRUE(my_vec1 < my_vec4);
  ASSERT_TRUE(my_vec4 > my_vec1);
  ASSERT_TRUE(my_vec1 <= my_vec5);
  ASSERT_TRUE(my_vec5 >= my_vec1);
}

TEST(DummyVectorTest, one) {
  bmstu::dummy_vector<int> v;
  ASSERT_EQ(v.size(), 0u);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.capacity(), 0u);
}

//
//
TEST(DummyVectorTest, Init) {
  // Инициализация вектора указанного размера
  bmstu::dummy_vector<int> v(5);
  ASSERT_EQ(v.size(), 5u);
  ASSERT_EQ(v.capacity(), 5u);
  ASSERT_TRUE(!v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 0);
  }
}

TEST(DummyVectorTest, Init2) {
  bmstu::dummy_vector<int> v(3, 42);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 42);
  }
}

//
TEST(DummyVectorTest, InitList) {
  bmstu::dummy_vector<int> v{1, 2, 3};
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  ASSERT_EQ(v[2], 3);
}

//
TEST(DummyVectorTest, Resize1) {
  {
    bmstu::dummy_vector<int> v(3);
    v[0] = 42;
    v[1] = 55;
    const size_t old_capacity = v.capacity();
    v.resize(2);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v[0], 42);
    ASSERT_EQ(v[1], 55);
  }
}

//
TEST(DummyVectorTest, Resize2) {
  const size_t old_size = 3;
  bmstu::dummy_vector<int> v(3);
  v.resize(old_size + 5);
  v[3] = 42;
  v.resize(old_size);
  ASSERT_EQ(v[2], 0);
  v.resize(old_size + 3);
  ASSERT_EQ(v[3], 0);
}

//
TEST(DummyVectorTest, DummyVectorTests) {
  {
    bmstu::dummy_vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::dummy_vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::dummy_vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::dummy_vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::dummy_vector<int> v(1);
    v.push_back(1);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(*(v.begin()) + 1, 1);
  }
}

TEST(DummyVectorTest, Push) {
  bmstu::dummy_vector<int> v(1);
  v.push_back(42);
  ASSERT_EQ(v.size(), 2);
  ASSERT_TRUE(v.capacity() >= v.size());
  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 42);
}

TEST(DummyVectorTest, CopyConstruct) {
  bmstu::dummy_vector<int> numbers{1, 2};
  auto numbers_copy(numbers);
  ASSERT_TRUE(&numbers_copy[0] != &numbers[0]);
  ASSERT_EQ(numbers_copy.size(), numbers.size());
  for (size_t i = 0; i < numbers.size(); ++i) {
    ASSERT_EQ(numbers_copy[i], numbers[i]);
    ASSERT_TRUE(&numbers_copy[i] != &numbers[i]);
  }
}

TEST(DummyVectorTest, Capacity) {
  bmstu::dummy_vector<int> v(2);
  v.resize(1);
  const size_t old_capacity = v.capacity();
  v.push_back(123);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(DummyVectorTest, Iterate) {
  // Итерирование по bmstu::dummy_vector
  {
    // Непустой вектор
    {
      bmstu::dummy_vector<int> v(10, 42);
      //            ASSERT_TRUE(v.begin());
      ASSERT_EQ(*v.begin(), 42);
      ASSERT_EQ(v.end(), v.begin() + v.size());
    }
  }
}

TEST(DummyVectorTest, Compare) {
  {
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} == bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} != bmstu::dummy_vector{1, 2, 2}));

    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3}
        < bmstu::dummy_vector{1, 2, 3, 1}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3}
        > bmstu::dummy_vector{1, 2, 2, 1}));

    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} >= bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 4} >= bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 4}));
  }
}

TEST(DummyVectorTest, Pushback2) {
  bmstu::dummy_vector<int> v2;
  v2.push_back(0);
  v2.push_back(1);
  v2.push_back(2);
  ASSERT_EQ(v2, (bmstu::dummy_vector<int>{0, 1, 2}));
}

TEST(DummyVectorTest, Swap2) {
  // Обмен значений векторов
  {
    bmstu::dummy_vector<int> v1{42, 666};
    bmstu::dummy_vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    const int *const begin1 = &v1[0];
    const int *const begin2 = &v2[0];

    const size_t capacity1 = v1.capacity();
    const size_t capacity2 = v2.capacity();

    const size_t size1 = v1.size();
    const size_t size2 = v2.size();

    v1.swap(v2);
    ASSERT_TRUE(&v2[0] == begin1);
    ASSERT_TRUE(&v1[0] == begin2);
    ASSERT_TRUE(v1.size() == size2);
    ASSERT_TRUE(v2.size() == size1);
    ASSERT_TRUE(v1.capacity() == capacity2);
    ASSERT_TRUE(v2.capacity() == capacity1);
  }
}

TEST(DummyVectorTest, Test1) {
  bmstu::dummy_vector<int> src_vector{1, 2, 3, 4};
  bmstu::dummy_vector<int> dst_vector{1, 2, 3, 4, 5, 6};
  dst_vector = src_vector;
  ASSERT_EQ(dst_vector, src_vector);
}

TEST(DummyVectorTest, Insert2) {
  // Вставка элементов

  bmstu::dummy_vector<int> v;
  v.insert(v.begin(), 42);
  ASSERT_EQ(v, (bmstu::dummy_vector<int>{42}));
}

TEST(DummyVectorTest, Reserve2) {
  {
    bmstu::dummy_vector<int> v(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_FALSE(v.empty());
  }
  {
    bmstu::dummy_vector<int> v;
    // зарезервируем 5 мест в векторе
    v.reserve(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_TRUE(v.empty());

    // попытаемся уменьшить capacity до 1
    v.reserve(1);
    // capacity должно остаться прежним
    ASSERT_EQ(v.capacity(), 5);
    // поместим 10 элементов в вектор
    for (int i = 0; i < 10; ++i) {
      v.push_back(i);
    }
    ASSERT_EQ(v.size(), 10);
    // увеличим capacity до 100
    v.reserve(100);
    // проверим, что размер не поменялся
    ASSERT_EQ(v.size(), 10);
    ASSERT_EQ(v.capacity(), 100);
    // проверим, что элементы на месте
    for (int i = 0; i < 10; ++i) {
      ASSERT_EQ(v[i], i);
    }
  }
}

bmstu::dummy_vector<int> GenerateVector(size_t size) {
  bmstu::dummy_vector<int> v(size);
  std::iota(v.begin(), v.end(), 1);
  return v;
}

TEST(DummyVectorTest, temporary) {
  const size_t size = 1000000;
  bmstu::dummy_vector<int> moved_vector(GenerateVector(size));
  ASSERT_EQ(moved_vector.size(), size);
}

TEST(DummyVectorTest, moveconstructor) {
  const size_t size = 1000000;

  bmstu::dummy_vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::dummy_vector<int> moved_vector(std::move(vector_to_move));
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(DummyVectorTest, moveoperator) {
  const size_t size = 1000000;
  bmstu::dummy_vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::dummy_vector<int> moved_vector = std::move(vector_to_move);
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(DummyVectorTest, test_new_push) {
  bmstu::dummy_vector<int> v;
  ASSERT_EQ(v.capacity(), 0);
  ASSERT_EQ(v.size(), 0);
  v.push_back(1);
  ASSERT_EQ(v.capacity(), 1);
  ASSERT_EQ(v.size(), 1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
}

TEST(DummyVectorTest, 1one) {
  bmstu::dummy_vector<int> v;
  ASSERT_EQ(v.size(), 0u);
  ASSERT_TRUE(v.empty());
  ASSERT_EQ(v.capacity(), 0u);
}

//
//
TEST(DummyVectorTest, 1Init) {
  // Инициализация вектора указанного размера
  bmstu::dummy_vector<int> v(5);
  ASSERT_EQ(v.size(), 5u);
  ASSERT_EQ(v.capacity(), 5u);
  ASSERT_TRUE(!v.empty());
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 0);
  }
}

TEST(DummyVectorTest, 1Init2) {
  bmstu::dummy_vector<int> v(3, 42);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], 42);
  }
}

//
TEST(DummyVectorTest, 1InitList) {
  bmstu::dummy_vector<int> v{1, 2, 3};
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 3);
  ASSERT_EQ(v[2], 3);
}

//
TEST(DummyVectorTest, 1At) {
  bmstu::dummy_vector<int> v(3);
  ASSERT_EQ(&v.at(2), &v[2]);
  try {
    v.at(3);
  }
  catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Invalid index"));
  }
}

//
TEST(DummyVectorTest, 1Clear) {
  bmstu::dummy_vector<int> v(10);
  const size_t old_capacity = v.capacity();
  v.clear();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), old_capacity);
}

//
TEST(DummyVectorTest, 1Resize) {
  // Изменение размера
  {
    bmstu::dummy_vector<int> v(3);
    v[2] = 17;
    v.resize(7);
    ASSERT_EQ(v.size(), 7);
    ASSERT_TRUE(v.capacity() >= v.size());
    ASSERT_EQ(v[2], 17);
    ASSERT_EQ(v[3], 0);
  }
}

//
TEST(DummyVectorTest, 1Resize1) {
  {
    bmstu::dummy_vector<int> v(3);
    v[0] = 42;
    v[1] = 55;
    const size_t old_capacity = v.capacity();
    v.resize(2);
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v[0], 42);
    ASSERT_EQ(v[1], 55);
  }
}

//
TEST(DummyVectorTest, 1Resize2) {
  const size_t old_size = 3;
  bmstu::dummy_vector<int> v(3);
  v.resize(old_size + 5);
  v[3] = 42;
  v.resize(old_size);
  ASSERT_EQ(v[2], 0);
  v.resize(old_size + 3);
  ASSERT_EQ(v[3], 0);
}

//
TEST(DummyVectorTest, 1Constructors) {
  {
    bmstu::dummy_vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::dummy_vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::dummy_vector<int> v(5);
    v[0] = 1;
    v[1] = 2;
    v[2] = 3;
    v[3] = 4;
    v[4] = 5;
    bmstu::dummy_vector<int> c(v);
    ASSERT_EQ(v[2], v[2]);
  }
  {
    bmstu::dummy_vector<int> v(1);
    v.push_back(1);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(*(v.begin()) + 1, 1);
  }
}

TEST(DummyVectorTest, 1Push) {
  bmstu::dummy_vector<int> v(1);
  v.push_back(42);
  ASSERT_EQ(v.size(), 2);
  ASSERT_TRUE(v.capacity() >= v.size());
  ASSERT_EQ(v[0], 0);
  ASSERT_EQ(v[1], 42);
}

TEST(DummyVectorTest, 1CopyConstruct) {
  bmstu::dummy_vector<int> numbers{1, 2};
  auto numbers_copy(numbers);
  ASSERT_TRUE(&numbers_copy[0] != &numbers[0]);
  ASSERT_EQ(numbers_copy.size(), numbers.size());
  for (size_t i = 0; i < numbers.size(); ++i) {
    ASSERT_EQ(numbers_copy[i], numbers[i]);
    ASSERT_TRUE(&numbers_copy[i] != &numbers[i]);
  }
}

TEST(DummyVectorTest, 1PopBack) {
  // PopBack
  {
    bmstu::dummy_vector<int> v{0, 1, 2, 3};
    const size_t old_capacity = v.capacity();
    const auto old_begin = v.begin();
    v.pop_back();
    ASSERT_EQ(v.capacity(), old_capacity);
    ASSERT_EQ(v.begin(), old_begin);
    ASSERT_EQ(v, (bmstu::dummy_vector<int>{0, 1, 2}));
  }
}

TEST(DummyVectorTest, 1Capacity) {
  bmstu::dummy_vector<int> v(2);
  v.resize(1);
  const size_t old_capacity = v.capacity();
  v.push_back(123);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), old_capacity);
}

TEST(DummyVectorTest, 1Iterate) {
  // Итерирование по bmstu::dummy_vector
  {
    // Пустой вектор
    {
      bmstu::dummy_vector<int> v;
      ASSERT_EQ(v.begin(), nullptr);
      ASSERT_EQ(v.end(), nullptr);
    }

    // Непустой вектор
    {
      bmstu::dummy_vector<int> v(10, 42);
      //            ASSERT_TRUE(v.begin());
      ASSERT_EQ(*v.begin(), 42);
      ASSERT_EQ(v.end(), v.begin() + v.size());
    }
  }
}

TEST(DummyVectorTest, 1Compare) {
  {
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} == bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} != bmstu::dummy_vector{1, 2, 2}));

    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3}
        < bmstu::dummy_vector{1, 2, 3, 1}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3}
        > bmstu::dummy_vector{1, 2, 2, 1}));

    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} >= bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 4} >= bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 3}));
    ASSERT_TRUE((bmstu::dummy_vector{1, 2, 3} <= bmstu::dummy_vector{1, 2, 4}));
  }
}

TEST(DummyVectorTest, 1Pushback2) {
  bmstu::dummy_vector<int> v2;
  v2.push_back(0);
  v2.push_back(1);
  v2.push_back(2);
  ASSERT_EQ(v2, (bmstu::dummy_vector<int>{0, 1, 2}));
}

TEST(DummyVectorTest, 1Swap) {
  // Обмен значений векторов
  {
    bmstu::dummy_vector<int> v1{42, 666};
    bmstu::dummy_vector<int> v2;
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(2);
    const int *const begin1 = &v1[0];
    const int *const begin2 = &v2[0];

    const size_t capacity1 = v1.capacity();
    const size_t capacity2 = v2.capacity();

    const size_t size1 = v1.size();
    const size_t size2 = v2.size();

    v1.swap(v2);
    ASSERT_TRUE(&v2[0] == begin1);
    ASSERT_TRUE(&v1[0] == begin2);
    ASSERT_TRUE(v1.size() == size2);
    ASSERT_TRUE(v2.size() == size1);
    ASSERT_TRUE(v1.capacity() == capacity2);
    ASSERT_TRUE(v2.capacity() == capacity1);
  }
}

TEST(DummyVectorTest, 1Test1) {
  {
    bmstu::dummy_vector<int> src_vector{1, 2, 3, 4};
    bmstu::dummy_vector<int> dst_vector{1, 2, 3, 4, 5, 6};
    dst_vector = src_vector;
    ASSERT_EQ(dst_vector, src_vector);
  }
}

TEST(DummyVectorTest, 11Insert) {
  // Вставка элементов
  {
    bmstu::dummy_vector<int> v{1, 2, 3, 4};
    auto vit = v.begin() + 3;
    v.insert(v.begin() + 2, 42);
    ASSERT_EQ(v, (bmstu::dummy_vector<int>{1, 2, 42, 3, 4}));
  }
}

TEST(DummyVectorTest, 1Insert2) {
  // Вставка элементов

  bmstu::dummy_vector<int> v;
  v.insert(v.begin(), 42);
  ASSERT_EQ(v, (bmstu::dummy_vector<int>{42}));
}

TEST(DummyVectorTest, 1Erase) {
  {
    bmstu::dummy_vector<int> v{1, 2, 3, 4};
    v.erase(v.begin() + 2);

    ASSERT_EQ(v, (bmstu::dummy_vector<int>{1, 2, 4}));
  }
}

TEST(DummyVectorTest, 1Reserve) {
  {
    bmstu::dummy_vector<int> v(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_FALSE(v.empty());
  }
  {
    bmstu::dummy_vector<int> v;
    // зарезервируем 5 мест в векторе
    v.reserve(5);
    ASSERT_EQ(v.capacity(), 5);
    ASSERT_TRUE(v.empty());

    // попытаемся уменьшить capacity до 1
    v.reserve(1);
    // capacity должно остаться прежним
    ASSERT_EQ(v.capacity(), 5);
    // поместим 10 элементов в вектор
    for (int i = 0; i < 10; ++i) {
      v.push_back(i);
    }
    ASSERT_EQ(v.size(), 10);
    // увеличим capacity до 100
    v.reserve(100);
    // проверим, что размер не поменялся
    ASSERT_EQ(v.size(), 10);
    ASSERT_EQ(v.capacity(), 100);
    // проверим, что элементы на месте
    for (int i = 0; i < 10; ++i) {
      ASSERT_EQ(v[i], i);
    }
  }
}

class X {
 public:
  X()
      : X(5) {
  }

  explicit X(size_t num)
      : x_(num) {
  }

  X(const X &other) = delete;

  X &operator=(const X &other) = delete;

  X(X &&other) {
    x_ = std::exchange(other.x_, 0);
  }

  X &operator=(X &&other) {
    x_ = std::exchange(other.x_, 0);
    return *this;
  }

  size_t GetX() const {
    return x_;
  }

 private:
  size_t x_;
};

TEST(DummyVectorTest, 1temporary) {
  const size_t size = 1000000;
  bmstu::dummy_vector<int> moved_vector(GenerateVector(size));
  ASSERT_EQ(moved_vector.size(), size);
}

TEST(DummyVectorTest, 1moveconstructor) {
  const size_t size = 1000000;

  bmstu::dummy_vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::dummy_vector<int> moved_vector(std::move(vector_to_move));
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(DummyVectorTest, 1moveoperator) {
  const size_t size = 1000000;
  bmstu::dummy_vector<int> vector_to_move(GenerateVector(size));
  ASSERT_EQ(vector_to_move.size(), size);

  bmstu::dummy_vector<int> moved_vector = std::move(vector_to_move);
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);
}

TEST(DummyVectorTest, 1noncopybable2) {
  const size_t size = 5;
  bmstu::dummy_vector<X> vector_to_move;
  for (size_t i = 0; i < size; ++i) {
    vector_to_move.push_back(X(i));
  }
  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(vector_to_move[i].GetX(), i);
  }

  bmstu::dummy_vector<X> moved_vector = std::move(vector_to_move);
  ASSERT_EQ(moved_vector.size(), size);
  ASSERT_EQ(vector_to_move.size(), 0);

  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(moved_vector[i].GetX(), i);
  }
}

TEST(DummyVectorTest, 1noncopypable3) {
  const size_t size = 5;
  bmstu::dummy_vector<X> v;
  for (size_t i = 0; i < size; ++i) {
    v.push_back(X(i));
  }

  ASSERT_EQ(v.size(), size);

  for (size_t i = 0; i < size; ++i) {
    ASSERT_EQ(v[i].GetX(), i);
  }
}

TEST(DummyVectorTest, 1noncopiableinsert) {
  const size_t size = 5;
  bmstu::dummy_vector<X> v;
  for (size_t i = 0; i < size; ++i) {
    v.push_back(X(i));
  }

  // в начало
  v.insert(v.begin(), X(size + 1));
  ASSERT_EQ(v.size(), size + 1);
  ASSERT_EQ(v.begin()->GetX(), size + 1);
  // в конец
  v.insert(v.end(), X(size + 2));
  ASSERT_EQ(v.size(), size + 2);
  ASSERT_EQ((v.end() - 1)->GetX(), size + 2);
  // в середину
  v.insert(v.begin() + 3, X(size + 3));
  ASSERT_EQ(v.size(), size + 3);
  ASSERT_EQ((v.begin() + 3)->GetX(), size + 3);
}

TEST(DummyVectorTest, 1erasenoncopy) {
  const size_t size = 3;

  bmstu::dummy_vector<X> v;
  for (size_t i = 0; i < size; ++i) {
    v.push_back(X(i));
  }

  auto it = v.erase(v.begin());
  assert(it->GetX() == 1);
}

TEST(DummyVectorTest, 1test_new_push) {
  bmstu::dummy_vector<int> v;
  ASSERT_EQ(v.capacity(), 0);
  ASSERT_EQ(v.size(), 0);
  v.push_back(1);
  ASSERT_EQ(v.capacity(), 1);
  ASSERT_EQ(v.size(), 1);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
}

class WithoutDefaultConstructor {
 public:
  WithoutDefaultConstructor() = delete;

  explicit WithoutDefaultConstructor(int other) : number(other) {
  }

  int number;
};

// TEST(DummyVectorTest, 1Disability) {
//  uint8_t *ptr = new uint8_t[sizeof(WithoutDefaultConstructor) * 10];
//  WithoutDefaultConstructor *wdc = new(ptr) WithoutDefaultConstructor(1);
//  std::cout << ptr << " " << wdc;
//  int b = 5;
// }
