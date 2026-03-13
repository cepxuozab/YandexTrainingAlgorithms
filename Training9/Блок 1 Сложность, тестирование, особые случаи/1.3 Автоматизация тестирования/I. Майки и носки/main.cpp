#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {  // NOLINT
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::vector<std::pair<int, int>> ans;
    if (a > 0 && c > 0) ans.emplace_back(b + 1, d + 1);
    if (b > 0 && d > 0) ans.emplace_back(a + 1, c + 1);
    if (a > 0 && b > 0) ans.emplace_back(std::max(a, b) + 1, 1);
    if (c > 0 && d > 0) ans.emplace_back(1, std::max(c, d) + 1);
    auto compare = [](std::pair<int, int> lhs, std::pair<int, int> rhs) {
        return lhs.first + lhs.second < rhs.first + rhs.second;
    };
    auto answer = std::min_element(ans.begin(), ans.end(), compare);
    std::cout << answer->first << ' ' << answer->second;
}
