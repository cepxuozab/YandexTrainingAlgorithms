#include <algorithm>
#include <cmath>
#include <iostream>

struct Point {
    long long x = 0;
    long long y = 0;
};

auto ReadPoint() -> Point;

auto Count(long long x, long long z1, long long z2, Point const& p1, Point const& p2) -> long long;

auto main() -> int
{
    Point leftdown = ReadPoint();
    Point rightup = ReadPoint();
    Point start = ReadPoint();
    long long radius;
    std::cin >> radius;
    long long k = Count(start.x, start.y - radius, start.y + radius, leftdown, rightup);
    long long y = radius;
    for (long long x = 1; x < radius; ++x) {
        while (x * x + y * y > radius * radius) {
            y--;
        }
        k = k + Count(start.x + x, start.y - y, start.y + y, leftdown, rightup)
            + Count(start.x - x, start.y - y, start.y + y, leftdown, rightup);
    }

    k += (Count(start.x + radius, start.y, start.y, leftdown, rightup) +
        Count(start.x - radius, start.y, start.y, leftdown, rightup));
    std::cout << k << std::endl;
    return 0;
}

auto ReadPoint() -> Point
{
    Point point;
    std::cin >> point.x >> point.y;
    return point;
}

auto Count(long long x, long long z1, long long z2, Point const& p1, Point const& p2) -> long long
{
    if ((x < p1.x || x > p2.x) || (z1 > p2.y || z2 < p1.y)) {
        return 0;
    }
    auto min = p1.y;
    if (z1 > p1.y) {
        min = z1;
    }
    auto max = p2.y;
    if (z2 < p2.y) {
        max = z2;
    }
    return max - min + 1;
}
