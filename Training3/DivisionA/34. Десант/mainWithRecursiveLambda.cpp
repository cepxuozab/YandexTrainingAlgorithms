#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

struct Edge {
    int vertex = 0;
    int height = 0;
};

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n * m);
    std::vector<std::vector<int>> field(n, std::vector<int>(m, 0));
    std::vector<Edge> vertexes_to_height;
    for (auto& line : field) {
        for (int& h : line) {
            std::cin >> h;
        }
    }
    int i_neibs[] = { 0, -1, 0, 1 };
    int j_neibs[] = { -1, 0, 1, 0 };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int v = i + j * n;
            int tmp = field[i][j];
            vertexes_to_height.push_back({ v, tmp });
            for (int k = 0; k < 4; ++k) {
                int i_neib = i + i_neibs[k];
                int j_neib = j + j_neibs[k];
                if (i_neib < 0 || i_neib >= n || j_neib < 0 || j_neib >= m) {
                    continue;
                }
                int v_neib = i_neib + j_neib * n;
                int neib = field[i_neib][j_neib];
                if (tmp <= neib) {
                    graph[v].push_back(v_neib);
                }
            }
        }
    }
    std::ranges::sort(vertexes_to_height, {}, &Edge::height);
    std::vector<int> visited(n * m);

    const auto Dfs = [&](int now, int component) {
        const auto Dfs_impl = [&](int now, int component, const auto& impl)->void {
            if (visited[now] == component) {
                return;
            }
            visited[now] = component;
            for (int v : graph[now]) {
                if (visited[v] == 0) {
                    impl(v, component,impl);
                }
            }
        };
        Dfs_impl(now, component,Dfs_impl);
    };

    int comp = 1;
    for (auto const& vertex_to_height : vertexes_to_height) {
        int v = vertex_to_height.vertex;
        if (visited[v] == 0) {
            Dfs(v, comp);
            comp++;
        }
    }
    std::ranges::sort(visited);
    const auto [first, last] = std::ranges::unique(visited.begin(), visited.end());
    visited.erase(first, last);
    std::cout << visited.size();
    return 0;
}
