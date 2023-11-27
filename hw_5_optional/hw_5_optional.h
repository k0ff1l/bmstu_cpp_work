// Copyright 2023 <fleurs>

#pragma once

#include <exception>
#include <optional>

namespace bmstu {
class bad_optional_access : public std::exception {
  using exception::exception;

  virtual const char *what() const noexcept {
    return "Bad optional access";
  }
};

template<typename T>
class optional {
 public:
  optional() = default;

  optional(const T &value) {  // NOLINT
    is_initialized_ = true;
    T *val = new(&data_[0])T{value};
    (void) (&val);
  }

  optional(const T &&value) {  // NOLINT
    is_initialized_ = true;
    T *val = new(&data_[0]) T(std::move(value));
    (void) (&val);
  }

  optional(const optional &other) {
    if (is_initialized_ && other.is_initialized_) {
      this->value() = other->value();
    } else if (!is_initialized_ && other.is_initialized_) {
      T *val = new(&data_[0])T{other.value()};
      is_initialized_ = true;
      (void) (&val);
    } else if (is_initialized_ && !other.is_initialized_) {
      this->reset();
    } else if (!is_initialized_ && !other.is_initialized_) {
      (void) (&data_);
    }
  }

  T &value() &{  // NOLINT
    if (!is_initialized_) {
      throw bad_optional_access();
    }
    // char* ptr = data_;
    // void* data_ptr = ptr;
    // T* type_ptr = data_ptr;
    return reinterpret_cast<T &>(*(T *) (&data_[0]));  // NOLINT
  }

  T &value() const &{  // NOLINT
    if (!is_initialized_) {
      throw bad_optional_access();
    }
    // char* ptr = data_;
    // void* data_ptr = ptr;
    // T* type_ptr = data_ptr;
    return reinterpret_cast<T &>(*(T *) (&data_[0]));  // NOLINT
  }

  T &&value() &&{  // NOLINT
    if (!is_initialized_) {
      throw bad_optional_access();
    }
    return std::move(*static_cast<T *>(static_cast<void *>(&data_[0])));
  }

  optional &operator=(const T &value) {
    if (is_initialized_) {
      this->value() = value;
    } else {
      is_initialized_ = true;
      T *val = new(&data_[0])T{value};
      (void) (&val);
    }
    return *this;
  }

  optional &operator=(T &&rhs) {
    if (is_initialized_) {
      this->value() = std::move(rhs);
    } else {
      is_initialized_ = true;
      T *val = new(&data_[0])T{std::move(rhs)};
      (void) (&val);
    }
    return *this;
  }

  optional &operator=(const optional &other) {
    if (&other == this) {
      return *this;
    }

    if (is_initialized_ && other.is_initialized_) {
      this->value() = other.value();
    } else if (!is_initialized_ && other.is_initialized_) {
      T *val = new(&data_[0])T{other.value()};
      is_initialized_ = true;
      (void) (&val);
    } else if (is_initialized_ && !other.is_initialized_) {
      this->reset();
    } else if (!is_initialized_ && !other.is_initialized_) {
      (void) (&data_);
    }

    return *this;
  }

  optional &operator=(optional &&rhs) noexcept {
    if (&rhs == this) {
      return *this;
    }

    if (is_initialized_ && rhs.is_initialized_) {
      this->value() = std::move(rhs->value());
    } else if (!is_initialized_ && rhs.is_initialized_) {
      T *val = new(&data_[0])T(std::move(rhs.value()));
      is_initialized_ = true;
      (void) (&val);
    } else if (is_initialized_ && !rhs.is_initialized_) {
      this->reset();
    } else if (!is_initialized_ && !rhs.is_initialized_) {
      (void) (&data_);
    }

    return *this;
  }

  T &operator*() &{  // NOLINT
    return *static_cast<T *>(static_cast<void *>(&data_[0]));
  }

  const T &operator*() const &{  // NOLINT
    return *static_cast<const T *>(static_cast<void *>(&data_[0]));
  }

  const T *operator->() const {
    return static_cast<const T *>(static_cast<void *>(&data_[0]));
  }

  T *operator->() {
    return static_cast<T *>(static_cast<void *>(&data_[0]));
  }

  void reset() {
    if (is_initialized_) {
      T *ptr = static_cast<T *>(static_cast<void *>(&data_[0]));;
      ptr->~T();
      is_initialized_ = false;
    }
  }

  ~optional() {
    if (is_initialized_) {
      T *ptr = static_cast<T *>(static_cast<void *>(&data_[0]));
      ptr->~T();
      is_initialized_ = false;
    }
  }

  [[nodiscard]] bool has_value() const {
    return is_initialized_;
  }

  template<typename... Args>
  void emplace(Args &&... args) {
    if (is_initialized_) {
      this->reset();
    }
    is_initialized_ = true;
    T *val = new(&data_[0])T(std::forward<Args>(args)...);
    (void) (&val);
  }

  friend void swap(optional<T> &first, optional<T> &second) {
    std::swap(first.data_, second.data_);
    std::swap(first.is_initialized_, second.is_initialized_);
  }

 private:
  alignas(T) char data_[sizeof(T)];
  bool is_initialized_ = false;
};
}  // namespace bmstu
