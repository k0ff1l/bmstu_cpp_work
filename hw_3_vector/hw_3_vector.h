//
// Created by fleurs on 30.10.23.
//

#pragma once

#include <iterator>

#include "hw_3_array_bundle.h"

namespace bmstu {
template<typename Type>
class vector {
 public:
  struct iterator {
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = Type;
    using pointer = Type *;
    using reference = Type &;
    explicit iterator(pointer ptr) : m_ptr(ptr) {}
    reference operator*() const {
      return *m_ptr;
    }
    pointer operator->() {
      return m_ptr;
    }
    iterator &operator++() {
      ++m_ptr;
      return *this;
    }
    iterator &operator--() {
      --m_ptr;
      return *this;
    }
    iterator &operator=(const iterator &other) {
      m_ptr = other.m_ptr;
      return *this;
    }
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
    friend bool operator==(const iterator &a, const iterator &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const iterator &a, const iterator &b) {
      return !(a == b);
    }
    friend difference_type operator-(const iterator &end, const iterator &begin) {
      difference_type result = end.m_ptr - begin.m_ptr;
      return result;
    }
    iterator &operator+(size_t n) noexcept {
      return (this+n);
    }
    iterator &operator-(size_t n) noexcept {
      return (this-n);
    }
   private:
    pointer m_ptr;
  };
  using const_iterator = const iterator;
  vector() noexcept = default;
  vector(size_t size, const Type &value = Type{}) {/*code*/ }
  vector(const vector<Type> &other) {/*code*/ }
  vector(vector<Type> &&other) {/*code*/ }
  vector(std::initializer_list<Type> ilist) {/*code*/ }
  void clear() noexcept {}
  vector &operator=(const vector<Type> &other) {/*code*/ }
  vector &operator=(vector<Type> &&other) {/*code*/ }
  iterator begin() noexcept {/*code*/ }
  iterator end() noexcept {/*code*/ }
  const_iterator begin() const noexcept {/*code*/ }
  const_iterator end() const noexcept {/*code*/ }
  const_iterator cbegin() const noexcept {/*code*/ }
  const_iterator cend() const noexcept {/*code*/ }
  typename iterator::reference operator[](size_t index) noexcept {/*code*/ }
  typename const_iterator::reference operator[](size_t index) const noexcept {/*code*/ }
  typename iterator::reference at(size_t index) {/*code*/ }
  typename const_iterator::reference at(size_t index) const {/*code*/ }
  size_t size() const noexcept {/*code*/ }
  size_t capacity() const noexcept {/*code*/ }
  bool empty() const noexcept {/*code*/ }
  void swap(vector &other) noexcept {/*code*/ }
  friend void swap(vector<Type> &lhs, vector<Type> &rhs) {/*code*/ }
  void resize(size_t new_size) {/*code*/ }
  void reserve(size_t new_capacity) {/*code*/ }
  iterator insert(const_iterator pos, Type &&value) {/*code*/ }
  iterator insert(const_iterator pos, const Type &value) {/*code*/ }
  void push_back(const Type &value) {/*code*/ }
  void push_back(Type &&value) {/*code*/ }
  void pop_back() noexcept {/*code*/ }
  friend bool operator==(const vector<Type> &l, const vector<Type> &r) {/*code*/ }
  friend bool operator!=(const vector<Type> &l, const vector<Type> &r) {/*code*/ }
  friend bool operator<(const vector<Type> &l, const vector<Type> &r) {/*code*/ }
  friend bool operator>(const vector<Type> &l, const vector<Type> &r) {/*code*/ }
  friend bool operator<=(const vector<Type> &l, const vector<Type> &r) {/*code*/ }
  friend bool operator>=(const vector<Type> &l, const vector<Type> &r) {/*code*/ }
  friend std::ostream &operator<<(std::ostream &os, const vector<Type> &other) {/*code*/ }
 private:
  static bool lexicographical_compare_(const vector<Type> &l, const vector<Type> &r) {}
  size_t size_ = 0;
  size_t capacity_ = 0;
  array_bundle<Type> data_;
};
}  // namespace bmstu
