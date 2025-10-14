#include <cstdint>
#include <iostream>
#include <vector>


auto tribonacci(int64_t n) {
  std::vector<int64_t> dp(n + 3);
  dp[0] = dp[1] = 0;
  dp[2] = 1;

  for (int i = 3; i < n + 3; i++)
    dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
  return dp.back();
}

auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t n;
  std::cin >> n;
  std::cout << tribonacci(n);
}