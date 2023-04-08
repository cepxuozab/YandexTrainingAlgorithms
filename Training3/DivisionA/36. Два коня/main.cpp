#include <climits>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>

struct Point {
    int x = 0, y = 0;
};

using Field = std::vector<std::vector<int>>;

std::optional<int> Bfs(
    std::queue<Point>& queue, Field& a, std::optional<Field> const& c, bool need_check = false);

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    std::string h1, h2;
    std::cin >> h1 >> h2;
    Point horse1{ h1[0] - 'a', h1[1] - '1' };
    Point horse2{ h2[0] - 'a', h2[1] - '1' };
    int const SIZE = 8;
    Field a(SIZE, std::vector<int>(SIZE, INT_MAX)); // first horse field
    Field c(SIZE, std::vector<int>(SIZE, INT_MAX)); // second horse field
    a[horse1.x][horse1.y] = 0;
    std::queue<Point> queue;
    queue.push(horse1);
    auto res = Bfs(queue, a, std::nullopt);
    c[horse2.x][horse2.y] = 0;
    queue.push(horse2);
    res = Bfs(queue, c, a, true);
    std::cout << (res.has_value() ? res.value() : -1);
    return 0;
}

std::optional<int> Bfs(
    std::queue<Point>& queue, Field& a, std::optional<Field> const& c, bool need_check)
{
    int const SIZE = static_cast<int>(a.size());
    int dx[] = { -1, -2, -2, -1, 1, 2, 2, 1 };
    int dy[] = { -2, -1, 1, 2, 2, 1, -1, -2 };
    auto check = [SIZE](Point point) {
        return point.x >= 0 && point.x < SIZE && point.y >= 0 && point.y < SIZE;
    };
    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();
        if (need_check) {
            if (a[x][y] == c.value()[x][y]) {
                return a[x][y];
            }
        }
        for (int i = 0; i < SIZE; ++i) {
            int curr_x = x + dx[i];
            int curr_y = y + dy[i];
            if (check({ curr_x, curr_y }) && a[curr_x][curr_y] == INT_MAX) {
                a[curr_x][curr_y] = a[x][y] + 1;
                queue.push({ curr_x, curr_y });
            }
        }
    }
    return std::nullopt;
}
