#include <iostream>
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

    [[nodiscard]] auto LCA(std::string const& one, std::string const& two) const
        -> std::string {  // NOLINT(*-easily-swappable-parameters)
        auto ancestor_tmp = Ancestors(one);
        auto ancestor_one = std::unordered_set(ancestor_tmp.begin(), ancestor_tmp.end());
        auto ancestor_two = Ancestors(two);
        for (auto const& ancestor : ancestor_two) {
            if (ancestor_one.contains(ancestor)) {
                return ancestor;
            }
        }
        return "";
    }

private:
    [[nodiscard]] auto Ancestors(std::string child) const -> std::vector<std::string> {
        std::vector<std::string> result{child};
        while (family_tree.contains(child)) {
            child = family_tree.at(child);
            result.push_back(child);
        }
        return result;
    }
};

auto main() -> int {  // NOLINT
    int n;
    std::cin >> n;
    std::vector<Child> family(n - 1);
    for (auto& [child, parent] : family) {
        std::cin >> child >> parent;
    }
    FamilyTree familyTree(family);
    for (std::string one, two; std::cin >> one >> two;) {
        std::cout << familyTree.LCA(one, two) << '\n';
    }
}