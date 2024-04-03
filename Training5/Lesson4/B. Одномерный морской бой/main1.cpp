#include <iostream>
#include <cstdint>
#include <ranges>

auto CheckShips(int64_t k, int64_t n) -> bool {
    n += 1;
    int64_t sum = 0;
    for (int64_t i : std::ranges::iota_view(1, k + 1)) {
        auto next = (i + 1) * (k - i + 1);
        if (n - sum < next) {
            return false;
        }
        sum += next;
    }
    return true;
}

template<typename Func, typename...Types>
auto LowerBound(int64_t l, int64_t r, Func cmp, Types...types) {
    while (l < r) {
        auto mid = (l + r + 1) / 2;
        if (cmp(mid, types...)) {
            l = mid;
        }
        else {
            r = mid - 1;
        }
    }
    return l;
}

auto main() -> int {
    int64_t n;
    std::cin >> n;
    std::cout << LowerBound(0, (n + 1) / 2, CheckShips, n);
}
