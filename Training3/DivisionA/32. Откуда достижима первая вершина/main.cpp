#include <algorithm>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        x--, y--;
        graph[y].push_back(x);
    }
    std::set<int> visited;
    std::function<void(int)> dfs = [&](int v) {
        visited.insert(v);
        for (int u : graph[v]) {
            if (!visited.contains(u)) {
                dfs(u);
            }
        }
    };
    dfs(0);
    for (int v : visited) {
        std::cout << v + 1 << ' ';
    }
    return 0;
}
