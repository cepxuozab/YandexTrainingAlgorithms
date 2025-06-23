#include <iostream>
#include <vector>
#include <unordered_map>

using Graph = std::unordered_map<int, std::vector<int>>;

// Функция чтения графа
auto read_input() -> std::pair<int, Graph> {
    int v;
    std::cin >> v;
    Graph node_map;
    for (int i = 0; i < v - 1; ++i) {
        int v1, v2;
        std::cin >> v1 >> v2;
        --v1; --v2;  // 0-индексация
        node_map[v1].push_back(v2);
        node_map[v2].push_back(v1);
    }
    return {v, node_map};
}

// Подсчет размеров поддеревьев
auto subtree_size(int v, const Graph& node_map) -> std::vector<int> {
    std::vector<int> ans(v, 0);
    std::vector<bool> visited(v, false);

    auto dfs = [&](auto&& self, int cur) -> int {
        if (visited[cur]) return 0;
        visited[cur] = true;
        ans[cur] = 1;
        for (int child : node_map.at(cur)) {
            ans[cur] += self(self, child);
        }
        return ans[cur];
    };

    dfs(dfs, 0);  // начинаем с вершины 0
    return ans;
}

// Основной вывод
auto main() -> int {
    auto [v, node_map] = read_input();
    auto result = subtree_size(v, node_map);
    for (int val : result) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
    return 0;
}
