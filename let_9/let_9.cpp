// Copyright 2024 <fleurs>

#include "let_9.hpp"
#include <iostream>
#include <vector>

// совершенное - сумма нат делителей = числу
// 8 - 1 2 4, 1+2+4=7.

bool perfect(int n) {
  std::vector<int> divs;
  int sum = 0;
  for (int i = 1; i < n; i++) {
    if (n % i == 0) {
      divs.push_back(i);
    }
  }
  for (const int div : divs) {
    sum += div;
  }
  return sum == n;
}

int main(int argv, char** argc) {
  int n = std::stoi(argc[1]);
  if (perfect(n)) {
    return 0;
  }
  return 1;
}
