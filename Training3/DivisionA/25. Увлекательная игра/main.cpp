#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    int n, a, b;
    std::cin >> n >> a >> b;
    if (n < 2) {
        std::cout << 0;
        return 0;
    }
    std::vector<int> dp(n + 1);
    dp[2] = std::max(a, b);
    int const MIN = (n + 1) * std::max(a, b);
    for (int i = 3; i < n + 1; ++i) {
        int min_k = MIN;
        for (int k = 1; k < i; ++k) {
            auto buf = std::max(dp[k] + a, dp[i - k] + b);
            if (buf < min_k) {
                min_k = buf;
            }
        }
        dp[i] = min_k;
    }
    std::cout << dp.back();
    return 0;
}
