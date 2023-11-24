// Copyright 2023 <fleurs>

#include "let_7.h"

bool palindrome(const std::string &old_word) {
  std::string word;
  std::for_each(old_word.begin(), old_word.end(), [&word](auto a) {
    if (a != ' ') {
      word += a;
    }
  });
  // TODO(fleurs) : fix tolower for russian symbols
  for (size_t i = 0; i < (word.size() / 2 + 1); ++i) {
    if (tolower(word[i]) != tolower(word[word.size() - i - 1])) {
      return false;
    }
  }
  return true;
}

void printPalindromes(const auto &palindromes) {
  std::cout << "{" << "\n\t \"count_palindromes\": " << palindromes.size()
            << ", \n\t \"palindromes\": [";
  for (size_t i = 0; i < palindromes.size(); ++i) {
    if (i != (palindromes.size() - 1)) {
      std::cout << "\"" << palindromes[i] << "\", ";
    } else {
      std::cout << "\"" << palindromes[i] << "\"";
    }
  }
  std::cout << "]" << "\n}";
}

int main(int argc, char **argv) {
  std::vector<std::string> result;
  std::ifstream in;
  in.open(argv[1]);
  std::string line;
  if (!in) {
    std::cout << "FILE NOT OPENED!";
    return 0;
  }
  while (std::getline(in, line)) {
    if (palindrome(line)) {
      result.push_back(line);
    }
  }
  printPalindromes(result);
}

