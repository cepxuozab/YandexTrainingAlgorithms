#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>


auto main() -> int {
    uint64_t n;
    std::cin >> n;
    uint64_t left = 0;
    uint64_t right = static_cast<uint64_t>(ceill(std::sqrt(n)));
    while (left <= right) {
        if (left == right) break;
        auto const step = std::max<uint64_t>(1LL, (right - left) / 2);
        auto const mid = left + step;
        uint64_t curr = 0;
        for (uint64_t i = 0; i <= mid; ++i) {
            curr += ((mid + 1 - i) * i);
        }
        curr + (mid * (mid + 1)) / 2 - 1 <= n ? left = mid : right = mid - 1;
    }
    std::cout << left;
}