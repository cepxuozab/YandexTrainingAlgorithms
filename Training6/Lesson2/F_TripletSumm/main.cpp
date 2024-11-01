#include <cstdint>
#include <iostream>
#include <vector>

int64_t sum(int n, int k, std::vector<int> const& a, std::vector<std::vector<int64_t>>& dp) {
    int const mod = 1000000007;
    if (k == -1) {
        return 1;
    }
    if (n == -1) {
        return 0;
    }

    if (dp[n][k] != -1) {
        return dp[n][k];
    }
    int64_t ans1 = (((int64_t) a[n]) % mod * sum(n - 1, k - 1, a, dp) % mod + mod) % mod;
    int64_t ans2 = (sum(n - 1, k, a, dp) + mod) % mod;
    dp[n][k] = (ans1 + ans2) % mod;
    return (ans1 + ans2 + mod) % mod;
}

auto main() -> int {  // NOLINT

    int n;
    std::cin >> n;
    int k = 3;
    std::vector<int> arr(n);
    for (int& a : arr) std::cin >> a;
    std::vector<std::vector<int64_t>> dp(n, std::vector<int64_t>(k, -1));
    std::cout << sum(n - 1, k - 1, arr, dp);
}