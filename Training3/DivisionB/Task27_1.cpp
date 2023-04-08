#include <algorithm>
#include <iostream>
#include <vector>

using Grid = std::vector<std::vector<int>>;

auto ReadGrid() -> Grid;

auto Preprocessind(Grid const& grid) -> Grid;

auto PathRecovery(Grid const& grid, Grid const& dp, std::vector<char>& answer) -> int64_t;

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }

    auto const grid = ReadGrid();
    auto const dp = Preprocessind(grid);
    std::vector<char> answer;
    auto sum = PathRecovery(grid, dp, answer);
    std::cout << sum << std::endl;
    for (char ch : answer) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;
    return 0;
}

auto ReadGrid() -> Grid
{
    int n;
    int m;
    std::cin >> n >> m;
    Grid grid(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> grid[i][j];
        }
    }
    return grid;
}

auto Preprocessind(Grid const& grid) -> Grid
{
    size_t n = grid.size();
    size_t m = grid.front().size();
    Grid dp(n, std::vector<int>(m, 0));
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
    return dp;
}

auto PathRecovery(Grid const& grid, Grid const& dp, std::vector<char>& answer) -> int64_t
{
    int n = grid.size() - 1;
    int m = grid.front().size() - 1;
    int64_t sum = grid[0][0];

    while (n > 0 && m > 0) {
        sum += grid[n][m];
        if (dp[n][m] - grid[n][m] == dp[n - 1][m]) {
            answer.push_back('D');
            n--;
        } else {
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
    std::reverse(answer.begin(), answer.end());
    return sum;
}
