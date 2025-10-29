#include <iostream>

auto main() -> int {
    int a, b, s;
    std::cin >> a >> b >> s;
    auto binary_search = [&](int left, int right) -> int {
        while (left < right) {
            long long middle = 1LL * left + (right - left) / 2;
            if (s <= (middle - a) * (middle - b))right = middle;
            else left = middle + 1;
        }
        return left;
    };
    auto left_bound = a < b ? b : a;
    auto right_bound = s + left_bound;
    auto ans = binary_search(left_bound, right_bound);
    if (s != (ans - a) * (ans - b)) ans = -1;
    std::cout << ans;
}