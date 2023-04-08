#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using AdjList = std::vector<std::vector<unsigned>>;

auto ReadAdjList(unsigned n) -> AdjList;

auto ShortedPath(AdjList const& graph, int from, int to, std::vector<int>& path) -> int;

void FindPath(std::vector<int> const& parent, int end);

int main()
{
    if (freopen("input.txt", "r", stdin) == 0) {
        puts("Can't open input.txt");
        return 0;
    }
    unsigned n;
    std::cin >> n;
    auto graph = ReadAdjList(n);
    int from, to;
    std::cin >> from >> to;
    from--, to--;
    std::vector<int> parent(n, -1);
    int ans = ShortedPath(graph, from, to, parent);
    std::cout << ans << std::endl;
    if (ans > 0) {
        FindPath(parent, to);
    }
    return 0;
}

auto ReadAdjList(unsigned n) -> AdjList
{
    AdjList graph(n);
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            short ch;
            std::cin >> ch;
            if (ch == 1) {
                graph[i].push_back(j);
            }
        }
    }
    return graph;
}

auto ShortedPath(AdjList const& graph, int from, int to, std::vector<int>& parent) -> int
{
    std::vector<int> dist(graph.size(), -1);
    dist[from] = 0;
    std::queue<int> queue;
    queue.push(from);
    while (!queue.empty()) {
        auto u = queue.front();
        queue.pop();
        for (int v : graph[u]) {
            if (dist[v] == -1) {
                queue.push(v);
                dist[v] = dist[u] + 1;
                parent[v] = u;
            }
        }
    }
    return dist[to];
}

void FindPath(std::vector<int> const& parent, int end)
{
    std::vector<int> path { end };
    while (parent[path.back()] != -1) {
        path.push_back(parent[path.back()]);
    }
    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        std::cout << *it + 1 << ' ';
    }
}
