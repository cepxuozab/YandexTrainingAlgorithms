#include <cstdint>
#include <iostream>
#include <vector>

auto main() -> int { // NOLINT
  int64_t const mod = 1000000007;
  int n;
  std::cin >> n;
  std::vector<int64_t> arr(n);
  for (int64_t &a : arr)
    std::cin >> a;
  std::vector<int64_t> pre(n);
  pre[0] = arr[0];
  for (int i = 1; i < n; ++i) {
    pre[i] = (pre[i - 1] % mod + arr[i] + mod) % mod;
  }
  int64_t sum = 0;
  for (int i = 1; i < n - 1; i++) {
    auto left =
        (mod + ((arr[i] % mod) * (pre[n - 1] - pre[i]) % mod) % mod) % mod;
    left = (((pre[i - 1] % mod) * (left % mod)) % mod + mod) % mod;
    sum = (mod + sum + left) % mod;
  }
  std::cout << sum % mod;
}
