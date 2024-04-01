// Copyright 2024 <fleurs>

#pragma once

#include <cassert>
#include <memory>
#include "hw_6_raw_memory.h"

namespace bmstu {
template<typename T>
class vector {
 public:  // NOLINT
  vector() = default;

  //  Yavnoe construirovanie
  explicit vector(size_t size) : data_(size), size_(size) {
    if constexpr (std::is_default_constructible_v<T>) {  // охиреть, без констэкспр валится.
      std::uninitialized_value_construct_n(data_.buffer(), size_);
    }
  }

  vector(const vector &other) : data_(other.size_), size_(other.size_) {
    std::uninitialized_copy_n(other.data_.buffer(), other.size_, this->data_.buffer());
  }

  vector(vector &&dying) noexcept: data_(std::move(dying.data_)), size_(std::move(dying.size_)) {
    dying.size_ = 0;
  }

  vector(std::initializer_list<T> init_list) : data_(init_list.size()), size_(init_list.size()) {
    std::uninitialized_copy(init_list.begin(), init_list.end(), data_.buffer());
  }

  vector &operator=(const vector &other) {
    if (&other != this) {
      if (other.size_ > data_.capacity()) {
        vector copy(other);  // copy and swap idiom
        this->swap_(copy);
      } else {
        if (size_ >= other.size_) {
          std::copy_n(other.data_.buffer(), other.size_, data_.buffer());
          std::destroy_n(data_.buffer() + other.size_, size_ - other.size_);
          size_ = other.size_;
        } else {
          std::copy_n(other.data_.buffer(), other.size_, data_.buffer());
          // construct_value_n ?
          std::uninitialized_copy_n(other.data_.buffer() + size_, other.size_ - size_, data_.buffer() + size_);
        }
      }
    }

    return *this;
  }

  vector &operator=(vector &&right) noexcept {
    if (this != &right) {
      data_ = std::move(right.data_);
      size_ = right.size_;
      right.size_ = 0;
    }
    return *this;
  }

  ~vector() {
    std::destroy_n(data_.buffer(), size_);
  }

  struct iterator {
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    explicit iterator(pointer ptr) : m_ptr(ptr) {
    }

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

    friend bool operator==(const iterator &a,
                           const std::nullptr_t &b) {  // П@РНУXА
      return a.m_ptr == b;
    }

    friend bool operator!=(const iterator &a, const iterator &b) {
      return !(a == b);
    }

    friend difference_type operator-(const iterator &end,
                                     const iterator &begin) {
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

   private:  // NOLINT
    pointer m_ptr;
  };

  using const_iterator = const iterator;

  iterator begin() { return iterator(data_.buffer()); }

  iterator end() { return iterator(data_.buffer() + size_); }

  const_iterator begin() const {
    return const_iterator(data_.buffer());
  }

  const_iterator end() const {
    return const_iterator(data_.buffer() + size_);
  }

  const_iterator cbegin() const {
    return const_iterator(data_.buffer());
  }

  const_iterator cend() const {
    return const_iterator(const_cast<T *>(data_.buffer() + size_));
  }

  friend void swap(vector<T> &left, vector<T> &right) {
    left.swap_(right);
  }

  [[nodiscard]] size_t size() const {
    return size_;
  }

  void pop_back() noexcept {
    assert(size_ != 0);
    std::destroy_at(data_.buffer() + --size_);
  }

  T &operator[](size_t index) noexcept {
    return data_[index];
  }

  const T &operator[](size_t index) const noexcept {
    return const_cast<vector<T> &>(*this)[index];
  }

  bool operator==(const vector<T> &other) const {
    if (size_ != other.size_) {
      return false;
    }
    for (size_t i = 0; i < size_; ++i) {
      if (data_[i] != other.data_[i]) {
        return false;
      }
    }
    return true;
  }

  // write operator for console output
  friend std::ostream &operator<<(std::ostream &out, const vector<T> &vec) {
    out << "[";
    for (size_t i = 0; i < vec.size_; ++i) {
      out << vec.data_[i];
      if (i != vec.size_ - 1) {
        out << ", ";
      }
    }
    out << "]";
    return out;
  }

  T &at(size_t index) {
    if (index >= size_) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  const T &at(size_t index) const {
    return const_cast<vector<T> &>(*this).at(index);
  }

  // todo: fix, as x2 capacity, not new_capacity, or only fix resize, check it
  // in std::vec (reserve 7 == 7, resize 7 == 12 (if from capacity 6)).
  void reserve(size_t new_capacity) {
    if (new_capacity <= data_.capacity()) {
      return;
    } else {
      size_t new_size = (new_capacity > 2 * data_.capacity()) ? new_capacity : 2 * data_.capacity();
      raw_memory<T> new_data(new_size);
      if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
        std::uninitialized_move_n(data_.buffer(), size_, new_data.buffer());
      } else {
        std::uninitialized_copy_n(data_.buffer(), size_, new_data.buffer());
      }
      std::destroy_n(data_.buffer(), size_);
      data_.swap(std::move(new_data));
    }
  }

  size_t capacity() {
    return data_.capacity();
  }

  void resize(size_t new_size) {
    if (new_size < size_) {
      std::destroy_n(data_.buffer() + new_size, size_ - new_size);
      size_ = new_size;
    } else {
      if (new_size > data_.capacity()) {
        reserve(new_size);
      }
      if constexpr (std::is_default_constructible_v<T>) {
        std::uninitialized_value_construct_n(data_.buffer() + size_, new_size);
      }
      size_ = new_size;
    }
  }

  template<typename... Args>
  T &emplace_back(Args &&... args) {
    if (size_ == data_.capacity()) {
      auto new_capacity = (size_ == 0) ? 1 : size_ * 2;
      this->reserve(new_capacity);
    }
    new(data_.buffer() + size_)T(std::forward<Args>(args)...);
    ++size_;
    return data_[size_ - 1];
  }

  template<typename... Args>
  iterator emplace(const_iterator pos, Args &&... args) {
    iterator res_pos = begin();
    if (pos == cend()) {
      push_back(std::forward<Args>(args)...);
      res_pos = end() - 1;
    } else if (size_ == data_.capacity()) {
      auto new_capacity = (size_ == 0) ? 1 : size_ * 2;
      raw_memory<T> new_data(new_capacity);
      const size_t dest_pos = pos - begin();
      new(new_data.buffer() + dest_pos)T(std::forward<Args>(args)...);
      if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
        std::uninitialized_move_n(data_.buffer(), dest_pos, new_data.buffer());
      } else {
        try {
          std::uninitialized_copy_n(data_.buffer(), dest_pos, new_data.buffer());
        } catch (...) {
          std::destroy_n(new_data.buffer() + dest_pos, 1);
          throw;
        }
      }
      if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
        std::uninitialized_move_n(data_.buffer() + dest_pos, size_ - dest_pos, new_data.buffer() + dest_pos + 1);
      } else {
        try {
          std::uninitialized_copy_n(data_.buffer() + dest_pos, size_ - dest_pos, new_data.buffer() + dest_pos + 1);
        } catch (...) {
          std::destroy_n(new_data.buffer() + dest_pos, 1);
          throw;
        }
      }
      std::destroy_n(data_.buffer(), size_);
      data_.swap(std::move(new_data));
      res_pos = begin() + dest_pos;
      ++size_;
    } else {
      T tmp(std::forward<Args>(args)...);
      new(data_.buffer() + size_) T(std::move(data_[size_ - 1]));
      res_pos = begin() + (pos - begin());
      std::move_backward(res_pos, end() - 1, end());
      *res_pos = std::move(tmp);
      ++size_;
    }
    return res_pos;
  }

  template<typename Type>
  void push_back(Type &&value) {
    emplace_back(std::forward<Type>(value));
  }

  template<typename Type>
  void insert(const_iterator pos, Type &&value) {
    emplace(pos, std::forward<Type>(value));
  }

  bool empty() {
    return size_ == 0;
  }

  void swap(vector<T> &other) {
    swap_(other);
  }

  void clear() {
    std::destroy_n(data_.buffer(), size_);
    size_ = 0;
  }

 private:  // NOLINT
  void swap_(vector<T> &other) {  // NOLINT
    std::swap(*this, other);
  }

  raw_memory<T> data_;
  size_t size_ = 0;
};
}  // namespace bmstu
