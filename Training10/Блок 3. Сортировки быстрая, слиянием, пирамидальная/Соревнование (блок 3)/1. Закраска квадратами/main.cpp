#include <cstdint>
#include <iostream>
#include <utility>

[[nodiscard]] constexpr std::uint64_t CountOperations(std::uint64_t a, std::uint64_t b) {
    if (a < b) {
        std::swap(a, b);
    }
    std::uint64_t operations = 0;
    while (b != 0) {
        operations += a / b;
        a %= b;
        std::swap(a, b);
    }
    return operations;
}

int main() {
    std::uint64_t x{};
    std::uint64_t y{};
    std::cin >> x >> y;
    std::cout << CountOperations(x, y) << '\n';
}