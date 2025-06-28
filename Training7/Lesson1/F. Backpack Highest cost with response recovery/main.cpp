#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

int main() {
    int n, M;
    std::cin >> n >> M;

    std::vector<int> weight(n + 1);
    std::vector<int> cost(n + 1);

    for (int i = 1; i <= n; ++i)
        std::cin >> weight[i];

    for (int i = 1; i <= n; ++i)
        std::cin >> cost[i];

    // dp[i][j] — максимальная стоимость, если рассматривать первые i предметов и вес j
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(M + 1));
    std::vector<std::vector<bool>> taken(n + 1, std::vector<bool>(M + 1));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= M; ++w) {
            if (w >= weight[i]) {
                int take = dp[i - 1][w - weight[i]] + cost[i];
                if (take > dp[i - 1][w]) {
                    dp[i][w] = take;
                    taken[i][w] = true;
                } else {
                    dp[i][w] = dp[i - 1][w];
                }
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Восстановление ответа
    std::vector<int> result;
    int w = M;
    for (int i = n; i >= 1; --i) {
        if (taken[i][w]) {
            result.push_back(i);
            w -= weight[i];
        }
    }

    std::ranges::sort(result);

    for (int idx : result)
        std::cout << idx << '\n';

    return 0;
}
