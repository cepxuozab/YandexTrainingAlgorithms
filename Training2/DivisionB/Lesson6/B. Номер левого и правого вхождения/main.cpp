#include <iostream>
#include <tuple>
#include <unordered_map>
#include <vector>
[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    //freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::unordered_map<int, std::vector<int>> dict;
    for (int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        dict[x].push_back(i);
    }
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int value;
        std::cin >> value;
        int left, right;
        if (auto it = dict.find(value); it == dict.end()) {
            std::tie(left, right) = std::tuple<int, int>(0, 0);
        }
        else {
            std::tie(left, right) = std::tuple<int, int>(it->second.front(), it->second.back());
        }
        std::cout << left << ' ' << right << '\n';
    }
}
