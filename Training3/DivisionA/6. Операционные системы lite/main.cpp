#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
int main() {
  int n, m;
  std::cin >> n >> m;
  std::set<std::pair<int, int>> os;
  for (int i = 0; i < m; ++i) {
    int a, b;
    std::cin >> a >> b;
    auto lower = os.lower_bound({a, b});
    if (lower != os.begin()) {
      auto [c, d] = *std::prev(lower);
      if (a <= d && c <= b) {
        os.erase(std::prev(lower));
      }
    }
    for (auto it = lower; it != os.end();) {
      auto [c, d] = *it;
      if (a <= d && c <= b) {
        it = os.erase(it);
      } else {
        if (c > b) {
          break;
        } else {
          it++;
        }
      }
    }
    os.emplace(a, b);
  }
  std::cout << os.size();
  return 0;
}
