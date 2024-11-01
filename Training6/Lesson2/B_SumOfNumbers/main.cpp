#include <iostream>
#include <vector>

auto main() -> int {  // NOLINT
    int n, k;
    std::cin >> n >> k;
    std::vector<int> prefix_sum(n + 1);
    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        prefix_sum[i] = prefix_sum[i - 1] + x;
    }
    int cnt = 0;
    int r = 0;
    for (int l = 0; l <= n; ++l) {
        while (r <= n && prefix_sum[r] - prefix_sum[l] < k) r++;
        if (prefix_sum[r] - prefix_sum[l] == k) cnt += 1;
    }
    std::cout << cnt;
}