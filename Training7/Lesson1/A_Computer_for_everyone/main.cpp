#include <algorithm>
#include <iostream>
#include <vector>

auto ReadEndSortData(unsigned n) -> std::vector<std::pair<int, int>> {
    std::vector<std::pair<int, int>> data(n);
    for (unsigned i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        data[i] = {x, i};
    }
    std::ranges::sort(data);
    return data;
}

struct Group {
    int total{};
    std::vector<int> ans;
};

auto ComputerForEveryone(std::vector<std::pair<int, int>> const& groups,
                         std::vector<std::pair<int, int>> const& rooms) -> Group {
    std::vector<int> ans(groups.size());
    int res = 0;
    size_t j = 0;
    for (auto const& [group_count, group_id] : groups) {
        while (j < rooms.size() && rooms[j].first <= group_count) {
            j++;
        }
        if (j < rooms.size()) {
            ans[group_id] = rooms[j].second + 1;
            res += 1;
            j += 1;
        }
    }
    return {.total = res, .ans = ans};
}

auto main() -> int {
    unsigned n, m;
    std::cin >> n >> m;
    auto groups = ReadEndSortData(n);
    auto rooms = ReadEndSortData(m);
    auto [res, ans] = ComputerForEveryone(groups, rooms);
    std::cout << res << '\n';
    for (int i : ans) std::cout << i << ' ';
}