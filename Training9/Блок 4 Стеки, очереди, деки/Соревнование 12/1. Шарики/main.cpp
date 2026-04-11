#include <iostream>
#include <vector>

struct Group {
    int color;
    int count;
};

auto main() -> int {
    int n;
    std::cin >> n;

    std::vector<int> balls(n);
    for (int& x : balls) {
        std::cin >> x;
    }

    // 1. Сжимаем в группы
    std::vector<Group> groups;
    for (const int color : balls) {
        if (!groups.empty() && groups.back().color == color) {
            groups.back().count++;
        } else {
            groups.push_back({.color=color, .count=1});
        }
    }

    int destroyed = 0;
    bool changed = true;

    // 2. Пока что-то удаляется
    while (changed) {
        changed = false;

        std::vector<Group> next;

        // удаляем группы >= 3
        for (const auto& g : groups) {
            if (g.count >= 3) {
                destroyed += g.count;
                changed = true;
            } else {
                if (!next.empty() && next.back().color == g.color) {
                    next.back().count += g.count;
                } else {
                    next.push_back(g);
                }
            }
        }

        groups = std::move(next);
    }

    std::cout << destroyed;
    return 0;
}