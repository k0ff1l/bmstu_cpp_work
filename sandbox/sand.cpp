//
// Created by fleurs on 09.11.23.
//

#include <iostream>
#include <string>

int main(){
  std::string str = "str";
  std::string str2 = "other";
  str2 = std::move(str);
  std::cout << str.c_str() << std::endl;
  if (str == ""){
    std::cout << "True";
  }
 return 0;
}
