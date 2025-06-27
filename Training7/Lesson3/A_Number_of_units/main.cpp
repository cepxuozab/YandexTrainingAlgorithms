#include <bitset>
#include <cstdint>
#include <iostream>


int main() {
  uint64_t x;
  std::cin >> x;
  std::cout << std::bitset<64>(x).count() << '\n';
}