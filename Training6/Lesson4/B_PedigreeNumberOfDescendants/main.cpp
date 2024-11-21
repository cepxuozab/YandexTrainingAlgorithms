#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

auto main() -> int {  // NOLINT
    std::unordered_map<std::string, std::string> childToParent;
    std::unordered_map<std::string, std::vector<std::string>> parentToChildren;

    int N;
    std::cin >> N;
    for (int i = 0; i < N - 1; ++i) {
        std::string parent;
        std::string child;
        std::cin >> child >> parent;
        childToParent[child] = parent;
        parentToChildren[parent].push_back(child);
    }

    std::vector<std::string> BFS = [&] {
        std::string forefather;
        for (const auto& [parent, children] : parentToChildren) {
            if (!childToParent.contains(parent)) {
                forefather = parent;
            }
        }
        std::vector<std::string> breadthFirstSearch;
        std::queue<std::string> deq;
        deq.push(forefather);

        while (!deq.empty()) {
            breadthFirstSearch.push_back(deq.front());
            for (const auto& children : parentToChildren[deq.front()]) {
                deq.push(children);
            }
            deq.pop();
        }

        return breadthFirstSearch;
    }();

    std::unordered_map<std::string, size_t> childrenQuantity;

    for (auto it = BFS.rbegin(); it != BFS.rend(); ++it) {
        for (const auto& child : parentToChildren[*it]) {
            childrenQuantity[*it] += childrenQuantity[child] + 1;
        }
    }

    std::ranges::sort(BFS);

    for (const auto& name : BFS) {
        std::cout << name << ' ' << childrenQuantity[name] << '\n';
    }

    return 0;
}
