#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>


auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, k;
  std::cin >> n >> k;

  std::vector<int> arr(n);
  std::unordered_map<int, int> freq;

  for (auto &x : arr) {
    std::cin >> x;
    ++freq[x];
  }

  std::unordered_set<int> visited;
  int removed = 0;

  for (auto &[v, cnt] : freq) {
    if (visited.contains(v))
      continue;
    int comp = k - v;

    if (comp == v) {
      if (cnt >= 2)
        removed += cnt - 1;
      visited.insert(v);
    } else {
      if (auto it = freq.find(comp); it != freq.end()) {
        removed += std::min(cnt, it->second);
        visited.insert(comp);
      }
      visited.insert(v);
    }
  }

  std::cout << removed << '\n';
  return 0;
}