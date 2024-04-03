#include <iostream>
#include <vector>

struct Point {
    double x{}, y{};
    double v{};
};
constexpr double EPS = 0.000001;

auto PointInCircle(Point center, double radius, Point point) -> bool {

    return (point.x - center.x) * (point.x - center.x) + (point.y - center.y) * (point.y - center.y)
           - radius * radius < EPS;
}

auto CheckRect(Point pll, double radius, Point pru, double time,
               std::vector<Point> const &points) -> std::pair<bool, Point> {
    Point tmp = pll;
    tmp.y = pru.y;
    Point tmp1 = pru;
    tmp1.y = pll.y;
    if (!PointInCircle(Point{}, radius, pll) && !PointInCircle(Point{}, radius, pru)
        && !PointInCircle(Point{}, radius, tmp) && !PointInCircle(Point{}, radius, tmp1)) {
        return {false, {}};
    }
    if (pru.x - pll.x < EPS) {
        return std::pair{true, Point{(pll.x + pru.x) / 2, (pll.y + pru.y) / 2, 0}};
    }
    for (auto const &point: points) {
        if (PointInCircle(point, point.v * time, pll) && PointInCircle(point, point.v * time, pru)
            && PointInCircle(point, point.v * time, tmp) && PointInCircle(point, point.v * time, tmp1)) {
            return {false, Point{}};
        }
    }
    Point cnt{(pll.x + pru.x) / 2, (pll.y + pru.y) / 2};
    std::vector<Point> xs{pll, cnt, pru};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            //xs[i], ys[j], xs[i + 1], ys[j + 1], time
            Point p{xs[i].x, xs[j].y, 0};
            Point p1{xs[i + 1].x, xs[j + 1].y, 0};
            auto quarter = CheckRect(p, radius, p1, time, points);
            if (quarter.first) {
                return quarter;
            }
        }
    }
    return {false, {}};
}

auto Check(double radius, std::vector<Point> const &points, double time) {
    Point ll{-radius, 0}, ru{radius, radius};
    return CheckRect(ll, radius, ru, time, points);
}

auto main() -> int {
    double radius;
    int n;
    std::cin >> radius >> n;
    std::vector<Point> points(n);
    for (auto &[x, y, v]: points) {
        std::cin >> x >> y >> v;
    }
    double l = 0, r = 4 * radius;
    while (r - l > EPS) {
        auto mid = (l + r) / 2;
        if (Check(radius, points, mid).first) {
            l = mid;
        } else {
            r = mid;
        }
    }
    auto now = Check(radius, points, l);
    std::cout << l << '\n';
    auto point = now.second;
    std::cout << point.x << ' ' << point.y;

}
