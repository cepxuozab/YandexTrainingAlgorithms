#include <cstdint>
#include <iostream>
#include <vector>

auto main() -> int {
    int n, m;
    std::cin >> n >> m;
    std::vector<int64_t> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        sum[i] = sum[i - 1] + x;
    }
    for (int i = 0; i < m; i++) {
        int len;
        int64_t s;
        std::cin >> len >> s;
        int l = 0, r = n - len + 1;
        while (l < r - 1) {
            int m = (l + r) / 2;
            if (sum[m + len] - sum[m] > s)
                r = m;
            else
                l = m;
        }
        std::cout << ((sum[l + len] - sum[l] == s) ? (l + 1) : -1) << "\n";
    }
}
