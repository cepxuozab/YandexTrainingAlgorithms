#include <iostream>
#include <vector>
#include <cstdint>
#include <cmath>
#include <ranges>
#include <optional>
#include <algorithm>

using Double = double;

constexpr Double MAX_LEVEL = 1e12;
constexpr Double MIN_LEVEL = -1e12;
constexpr Double EPS = 1e-6;


enum class TYPE : uint8_t {
    OTHER = 0,
    PEAK = 1,
    DEEP = 2,
    LEFT_WALL = 3,
    RIGHT_WALL = 4
};

struct Point {
    Double x{}, y{};
    TYPE type = TYPE::OTHER;
};

auto ReadInput(int n) -> std::vector<Point> {
    std::vector<Point> points(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        int x{}, y{};
        std::cin >> x >> y;
        points[i].x = x, points[i].y = y;
    }
    return points;
}

template<typename Predicate, typename... Params>
auto UpperBound(Double l, Double r, Double eps, Predicate compare, Params...params) -> Double {
    while (std::abs(r - l) >= eps) {
        auto mid = (l + r) / 2;
        if (compare(mid, params...)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}

auto HighestMidPeak(int l, int r, std::vector<Point> const &points) {
    std::optional<int> ans = std::nullopt;
    auto max_y = MIN_LEVEL;
    for (int i: std::ranges::iota_view(l + 1, r)) {
        auto const point = points[i];
        if (point.type == TYPE::PEAK && point.y > max_y) {
            ans = i;
            max_y = point.y;
        }
    }
    return ans;
}

auto CalcValue(Point p1, Point p2, Double h) -> Double {
    if (h < std::min(p1.y, p2.y)) {
        return 0;
    }
    auto dx = std::abs(p2.x - p1.x);
    auto dy = std::abs(p2.y - p1.y);
    Double s = static_cast<double>(dx * dy) / 2;
    Double ans{};
    if (h >= std::max(p1.y, p2.y)) {
        ans = s + dx * (h - std::max(p1.y, p2.y));
    } else {
        auto k = 1.0 * (h - std::min(p1.y, p2.y)) / dy;
        ans = s * k * k;
    }
    return ans;
}

auto MinPeakOfTwo(int l, int r, std::vector<Point> const &points) -> Double {
    auto lhs = points[l], rhs = points[r];
    if (lhs.type == TYPE::LEFT_WALL && rhs.type == TYPE::RIGHT_WALL) {
        return MAX_LEVEL;
    }
    if (lhs.type == TYPE::LEFT_WALL) {
        return rhs.y;
    }
    if (rhs.type == TYPE::RIGHT_WALL) {
        return lhs.y;
    }
    return std::min(lhs.y, rhs.y);
}

auto Capacity(int l, int r, std::vector<Point> const &points) -> Double {
    auto h = MinPeakOfTwo(l, r, points);
    Double cap = 0;
    for (int i: std::ranges::iota_view(l, r)) {
        cap += CalcValue(points[i], points[i + 1], h);
    }
    return cap;
}

auto TryAccommodate(int l, int r, Double value, std::vector<Point> const &points) -> std::pair<bool, Double> {
    auto const &lhs = points[l], &rhs = points[r];
    if (lhs.type == TYPE::LEFT_WALL && rhs.type == TYPE::RIGHT_WALL) {
        return {true, 1e10};
    }
    auto cap = Capacity(l, r, points);
    return {cap >= value, cap};
}

auto Check(Double h, int l, int r, Double target_v, std::vector<Point> const &points) -> bool {
    Double v = 0;
    for (int i: std::ranges::iota_view(l, r)) {
        v += CalcValue(points[i], points[i + 1], h);
    }
    return v > target_v;
}

auto CalcH(int l, int r, Double target_v, std::vector<Point> const &points) -> Double {
    auto min_level = MAX_LEVEL;
    for (int i: std::ranges::iota_view(l, r + 1)) {
        min_level = std::min(min_level, points[i].y);
    }
    auto max_level = MinPeakOfTwo(l, r, points);
    auto h = UpperBound(min_level, max_level, EPS, Check, l, r, target_v, points);
    return h;
}

void FillExact(int l, int r, Double h, std::vector<Double> &water_levels) {
    while (l <= r) {
        water_levels[l] = std::max(h, water_levels[l]);
        l += 1;
    }
}

void
FillLevels(int l, int r, Double v, std::vector<Point> &points, std::vector<Double> &water_levels, Double extra_left,
           Double extra_right) {
    auto m_peak = HighestMidPeak(l, r, points);
    if (!m_peak.has_value()) {
        auto v1 = v + extra_left + extra_right;
        auto local_h = CalcH(l, r, v1, points);
        FillExact(l, r, local_h, water_levels);
        return;
    }
    auto mid_peak = m_peak.value();
    auto left_v = v * ((points[mid_peak].x - points[l].x) / (points[r].x - points[l].x));
    auto right_v = v - left_v;
    auto [left_ok, left_cap] = TryAccommodate(l, mid_peak, left_v + extra_left, points);
    auto [right_ok, right_cap] = TryAccommodate(mid_peak, r, right_v + extra_right, points);
    if (left_ok && right_ok) {
        FillLevels(l, mid_peak, left_v, points, water_levels, extra_left, 0);
        FillLevels(mid_peak, r, right_v, points, water_levels, 0, extra_right);
        return;
    } else if (left_ok) {
        auto extra_right1 = right_v + extra_right - right_cap;
        if (left_cap > left_v + extra_left + extra_right1) {
            FillExact(mid_peak, r, MinPeakOfTwo(mid_peak, r, points), water_levels);
            FillLevels(l, mid_peak, left_v, points, water_levels, extra_left, extra_right1);
            return;
        }
    } else if (right_ok) {
        auto extra_left1 = left_v + extra_left - left_cap;
        if (right_cap > right_v + extra_left1 + extra_right) {
            FillExact(l, mid_peak, MinPeakOfTwo(l, mid_peak, points), water_levels);
            FillLevels(mid_peak, r, right_v, points, water_levels, extra_left1, extra_right);
            return;
        }
    }
    auto local_h1 = CalcH(l, r, v + extra_left + extra_right, points);
    FillExact(l, r, local_h1, water_levels);
    return;
}

auto main() -> int {
    int n;
    Double h;
    std::cin >> n >> h;
    auto points = ReadInput(n);
    std::ranges::sort(points, {}, &Point::x);
    points.front().type = TYPE::LEFT_WALL;
    for (int i: std::ranges::iota_view(1, n)) {
        if (points[i - 1].y > points[i].y and points[i].y < points[i + 1].y) {
            points[i].type = TYPE::DEEP;
        } else if (points[i - 1].y < points[i].y and points[i].y > points[i + 1].y) {
            points[i].type = TYPE::PEAK;
        }
    }
    points.back().type = TYPE::RIGHT_WALL;
    std::vector<Double> water_levels(n + 1, MIN_LEVEL);
    FillLevels(0, n, h * (points.back().x - points[0].x), points, water_levels, 0, 0);
    auto ans = water_levels[0] - points[0].y;
    for (int i: std::ranges::iota_view(1, n + 1)) {
        ans = std::max(ans, water_levels[i] - points[i].y);
    }
    std::cout << ans;
}
