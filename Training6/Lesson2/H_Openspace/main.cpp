#include <algorithm>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

auto MakePrefix(std::vector<int64_t> arr, bool need_reverse = false) -> std::vector<int64_t> {
    std::vector<int64_t> pre(arr.size());
    int64_t sum = 0;
    if (need_reverse) {
        std::ranges::reverse(arr);
    }
    for (size_t i = 1; i < arr.size(); ++i) {
        sum += arr[i - 1];
        pre[i] = pre[i - 1] + sum;
    }
    if (need_reverse) {
        return {pre.rbegin(), pre.rend()};
    }
    return pre;
}

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<int64_t> arr(n);
    for (int64_t& a : arr) std::cin >> a;
    auto left = MakePrefix(arr), right = MakePrefix(arr, true);
    std::optional<int64_t> res;
    for (int i = 0; i < n; ++i) {
        if (!res) {
            res = left[i] + right[i];
        } else {
            *res = std::min(res.value(), left[i] + right[i]);
        }
    }
    std::cout << res.value();
}
