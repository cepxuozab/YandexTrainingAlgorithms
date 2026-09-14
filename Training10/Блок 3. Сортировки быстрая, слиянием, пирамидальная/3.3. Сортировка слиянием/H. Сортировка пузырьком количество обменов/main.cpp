#include <algorithm>
#include <iostream>
#include <span>
#include <vector>

namespace {
struct CountInv {
    std::vector<int> arr;
    long long inversions = 0;  // n может быть до ~5*10^5-10^6, число инверсий может не влезть в int
};

auto merge(std::span<const int> lhs, std::span<const int> rhs) -> CountInv {
    CountInv inv{};
    size_t i = 0;
    size_t j = 0;
    while (i < lhs.size() && j < rhs.size()) {
        if (lhs[i] <= rhs[j]) {
            inv.arr.push_back(lhs[i++]);
        } else {
            inv.arr.push_back(rhs[j++]);
            inv.inversions += static_cast<long long>(lhs.size() - i);
        }
    }
    std::ranges::copy(lhs.begin() + i, lhs.end(), std::back_inserter(inv.arr));
    std::ranges::copy(rhs.begin() + j, rhs.end(), std::back_inserter(inv.arr));
    return inv;
}

auto count_inversion(std::span<const int> arr) -> CountInv {
    const size_t n = arr.size();
    if (n <= 1) {
        return {.arr = std::vector<int>(arr.begin(), arr.end()), .inversions = 0};
    }
    const size_t pivot = n / 2;
    std::vector<int> lhs(arr.begin(), arr.begin() + pivot);
    std::vector<int> rhs(arr.begin() + pivot, arr.end());

    auto [left_half, left_rec] = count_inversion(lhs);
    auto [right_half, right_rec] = count_inversion(rhs);
    auto merged = merge(left_half, right_half);
    return {.arr = merged.arr, .inversions = merged.inversions + left_rec + right_rec};
}
}  // namespace

auto main() -> int {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) std::cin >> a;
    auto [_, inv] = count_inversion(arr);
    std::cout << inv;
}
