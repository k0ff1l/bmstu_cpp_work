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

    vector(size_t size) : data_(size), size_(size) {
      size_t pos = 0;
      try {
        for (auto i = 0; i < data_.capacity(); ++i) {
          ++pos;
          ::new(const_cast<void *>(static_cast<const volatile void *>(std::addressof(*(data_.buffer() + i))))) T();
        }
      } catch (...) {
        for (auto i = 0; i < pos; ++i) {
          std::destroy_at(std::addressof(*(data_.buffer() + i)));
          std::cout << "wow exception here." << std::endl;
          throw;
        }
      }
    }
  private:
    raw_memory<T> data_;
    size_t size_ = 0;
};
}  // namespace bmstu
