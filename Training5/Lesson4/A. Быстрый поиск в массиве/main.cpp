#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int& a : arr) {
        std::cin >> a;
    }
    std::ranges::sort(arr);
    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        std::cin >> l >> r;
        auto left = std::ranges::lower_bound(arr, l);
        auto right = std::ranges::upper_bound(arr, r);
        std::cout << std::ranges::distance(left, right) << '\n';
    }
}