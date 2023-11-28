// Copyright 2023 <fleurs>

#include "let_3.h"
#include <string>
#include <iostream>

void generateChar(const std::string &alphabet,
                  const std::string &password,
                  int count) {
  if (count == 0) {
    std::cout << password << "\n";
    return;
  }
  --count;
  for (auto i = 0; i < alphabet.size(); ++i) {
    generateChar(alphabet, password + alphabet[i], count);
  }
}

int let_3(int argc, char **argv) {
  std::string empty{};
  std::string alphabet = "1234567890AaBbCcDdEeFfGgHhXxYyZz";
  auto cnt = std::stoi(argv[1]);
  int count = cnt + 1;
  generateChar(alphabet, empty, count);
}

int main() {
  return 0;
}
