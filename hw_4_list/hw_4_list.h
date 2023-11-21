// Copyright 2023 <fleurs>

#pragma once

#include <iostream>

namespace bmstu {
template<typename T>
class list {
  struct node { };
 public:
  template<typename value_t>
  struct list_iterator { /*Сами разбираемся какая сигнатура у итератора*/ };
  using value_type = T;
  using reference = value_type &;
  using const_reference =
      const value_type &;
  using iterator = list_iterator<T>;
  using const_iterator = list_iterator<const T>;
  list() : size_(0), tail_(new node()), head_(new node()) { }
  template<typename it>
  list(it begin, it end) { }
  list(std::initializer_list<T> values) { }
  list(const list &other) { }
  list(list &&other) { }
  template<typename Type>
  void push_back(const Type &value) { }
  template<typename Type>
  void push_front(const Type &value) { }
  bool empty() const noexcept { }
  ~list() { }
  void clear() { }
  size_t size() const { }
  void swap(list &other) noexcept { }
  friend void swap(list &l, list &r) { }
  iterator begin() noexcept { }
  iterator end() noexcept { }
  const_iterator begin() const noexcept { }
  const_iterator end() const noexcept { }
  const_iterator cbegin() const noexcept { }
  const_iterator cend() const noexcept { }
  T operator[](size_t pos) const { }
  T &operator[](size_t pos) { }
  friend bool operator==(const list &l, const list &r) { }
  friend bool operator!=(const list &l, const list &r) { }
  friend bool operator<(const list &l, const list &r) { }
  friend bool operator>(const list &l, const list &r) { }
  friend bool operator<=(const list &l, const list &r) { }
  friend bool operator>=(const list &l, const list &r) { }
  friend std::ostream &operator<<(std::ostream &os, const list &other) { }
  iterator insert(const_iterator pos, const T &value) { }

 private:
  static bool lexicographical_compare_(const list<T> &l, const list<T> &r) { }
  size_t size_ = 0;
  node *tail_ = nullptr;
  node *head_ = nullptr;
};
}  // namespace bmstu
