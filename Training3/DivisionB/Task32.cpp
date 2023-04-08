#include <functional>
#include <iostream>
#include <vector>

int main()
{
    freopen("input.txt", "r", stdin);
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n), components;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        a--, b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    std::vector<bool> visited(n, false);
    std::function<void(int, std::vector<int>&)> dfs = [&](int v, std::vector<int>& comp) {
        visited[v] = true;
        comp.push_back(v);
        for (int u : graph[v]) {
            if (!visited[u]) {
                dfs(u, comp);
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            components.emplace_back();
            dfs(i, components.back());
        }
    }
    std::cout << components.size() << std::endl;
    for (auto const& component : components) {
        std::cout << component.size() << std::endl;
        for (int v : component) {
            std::cout << v + 1 << ' ';
        }
        std::cout << std::endl;
    }
}
