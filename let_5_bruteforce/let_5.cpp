// Copyright 2023 <fleurs>

#include "let_5.h"
#include <fstream>

int bruteforce() {
  const char *alphabet = "1234567890AaBbCcDdEeFfGgHhXxYyZz";
  std::ofstream fout;
  fout.open("file.txt");
  for (size_t i = 0; i < 32; ++i) {
    for (size_t j = 0; j < 32; ++j) {
      for (size_t k = 0; k < 32; ++k) {
        for (size_t l = 0; l < 32; ++l) {
          for (size_t m = 0; m < 32; ++m) {
            fout << alphabet[i] << alphabet[j] << alphabet[k] << alphabet[l]
                 << alphabet[m] << std::endl;
          }
        }
      }
    }
  }
  fout.close();
  return 0;
}


// 32**5 -> вариантов строки, одна строка весит 6 байт, 5 чар + '\n'
// 201326592 байт.
