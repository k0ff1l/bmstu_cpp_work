// Copyright 2023 <fleurs>

#include "let_6.h"

void top_age(auto &Students, size_t count) {  // NOLINT
  count = count > Students.size() ? Students.size() : count;
  std::sort(Students.begin(), Students.end(), compareByAge);
  size_t j = 0;
  for (auto &vec : Students) {
    ++j;
    vec.print();
    if (j == count) {
      break;
    }
  }
}

void top_age_alphabet(auto &Students, size_t count) {  // NOLINT
  count = count > Students.size() ? Students.size() : count;
  std::sort(Students.begin(), Students.end(), compareByAge);
  size_t j = 0;
  std::vector<Student> topAge;
  for (auto &vec : Students) {
    topAge.push_back(vec);
    ++j;
    if (j == count) {
      break;
    }
  }
  std::sort(topAge.begin(), topAge.end(), compareByAlphabet);
  for (auto &element : topAge) {
    element.print();
  }
}

void top_rating(auto &Students, size_t count) {  // NOLINT
  count = count > Students.size() ? Students.size() : count;
  std::sort(Students.begin(), Students.end(), compareByRating);
  size_t j = 0;
  for (auto &vec : Students) {
    ++j;
    vec.print();
    if (j == count) {
      break;
    }
  }
}

void top_rating_alphabet(auto &Students, size_t count) {  // NOLINT
  count = count > Students.size() ? Students.size() : count;
  std::sort(Students.begin(), Students.end(), compareByRating);
  size_t j = 0;
  std::vector<Student> topRating;
  for (auto &vec : Students) {
    topRating.push_back(vec);
    ++j;
    if (j == count) {
      break;
    }
  }
  std::sort(topRating.begin(), topRating.end(), compareByAlphabet);
  for (auto &element : topRating) {
    element.print();
  }
}

int let_6(int argc, char **argv) {
  mode(argc, argv);
  std::ifstream in(argv[1], std::ios::in | std::ios::binary);
  uint32_t students_count;
  in.read(reinterpret_cast<char *>(&students_count), sizeof(students_count));
  std::vector<Student> Students;
  Students.resize(students_count);
  size_t i = 0;
  while (in.peek() != EOF) {
    while (in.peek() != 0) {
      char byte;
      in.read(reinterpret_cast<char *>(&byte), sizeof(byte));
      Students[i].name += byte;
    }
    char zero;
    in.read(reinterpret_cast<char *>(&zero), sizeof(char));
    in.read(reinterpret_cast<char *>(&Students[i].age), sizeof(int));
    in.read(reinterpret_cast<char *>(&Students[i].rating), sizeof(int));
    ++i;
  }
  std::string argument(argv[2]);
  if (argument == "-a") {
    size_t count;
    std::cout << "Write the number of top-aged students you want\n";
    std::cin >> count;
    top_age(Students, count);
  }
  if (argument == "-o") {
    size_t count;
    std::cout
        << "Write the number of top-aged students you want, sorted by alphabet\n";
    std::cin >> count;
    top_age_alphabet(Students, count);
  }
  if (argument == "-g") {
    size_t count;
    std::cout << "Write the number of top-rated students you want\n";
    std::cin >> count;
    top_rating(Students, count);
  }
  if (argument == "-r") {
    size_t count;
    std::cout
        << "Write the number of top-rated students you want, sorted by alphabet\n";
    std::cin >> count;
    top_rating_alphabet(Students, count);
  }
}
