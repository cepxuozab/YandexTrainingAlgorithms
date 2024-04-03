#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <ranges>

struct Point {
    int x{};
    int y{};

    auto operator<=>(Point const &) const = default;
};

struct Edge {
    Point a{}, b{};
    int dx{}, dy{};

    Edge() = default;

    Edge(Point a_, Point b_) : a(a_), b(b_) {
        if (b < a) std::swap(a, b);
        dx = b.x - a.x;
        dy = b.y - a.y;
    }

};

auto IsEqual(Edge const &lhs, Edge const &rhs) -> bool {
    return std::tie(lhs.dx, lhs.dy) == std::tie(rhs.dx, rhs.dy);
}

auto Matches(int n, std::vector<Edge> const &matches_a, std::vector<Edge> const &matches_b) -> int {
    std::map<std::pair<int, int>, int> offset_map;
    for (auto const &edge_a: matches_a) {
        for (auto const &edge_b: matches_b) {
            if (IsEqual(edge_a, edge_b)) {
                offset_map[{edge_b.a.x - edge_a.a.x, edge_b.a.y - edge_a.a.y}] += 1;
            }
        }
    }
    if (offset_map.empty()) {
        return n;
    }
    return n - std::ranges::max(std::views::values(offset_map));
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Edge> matches_a, matches_b;
    matches_a.reserve(n), matches_b.reserve(n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        matches_a.emplace_back(Point{x1, y1}, Point{x2, y2});
    }
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        matches_b.emplace_back(Point{x1, y1}, Point{x2, y2});
    }
    std::cout << Matches(n, matches_a, matches_b);
}


