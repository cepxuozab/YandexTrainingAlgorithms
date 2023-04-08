#include <iostream>
#include <queue>
#include <vector>

using AdjList = std::vector<std::vector<unsigned>>;

auto ReadAdjList(unsigned n) -> AdjList;

auto ShortedPath(AdjList const& graph, int from, int to) -> int;

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
    std::cout << ShortedPath(graph, from, to);
    return 0;
}
auto ShortedPath(AdjList const& graph, int from, int to) -> int
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
            }
        }
    }
    return dist[to];
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
