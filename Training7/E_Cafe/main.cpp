#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

auto main() -> int {
  int n;
  std::cin >> n;
  std::vector<int> costs(n);
  for (auto &cost : costs) {
    std::cin >> cost;
  }
  const int MAX_COST = 100;
  std::vector<std::vector<int64_t>> dp(n + 1,
                                       std::vector<int64_t>(n + 1, INT_MAX));
  dp[0][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      if (j == 0) {
        dp[i][j] = std::min(costs[i - 1] + dp[i - 1][j], dp[i - 1][j + 1]);
      } else {
        if (costs[i - 1] > MAX_COST) {
          if (j != n) {
            dp[i][j] =
                std::min(dp[i - 1][j - 1] + costs[i - 1], dp[i - 1][j + 1]);
          } else {
            dp[i][j] = dp[i - 1][j - 1] + costs[i - 1];
          }
        } else {
          if (j != n) {
            dp[i][j] = std::min(dp[i - 1][j] + costs[i - 1], dp[i - 1][j + 1]);
          } else {
            dp[i][j] = dp[i - 1][j] + costs[i - 1];
          }
        }
      }
    }
  }

  int64_t res = INT_MAX;
  std::vector<int> dayOfCoupon;
  int K1 = -1;
  int K2 = 0;
  for (int i = 0; i <= n; i++) {
    if (res >= dp[n][i]) {
      res = dp[n][i];
      K1 = i;
    }
    res = std::min(res, dp[n][i]);
  }
  int j = K1;
  int i = n;
  while (i - 1 >= 0 && j < n) {
    if (dp[i - 1][j + 1] == dp[i][j]) {
      dayOfCoupon.push_back(i);
      i--;
      j++;
      K2++;
    } else if (dp[i - 1][j] + costs[i - 1] == dp[i][j]) {
      i--;
    } else if (j - 1 >= 0 && dp[i - 1][j - 1] + costs[i - 1] == dp[i][j]) {
      i--;
      j--;
    }
  }
  std::sort(dayOfCoupon.begin(), dayOfCoupon.end());
  std::cout << res << std::endl;
  std::cout << K1 << ' ' << K2 << std::endl;
  for (int d : dayOfCoupon) {
    std::cout << d << ' ';
  }
}