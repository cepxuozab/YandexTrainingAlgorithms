#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <ranges>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::map<int, int> maps;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        maps[x]++;
    }
    std::vector<int> nums;
    auto prev = maps.begin();
    for (auto it = std::next(maps.begin()); it != maps.end(); ++it) {
        if (it->first - prev->first == 1) {
            nums.push_back(prev->second + it->second);
        }
        prev = it;
    }
    if (!nums.empty()) {
        int ans = std::ranges::max(nums);
        std::cout << n - ans;
    } else {
        int u = std::ranges::max(std::ranges::views::values(maps));
        std::cout << n - u;
    }
}


