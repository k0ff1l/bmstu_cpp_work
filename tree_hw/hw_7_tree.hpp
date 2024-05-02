// Copyright 2024 <konstantin filippov>

#pragma once

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <math.h>

namespace bmstu {
template<typename T>
class search_tree {
  struct TreeNode;
  using uptr_tn = std::unique_ptr<TreeNode>;
 public:
  search_tree() : root_(nullptr), size_(0) { }

  void insert(T value) {
    this->insert(value, this->root_);
  }

  bool contains(T value) {
    return this->contains_(value, this->root_);
  }

  void remove(T value) {
    this->remove(value, this->root_);
  }

  size_t size() const {
    return size_;
  }

  size_t height() {
    return height_(this->root_);
  }

  void print() const {
    this->print_tree_(this->root_, 0);
  };

  void draw() {
    int h = height();
    std::vector<std::string> output(h), links_above(h);
    draw_node_(output, links_above, this->root_, 0, 0, ' ');
    for (int i = 0; i < h; ++i) {
      if (i) {
        std::cout << links_above[i] << '\n';
      }
      std::cout << output[i] << '\n';
    }
    std::cout << std::endl;
  }

 private:
  struct TreeNode {
    TreeNode(T key) : data(key), left(nullptr), right(nullptr), height(1) { };
    T data;
    uint8_t height;
    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;
  };

  void print_tree_(const std::unique_ptr<TreeNode> &node, int space) const {
    if (node == nullptr)
      return;
    space += size_;
    this->print_tree_(node->right, space);
    for (auto i = size_; i < space; ++i)
      std::cout << " ";
    std::cout << node->data << "\n";
    print_tree_(node->left, space);
  }

  bool contains_(T value, std::unique_ptr<TreeNode> &node) {
    if (node == nullptr) {
      return false;
    } else if (node->data == value) {
      return true;
    } else if (value < node->data) {
      return contains(value, node->left);
    } else {
      return contains(value, node->right);
    }
  }

  uint8_t height_(uptr_tn &node) {
    if (!node) return 0;
    // konstantin filippov code
    return 1 + std::max(height_(node->left), height_(node->right));
  }

  void draw_node_(std::vector<std::string> &acc,
                 std::vector<std::string> &links_above,
                 uptr_tn &node,
                 int level,
                 int p,
                 char link_char) {
    p = std::max(p, 0);
    if (!node) return;
    if (node->left) {
      draw_node_(acc, links_above, node->left, level + 1, p - std::to_string(node->left->data).size() - 2, '/');
    }
    int space = p - acc[level].size();
    if (space > 0) acc[level] += std::string(space, ' ');
    acc[level] += ' ' + std::to_string(node->data) + ' ';
    if (link_char == '/') p = acc[level].size();
    space = p - links_above[level].size();
    if (space > 0) links_above[level] += std::string(space, ' ');
    links_above[level] += link_char;
    p = acc[level].size();
    draw_node_(acc, links_above, node->right, level + 1, p, '\\');
  }

  std::unique_ptr<TreeNode> &insert(T value, std::unique_ptr<TreeNode> &node) {
    if (node == nullptr) {
      node = std::make_unique<TreeNode>(value);
      ++size_;
      return node;
    }

    if (value < node->data) {
      this->insert(value, node->left);
    } else if (value > node->data) {
      this->insert(value, node->right);
    } else {
      return node;
    }
    return node;
  };
  uptr_tn root_;
  size_t size_;
};
}