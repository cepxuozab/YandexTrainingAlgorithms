#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    struct Film {
        int number_of_episodes{};
        int importance_coefficient{};

        auto operator<=>(Film const &) const = default;
    };
    std::vector<Film> sa(n);
    for (auto &[episode, _]: sa) std::cin >> episode;
    long long total_weight{};
    for (auto &[_, w]: sa) {
        std::cin >> w;
        total_weight += w;
    }
    std::ranges::sort(sa);
    long long need = (total_weight + 1) / 2;
    long long accumulated = 0;
    int num = sa.front().number_of_episodes;
    for (auto const &[idx, w]: sa) {
        accumulated += w;
        if (accumulated >= need) {
            num = idx;
            break;
        }
    }
    long long cost = 0;
    for (auto const &[idx, w]: sa) {
        cost += 1LL * w * std::abs(num - idx);
    }
    std::cout << num << ' ' << cost << '\n';
}