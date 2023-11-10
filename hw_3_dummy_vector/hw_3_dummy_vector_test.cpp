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

// TEST(dummy_vector, Erase){
//  bmstu::dummy_vector<int> v{1,2,3,4,5,6,7,8,9};
//  bmstu::dummy_vector<int>::iterator v_it = v.begin() + 3; // число 4, 3-ий элемент
//  v.erase(v_it);
//  std::cout << v << std::endl;
//}

TEST(dummy_vector, lexical) {
  bmstu::dummy_vector<char> v{'1', '2', '3'};
  bmstu::dummy_vector<char> v_c{'1', '2', '3'};
  std::cout << v << std::endl;
  ASSERT_TRUE(v <= v_c);
}

