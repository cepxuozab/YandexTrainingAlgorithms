#include <iostream>
#include <vector>

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> dp(n, std::vector<int>(m, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j - 1 >= 0 && i - 2 >= 0)
                dp[i][j] += dp[i - 2][j - 1];
            if (j - 2 >= 0 && i - 1 >= 0)
                dp[i][j] += dp[i - 1][j - 2];
        }
    }
    std::cout << dp.back().back() << std::endl;
}
