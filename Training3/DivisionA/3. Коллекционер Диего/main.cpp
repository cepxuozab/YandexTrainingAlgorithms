#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

int main() {
  if (freopen("input.txt", "r", stdin) == nullptr) {
    puts("Can't open input file");
    return 1;
  }
  int n;
  std::cin >> n;
  std::vector<int> cards(n);
  for (int &i : cards) {
    std::cin >> i;
  }
  std::ranges::sort(cards);
  const auto [first, last] = std::ranges::unique(cards);
  cards.erase(first, last);
  int k;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    int x;
    std::cin >> x;
    auto it = std::ranges::lower_bound(cards, x);
    std::cout << std::ranges::distance(cards.begin(), it) << std::endl;
  }
}
