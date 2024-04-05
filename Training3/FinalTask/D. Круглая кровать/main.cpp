#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdint>
#include <cmath>

struct Point {
    int x{};
    int y{};

    Point() = default;

    Point(int a, int b) : x(a), y(b) {}

    auto operator<=>(Point const &) const = default;
};

void Dfs(std::vector<std::vector<int>> const &graph, std::vector<bool> &visited, int now) {
    if (visited[now]) {
        return;
    }
    visited[now] = true;
    for (int v: graph[now]) {
        if (!visited[v]) {
            Dfs(graph, visited, v);
        }
    }
}

auto Distance(Point const &lhs, Point const &rhs) -> int64_t {
    int64_t dx = lhs.x - rhs.x;
    dx *= dx;
    int64_t dy = lhs.y - rhs.y;
    dy *= dy;
    return dx + dy;
}

auto Check(std::vector<std::vector<int>> const &graph, std::vector<int> const &points_l,
           std::vector<int> const &points_r) -> bool {
    std::vector<bool> visited(graph.size(), false);
    for (int v: points_l) {
        if (!visited[v]) {
            Dfs(graph, visited, v);
        }
    }
    for (int v: points_r) {
        if (visited[v]) {
            return false;
        }
    }
    return true;
}

auto FormGraph(std::vector<Point> const &points, int64_t max_distance) -> std::vector<std::vector<int>> {
    int const n = static_cast<int>(points.size());
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (Distance(points[i], points[j]) < max_distance) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }
    return graph;
}

auto BinSearch(std::vector<Point> const &points, std::vector<int64_t> const &distances, int begin, int end,
               std::vector<int> const &points_l,
               std::vector<int> const &points_r) {
    int mid = (begin + end) / 2;
    auto dist_mid = distances[mid];
    auto graph = FormGraph(points, dist_mid);
    auto checked = Check(graph, points_l, points_r);
    if (checked) {
        if (mid + 1 == static_cast<int>(distances.size())) {
            return dist_mid;
        }
        graph = FormGraph(points, distances[mid + 1]);
        auto checked2 = Check(graph, points_l, points_r);
        if (!checked2) {
            return dist_mid;
        }
    }
    checked ? begin = mid + 1 : end = mid;
    return BinSearch(points, distances, begin, end, points_l, points_r);
}

auto Bad(int xl, int xr, int r, int n, std::vector<Point> &points) -> long double {
    std::set<int64_t> distances;
    std::set<Point> points_l, points_r;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            distances.insert(Distance(points[i], points[j]));
        }
        auto point_l = Point(xl - r, points[i].y);
        auto point_r = Point(xr + r, points[i].y);
        points.push_back(point_l);
        points.push_back(point_r);
        distances.insert(Distance(points[i], point_l));
        distances.insert(Distance(points[i], point_r));
        points_l.insert(point_l);
        points_r.insert(point_r);
    }
    std::ranges::sort(points);
    auto [first, last] = std::ranges::unique(points);
    points.erase(first, last);
    std::vector<int> points_l_idx, points_r_idx;
    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        auto const &point = points[i];
        if (points_l.contains(point)) {
            points_l_idx.push_back(i);
        }
        if (points_r.contains(point)) {
            points_r_idx.push_back(i);
        }
    }
    std::vector<int64_t> dist(distances.begin(), distances.end());
    long double res = BinSearch(points, dist, 0, (int) dist.size(), points_l_idx, points_r_idx);
    return sqrtl(res) - 2 * r;
}

auto main() -> int {
    int xl, xr, r, n;
    std::cin >> xl >> xr >> r >> n;
    std::vector<Point> points(n);
    for (auto &[x, y]: points) {
        std::cin >> x >> y;
    }
    auto ans = Bad(xl, xr, r, n, points);
    if (ans <= 0)ans = 0;
    std::cout << ans;
}
