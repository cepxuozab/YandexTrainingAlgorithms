#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

auto solve(const std::vector<std::pair<std::pair<int, int>, std::string>>& records) -> std::pair<std::string, int>
{
    std::unordered_map<std::string, int> player_scores;

    int prev_a = 0, prev_b = 0;
    for (const auto& [score, name] : records)
    {
        const auto& [cur_a, cur_b] = score;
        player_scores[name] += (cur_a - prev_a) + (cur_b - prev_b);
        prev_a = cur_a;
        prev_b = cur_b;
    }

    const auto best = std::ranges::max_element(player_scores, {}, [](const auto& p)-> auto { return p.second; });
    return {best->first, best->second};
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        std::string name;
        std::cin >> name;
    }

    int m;
    std::cin >> m;

    std::vector<std::pair<std::pair<int, int>, std::string>> records(m);
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        char colon;
        std::string name;
        std::cin >> a >> colon >> b >> name;
        records[i] = {{a, b}, name};
    }

    auto [best_name, best_score] = solve(records);
    std::cout << best_name << " " << best_score << "\n";
}
