#include <algorithm>
#include <iostream>
#include <vector>

static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());
    dp[2] = a[2] - a[1];
    dp[3] = a[3] - a[1];

    for (int i = 4; i <= n; i++) {
        dp[i] = std::min(dp[i - 1], dp[i - 2]) + a[i] - a[i - 1];
    }
    std::cout << dp.back();
}
