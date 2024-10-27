#include <algorithm>
#include <iostream>
#include <string>

using namespace std::literals;
struct Point {
    int x{}, y{};
};
auto operator>>(std::istream& in, Point& point) -> std::istream& {
    return in >> point.x >> point.y;
}

auto FindDirection(Point bottom_left, Point upper_right, Point point) -> std::string {
    if (point.y > upper_right.y) {
        if (point.x < bottom_left.x) return "NW"s;
        if (point.x > upper_right.x) return "NE"s;
        return "N"s;
    }
    if (point.y >= bottom_left.y) {
        if (point.x < bottom_left.x) return "W"s;
        return "E"s;
    }
    if (point.x < bottom_left.x) return "SW"s;
    if (point.x > upper_right.x) return "SE"s;
    return "S"s;
}
auto main() -> int {  // NOLINT
    Point bottom_left, upper_right, point;
    std::cin >> bottom_left >> upper_right >> point;
    std::cout << FindDirection(bottom_left, upper_right, point);
}