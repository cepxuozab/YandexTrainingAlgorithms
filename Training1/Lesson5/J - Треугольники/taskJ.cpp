#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
    int64_t x;
    int64_t y;
    [[nodiscard]] auto dist() const -> int64_t;
    [[nodiscard]] auto dir() const -> int;
};

auto operator==(Point const& lhs, Point const& rhs) -> bool;

auto operator!=(Point const& lhs, Point const& rhs) -> bool;

auto vectorise(Point const& left, Point const& right) -> int64_t;

auto operator<(Point const& left, Point const& right) -> bool;

auto distance(Point const& lhs, Point const& rhs) -> int64_t;

auto Read(int n) -> std::vector<Point>;

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<Point> p0 = Read(n);
    int isoScelesCount = 0;
    std::vector<Point> p(n - 1);
    for (int centerI = 0; centerI < n; ++centerI) {
        std::copy_if(p0.begin(), p0.end(), p.begin(),
            [&](Point const& point) { return point != p0[centerI]; });
        Point center = p0[centerI];
        for (auto& [x, y] : p) {
            x -= center.x;
            y -= center.y;
        }
        std::sort(p.begin(), p.end());
        int groupFirst = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (i == n - 2 || p[i].dist() != p[i + 1].dist()) {
                int afterGroup = i + 1;
                int groupSize = afterGroup - groupFirst;
                int nDegen = 0;
                int second = groupFirst;
                for (int first = groupFirst; first < afterGroup; ++first) {
                    if (p[first].dir() > 2) {
                        break;
                    }
                    if (second <= first) {
                        second = first + 1;
                    }

                    while (second < afterGroup
                        && vectorise(p[first], p[second]) > 0) {
                        second++;
                    }
                    if (second < afterGroup
                        && vectorise(p[first], p[second]) == 0) {
                        nDegen++;
                    }
                }
                isoScelesCount += groupSize * (groupSize - 1) / 2 - nDegen;
                groupFirst = afterGroup;
            }
        }
    }
    std::cout << isoScelesCount << std::endl;
}

auto Point::dist() const -> int64_t
{
    return x * x + y * y;
}

auto Point::dir() const -> int
{
    if (y == 0) {
        return x > 0 ? 1 : 3;
    } else if (y > 0) {
        return 2;
    } else {
        return 4;
    }
}

auto operator==(Point const& lhs, Point const& rhs) -> bool
{
    return std::pair(lhs.x, lhs.y) == std::pair(rhs.x, rhs.y);
}

auto operator!=(Point const& lhs, Point const& rhs) -> bool
{
    return !(lhs == rhs);
}

auto vectorise(Point const& left, Point const& right) -> int64_t
{
    return left.x * right.y - right.x * left.y;
}

auto operator<(Point const& left, Point const& right) -> bool
{
    int64_t d2L = left.dist();
    int64_t d2R = right.dist();
    if (d2L != d2R) {
        return d2L < d2R;
    }
    int dirL = left.dir();
    int dirR = right.dir();
    if (dirL != dirR) {
        return dirL < dirR;
    }
    return vectorise(left, right) > 0;
}

auto distance(Point const& lhs, Point const& rhs) -> int64_t
{
    int64_t dx = lhs.x - rhs.x;
    int64_t dy = lhs.y - rhs.y;
    return dx * dx + dy * dy;
}

auto Read(int n) -> std::vector<Point>
{
    std::vector<Point> arr(n);
    for (auto& [x, y] : arr) {
        std::cin >> x >> y;
    }
    return arr;
}
