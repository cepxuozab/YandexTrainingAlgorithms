#include <iostream>
#include <vector>
#include <algorithm>

struct Point
{
    int x{}, y{};
    auto operator <=>(Point const&) const = default;
};

auto operator >>(std::istream& in, Point& point) -> std::istream&
{
    return in >> point.x >> point.y;
}

auto check(Point points[]) -> bool
{
    bool is_flag = (points[1].x - points[0].x) == (points[3].x - points[2].x);
    is_flag = is_flag && (points[1].y - points[0].y) == (points[3].y - points[2].y);
    return is_flag;
}

auto main() -> int
{
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i)
    {
        Point points[4]{};
        for (auto& point : points)std::cin >> point;
        std::ranges::sort(points);
        check(points) ? puts("YES") : puts("NO");
    }
}
