#include <cstdint>
#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<int> managers(n - 1);
    for (int& m : managers) std::cin >> m;
    std::vector<int64_t> coins(n + 1);
    std::unordered_map<int, int64_t> total_employees;
    std::unordered_map<int, std::vector<int>> tree;
    int idx = 2;
    for (int num : managers) {
        tree[num].push_back(idx++);
    }
    auto dfs_ = [&](auto&& self, int employee) -> int64_t {
        int64_t count = 0;
        for (int sub : tree[employee]) {
            count += (1 + self(self, sub));
        }
        total_employees[employee] = count;
        return count;
    };

    dfs_(dfs_, 1);
    for (auto employer = n; employer >= 0; --employer) {
        int64_t direct_sum = 0;
        if (tree.contains(employer)) {
            for (int sub : tree[employer]) {
                direct_sum += coins[sub];
            }
        }
        coins[employer] = 1 + total_employees[employer] + direct_sum;
    }
    for (int i = 1; i <= n; ++i) {
        std::cout << coins[i] << ' ';
    }
}