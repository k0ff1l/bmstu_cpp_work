//
// Created by fleurs on 29.10.23.
//

#include <iostream>

#include "let_4.h"

namespace {
struct MobilePhone {
  double weight;
  bool is_broken;
  double price;
};
}

int phones() {
  size_t count;
  std::cin >> count;
  if (count == 0) {
    std::cout << "<MobilePhones>" << std::endl;
    std::cout << "</MobilePhones>" << std::endl;
    return 0;
  }
  ::MobilePhone *phones = new ::MobilePhone[count]; // вполне XML::MobilePhone перед *phones заменяемо на auto.
  for (size_t i = 0; i < count; ++i) {
    std::cin >> phones[i].weight;
    std::cin >> phones[i].is_broken;
    std::cin >> phones[i].price;
  } // ввод данных
  std::cout << "<MobilePhones>" << std::endl;
  for (size_t i = 0; i < count; ++i) {
    std::cout << "\t" << "<MobilePhone id=\"" << i << "\" weight=\"" << phones[i].weight << "\" is_broken=\"";
    std::cout << (phones[i].is_broken ? "true" : "false");
    std::cout << "\" price=\"" << phones[i].price << "\"/>" << std::endl;
  }
  std::cout << "</MobilePhones>" << std::endl;
  delete[] phones;
  return 0;
}