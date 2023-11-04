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
    iterator(pointer ptr) : m_ptr(ptr) {/*code*/ }
    reference operator*() const {/*code*/ }
    pointer operator->() {/*code*/ }
    iterator &operator++() {/*code*/ }
    iterator &operator--() {/*code*/ }
    iterator &operator=(const iterator &other) {/*code*/ }
    iterator operator++(int) {/*code*/ }
    iterator operator--(int) {/*code*/ }
    friend bool operator==(const iterator &a, const iterator &b) {/*code*/ }
    friend bool operator!=(const iterator &a, const iterator &b) {/*code*/ }
    friend ptrdiff_t operator-(const iterator &a, const iterator &b) {/*code*/ }
    iterator &operator+(size_t n) noexcept {/*code*/ }
    iterator &operator-(size_t n) noexcept {/*code*/ }
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
  iterator insert(const_iterator pos,
  3
  const Type &value
  ) {/*code*/ }
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
