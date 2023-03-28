#include <climits>
#include <iostream>
#include <vector>

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<std::vector<int>> grid(n, std::vector<int>(m, 0));
    for (int i = 0; i < k; ++i) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        grid[x][y] = INT_MAX;
    }

    auto neight = [&](int i, int j) {
        if (i < 0 || i >= n || j < 0 || j >= m || grid[i][j] != INT_MAX) {
            return 0;
        }
        return 1;
    };
    std::vector<std::pair<int, int>> direction {
        { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }
    };
    std::vector<std::vector<int>> ans(grid);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == INT_MAX) {
                continue;
            }
            for (auto const& [x, y] : direction) {
                int num = neight(i + x, j + y);
                ans[i][j] += num;
            }
        }
    }

    for (auto const& arr : ans) {
        for (int a : arr) {
            if (a == INT_MAX) {
                std::cout << "* ";
            } else {
                std::cout << a << ' ';
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
