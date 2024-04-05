#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<int> a, b;
    int a_sum = 0, b_sum = 0;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        a_sum += x, b_sum += y;
        a.push_back(x), b.push_back(y);
    }
    int const t_max = std::max(a_sum, b_sum);
    int const INF = t_max + 1;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(t_max + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i < n + 1; ++i) {
        for (int t_first_courier = 0; t_first_courier < t_max + 1; ++t_first_courier) {
            dp[i][t_first_courier] = dp[i - 1][t_first_courier] + b[i - 1];
            if (t_first_courier >= a[i - 1]) {
                dp[i][t_first_courier] = std::min(dp[i][t_first_courier], dp[i - 1][t_first_courier - a[i - 1]]);
            }
        }
    }
    std::vector<int> answer;
    for(int i=0;i<(int)dp[n].size();++i){
        answer.push_back(std::max(i,dp[n][i]));
    }
    auto it = std::min_element(answer.begin(),answer.end());
    int t_first_courier = it-answer.begin();
    int64_t t_second_courier = dp[n][t_first_courier];

    std::vector<int> path;
    for (int i = n - 1; i >= 0; --i) {
        int step = -1;
        if (dp[i][t_first_courier] + b[i] == t_second_courier) {
            t_second_courier -= b[i];
            step = 2;
        } else {
            t_first_courier -= a[i];
            step = 1;
        }
        path.push_back(step);
    }
    std::ranges::reverse(path);
    for (int i: path)std::cout << i << ' ';
}