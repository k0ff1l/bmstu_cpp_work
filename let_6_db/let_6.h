// Copyright 2023 <fleurs>

#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Student {
 public:
  std::string name;
  int age;
  int rating;

  void print() const {
    std::cout << name << " " << age << " " << rating << std::endl;
  }
};

void mode(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[1] << "input file" << std::endl;
  } else {
    std::cerr << "Usage: " << argv[1] << " input file" << std::endl;
    std::cerr << "Mode: " << argv[2] << std::endl;
  }
}

bool compareByAge(const Student &a, const Student &b) {
  return a.age > b.age;
}
bool compareByRating(const Student &a, const Student &b) {
  return a.rating > b.rating;
}
bool compareByAlphabet(const Student &a, const Student &b) {
  return a.name < b.name;
}

void top_age(auto &Students, size_t count);  // NOLINT
void top_age_alphabet(auto &Students, size_t count);  // NOLINT
void top_rating(auto &Students, size_t count);  // NOLINT
void top_rating_alphabet(auto &Students, size_t count);  // NOLINT
