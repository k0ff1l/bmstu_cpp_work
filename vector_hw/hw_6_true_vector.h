// Copyright 2024 <fleurs>

#pragma once

#include <cassert>
#include <memory>
#include "hw_6_raw_memory.h"

namespace bmstu {
template<typename T>
class vector {
  public:
    vector() = default;

    //  Yavnoe construirovanie
    explicit vector(size_t size) : data_(size), size_(size) {
      std::uninitialized_value_construct_n(data_.buffer(), size_);
    }

    vector(const vector& other) : data_(other.data_), size_(other.size_) {
      std::uninitialized_copy_n(other.data_.buffer_(), other.size_, data_.buffer_());
    }

    vector(vector&& dying) noexcept : data_(std::move(dying.data_)), size_(std::move(dying.size_)) {
      dying.size_ = 0;
    }

    vector& operator=(const vector& other) {
      if (&other != this) {
        if (other.size_ > data_.capacity()) {
          vector copy(other);  // copy and swap idiom
          swap_(copy);
        } else {
          if (!(size_ < other.size_)) {
            std::copy_n(other.data_.buffer(), other.size_, data_.buffer());
            std::destroy_n(data_.buffer() + other.size_, size_ - other.size_);
            size = other.size_;
          } else {
            std::copy_n(other.data_.buffer(), other.size_, data_.buffer());
            // construct_value_n ?
            std::uninitialized_copy_n(other.data_.buffer_ + size_, other.size_ - size_, data_.buffer_ + size_);
          }
        }
      }

      return *this;
    }

    vector& operator=(vector&& right) noexcept {
      if (this != &right) {
        data_ = std::move(right.data_);
        size_ = right.size_;
        right.size_ = 0;
      }
      return *this;
    }

    ~vector() {
      std::destroy_n(data_.buffer_, size_);
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
      iterator& operator++() {
        ++m_ptr;
        return *this;
      }
      iterator& operator--() {
        --m_ptr;
        return *this;
      }
      iterator& operator=(const iterator& other) {
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
      friend bool operator==(const iterator& a, const iterator& b) {
        return a.m_ptr == b.m_ptr;
      }
      friend bool operator==(const iterator& a,
                             const std::nullptr_t& b) {  // П@РНУXА
        return a.m_ptr == b;
      }
      friend bool operator!=(const iterator& a, const iterator& b) {
        return !(a == b);
      }
      friend difference_type operator-(const iterator& end,
                                       const iterator& begin) {
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

    iterator begin() { return data_.buffer(); }

    iterator end() { return data_.buffer() + size_; }

    const_iterator begin() const {
      return data_.buffer();
    }

    const_iterator end() const {
      return data_.buffer() + size_;
    }

    const_iterator cbegin() const {
      return data_.buffer();
    }

    const_iterator cend() const {
      return data_.buffer() + size_;
    }

    friend void swap(vector<T>& left, vector<T>& right) {
      std::swap(left.data_, right.data_);
      std::swap(left.size_, right.size_);
    }

    [[nodiscard]] size_t size() const {
      return size_;
    }

    void pop_back() noexcept {
      assert(size_ != 0);
      std::destroy_at(data_.buffer() + --size_);
    }

    T& operator[](size_t index) noexcept {
      return data_[index];
    }

    const T& operator[](size_t index) const noexcept {
      return const_cast<vector<T> &>(*this)[index];
    }

    // todo: fix, as x2 capacity, not new_capacity, or only fix resize, check it
    // in std::vec (reserve 7 == 7, resize 7 == 12 (if from capacity 6)).
    void reserve(size_t new_capacity) {
      if (new_capacity <= data_.capacity) {
        return;
      } else {
        raw_memory<T> new_data(new_capacity);
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
          std::uninitialized_move_n(data_.buffer(), new_data.buffer_);
        } else {
          std::uninitialized_copy_n(data_.buffer(), new_data.buffer_);
        }
        std::destroy_n(data_.buffer, size_);
        data_.swap(new_data);
      }
    }

    void resize(size_t new_size) {
      if (new_size < size_) {
        std::destroy_n(data_.buffer() + new_size, size - new_size);
        size_ = new_size;
      } else {
        if (new_size > data_.capacity()) {
          reserve(new_size);
        }
        std::uninitialized_value_construct_n(data_.buffer_ + size_, new_size);
      }
    }

    template<typename... Args>
    T& emplace_back(Args&&... args) {
      if (size_ == data_.capacity()) {
        auto new_capacity = (size_ == 0) ? 1 : size_ * 2;
        this->reserve(new_capacity);
        new(data_.buffer() + size_)T(std::forward<Args>(args)...);
      } else {
        new(data_.buffer() + size_)T(std::forward<Args>(args)...);
      }
      ++size;
      return data_[size_ - 1];
    }

    template<typename... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
      iterator res_pos = begin();
      if (pos == cend()) {
        res_pos = &emplace_back(std::forward<Args>(args)...);
      } else if (size_ == data_.capacity()) {
        auto new_capacity = (size_ == 0) ? 1 : size * 2;
        raw_memory<T> new_data(new_capacity);
        const size_t dest_pos = pos - begin();
        new(new_data.buffer() + dest_pos)T(std::forward<Args>(args)...);
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
          std::uninitialized_move_n(data_.buffer(), dest_pos, new_data.buffer_);
        } else {
          try {
            std::uninitialized_copy_n(data_.buffer(), dest_pos, new_data.buffer_);
          } catch (...) {
            std::destroy_n(new_data.buffer() + dest_pos, 1);
            throw;
          }
        }
      } else {
        T tmp(std::forward<Args>(args)...);
        new(data_.buffer() + size_) T(std::move(data_[size_ - 1]));
        res_pos = begin() + (pos - begin());
        std::move_backward(res_pos, end() - 1, end());
        *res_pos = std::move(tmp);
        ++size;
      }
      return res_pos;
    }
  private:
    void swap_(vector<T>& other) {
      std::swap(*this, other);
    }
    raw_memory<T> data_;
    size_t size_ = 0;
};
}  // namespace bmstu
