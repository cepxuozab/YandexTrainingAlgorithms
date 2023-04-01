#include <iostream>
#include <cmath>

struct Point {
    double x{};
    double y{};
};

auto operator>>(std::istream& input, Point& point)->std::istream&;

constexpr auto AlmostEqual(double f1, double f2) -> bool;

auto IsSameLine(Point p1, Point p2, Point p3) -> bool;

auto IsParallel(Point a1, Point a2, Point b1, Point b2) -> bool;

auto IsParallelogram(Point a, Point b, Point c, Point d) -> bool;

int main()
{
    int n; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        Point a, b, c, d;
        std::cin >> a >> b >> c >> d;
        IsParallelogram(a, b, c, d) ? puts("YES") : puts("NO");
    }
}

auto operator>>(std::istream& input, Point& point) -> std::istream&
{
    return input >> point.x >> point.y;
}

constexpr auto AlmostEqual(double f1, double f2) -> bool
{
    constexpr double PRESISION{ 1e-11 };
    return std::abs(f1 - f2) < PRESISION;
}

auto IsSameLine(Point p1, Point p2, Point p3) -> bool
{
    return AlmostEqual(p3.x * (p1.y - p2.y)
        + p3.y * (p2.x - p1.x)
        + (p1.x * p2.y - p2.x * p1.y),
        0.0);
}

auto IsParallel(Point a1, Point a2, Point b1, Point b2) -> bool
{
    double dax = a1.x - a2.x, dbx = b1.x - b2.x;
    if (AlmostEqual(dax, 0.0) || AlmostEqual(dbx, 0.0)) {
        return AlmostEqual(dax, dbx);
    }
    double k1 = (a1.y - a2.y) / dax, k2 = (b1.y - b2.y) / dbx;
    return AlmostEqual(k1, k2);
}

auto IsParallelogram(Point a, Point b, Point c, Point d) -> bool
{
    if (IsSameLine(a, b, c) && IsSameLine(d, c, d))
        return false;

    return (IsParallel(a, b, c, d) && IsParallel(b, c, a, d))
        || (IsParallel(a, b, c, d) && IsParallel(a, c, b, d))
        || (IsParallel(b, c, a, d) && IsParallel(a, c, b, d));
}
