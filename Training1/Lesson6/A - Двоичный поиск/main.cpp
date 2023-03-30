#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

auto main() -> int
{
    int n, k;
    std::cin >> n >> k;
    std::vector<int> arr(n);
    for (int& i : arr) {
        std::cin >> i;
    }
    std::ranges::sort(arr);
    for (int i = 0, x; i < k && std::cin >> x; ++i) {
        std::ranges::binary_search(arr, x) ? puts("YES") : puts("NO");
    }
    return 0;
}
