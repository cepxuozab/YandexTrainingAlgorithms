#include <cstdint>
#include <iostream>
#include <limits>
#include <tuple>

auto Cals_sum_steps_to_change_number_top(int64_t number_top) {
    int64_t n1 = number_top / 2, n2{};
    if (number_top > 2LL) {
        auto an = number_top - (2 - number_top % 2);
        n2 = (2 + an) * (an / 2) / 2;
    }
    return n1 + 2 * n2;
}

auto Find_start_diagonal(int64_t n) {
    int64_t left = 1;
    int64_t right = std::numeric_limits<int>::max();
    int64_t ans = -1;
    while (left <= right) {
        auto mid = left + (right - left) / 2;
        if (Cals_sum_steps_to_change_number_top(mid) > n) {
            right = mid - 1;
        } else {
            ans = mid;
            left = mid + 1;
        }
    }
    return ans;
}

auto Numerations(int64_t n) -> std::tuple<int64_t, int64_t> {
    n -= 1;
    auto start_diag = Find_start_diagonal(n);
    n -= Cals_sum_steps_to_change_number_top(start_diag);
    if (n == 0) return std::tuple(start_diag, 1LL);
    if (n > start_diag - 1) {
        n -= start_diag - 1;
        return std::tuple(n, start_diag + 1 - n + 1);
    }
    return std::tuple(start_diag - n, n + 1);
}

auto main() -> int {
    int64_t n;
    std::cin >> n;
    auto [res1, res2] = Numerations(n);
    std::cout << res1 << "/" << res2;
}