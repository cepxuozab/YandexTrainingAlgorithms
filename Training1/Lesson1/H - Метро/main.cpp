#include <algorithm>
#include <iostream>

auto main() -> int
{
    int a;
    int b;
    int n;
    int m;
    std::cin >> a >> b >> n >> m;

    int firstMin = n + (n - 1) * a;
    int firstMax = firstMin + 2 * a;
    int secondMin = m + (m - 1) * b;
    int secondMax = secondMin + 2 * b;

    if ((firstMin > secondMax) || (secondMin > firstMax)) {
        std::cout << -1 << std::endl;
    } else {
        int tMin = std::max(firstMin, secondMin);
        int tMax = std::min(firstMax, secondMax);
        std::cout << tMin << ' ' << tMax << std::endl;
    }

    return 0;
}
