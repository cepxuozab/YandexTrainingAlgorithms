#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using Event = std::pair<int, int>;

int main()
{
    freopen("input.txt", "r", stdin);
    int m;
    std::cin >> m;
    std::unordered_map<int, std::unordered_set<int>> real_map;
    for (int i = 1; i < m; ++i) {
        int parent, child;
        std::cin >> parent >> child;
        real_map[parent].insert(child);
        real_map[child].insert(parent);
    }
    auto get_leaves = [&]() {
        std::vector<int> lea;
        for (auto const& [key, value] : real_map) {
            if (value.size() == 1U) {
                lea.push_back(key);
            }
        }
        return lea;
    };
    int dist = 0;
    while (real_map.size() >= 2U) {
        auto leaves = get_leaves();
        for (auto leaf : leaves) {
            for (auto leaf_child : real_map.at(leaf)) {
                real_map[leaf_child].erase(leaf);
            }
            real_map.erase(leaf);
        }
        leaves.size() < 2 ? dist += 1 : dist += 2;
    }
    dist += (int)real_map.size();
    std::cout << dist;
}
