#include <iostream>
#include <map>
#include <vector>
#include <numeric>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin >> n >> k;
    std::map<int, std::vector<int>> maps;
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        maps[x].push_back(i);
    }
    for (auto &[key, indexes]: maps) {
        if (indexes.size() < 2) {
            continue;
        }
        std::adjacent_difference(indexes.begin(), indexes.end(), indexes.begin());
        for (size_t i = 1; i < indexes.size(); ++i) {
            if (indexes[i] <= k) {
                std::cout << "YES";
                return 0;
            }
        }
    }
    puts("NO");

}


