#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>


auto main() -> int {
    uint64_t n;
    std::cin >> n;
    uint64_t left = 0;
    auto right = static_cast<uint64_t>(ceill(std::sqrt(n)));
    while (left <= right) {
        if (left == right) break;
        auto const step = std::max<uint64_t>(1LL, (right - left) / 2);
        auto const mid = left + step;
        long double curr = static_cast<long double>(mid) * (mid + 2) * (mid + 1) / 2 -
                           static_cast<long double>(mid) * (mid + 1) * (2 * mid + 1) / 6;
        curr - 1 <= n ? left = mid : right = mid - 1;
    }
    std::cout << left;
}