#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

auto Calc(std::vector<int> const& a, int w) -> int {
    int ans = 1;
    int pos = 0;
    for (auto& ids : a) {
        if (ids > w) {
            return std::numeric_limits<int>::max();
        }
        if (pos + ids <= w) {
            pos += (ids + 1);
        } else {
            ans++;
            pos = ids + 1;
        }
    }
    return ans;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int w, n, m;
    std::cin >> w >> n >> m;
    std::vector<int> a(n), b(m);

    for (int& i : a) {
        std::cin >> i;
    }
    int max1 = std::ranges::max(a);
    for (int& i : b) {
        std::cin >> i;
    }
    int max2 = std::ranges::max(b);
    int l = max1, r = w - max2 + 1;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        auto const f1 = Calc(a, mid);
        auto const f2 = Calc(b, w - mid);
        f1 < f2 ? r = mid : l = mid;
    }
    auto const f1 = std::max(Calc(a, l), Calc(b, w - l));
    auto const f2 = std::max(Calc(a, r), Calc(b, w - r));
    std::cout << std::min(f1, f2);
    return 0;
}