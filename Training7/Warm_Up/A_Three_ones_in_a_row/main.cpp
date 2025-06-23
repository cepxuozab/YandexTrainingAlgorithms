#include <iostream>
#include <print>
#include <vector>

auto three_ones_in_row(int n) -> long long {
    if (n <= 3)
        return n == 3 ? 1 : 0;
    std::vector<long long> dp{0, 0, 1};
    for (int i = 3; i < n; i++) {
        auto curr = (1LL << (i - 2)) + dp[i - 1] + dp[i - 2] + dp[i - 3];
        dp.push_back(curr);
    }
    return dp.back();
}

auto main() -> int {
    int n;
    std::cin >> n;
    std::cout<< (1LL << n) - three_ones_in_row(n);
    return EXIT_SUCCESS;
}