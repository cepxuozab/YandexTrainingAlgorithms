#include <algorithm>
#include <iostream>
#include <vector>


auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> bounds, rates;
    for (int i = 0; i < n; ++i) {
        int b, t;
        std::cin >> b >> t;
        bounds.push_back(b);
        rates.push_back(t);
    }

    int m;
    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        long long q;
        std::cin >> q;

        // Find last index where bounds[idx] < q
        auto idx = std::ranges::lower_bound(bounds, q) - bounds.begin() - 1;
        // Since bounds[0] = 0 and q >= 1, idx is always >= 0

        auto tax = q * rates[idx];
        std::cout << tax << '\n';
    }

    return 0;
}