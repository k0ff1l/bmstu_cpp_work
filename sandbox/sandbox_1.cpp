// Copyright 2023 <fleurs>

#include "sandbox_1.h"
#include <optional>
#include <cstdint>
#include <iostream>

// #pragma pack(1)  // выравнивание на 1 байт
struct Student {
  Student(const int a, const uint64_t s) : age(a), score(s) {
  }
  int age;
  uint64_t score;

  Student(Student &&other) {
    age = std::move(other.age);
    score = std::move(other.score);
  }

  Student(const Student &other) {
    age = other.age;
    score = other.score;
  }

  Student &operator=(const Student &other) {
    age = other.age;
    score = other.score;
    return *this;
  }

  ~Student() {
    std::cout << "Я тупо сдох\n";
    age = 0;
    score = 0;
  }
};
// #pragma pop()

int main() {
  bmstu::hw_5_optional<Student> a;
  a.emplace(1, 2);
  bmstu::hw_5_optional<Student> st(std::move(Student(666, 0xFF00FF00FF00FF00)));
  st.reset();
  return 0;
}
