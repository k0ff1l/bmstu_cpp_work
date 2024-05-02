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
  tree.insert(30);
  tree.insert(20);
  tree.insert(45);
  tree.insert(10);
  tree.insert(25);
  tree.insert(40);
  tree.insert(50);
  tree.draw(std::cout);
  tree.remove(45);
  tree.draw(std::cout);

}