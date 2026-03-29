#include <iostream>
#include <algorithm>
#include <climits>

auto main() -> int
{
    int n;
    std::cin >> n;
    int max_left = INT_MIN, min_right = INT_MAX;
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        std::cin >> a >> b;
        max_left = std::max(max_left, a - b);
        min_right = std::min(min_right, a + b);
    }
    if (min_right < max_left)std::cout << -1;
    else std::cout << min_right;
}
