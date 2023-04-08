#include <algorithm>
#include <iostream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void ReadGraph(Graph& graph, int verticies, int edges);

void Dfs(Graph const& graph, std::vector<bool>& visited, std::vector<int>& componen, int start = 0);

void PrintComponent(std::vector<int>& component);

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int vertisies, edges;
    std::cin >> vertisies >> edges;
    Graph graph;
    ReadGraph(graph, vertisies, edges);
    std::vector<bool> visited(vertisies, false);
    std::vector<int> component;
    Dfs(graph, visited, component);
    PrintComponent(component);
    return 0;
}

void Dfs(Graph const& graph, std::vector<bool>& visited, std::vector<int>& componen, int start)
{
    visited[start] = true;
    for (int u : graph[start]) {
        if (!visited[u]) {
            Dfs(graph, visited, componen, u);
        }
    }
    componen.push_back(start);
}

void PrintComponent(std::vector<int>& component)
{
    std::sort(component.begin(), component.end());
    std::cout << component.size() << std::endl;
    for (int vertex : component) {
        std::cout << vertex + 1 << ' ';
    }
    std::cout << std::endl;
}

void ReadGraph(Graph& graph, int verticies, int edges)
{
    graph.resize(verticies);
    for (int i = 0; i < edges; ++i) {
        int from, to;
        std::cin >> from >> to;
        from--, to--;
        graph[from].push_back(to);
        graph[to].push_back(from);
    }
}
