#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

constexpr int INF = 1e9;

auto ReadGraph(int n) -> std::vector<std::vector<int>> {
    std::vector<std::vector<int>> graph(n, std::vector<int>(n));
    for (auto &arr: graph) {
        for (int &a: arr) {
            std::cin >> a;
        }
    }
    return graph;
}

auto CalcLen(int curr_v, int n, std::vector<std::vector<int>> const &graph, std::vector<int> &visited) {
    visited[curr_v] = 1;
    if (std::reduce(visited.begin(), visited.end()) == n) {
        visited[curr_v] = 0;
        return graph[curr_v][0] != 0 ? graph[curr_v][0]  : INF;
    }
    auto min_len = INF;
    for (int v = 0; v < n; ++v) {
        if (graph[curr_v][v] == 0 || visited[v] == 1)continue;
        min_len = std::min(min_len, CalcLen(v, n, graph, visited) + graph[curr_v][v]);
    }
    visited[curr_v] = 0;
    return min_len;
}

auto SalesmanTrip(int n, std::vector<std::vector<int>> const &graph) {
    if (n == 1) {
        return 0;
    }
    std::vector<int> visited(n);
    auto distance = CalcLen(0, n, graph, visited);
    return distance != INF ? distance : -1;
}

auto main() -> int {
    int n;
    std::cin >> n;
    auto const graph = ReadGraph(n);
    std::cout << SalesmanTrip(n, graph);
}