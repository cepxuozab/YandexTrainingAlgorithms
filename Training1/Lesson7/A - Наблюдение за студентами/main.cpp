#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    // freopen("input.txt", "r", stdin);
    int n;
    int m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> mentors(m);
    for (auto& [l, r] : mentors) {
        std::cin >> l >> r;
    }
    sort(mentors.begin(), mentors.end());
    std::vector<std::pair<int, int>> intervals;
    for (auto const& [left, right] : mentors) {
        if (intervals.empty() || left > intervals.back().second) {
            intervals.emplace_back(left, right);
        } else {
            auto& [l, r] = intervals.back();
            l = std::min(left, l);
            r = std::max(right, r);
        }
    }
    for (auto const& [l, r] : intervals) {
        n -= (r - l + 1);
    }
    std::cout << n << std::endl;
}
