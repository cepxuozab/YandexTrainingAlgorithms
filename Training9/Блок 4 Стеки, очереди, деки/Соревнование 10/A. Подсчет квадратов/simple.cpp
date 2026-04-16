#include <iostream>
#include <string>
#include <vector>

auto main() -> int
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> field { std::string(m + 1, '.') };
    for (int i = 0; i < n; ++i) {
        std::string str;
        std::cin >> str;
        field.push_back("." + str);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (field[i + 1][j] == '.' && field[i][j + 1] == '.'
                && field[i + 1][j + 1] == '#')
                ans++;
        }
    }
    std::cout << ans;
}
