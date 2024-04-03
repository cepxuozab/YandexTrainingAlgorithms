#include <iostream>
#include <map>
#include <set>

auto main() -> int {
    std::map<int, std::set<int>> nums;
    for (int i = 0; i < 3; ++i) {
        int n;
        std::cin >> n;
        for (int j = 0; j < n; ++j) {
            int x;
            std::cin >> x;
            nums[x].insert(i);
        }
    }
    for (auto const &[key, value]: nums) {
        if (value.size() > 1) {
            std::cout << key << ' ';
        }
    }
}