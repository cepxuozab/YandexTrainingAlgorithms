#include <algorithm>
#include <cstdint>
#include <iostream>

auto main() -> int {  // NOLINT
  int n;
  std::cin >> n;
  int64_t b;
  std::cin >> b;
  int64_t ans = 0, res = 0;
  int64_t a = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> a;
    a += res;
    ans += a;
    res = std::max<int64_t>(0LL, a - b);
  }
  ans += res;
  std::cout << ans;
}
