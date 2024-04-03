#include <algorithm>
#include <iostream>
#include <vector>


[[maybe_unused]] static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct Point {
    int x{};
    int y{};
    auto operator<=>(Point const &other) const = default;
};

std::ostream &operator<<(std::ostream &out, Point const &point) { return out << point.x << ' ' << point.y; }

auto MinimumRectangle(std::vector<Point> const &points) -> std::pair<Point, Point> {
    auto [min_x, max_x] = std::ranges::minmax(points, {}, &Point::x);
    auto [min_y, max_y] = std::ranges::minmax(points, {}, &Point::y);
    return {{min_x.x, min_y.y}, {max_x.x, max_y.y}};
}

int main() {
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (auto &[x, y]: points) {
        std::cin >> x >> y;
    }
    auto [left_down, right_up] = MinimumRectangle(points);
    std::cout << left_down << ' ' << right_up;
}
