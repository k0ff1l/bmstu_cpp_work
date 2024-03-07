// какие бы действия не придпринимал, кажется,
// что всегда приду к ответу.

#include <iostream>
#include <string>
#include <vector>

std::string helper(unsigned long long a, unsigned long long b, unsigned long long c) {
  if ((a % 3 + b % 3 + c % 3) % 3 == 0) return "No"; // overflow

  return "Yes";
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<unsigned long long>> vec;
  while (n--) {
    unsigned long long a, b, c;
    std::cin >> a >> b >> c;
    vec.push_back(std::vector<unsigned long long>{a, b, c});
  }
  for (auto i : vec) {
    if (i == vec[vec.size() - 1]) std::cout << helper(i[0], i[1], i[2]);
    else std::cout << helper(i[0], i[1], i[2]) << std::endl;
  }
  return 0;
}
