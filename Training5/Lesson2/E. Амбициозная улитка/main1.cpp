#include <iostream>
#include <vector>
#include <ranges>
#include <cstdint>

auto MaxHeight(int n, std::vector<std::pair<int, int>> const &berries) {
    int64_t buf_h = 0;
    for (auto const &[a, b]: berries) {
        if (a - b > 0) {
            buf_h += a;
            buf_h -= b;
        }
    }
    int last_day_i = 0;
    auto max_h = buf_h;
    for (int i: std::ranges::iota_view(0, n)) {
        auto [a, b] = berries[i];
        if (a - b >= 0) {
            if (buf_h + b > max_h) {
                max_h = buf_h + b;
                last_day_i = i;
            }
        } else {
            if (buf_h + a > max_h) {
                max_h = buf_h + a;
                last_day_i = i;
            }
        }
    }
    std::vector<int> ans;
    for (int i: std::ranges::iota_view(0, n)) {
        auto [a, b] = berries[i];
        if (a - b > 0 && i != last_day_i) {
            ans.push_back(i + 1);
        }
    }
    ans.push_back(last_day_i + 1);
    for (int i: std::ranges::iota_view(0, n)) {
        auto [a, b] = berries[i];
        if (a - b <= 0 && i != last_day_i) {
            ans.push_back(i + 1);
        }
    }
    return std::pair(max_h, ans);
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> berries(n);
    for (auto &[a, b]: berries)std::cin >> a >> b;
    auto [max_h, arr] = MaxHeight(n, berries);
    std::cout << max_h << '\n';
    for (int i: arr)std::cout << i << ' ';
}