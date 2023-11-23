// Copyright 2023 <fleurs>

#pragma once

#include <iostream>
#include <iterator>

namespace bmstu {
template<typename T>
class list {
  // Объявление чтобы итератор видел
  struct node;

 public:
  list() : size_(0), head_(new node), tail_(new node) {
    head_->next_node_ = tail_;
    tail_->prev_node_ = head_;
  }
  struct iterator;
  using const_iterator = const iterator;
  template<typename value_t>
  struct iterator {
    friend class list;
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = value_t;
    using difference_type = ptrdiff_t;
    using pointer = value_t *;
    using reference = value_t &;

    iterator() = default;

    explicit iterator(node *node) : node_(node) { }

    explicit iterator(const iterator<T> &other) : node_(other.node_) { }

    reference operator*() const {
      assert(node_ != nullptr);
      return static_cast<T>(node_->value);
    }

    pointer operator->() const {
      assert(node_ != nullptr);
      return static_cast<T *>(node_->value);
    }

    // prefix

    iterator &operator++() {
      assert(node_ != nullptr);
      node_ = node_->next_node_;
      return *this;
    }
    iterator &operator--() {
      assert(node_ != nullptr);
      node_ = node_->prev_node_;
      return *this;
    }

    // postfix

    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }

    template<typename Integer>
    iterator operator+(Integer n) const {
      iterator copy(*this);
      for (auto i = 1; i <= n; ++i) {
        ++(copy);
      }
      return copy;
    }
    iterator operator-(const difference_type n) const {
      iterator copy(*this);
      for (auto i = 1; i <= n; ++i) {
        --(copy);
      }
      return copy;
    }

    friend difference_type operator-(const iterator &end,
                                     const iterator &begin) {
      difference_type count = 0;
      iterator copy(begin);
      for (count = 0; copy != end; ++copy, ++count) {
      }
      return count;
    }

    iterator &operator=(const iterator &other) = default;

    friend bool operator==(const iterator<T> &l, const iterator<T> &r) {
      return l.node_ == r.node_;
    }

    bool operator==(const iterator<const T> &other) const {
      return node_ == other.node_;
    }

    explicit operator bool() {
      return node_ != nullptr;
    }

    bool operator!=(const iterator &other) const {
      return !(*this == other);
    }

    iterator begin() {
      return iterator(head_->next_node_);
    }
    iterator end() {
      return iterator(tail_);
    }

   private:
    list::node *node_ = nullptr;
  };
  list(std::initializer_list<T> list) {
  }

  template<typename It>
  list(It begin, It end) {
    for (auto it = begin; it != end; ++it) {
      push_back(*it);
    }
  }

  list(list &&other) {
    swap(other);
  }

  ~list() {  // нужен фикс, чтобы в итоге и head, и tail удалялся.
    // ибо конструктор - 5 раз, а деструктор - 3. утечка памяти
    clear_();
    delete head_;
    delete tail_;
  }

  template<typename Type>
  void push_back(const Type &value) {
    node *last = tail_->prev_node_;
    node *new_last = new node(tail_->prev_node_, value, tail_);
    last->next_node_ = new_last;
    tail_->prev_node_ = new_last;
    ++size_;
  }

  template<typename Type>
  void push_front(const Type &value) {
    node *first = head_->next_node_;
    node *new_first = new node(head_, value, head_->next_node_);
    first->prev_node_ = new_first;
    head_->next_node_ = new_first;
    ++size_;
  }

  iterator insert(iterator pos, const T &value) {
    node *new_node = new node(pos.node_, value, pos.node_->next_node_);
  }

  template<typename OS>
  friend std::basic_ostream<OS>() { }

  T operator[](size_t pos) const {
    return *(begin() + pos);
  }

  T &operator[](size_t pos) {
    return *(begin() + pos);
  }

  size_t GetSize() const {
    return size_;
  }
  bool empty() {
    return size_ == 0;
  }

 private:
  void clear_() {
    if (!empty()) {
      while (head_->next_node_ != tail_) {
        node *tmp = head_->next_node_;
        head_->next_node_ = tmp->next_node_;
        delete tmp;
      }
      size_ = 0;
    }
  }
  struct node {
    node() = default;
    node(node *prev, const T &value, node *next)
        : value(value), prev_node_(prev), next_node_(next) {
    }
    T value;
    node *next_node_ = nullptr;
    node *prev_node_ = nullptr;
  };
  size_t size_ = 0;
  node *head_ = nullptr;
  node *tail_ = nullptr;
};
}  // namespace bmstu
