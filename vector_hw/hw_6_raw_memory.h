// Copyright 2024 <fleurs>

#pragma once

#include <memory>
#include <utility>

namespace bmstu {
template<typename Z>
class raw_memory {
 public:  // NOLINT
  raw_memory() = default;

  explicit raw_memory(size_t size) : buffer_(allocate_(size)), capacity_(size) {
  }

  ~raw_memory() {
    deallocate_(buffer_);
    capacity_ = 0;
  }

  raw_memory(const raw_memory &other) = delete;

  // мы не хотим копировать указатель на память одну и ту же, вдруг один удалится указатель, а второй - нет, будет UB.

  raw_memory &operator=(const raw_memory &other) = delete;

  raw_memory(const raw_memory &&other) noexcept: capacity_(
      std::exchange(const_cast<size_t &>(other.capacity_), 0)),
                                                 buffer_(
                                                     std::exchange(
                                                         const_cast<Z *&>(other.buffer_),
                                                         nullptr)) {
  }

  raw_memory &operator=(raw_memory &&other) {
    if (this != &other) {
      deallocate_(buffer_);
      buffer_ = std::exchange(other.buffer_, nullptr);
      // buffer = other.buffer_, other.buffer_ = nullptr
      capacity_ = std::exchange(other.capacity_, 0);
    }
    return *this;
  }

  Z &operator[](size_t index) noexcept {
    assert(index < capacity_);
    return buffer_[index];
  }

  const Z &operator[](size_t index) const noexcept {
    return const_cast<raw_memory &>(*this)[index];
    // todo: возможно нужен raw_memory&
  }

  Z *operator+(size_t offset) noexcept {
    assert(offset <= capacity_);  // = потому что мы хотим еще и end хранить,
    return buffer_ + offset;
  }

  const Z *operator+(size_t offset) const noexcept {
    return const_cast<raw_memory &>(*this) + offset;
  }

  [[nodiscard]] size_t capacity() const {
    return capacity_;
  }

  Z *buffer() {
    return buffer_;
  }

  const Z *buffer() const {
    return buffer_;
  }

  void swap(raw_memory other) noexcept {
    std::swap(buffer_, other.buffer_);
    std::swap(capacity_, other.capacity_);
  }  // todo: возможно в прайват надо
 private: // NOLINT
  // нужны методы, которые аллоцируют и деаллоцируют сырую память.
  static Z *allocate_(size_t size) {
    return size != 0
           ? static_cast<Z *>(operator new(size * sizeof(Z)))
           : nullptr;
  }

  static void deallocate_(Z *ptr) {
    operator delete(ptr);
  }

  Z *buffer_ = nullptr;
  size_t capacity_ = 0;
};
} // namespace bmstu // NOLINT
