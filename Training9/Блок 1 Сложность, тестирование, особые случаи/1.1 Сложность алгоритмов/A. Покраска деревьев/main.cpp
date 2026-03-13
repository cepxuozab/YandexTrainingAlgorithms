#include <iostream>
#include <algorithm>

auto main() -> int
{
    int p, v;
    std::cin >> p >> v;
    int q, m;
    std::cin >> q >> m;
    auto minv = p - v, maxv = p + v;
    auto minm = q - m, maxm = q + m;
    if (std::max(minv, minm) <= std::min(maxv, maxm))
        std::cout << std::max(maxv, maxm) - std::min(minv, minm) + 1;
    else
        std::cout << (maxv - minv + 1) + (maxm - minm + 1);
}
