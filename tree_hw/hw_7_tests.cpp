// Copyright 2024 <konstantin filippov>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_7_tree.hpp"

TEST(TreeTest, Test1) {
  bmstu::search_tree<int> tree;
  tree.insert(1);
  tree.insert(2);
  tree.insert(3);
  tree.insert(-1);
  tree.insert(-3);

  tree.draw();
}