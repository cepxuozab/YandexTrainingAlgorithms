#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::unordered_map<std::string, std::string> parents;
    for (int i = 0; i + 1 < n; ++i) {
        std::string child, parent;
        std::cin >> child >> parent;
        parents[child] = parent;
    }

    auto get_ancestor = [&](std::string name1, std::string name2) -> std::string {
        std::unordered_set<std::string> ancestors{name1};
        while (parents.contains(name1)) {
            name1 = parents[name1];
            ancestors.insert(name1);
        }
        while (!ancestors.contains(name2)) {
            name2 = parents[name2];
        }
        return name2;
    };

    for (std::string one, two; std::cin >> one >> two;) {
        std::cout << get_ancestor(one, two) << '\n';
    }
}