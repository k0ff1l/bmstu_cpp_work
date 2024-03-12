// Copyright 2024 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_6_raw_memory.h"
#include "hw_6_true_vector.h"

class WithoutDefaultConstructor {
  public: // NOLINT
    WithoutDefaultConstructor() = delete;

    explicit WithoutDefaultConstructor(int other) : number(other) {
    }

    int number;
};

class TestClass {
  public:  // NOLINT
    TestClass() {
      std::cout << "alloc def\n";
      ++cnt;
      if (cnt == 10) throw std::runtime_error("created 10 testclass species \n");
    }

    TestClass(int z) : z(z) {
      std::cout << "alloc with num\n";
      ++cnt;
      if (cnt == 10) throw std::runtime_error("created 10 testclass species");
    }

    ~TestClass() {
      std::cout << "dealloc\n";
    }
  private:
    int z;
    static size_t cnt;
};

size_t TestClass::cnt = 0;

TEST(Vector, test1) {
  bmstu::raw_memory<WithoutDefaultConstructor> memory(10);
}

TEST(Vector, test2) {
  try {
    bmstu::vector<TestClass> a(9);
    TestClass b(10);
  } catch (std::runtime_error& e) {
    std::cout << "catched exception: " << e.what() << "\n";
  }
}
