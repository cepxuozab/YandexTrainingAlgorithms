#include <algorithm>
#include <iostream>
#include <vector>


int main() {
  int m;
  std::cin >> m;
  std::vector<int> times(31);

  for (int &time : times) {
    std::cin >> time;
  }

  for (size_t i = 1; i < times.size(); ++i) {
    times[i] = std::min(std::max(times[i], times[i - 1] * 2), 1000000000);
  }

  int i =
      distance(times.begin(), std::lower_bound(times.begin(), times.end(), m));
  int result_up = times[i];
  int result = 0;
  --i;

  while (m > 0 && i >= 0) {
    const int &time = times[i];

    if (m >= time) {
      result += 1 << i;
      m -= times[i];
    }

    --i;
  }

  if (m > 0) {
    ++result;
  }

  std::cout << std::min(result, result_up) << '\n';

  return 0;
}