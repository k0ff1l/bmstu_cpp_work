// Copyright 2024 <konstantin filippov>

#pragma once

#include "hw_7_tree.hpp"

namespace bmstu {
template <typename T>
class set {
 public:
  using TreeNode = bmstu::search_tree<T>::TreeNode;
  set() { data = new bmstu::search_tree<T>(); }
  ~set() { delete data; }
  void insert(T value) { data->insert(value); }
  void erase(T value) { data->remove(value); }
  size_t size() { return data->size(); }
  void clear() {
    delete data;
    data = new bmstu::search_tree<T>();
  }
  void print() { data->inorderTraversal(std::cout); }
  bool empty() { return data->size() == 0; }
  TreeNode* find(T value) { return data->find(value); }

 private:
  bmstu::search_tree<T>* data;
};
}  // namespace bmstu
