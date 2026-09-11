#include <algorithm>
#include <deque>
#include <iostream>
#include <print>
#include <utility>
#include <vector>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::deque<int> dq;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        dq.push_back(x);
    }

    const int mx = std::ranges::max(dq);

    std::vector<std::pair<int, int>> ans;
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        int f = dq[0];
        int s = dq[1];

        if (f == mx) break;

        ans.emplace_back(f, s);
        ++cnt;

        if (f >= s) std::swap(dq[0], dq[1]);
        dq.push_back(dq.front());
        dq.pop_front();
    }

    dq.pop_front();

    int q;
    std::cin >> q;

    while (q--) {
        long long k;
        std::cin >> k;

        if (k <= cnt) {
            std::println("{} {}", ans[k - 1].first, ans[k - 1].second);

        } else {
            auto const idx = (k - cnt - 1) % (n - 1);
            std::println("{} {}", mx, dq[idx]);
        }
    }

    return 0;
}