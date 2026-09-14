#include <algorithm>
#include <iostream>
#include <vector>

namespace my_sort {

auto min_moves(std::vector<std::pair<int, int>> const& ships) -> int {
    size_t const n = ships.size();
    std::vector<int> x, y;
    x.reserve(n), y.reserve(n);
    for (auto& [i, j] : ships) {
        x.push_back(i), y.push_back(j);
    }
    std::ranges::sort(x);
    std::ranges::sort(y);
    auto median_y = y[n / 2];
    int moves_x = 0, moves_y = 0;
    for (int i = 0; i < n; ++i)
        moves_x += abs(x[i] - (i + 1));
    for (int u : y)
        moves_y += abs(u - median_y);
    return moves_x + moves_y;
}
} // namespace

auto main() -> int {
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> ships(n);
    for (auto& [x, y] : ships)
        std::cin >> x >> y;
    std::cout << my_sort::min_moves(ships);
}
