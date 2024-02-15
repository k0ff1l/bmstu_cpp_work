// Copyright 2024 <fleurs>

#pragma once

namespace bmstu {
template<typename Z>
class raw_memory {
  public:
    raw_memory() = default;

    raw_memory(size_t size) : buffer_(allocate_(size)), capacity_(size) {
    }

    raw_memory(const raw_memory& other) = delete;
    // мы не хотим копировать указатель на память одну и ту же, вдруг один удалится указатель, а второй - нет, будет UB.

    raw_memory& operator=(const raw_memory& other) = delete;

    raw_memory(const raw_memory&& other);

    ~raw_memory() { deallocate_(buffer_); }

  private:
    // нужны методы, которые аллоцируют и деаллоцируют сырую память.
    static Z* allocate_(size_t size) {
      return size != 0
               ? static_cast<Z *>(operator new(size * sizeof(Z)))
               : nullptr;
    }

    static void deallocate_(Z* ptr) {
      operator delete(ptr);
    }

    Z* buffer_ = nullptr;
    size_t capacity_ = 0;
};
}
