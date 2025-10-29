#include <iostream>
#include <vector>

auto main() -> int {
    int n;
    std::cin >> n;
    int root = -1;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> used(n + 1), in(n + 1), out(n + 1);
    for (int i = 1; i <= n; ++i) {
        int a;
        std::cin >> a;
        if (a == 0)root = i;
        else graph[a].push_back(i);
    }

    auto is_Parent = [&](int a, int b) {
        return (in[a] < in[b]) && (out[b] < out[a]);
    };
    int time = 1;
    auto dfs = [&](auto &&self, int v) -> void {
        used[v] = 1;
        in[v] = time++;
        for (int u: graph[v]) {
            if (!used[u])self(self, u);
        }
        out[v] = time++;
    };
    dfs(dfs, root);
    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        is_Parent(a, b) ? puts("1") : puts("0");
    }

}