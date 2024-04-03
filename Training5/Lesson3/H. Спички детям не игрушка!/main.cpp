#include <iostream>
#include <vector>
#include <map>

struct Point {
    int x{};
    int y{};

    auto operator<=>(Point const &) const = default;
};

auto operator>>(std::istream &input, Point &point) -> std::istream & {
    return input >> point.x >> point.y;
}

struct Vector2D {
    Point start{};
    Point end{};

    auto operator<=>(Vector2D const &) const = default;
};

auto operator>>(std::istream &input, Vector2D &vector2D) -> std::istream & {
    return input >> vector2D.start >> vector2D.end;
}

auto CreateVector2D(Vector2D const &vector2D) -> Vector2D {
    auto new_start = vector2D.start;
    auto new_end = vector2D.end;
    if (new_start.y > new_end.y || (new_start.y == new_end.y && new_start.x > new_end.x)) {
        std::swap(new_end, new_start);
    }
    Point p_move{new_end.x - new_start.x, new_end.y - new_start.y};
    return {new_start, p_move};
}

auto CreateVectorDirections(std::vector<Vector2D> const &figure) {
    std::map<Point, std::vector<Point>> vector_directions;
    for (auto &vector2D: figure) {
        auto [start, end] = CreateVector2D(vector2D);
        vector_directions[end].push_back(start);
    }
    return vector_directions;
}

auto MinMove(int n, std::vector<Vector2D> const &figure_A, std::vector<Vector2D> const &figure_B) {
    auto vectors_direction_A = CreateVectorDirections(figure_A);
    auto vectors_direction_B = CreateVectorDirections(figure_B);
    std::map<std::pair<int, int>, int> diff;
    int max_move = 0;
    for (auto &[k, items_A]: vectors_direction_B) {
        if (!vectors_direction_A.contains(k)) {
            continue;
        }
        for (auto &[x1, y1]: items_A) {
            for (auto &[x2, y2]: vectors_direction_A[k]) {
                int dx = x2 - x1, dy = y2 - y1;
                auto const curr_max = ++diff[{dx, dy}];
                if (max_move < curr_max) {
                    max_move = curr_max;
                }
            }
        }
    }
    return n - max_move;
}

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<Vector2D> figure_A(n), figure_B(n);
    for (auto &elem: figure_A) {
        std::cin >> elem;
    }
    for (auto &elem: figure_B) {
        std::cin >> elem;
    }
    std::cout << MinMove(n, figure_A, figure_B);

}