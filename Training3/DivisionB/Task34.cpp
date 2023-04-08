#include <iostream>
#include <queue>
#include <vector>

static auto _ = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

using Graph = std::vector<std::vector<int>>;

void ReadGraph(Graph& graph, int vert, int edges);

bool TopologicalSort(Graph const& graph, std::vector<int>& topsort);

int main()
{
    freopen("input.txt", "r", stdin);
    int vert, edges;
    std::cin >> vert >> edges;
    Graph graph;
    ReadGraph(graph, vert, edges);
    std::vector<int> toposort;
    if (TopologicalSort(graph, toposort)) {
        for (int v : toposort) {
            std::cout << v + 1 << ' ';
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "-1" << std::endl;
    }
}

void ReadGraph(Graph& graph, int vert, int edges)
{
    graph.resize(vert);
    for (int i = 0; i < edges; ++i) {
        int from, to;
        std::cin >> from >> to;
        from--, to--;
        graph[from].push_back(to);
    }
}

bool TopologicalSort(Graph const& graph, std::vector<int>& topsort)
{
    int vertices = graph.size();
    std::vector<int> indegree_count(vertices, 0);
    for (auto const& arr : graph) {
        for (int u : arr) {
            indegree_count[u]++;
        }
    }
    std::queue<int> queue;
    for (int i = 0; i < vertices; ++i) {
        if (indegree_count[i] == 0) {
            queue.push(i);
        }
    }
    int visited_node = 0;
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop();
        topsort.push_back(u);
        for (int v : graph[u]) {
            if (--indegree_count[v] == 0) {
                queue.push(v);
            }
        }
        visited_node++;
    }
    return visited_node == vertices;
}
