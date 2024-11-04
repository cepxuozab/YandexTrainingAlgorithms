#include <cstdint>
#include <iostream>
#include <vector>

auto main() -> int {  // NOLINT

    int n;
    int64_t c;
    std::cin >> n >> c;
    std::string s;
    std::cin >> s;

    std::vector<int64_t> prefix_a(n, 0);
    std::vector<int64_t> prefix_b(n, 0);
    std::vector<int64_t> sum_b_a(n, 0);

    for (int i = 0; i < n; ++i) {
        prefix_a[i] = (i > 0 ? prefix_a[i - 1] : 0) + (s[i] == 'a' ? 1 : 0);
        prefix_b[i] = (i > 0 ? prefix_b[i - 1] : 0) + (s[i] == 'b' ? 1 : 0);
        sum_b_a[i] = (i > 0 ? sum_b_a[i - 1] : 0) + (s[i] == 'a' ? prefix_b[i] : 0);
    }

    int left = 0;
    int max_len = 0;

    for (int right = 0; right < n; ++right) {
        auto rudeness = prefix_b[right] * (prefix_a[right] - (left > 0 ? prefix_a[left - 1] : 0))
            - (sum_b_a[right] - (left > 0 ? sum_b_a[left - 1] : 0));

        while (left <= right && rudeness > c) {
            left += 1;
            if (left > right) {
                break;
            }
            rudeness = prefix_b[right] * (prefix_a[right] - (left > 0 ? prefix_a[left - 1] : 0))
                - (sum_b_a[right] - (left > 0 ? sum_b_a[left - 1] : 0));
        }

        if (rudeness <= c) {
            max_len = std::max(max_len, (right - left + 1));
        }
    }

    std::cout << max_len;
}