// Copyright 2024 <konstantin filippov>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_7_tree.hpp"

TEST(Tree, Test1) {
  bmstu::search_tree<int> tree;
  tree.insert(std::numeric_limits<int>::max());
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(-1);
  tree.insert(-3);
  tree.insert(std::numeric_limits<int>::max() - 1);
  std::stringstream ss;
  tree.draw(std::cout);

  auto s = ss.str();
  int a = 5;
}