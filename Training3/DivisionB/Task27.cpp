#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));
    auto dp = grid;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> grid[i][j];
        }
    }
    dp[0][0] = grid[0][0];
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < m; ++j) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j] = grid[i][j] + std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    std::vector<char> answer;
    int64_t sum = grid[0][0];
    n--, m--;
    while (n > 0 && m > 0) {
        sum += grid[n][m];
        if (dp[n][m] - grid[n][m] == dp[n - 1][m]) {
            answer.push_back('D');
            n--;
        }
        else {
            answer.push_back('R');
            m--;
        }
    }
    while (n > 0) {
        sum += grid[n][0];
        answer.push_back('D');
        n--;
    }
    while (m > 0) {
        sum += grid[0][m];
        answer.push_back('R');
        m--;
    }
    std::cout << sum << std::endl;
    for (auto it = answer.rbegin(); it != answer.rend(); ++it) {
        std::cout << *it << ' ';
    }
}
