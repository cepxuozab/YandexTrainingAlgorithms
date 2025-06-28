#include <algorithm>
#include <format>
#include <iostream>
#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <vector>


struct Item {
  std::string name;
  int m;
};

auto read_input() {
  int n, d;
  std::cin >> n >> d;
  std::vector<Item> items(n);

  for (auto &item : items) {
    std::cin >> item.name >> item.m;
  }

  return std::tuple{n, d, std::move(items)};
}

std::string asceticism(int d, std::vector<Item> &items) {
  // Sort items by m using ranges
  std::ranges::sort(items, {}, &Item::m);

  const int max_mi = items.back().m;
  std::vector<std::optional<int>> dp(max_mi + 1);
  dp[0] = 0;

  // Process items using ranges
  for (const auto &item : items) {
    if (item.m <= d) {
      // Backward iteration using views
      for (int mi :
           std::views::iota(0, max_mi - item.m + 1) | std::views::reverse) {
        if (!dp[mi])
          continue;
        const int next = mi + item.m;
        dp[next] = dp[next] ? std::min(*dp[next], *dp[mi] + 1) : *dp[mi] + 1;
      }
    } else {
      // Forward iteration for special case
      for (int mi : std::views::iota(item.m - d, item.m)) {
        if (mi < 0 || mi > max_mi || !dp[mi])
          continue;
        dp[item.m] =
            dp[item.m] ? std::min(*dp[item.m], *dp[mi] + 1) : *dp[mi] + 1;
      }

      if (!dp[item.m])
        continue;

      // Backward iteration for remaining sums
      for (int mi :
           std::views::iota(0, max_mi - item.m + 1) | std::views::reverse) {
        if (mi == item.m || !dp[mi])
          continue;
        const int next = mi + item.m;
        dp[next] = dp[next] ? std::min(*dp[next], *dp[mi] + *dp[item.m])
                            : *dp[mi] + *dp[item.m];
      }
    }
  }

  // Filter and process answer using ranges
  auto valid_items = items | std::views::filter([&dp](const Item &item) {
                       return dp[item.m].has_value();
                     });

  // Calculate total count
  const int total_count = std::accumulate(
      valid_items.begin(), valid_items.end(), 0,
      [&dp](int sum, const Item &item) { return sum + *dp[item.m]; });

  // Sort names and format output
  std::vector<std::string> names;
  std::ranges::transform(valid_items, std::back_inserter(names), &Item::name);
  std::ranges::sort(names);

  // Build output string with format
  std::string output = std::format("{} {}\n", names.size(), total_count);
  for (const auto &name : names) {
    output += std::format("{}\n", name);
  }

  return output;
}

int main() {
  auto [n, d, items] = read_input();
  std::cout << asceticism(d, items);
  return 0;
}