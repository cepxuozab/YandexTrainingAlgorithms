#include <iostream>
#include <vector>
#include <map>
#include <set>

auto Square(int n, std::vector<std::pair<int, int>> const &points) -> std::vector<std::pair<int, int>> {
    auto [init_x, init_y] = points.front();
    std::vector<std::pair<int, int>> ans{{init_x + 1, init_y},
                                         {init_x,     init_y + 1},
                                         {init_x + 1, init_y + 1}};
    if (n == 1) {
        return ans;
    }
    std::map<int, std::set<int>> y_to_xs;
    for (auto const &[x, y]: points) {
        y_to_xs[y].insert(x);
    }
    for (int i = 0; i + 1 < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (points[i] == points[j])
                continue;
            auto [xa, ya] = points[i];
            auto [xb, yb] = points[j];
            auto dx = xb - xa;
            auto dy = yb - ya;
            auto Clear = [&ans](int a, int b) {
                if (ans.size() > 1) {
                    ans.clear();
                    ans.emplace_back(a, b);
                }
            };
            if (y_to_xs.contains(yb - dx) && y_to_xs[yb - dx].contains(xb + dy)) {
                if (y_to_xs.contains(ya - dx) && y_to_xs[ya - dx].contains(xa + dy))
                    return {};
                Clear(xa + dy, ya - dx);
            } else if (y_to_xs.contains(ya - dx) && y_to_xs[ya - dx].contains(xa + dy)) {
                Clear(xb + dy, yb - dx);
            }
            if (y_to_xs.contains(yb + dx) && y_to_xs[yb + dx].contains(xb - dy)) {
                if (y_to_xs.contains(ya + dx) && y_to_xs[ya + dx].contains(xa - dy))
                    return {};
                Clear(xa - dy, ya + dx);
            } else if (y_to_xs.contains(ya + dx) && y_to_xs[ya + dx].contains(xa - dy)) {
                Clear(xb - dy, yb + dx);
            }
            if (ans.size() > 2) {
                ans.clear();
                ans.emplace_back(xa + dy, ya - dx);
                ans.emplace_back(xb + dy, yb - dx);
            }
        }
    }
    return ans;
}

auto main() -> int {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> points(n);
    for (auto &[x, y]: points) {
        std::cin >> x >> y;
    }
    auto ans = Square(n, points);
    std::cout << ans.size() << '\n';
    for (auto &[x, y]: ans) {
        std::cout << x << ' ' << y << '\n';
    }
}