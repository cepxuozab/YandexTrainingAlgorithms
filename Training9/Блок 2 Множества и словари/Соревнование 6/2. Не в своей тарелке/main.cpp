#include <iostream>
#include <vector>
#include <unordered_set>

auto solve(int n, const std::vector<int>& a) -> int
{
    std::unordered_set<int> forbidden;
    for (int j = 0; j < n; ++j)
    {
        forbidden.insert((j - (a[j] - 1) + n) % n);
    }
    for (int k = 0; k < n; ++k)
    {
        if (!forbidden.contains(k)) return k;
    }
    return -1;
}

auto main() -> int
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::cout << solve(n, a) << '\n';
}
