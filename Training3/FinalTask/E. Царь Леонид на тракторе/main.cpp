#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <deque>

int H, W, INF = 1e6;

struct Point {
    int x{}, y{}, d{};

    auto operator<=>(Point const &) const = default;

    [[nodiscard]] auto to_vertex() const {
        return y + x * H + d * H * W;
    }
};

auto Leonide(std::vector<std::string> const &field, Point const &start, Point const &end) {
    std::vector dx = {-1, 0, 1, 1, 1, 0, -1, -1, 0};
    std::vector dy = {-1, -1, -1, 0, 1, 1, 1, 0, 0};
    std::vector<int> visited(H * W * 9, INF);
    visited[start.to_vertex()] = 1;
    std::deque<Point> queue;
    queue.push_back(start);
    while (!queue.empty()) {
        auto now = queue.front();
        queue.pop_front();
        if (now.d == 8) {
            for (int i = 0; i < 8; ++i) {

                int y = (now.y + dy[i] + field.size()) % field.size();
                int x = (now.x + dx[i] + field[y].size()) % field[y].size();
                if (field[y][x] != '.') {
                    continue;
                }
                auto v = Point(x, y, i);
                auto cur_dst = visited[now.to_vertex()];
                if (cur_dst < visited[v.to_vertex()]) {
                    visited[v.to_vertex()] = cur_dst;
                    queue.push_front(v);
                }
            }
        } else {
            auto v = Point(now.x, now.y, 8);
            auto cost = 1;
            auto cur_dst = visited[now.to_vertex()] + cost;
            if (cur_dst < visited[v.to_vertex()]) {
                visited[v.to_vertex()] = cur_dst;
                queue.push_back(v);
            }

            int y = (now.y + dy[now.d] + field.size()) % field.size();
            int x = (now.x + dx[now.d] + field[y].size()) % field[y].size();
            if (field[y][x] != '.') {
                continue;
            }
            v = Point(x, y, now.d);
            cur_dst = visited[now.to_vertex()];
            if (cur_dst < visited[v.to_vertex()]) {
                visited[v.to_vertex()] = cur_dst;
                queue.push_front(v);
            }
        }
    }
    auto turns = INF;
    for (int i = 0; i < 8; ++i) {
        if (visited[Point(end.x, end.y, i).to_vertex()] < turns) {
            turns = visited[Point(end.x, end.y, i).to_vertex()];
        }
    }
    return turns != INF ? turns : -1;
}

auto main() -> int {
    std::cin >> H >> W;
    std::vector<std::string> field{std::string(W + 1, 'X')};
    for (int i = 0; i < H; ++i) {
        std::string str;
        std::cin >> str;
        str += 'X';
        field.push_back(str);
    }
    std::ranges::reverse(field);
    int a, b;
    std::cin >> a >> b;
    a--, b--;
    Point start(0, 0, 8);
    start.x = a, start.y = b;
    std::cin >> a >> b;
    a--, b--;
    Point end(0, 0, 8);
    end.x = a, end.y = b;
    std::cout << Leonide(field, start, end);
}