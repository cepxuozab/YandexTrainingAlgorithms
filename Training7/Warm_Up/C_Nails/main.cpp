#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), dp(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> a[i];
    }
    std::ranges::sort(a);
    dp[2] = a[2] - a[1];
    dp[3] = a[3] - a[1];

    for (int i = 4; i <= n; i++)
    {
        dp[i] = std::min(dp[i - 1], dp[i - 2]) + a[i] - a[i - 1];
    }
    std::cout << dp.back();

    return 0;
}