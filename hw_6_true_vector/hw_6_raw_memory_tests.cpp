// Copyright 2024 <fleurs>

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

#include "hw_6_raw_memory.h"

class WithoutDefaultConstructor {
  public: // NOLINT
    WithoutDefaultConstructor() = delete;

    explicit WithoutDefaultConstructor(int other) : number(other) {
    }

    int number;
};

TEST(TrueVector, test1) {
  bmstu::raw_memory<WithoutDefaultConstructor> memory(10);
}
