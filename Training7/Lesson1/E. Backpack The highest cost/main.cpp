#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>


int main() {
  // Read input
  int N, M;
  std::cin >> N >> M;

  std::vector<int> m(N), c(N);
  for (auto &mass : m)
    std::cin >> mass;
  for (auto &cost : c)
    std::cin >> cost;

  // Initialize DP array
  std::vector<int> dp(M + 1, 0);

  // Process each item
  for (int i = 0; i < N; ++i) {
    // Iterate backwards to avoid overwriting
    for (int w = M; w >= m[i]; --w) {
      dp[w] = std::max(dp[w], dp[w - m[i]] + c[i]);
    }
  }

  // Find maximum value
  int max_value = *std::ranges::max_element(dp);
  std::cout << max_value << '\n';

  return 0;
}