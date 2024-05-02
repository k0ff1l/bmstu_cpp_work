// Copyright 2024 <konstantin filippov>

#pragma once

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <math.h>
#include <iostream>


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

  template<typename CharT>
  std::basic_ostream<CharT>& draw(std::basic_ostream<CharT>& os) {
    int h = height();
    std::vector<std::basic_string<CharT>> output(h), links_above(h);
    draw_node_(output, links_above, this->root_, 0, 0, ' ');
    for (int i = 0; i < h; ++i) {
      if (i) {
        os << links_above[i] << '\n';
      }
      os << output[i] << '\n';
    }
    os << std::endl;
    return os;
  }

  template <typename CharT, typename TreeType>
  friend std::basic_ostream<CharT> &operator<<(std::ostream &os, const bmstu::search_tree<CharT> &tree) {
    return tree.draw(os);
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
      // todo: добавить пробелов
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

    // todo: balance me
    return node;
  };

  uptr_tn& find_min(uptr_tn& node) const {
    if (!node) {
      // todo: придумать
      throw "MINT WTF???";
    } else if (!node->left) {
      return node;
    } else {
      return find_min(node->left);
    }
  }

  uptr_tn& find_max(uptr_tn& node) const {
    if (!node) {
      // todo: придумать
      throw "MAX WTF???";
    } else if (!node->right) {
      return node;
    } else {
      return find_max(node->right);
    }
  }

  void remove(T value, uptr_tn &node) {
    if (!node) return;

    if (value == node->data) {
      --size_;
      // нет дочерних узлов
      if (!node->left && !node->right) {
        node = nullptr;
      } else if (node->left && !node->right) {
        node = std::move(node->left);
      } else if (!node->left && node->right) {
        node = std::move(node->right);
      } else {
        // todo: find min and replace node with it,
        // then stick the another one

        // node->data = minNode->Data
        // remove(minNode->Data, minNode)

        uptr_tn minNode = std::move(find_min(node->right));

        node->data = std::move(minNode->data);

        remove(minNode->data, minNode);

      }
    } else if (value < node->data) {
      remove(value, node->left);
    } else {
      remove(value, node->right);
    }
  }
  uptr_tn root_;
  size_t size_;
};

// todo: оператор клювик клювик для вывода basic_ostream
// возможно нужен темплейт темплейт template<typename CharT, template<typename Z> fdsf> как-то так

}