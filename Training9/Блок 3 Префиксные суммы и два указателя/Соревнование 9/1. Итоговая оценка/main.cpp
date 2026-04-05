#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string_view>

auto solve(std::string_view grades) -> char
{
    std::vector<int> scores(grades.size());
    std::ranges::transform(grades, scores.begin(), [](char c) -> int { return c - 'A'; });

    const int worst = std::ranges::max(scores);

    const long long sum = std::accumulate(scores.begin(), scores.end(), 0LL);
    const auto n = static_cast<long long>(scores.size());
    const long long avg = (2 * sum + n - 1) / (2 * n);

    const long long final_score = std::max(avg, static_cast<long long>(worst) - 1);

    return static_cast<char>('A' + final_score);
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string grades;
    std::cin >> grades;

    std::cout << solve(grades) << '\n';
    return 0;
}
