#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <vector>

constexpr int SIZE = 4;

struct Point {
    int x = 0;
    int y = 0;
};

auto Read(int n) -> std::vector<Point>;

void Print(std::vector<Point> const& points);

struct Rectangle {
    std::array<int, SIZE> rect {};
    Rectangle() = default;
    Rectangle(Rectangle const& other) = default;
    Rectangle(std::initializer_list<int> list);
};

auto Extend(Rectangle const& rect, int d) -> Rectangle;

auto Intersect(Rectangle const& lhs, Rectangle const& rhs) -> Rectangle;

auto MakePath(std::vector<Point> const& points, int t, int d) -> Rectangle;

auto FinalPositions(Rectangle const& rectangle) -> std::vector<Point>;

void Solve()
{
    int t;
    int n;
    int d;
    std::cin >> t >> d >> n;
    std::vector<Point> points = Read(n);
    Rectangle rect = MakePath(points, t, d);
    Print(FinalPositions(rect));
}

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    Solve();
    return 0;
}

void Print(std::vector<Point> const& points)
{
    std::cout << points.size() << '\n';
    for (auto const& [x, y] : points) {
        std::cout << x << ' ' << y << '\n';
    }
}

auto Read(int n) -> std::vector<Point>
{
    std::vector<Point> points(n);
    for (auto& [x, y] : points) {
        std::cin >> x >> y;
    }
    return points;
}

Rectangle::Rectangle(std::initializer_list<int> list)
{
    auto begin = list.begin();
    for (int i = 0; i < SIZE; ++i) {
        rect[i] = *begin++;
    }
}

auto Extend(Rectangle const& rect, int d) -> Rectangle
{
    Rectangle ans(rect);
    for (int i = 0; i < SIZE; ++i) {
        ans.rect[i] += (i % 2 == 0) ? -d : d;
    }
    return ans;
}

auto Intersect(Rectangle const& lhs, Rectangle const& rhs) -> Rectangle
{
    Rectangle ans;
    for (int i = 0; i < SIZE; ++i) {
        ans.rect[i] = (i % 2 == 0)
            ? std::max(lhs.rect[i], rhs.rect[i])
            : std::min(lhs.rect[i], rhs.rect[i]);
    }
    return ans;
}

auto MakePath(std::vector<Point> const& points, int t, int d) -> Rectangle
{
    Rectangle rect;
    for (auto const& [navX, navY] : points) {
        rect = Extend(rect, t);
        int plus = navX + navY;
        int minus = navX - navY;
        rect = Intersect(rect, Extend(Rectangle({ plus, plus, minus, minus }), d));
    }
    return rect;
}

auto FinalPositions(Rectangle const& rectangle) -> std::vector<Point>
{
    std::vector<Point> points;
    for (int xPlusY = rectangle.rect[0]; xPlusY <= rectangle.rect[1]; ++xPlusY) {
        for (int xMinusY = rectangle.rect[2]; xMinusY <= rectangle.rect[3]; ++xMinusY) {
            if ((xPlusY + xMinusY) % 2 == 0) {
                int x = (xPlusY + xMinusY) / 2;
                int y = xPlusY - x;
                points.push_back({ x, y });
            }
        }
    }
    return points;
}
