#include <iostream>
#include <vector>
#include <unordered_map>

auto solve(const std::vector<int>& p) -> int
{
    int n = static_cast<int>(p.size());
    std::unordered_map<int, int> cnt;
    int left = 0;
    int best = 0;

    for (int right = 0; right < n; ++right)
    {
        ++cnt[p[right]];

        while (cnt.size() > 2)
        {
            int type = p[left];
            if (--cnt[type] == 0)
                cnt.erase(type);
            ++left;
        }

        if (cnt.size() == 2)
            best = std::max(best, right - left + 1);
    }

    return best;
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> p(n);
    for (int i = 0; i < n; ++i)
        std::cin >> p[i];

    std::cout << solve(p) << '\n';
    return 0;
}
