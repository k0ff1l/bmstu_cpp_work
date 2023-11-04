//
// Created by fleurs on 30.10.23.
//

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>

#include "hw_3_vector.h"

TEST(TestName_Other, Foo3) {
  using namespace bmstu;
  vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
}

TEST(TestName_Other, PushBack) {
  using namespace bmstu;
  vector<int> a;
  ASSERT_EQ(a.capacity(), 0);
  ASSERT_EQ(a.size(), 0);
  a.push_back(6);
  ASSERT_EQ(a.size(),1);
  ASSERT_EQ(a.capacity(),1);
  a.push_back(6);
  ASSERT_EQ(a.size(),2);
  ASSERT_EQ(a.capacity(),2);
  a.push_back(6);
  ASSERT_EQ(a.size(),3);
  ASSERT_EQ(a.capacity(),4);
  a.push_back(6);
  ASSERT_EQ(a.size(),4);
  ASSERT_EQ(a.capacity(),4);
  a.push_back(6);
  ASSERT_EQ(a.size(),5);
  ASSERT_EQ(a.capacity(),8);
  std::cout << a << std::endl;
}

TEST(Vector, insert){
  bmstu::vector<int> v;
  bmstu::vector<int> v_expected{0, 666, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (int i = 0; i < 10; ++i){
    v.push_back(i);
  }
//  std::cout << v << std::endl;
  v.insert(v.begin()+1, 666);
//  std::cout << v << std::endl;

  ASSERT_EQ(v, v_expected);
}

//TEST(Vector, Erase){
//  bmstu::vector<int> v{1,2,3,4,5,6,7,8,9};
//  bmstu::vector<int>::iterator v_it = v.begin() + 3; // число 4, 3-ий элемент
//  v.erase(v_it);
//  std::cout << v << std::endl;
//}

TEST(Vector, lexical){ // лексикографическое сравнение по циферкам чарикам начиная с первого
  bmstu::vector<char> v{'1','2','3'};
  bmstu::vector<char> v_c{'1','2','3'};
  std::cout << v << std::endl;
  ASSERT_TRUE(v <= v_c);
}

