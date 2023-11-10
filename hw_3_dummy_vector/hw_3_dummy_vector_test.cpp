// Copyright 2023 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>

#include "hw_3_dummy_vector.h"

using bmstu::dummy_vector;

TEST(TestName_Other, Foo3) {
  dummy_vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(TestName_Other, PushBack) {
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
  std::cout << a << std::endl;
}

TEST(dummy_vector, insert) {
  bmstu::dummy_vector<int> v;
  bmstu::dummy_vector<int> v_expected{0, 666, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; ++i) {
    v.push_back(i);
  }
//  std::cout << v << std::endl;
  v.insert(v.begin() + 1, 666);
//  std::cout << v << std::endl;

  ASSERT_EQ(v, v_expected);
}

TEST(dummy_vector, lexical) {
  bmstu::dummy_vector<char> v{'1', '2', '3'};
  bmstu::dummy_vector<char> v_c{'1', '2', '3'};
  std::cout << v << std::endl;
  ASSERT_TRUE(v <= v_c);
}

TEST(DummyVectorTest, DefaultConstructor) {
  bmstu::dummy_vector<int> vec_default;
  EXPECT_EQ(vec_default.size(), 0);
  EXPECT_EQ(vec_default.capacity(), 0);
}

TEST(DummyVectorTest, ConstructorWithSizeAndValue) {
  bmstu::dummy_vector<int> vec_with_size(5, 42);
  EXPECT_EQ(vec_with_size.size(), 5);
  EXPECT_EQ(vec_with_size.capacity(), 5);
  for (int value : vec_with_size) {
    EXPECT_EQ(value, 42);
  }
}

TEST(DummyVectorTest, CopyConstructor) {
  bmstu::dummy_vector<int> original(3, 7);
  bmstu::dummy_vector<int> copy(original);
  EXPECT_EQ(original.size(), copy.size());
  EXPECT_EQ(original.capacity(), copy.capacity());
  EXPECT_TRUE(std::equal(original.begin(), original.end(), copy.begin()));
}

TEST(DummyVectorTest, MoveConstructor) {
  bmstu::dummy_vector<int> original(3, 7);
  bmstu::dummy_vector<int> moved(std::move(original));
  EXPECT_EQ(original.size(), 0);
  EXPECT_EQ(original.capacity(), 0);
  EXPECT_EQ(moved.size(), 3);
  EXPECT_EQ(moved.capacity(), 3);
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

TEST(DummyVectorTest, Insert) {
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
  EXPECT_THROW(vec.at(5), std::out_of_range);
}

TEST(DummyVectorTest, PopBack) {
  bmstu::dummy_vector<int> vec = {1, 2, 3};
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
  EXPECT_EQ(vec[2], 2);
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

