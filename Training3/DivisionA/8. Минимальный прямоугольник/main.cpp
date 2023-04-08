#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

struct Point {
  int x = 0;
  int y = 0;
};

int main() {
  if (freopen("input.txt", "r", stdin) == nullptr) {
    puts("Can't open input file");
    return 1;
  }
  int n;
  std::cin >> n;
  std::vector<Point> points(n);
  for (auto &[x, y] : points) {
    std::cin >> x >> y;
  }
  auto [x1, x2] = std::ranges::minmax_element(points, {}, &Point::x);
  auto [y1, y2] = std::ranges::minmax_element(points, {}, &Point::y);
  std::cout << x1->x << ' ' << y1->y << ' ' << x2->x << ' ' << y2->y << std::endl;
  return 0;
}
