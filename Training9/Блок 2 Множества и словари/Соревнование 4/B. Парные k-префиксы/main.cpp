#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <span>

auto can(int k, std::span<std::string const> words) -> bool
{
    std::unordered_map<std::string, int> cnt;
    cnt.reserve(words.size());

    for (const auto& w : words)
        cnt[w.substr(0, k)]++;

    return std::ranges::all_of(std::ranges::views::values(cnt), [](int a) -> bool { return a % 2 == 0; });
}

auto solve(std::span<std::string const> words) -> int
{
    int l = 0;
    int r = words[0].size();

    while (l < r)
    {
        int mid = (l + r + 1) / 2;
        can(mid, words) ? l = mid : r = mid - 1;
    }

    return l;
}

auto main() -> int
{
    int n;
    std::cin >> n;
    std::vector<std::string> words(n);
    for (auto& str : words)std::cin >> str;
    std::cout << solve(words) << '\n';
    return 0;
}
