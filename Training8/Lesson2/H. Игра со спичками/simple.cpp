#include <iostream>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::cout << (n % 4 == 0 ? 2 : 1);
}