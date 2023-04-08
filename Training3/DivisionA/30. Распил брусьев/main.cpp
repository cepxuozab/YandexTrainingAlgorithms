#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int64_t length;
    int n;
    std::cin >> length >> n;
    std::vector<int> wood{ 0 };
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        wood.push_back(x);
    }
    wood.push_back(length);
    int N = n + 2;
    std::vector<std::vector<int64_t>> dp(N, std::vector<int64_t>(N, 0));
    auto max_cost = length * length;
    for (int diagonal = N + 1; diagonal < 2 * N - 1; ++diagonal) {
        int l = diagonal >= N - 1 ? 2 * (N - 1) - diagonal : N - 1;
        int r = diagonal < N - 1 ? diagonal : N - 1;
        while (l >= 0 && r >= (std::max(0, diagonal - N + 1))) {
            int64_t min_cost = r - l > 1 ? max_cost : 0;
            for (int i = l + 1; i < r; ++i) {
                int64_t cost = dp[l][i] + dp[i][r];
                if (min_cost > cost) {
                    min_cost = cost;
                }
            }
            dp[l][r] = wood[r] - wood[l] + min_cost;
            l--;
            r--;
        }
    }
    std::cout << dp.front().back();
    return 0;
}
