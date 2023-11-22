// Copyright 2023 <fleurs>

#include <iostream>
#include <string>

// int main() {
//  std::string str = "str";
//  std::string str2 = "other";
//  str2 = std::move(str);
//  std::cout << str.c_str() << std::endl;
//  if (str == "") {
//    std::cout << "True";
//  }
//  return 0;
//}

#include <vector>

int main() {
  std::vector<int> a = {2, 3, 4, 5};
  a.resize(6);
  for (auto b : a) {
    std::cout << b << std::endl;
  }
  // 2 3 4 5 0 0
  a[4] = 6;
  a.resize(4);
  std::cout << a[4] << std::endl;  // 6
  a.resize(5);
  std::cout << a[4] << std::endl;  // 0
  return 0;
}
