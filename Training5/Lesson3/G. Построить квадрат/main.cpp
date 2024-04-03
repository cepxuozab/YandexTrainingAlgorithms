#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Vector2 {
    int x;
    int y;

    auto operator==(const Vector2& other) const -> bool {
        return x == other.x && y == other.y;
    }
};

auto operator-(Vector2 const& lhv, Vector2 const& rhv) -> Vector2 {
    return Vector2{lhv.x - rhv.x, lhv.y - rhv.y};
}

auto operator+(Vector2 const& lhv, Vector2 const& rhv) -> Vector2 {
    return Vector2{rhv.x + lhv.x, rhv.y + lhv.y};
}

auto operator*(Vector2 const& lhv, Vector2 const& rhv) -> int64_t {
    return static_cast<int64_t>(lhv.x) * static_cast<int64_t>(rhv.x)
        + static_cast<int64_t>(lhv.y) * static_cast<int64_t>(rhv.y);
}

struct PointHash {
    auto operator()(const Vector2& p) const noexcept -> size_t {
        size_t h1 = hash<int>{}(p.x);
        size_t h2 = hash<int>{}(p.y);
        return h1 ^ (h2 << 1);
    }
};

void processToOneSide(const Vector2& point1, const Vector2& point2, const Vector2& diff,
                      size_t& maxCount, vector<Vector2>& rect,
                      const unordered_set<Vector2, PointHash>& points) {
    vector<Vector2> result;
    result.reserve(4);
    result.push_back(point1);
    result.push_back(point2);
    size_t count = 2;
    Vector2 point3 = point2 + diff;
    if (points.contains(point3)) {
        ++count;
        result.push_back(point3);
    }
    Vector2 point4 = point1 + diff;
    if (points.contains(point4)) {
        ++count;
        result.push_back(point4);
    }
    if (maxCount < count) {
        maxCount = count;
        rect.swap(result);
    }
}

auto process(const Vector2& point1, const Vector2& point2, size_t& maxCount, vector<Vector2>& rect,
             const unordered_set<Vector2, PointHash>& points) -> bool {
    Vector2 a = point2 - point1;
    Vector2 b1{a.y, -a.x};
    Vector2 b2{-a.y, a.x};

    processToOneSide(point1, point2, b1, maxCount, rect, points);
    processToOneSide(point1, point2, b2, maxCount, rect, points);

    return maxCount == 4;
}

auto makeRectFrom1Point(const vector<Vector2>& rect) -> vector<Vector2> {
    vector<Vector2> result;
    Vector2 point = rect.at(0);
    int delta = 1;
    result.push_back(Vector2{point.x + delta, point.y});
    result.push_back(Vector2{point.x + delta, point.y + delta});
    result.push_back(Vector2{point.x, point.y + delta});
    return result;
}

auto makeRectFrom2Points(const vector<Vector2>& rect) -> vector<Vector2> {
    vector<Vector2> result;
    Vector2 point1 = rect.at(0);
    Vector2 point2 = rect.at(1);
    Vector2 a = point2 - point1;
    Vector2 b1{a.y, -a.x};
    Vector2 point3 = point1 + b1;
    Vector2 point4 = point2 + b1;
    result.push_back(point3);
    result.push_back(point4);
    return result;
}

auto makeRectFrom3Points(const vector<Vector2>& rect) -> vector<Vector2> {
    vector<Vector2> result;
    Vector2 point1 = rect.at(0);
    Vector2 point2 = rect.at(1);
    Vector2 point3 = rect.at(2);

    Vector2 p1p2 = point2 - point1;
    Vector2 p1p3 = point3 - point1;
    Vector2 p2p3 = point3 - point2;
    if (p1p2 * p1p3 == 0) {
        Vector2 point = point3 + p1p2;
        result.push_back(point);
    } else if (p1p2 * p2p3 == 0) {
        Vector2 point = point1 + p2p3;
        result.push_back(point);
    } else {
        Vector2 point = point1 + (point2 - point3);
        result.push_back(point);
    }

    return result;
}

auto makeRect(const vector<Vector2>& rect) -> vector<Vector2> {
    vector<Vector2> result;
    if (rect.size() == 1) {
        return makeRectFrom1Point(rect);
    } else if (rect.size() == 2) {
        return makeRectFrom2Points(rect);
    } else if (rect.size() == 3) {
        return makeRectFrom3Points(rect);
    }
    return result;
}

auto main() -> int {
    int n;
    cin >> n;
    unordered_set<Vector2, PointHash> points;
    size_t maxCount = 0;
    vector<Vector2> rect;
    rect.reserve(4);
    bool found = false;
    for (int i = 0; i < n; ++i) {
        int x;
        int y;
        cin >> x >> y;
        Vector2 newPoint{x, y};
        for (auto& point : points) {
            found = process(newPoint, point, maxCount, rect, points);
            if (found) {
                break;
            }
        }
        if (found) {
            break;
        }
        points.insert(newPoint);
    }
    if (rect.empty()) {
        rect.push_back(*points.begin());
    }

    rect = makeRect(rect);

    cout << rect.size();
    for (auto& p : rect) {
        cout << '\n' << p.x << " " << p.y;
    }
}
