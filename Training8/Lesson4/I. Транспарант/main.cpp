#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>


struct Point {
    int x, y;

    bool operator==(const Point &o) const noexcept {
        return x == o.x && y == o.y;
    }
};

// для unordered_set
struct HashPoint {
    size_t operator()(const Point &p) const noexcept {
        return ((uint64_t) (p.x) * 31u + (uint64_t) (p.y + 1000000000)) % 1000000007;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    long long d;
    std::cin >> n >> d;

    std::vector<Point> trees(n);
    for (int i = 0; i < n; ++i)
        std::cin >> trees[i].x >> trees[i].y;

    // находим все целые вектора (dx, dy), для которых dx^2 + dy^2 = d
    std::vector<std::pair<int, int>> deltas;
    for (int dx = -sqrt(d); dx <= sqrt(d); ++dx) {
        long long dy2 = d - 1LL * dx * dx;
        if (dy2 < 0) continue;
        long long dy = llround(sqrt(dy2));
        if (dy * dy == dy2) {
            deltas.push_back({dx, (int) dy});
            if (dy != 0) deltas.push_back({dx, -(int) dy});
        }
    }

    std::unordered_set<Point, HashPoint> seen;
    long long ans = 0;

    for (auto &p: trees) {
        for (auto [dx, dy]: deltas) {
            Point q{p.x + dx, p.y + dy};
            if (seen.count(q))
                ans++;
        }
        seen.insert(p);
    }

    std::cout << ans << "\n";
    return 0;
}
