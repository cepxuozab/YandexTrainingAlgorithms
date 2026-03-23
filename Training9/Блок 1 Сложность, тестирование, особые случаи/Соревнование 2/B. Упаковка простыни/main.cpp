#include <iostream>
#include <algorithm>


auto min_folds(long long size, long long target) -> long long
{
    if (size <= target) return 0;
    long long folds = 0;
    while (size > target)
    {
        size = (size + 1) / 2;
        folds++;
    }
    return folds;
}

auto main() -> int
{
    long long n, m, h, w;
    std::cin >> n >> m >> h >> w;
    long long ans = min_folds(n, h) + min_folds(m, w);
    ans = std::min(ans, min_folds(n, w) + min_folds(m, h));
    std::cout << ans << '\n';
    return 0;
}
