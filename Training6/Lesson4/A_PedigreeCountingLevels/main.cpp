#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Child {
    std::string child, parent;
};

class FamilyTree {
    std::unordered_map<std::string, std::string> family_tree;

public:
    FamilyTree(std::vector<Child> const& peoples) {
        for (auto const& [child, parent] : peoples) {
            family_tree[child] = parent;
        }
    }

    [[nodiscard]] auto Height(std::string const& man) const -> int {
        return family_tree.contains(man) ? 1 + Height(family_tree.at(man)) : 0;
    }
};

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<Child> family(n - 1);
    std::unordered_set<std::string> names;
    for (auto& [child, parent] : family) {
        std::cin >> child >> parent;
        names.insert(child);
        names.insert(parent);
    }
    FamilyTree familyTree(family);
    std::map<std::string, int> heights;
    for (auto const& man : names) {
        heights[man] = familyTree.Height(man);
    }
    for (auto const& [name, height] : heights) {
        std::cout << name << ' ' << height << '\n';
    }
}