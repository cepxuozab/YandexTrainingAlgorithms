#include <iostream>
#include <vector>

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int m, n;
    std::cin >> m >> n;
    std::vector<std::vector<int64_t>> dp(m + 1, std::vector<int64_t>(n + 1, 1));
    for (int i = 2; i < m + 1; ++i) {
        for (int j = 2; j < n + 1; ++j) {
            dp[i][j] = dp[i][j - 1] + dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
    std::cout << dp.back().back();
    return 0;
}
