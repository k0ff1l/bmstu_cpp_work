//
// Created by fleurs on 30.10.23.
//

#pragma once

//#include <utility>
//#include <iterator>
#include "hw_3_array_bundle.h"

namespace {
size_t dummy_max(size_t a, size_t b) {
  if (a > b) {
    return a;
  }
  else{
    return b;
  }
}
}  // namespace

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
      if (begin.m_ptr == NULL){
        return 0;
      }
      difference_type result = end.m_ptr - begin.m_ptr;
      return result;
    }
    iterator operator+(const difference_type value) noexcept {
      iterator copy(*this);
      copy.m_ptr += value;
      return copy;
    }
    iterator operator-(const difference_type value) noexcept {
      iterator copy(*this);
      copy.m_ptr -= value;
      return copy;
    }

   private:
    pointer m_ptr;
  };
  using const_iterator = const iterator;
  vector() noexcept = default;
  explicit vector(size_t size, const Type &value = Type{}) : size_(size), capacity_(size), data_(size) {
    auto first = begin();
    auto last = end();
    for (; first != last; ++first) {
      *first = value;
    }
  }
  vector(const vector<Type> &other) : size_(other.size_), capacity_(other.capacity_), data_(other.data_) {
    auto first = begin();
    auto ofirst = other.begin();
    auto olast = other.end();
    for (; ofirst != olast; ++ofirst, ++first) {
      *first = *ofirst;
    }
  }
  vector(vector<Type> &&other) {
    this->swap(other);
  }
  vector(std::initializer_list<Type> ilist) {/*code*/ }
  void clear() noexcept {}
  vector &operator=(const vector<Type> &other) {/*code*/ }
  vector &operator=(vector<Type> &&other) {/*code*/ }
  iterator begin() noexcept {
    return iterator(data_.Get());
  }
  iterator end() noexcept {
    return iterator(data_.Get()+size_);
  }
  iterator begin() const noexcept {
    return iterator(data_.Get());
  }
  iterator end() const noexcept {
    return iterator(data_.Get() + size_);
  }
  const_iterator cbegin() const noexcept {
    return iterator(data_.Get());
  }
  const_iterator cend() const noexcept {
    return iterator(data_.Get() + size_);
  }
  typename iterator::reference operator[](size_t index) noexcept {/*code*/ }
  typename const_iterator::reference operator[](size_t index) const noexcept {/*code*/ }
  typename iterator::reference at(size_t index) {/*code*/ }
  typename const_iterator::reference at(size_t index) const {/*code*/ }
  size_t size() const noexcept {
    return size_;
  }
  size_t capacity() const noexcept {
    return capacity_;
  }
  bool empty() const noexcept {
    return (size_ == 0);
  }
  void swap(vector &other) noexcept {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    data_.swap(other.data_);
  }
  friend void swap(vector<Type> &lhs, vector<Type> &rhs) {
    lhs.swap(rhs);
  }
  void resize(size_t new_size) {
    if (new_size > capacity_) {
      size_t new_capacity = ::dummy_max(new_size, capacity_ * 2);
      reserve(new_capacity);
      for (auto it = --end(); it != begin() + capacity_; ++it) {
        if (begin() == end()){
          break;
        }
        *it = Type{};
      }
      size_ = new_size;
    }
  }
  void reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
      new_capacity = ::dummy_max(new_capacity, capacity_ * 2);
      array_bundle<Type> new_data(new_capacity);
      if (size_ != 0){
        for (auto it = begin(), nit = iterator(new_data.Get()); it != end(); ++it, ++nit) {
          *nit = std::move(*it);
        }
      }
      data_.swap(new_data);
      capacity_ = new_capacity;
    }
  }
  iterator insert(const_iterator pos, Type &&value) {
    if (size_ == 0){
      (*this).resize(1);
      return pos;
    }
    vector<Type> temp(size_+1);
    auto n = pos - begin();
    if (capacity_ - size_ == 0){
      reserve(capacity_ + 1);
    }
    for (auto it = begin(), t_it = temp.begin(); it != begin() + n - 1; ++it, ++t_it){
      *t_it = *it;
    }
    *(temp.begin() + n - 1) = value;
    auto itb = begin() + n;
    auto ite = end();
    for (auto it = begin() + n, t_it = temp.begin() + n; it != end(); ++it, t_it){
      *t_it = *it;
    }
    *this = std::move(temp);
  }
  iterator insert(const_iterator pos, const Type &value) {
    if (size_ == 0){
      (*this).resize(1);
      return pos;
    }
    vector<Type> temp(size_+1);
    auto n = pos - begin();
    if (capacity_ - size_ == 0){
      reserve(capacity_ + 1);
      size_+=1;
    }
    for (auto it = begin(), t_it = temp.begin(); it != begin() + n - 1; ++it, ++t_it){
      *t_it = *it;
    }
    *(temp.begin() + n - 1) = value;
    auto itb = begin() + n;
    auto ite = end();
    for (auto it = begin() + n, t_it = temp.begin() + n; it != end(); ++it, t_it){
      *t_it = *it;
    }
    size_ = temp.size_;
    *this = std::move(temp);
  }
  void push_back(const Type &value) {
    insert(end(),value);
  }
  void push_back(Type &&value) {
    insert(end(),value);
  }
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
