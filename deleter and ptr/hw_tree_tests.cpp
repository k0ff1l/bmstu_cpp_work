// Copyright 2024 <fleurs>

#include "hw_tree.hpp"
#include <iostream>

#include <gtest/gtest.h>

struct dummy_object {
  dummy_object() {
    buf = new int[1024 * 1024 * 1024];
    std::cout << "dummy_object many memory alloc\n";
  }

  ~dummy_object() {
    delete[] buf;
    std::cout << "dummy_object many memory dealloc\n";
  }

  int *buf;
};

auto mul(int a, int b) -> int {
  return a + b;
}

typedef int(*f_ptr)(int, int);

typedef int(*funcs_ptr[3])(int, int);

bmstu::default_delete<dummy_object> deleter;

TEST(TestName_other, Foo3) {
//  int a = 300;
//  int b = 1;
//  funcs_ptr arr = {mul, mul, mul};
//  for (int i = 0; i < 3; ++i) {
//    std::cout << arr[i](a, b);
//  }
  auto *ptr = new dummy_object;
  // позволяет подменять
  deleter(ptr);
//  auto ptr = new dummy_object;
//  {
//    bmstu::dummy_ptr<dummy_object> dyn(ptr);
//  }
//  std::cout << ptr->buf[(1024 * 1024) - 2];
//  bmstu::dummy_ptr<dummy_object> ptr(new dummy_object());
}

TEST(TestName_other, FOO2) {
//  bmstu::unique_ptr<dummy_object, bmstu::non_default_delete<dummy_object>> ptr = new dummy_object;
  bmstu::unique_ptr<int[]> dummy_array{new int[1000000]};
}
