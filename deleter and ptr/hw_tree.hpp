// Copyright 2024 <fleurs>

#pragma once

#include <utility>

namespace bmstu {
template<typename T>
class dummy_ptr {
 private:
  T *ptr_;
 public:
  explicit dummy_ptr(T *ptr) : ptr_(ptr) { }

  dummy_ptr(const dummy_ptr &) = delete;

  dummy_ptr &operator=(const dummy_ptr &) = delete;

  dummy_ptr(dummy_ptr &&dying) noexcept {
    ptr_ = std::exchange(dying.ptr_, nullptr);
  }

  dummy_ptr &operator=(dummy_ptr &&dying) noexcept {
    if (this != &dying) {
      delete ptr_;
      ptr_ = std::exchange(dying.ptr_, nullptr);
    }
    return *this;
  }

  ~dummy_ptr() {
    delete ptr_;
  }

  T *operator->() const {
    return ptr_;
  }

  T &operator*() const {
    return *ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  T *get() const {
    return ptr_;
  }

  void reset(T *ptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void swap(dummy_ptr &other) {
    std::swap(ptr_, other.ptr_);
  }

  T *release() {
    return std::exchange(ptr_, nullptr);
  }

  void reset() {
    delete ptr_;
    ptr_ = nullptr;
  }

  bool operator==(const dummy_ptr &other) const {
    return ptr_ == other.ptr_;
  }

  bool operator!=(const dummy_ptr &other) const {
    return ptr_ != other.ptr_;
  }

  bool operator==(const std::nullptr_t) const {
    return ptr_ == nullptr;
  }

  bool operator!=(const std::nullptr_t) const {
    return ptr_ != nullptr;
  }
};

template<typename T>
struct default_delete {
  default_delete() = default;

  default_delete(const default_delete &) = default;

  template<class U>
  default_delete(const default_delete<U> &) {

  }

  void operator[]

  void operator()(T *ptr) const {
    delete ptr;
  }
};

struct non_default_delete {

};


// функтор
template<typename T, typename Deleter = default_delete<T>>
class unique_ptr {
 public:
  unique_ptr() = default;

  explicit unique_ptr(T *ptr) : ptr_(ptr) { }

  unique_ptr(T *ptr, const Deleter &deleter) : ptr_(ptr), deleter_(deleter) { }

  template<class O, class D>
  explicit unique_ptr(unique_ptr<O, D> &&other) noexcept
      : ptr_(other.release()), deleter_(std::forward<D>(other.deleter_)) { }

  ~unique_ptr() {
    deleter_(ptr_);
  }

  unique_ptr(const unique_ptr &) = delete;

  unique_ptr(unique_ptr &&other) noexcept: ptr_(other.release()), deleter_(other.getDeleter()) {

  }

  unique_ptr &operator=(unique_ptr &&other) noexcept {
    unique_ptr(std::move(other)).swap(*this);
    return *this;
  }


  void reset(T *ptr) noexcept {
    deleter_(ptr_);
    ptr_ = ptr;
  }

  T *release() noexcept {
    auto old_ptr = ptr_;
    ptr_ = nullptr;
    return old_ptr;
  }

  void swap(unique_ptr &other) noexcept {
    std::swap(ptr_, other.ptr_);
  }

  T *operator->() const {
    return ptr_;
  }

  T &operator*() const {
    return *ptr_;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

 private:
  T *ptr_;
  // подменяя делитер вся логика меняется
  Deleter deleter_ = Deleter();
 public:
  T *getPtr() const {
    return ptr_;
  }

  Deleter getDeleter() const {
    return deleter_;
  }
};
}