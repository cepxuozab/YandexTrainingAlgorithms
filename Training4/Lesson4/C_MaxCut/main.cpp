#include <iostream>
#include <optional>
#include <queue>
#include <vector>

using Graph = std::vector<std::vector<int>>;
using Opt = std::optional<int>;
bool bfs(Graph const& graph, std::vector<Opt> const& pair_u, std::vector<Opt> const& pair_v,
    std::vector<int>& dist)
{
    int const INF = 1'000'000'007;
    std::queue<int> queue;
    int const size = graph.size();
    for (int u = 0; u < size; ++u) {
        if (!pair_u[u].has_value()) {
            dist[u] = 0;
            queue.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[size] = INF;
    while (!queue.empty()) {
        auto u = queue.front();
        queue.pop();
        if (dist[u] < dist[size]) {
            for (int v = 0; v < size; ++v) {
                if (graph[u][v] != 0 && dist[pair_v[v].value()] == INF) {
                    dist[pair_v[v].value()] = dist[u] + 1;
                    queue.push(pair_v[v].value());
                }
            }
        }
    }
    return dist[size] != INF;
}

/*
from queue import Queue

def bfs(graph, pair_u, pair_v, dist):
    q = Queue()
    for u in range(len(graph)):
        if pair_u[u] is None:
            dist[u] = 0
            q.put(u)
        else:
            dist[u] = float('inf')
    dist[len(graph)] = float('inf')
    while not q.empty():
        u = q.get()
        if dist[u] < dist[len(graph)]:
            for v in range(len(graph)):
                if graph[u][v] and dist[pair_v[v]] == float('inf'):
                    dist[pair_v[v]] = dist[u] + 1
                    q.put(pair_v[v])
    return dist[len(graph)] != float('inf')

def dfs(graph, pair_u, pair_v, dist, u):
    if u is not None:
        for v in range(len(graph)):
            if graph[u][v] and dist[pair_v[v]] == dist[u] + 1 and dfs(graph, pair_u, pair_v, dist, pair_v[v]):
                pair_v[v] = u
                pair_u[u] = v
                return True
        dist[u] = float('inf')
        return False
    return True

def hopcroft_karp(graph):
    pair_u = [None] * len(graph)
    pair_v = [None] * len(graph[0])
    dist = [float('inf')] * (len(graph) + 1)
    matching = 0
    while bfs(graph, pair_u, pair_v, dist):
        for u in range(len(graph)):
            if pair_u[u] is None and dfs(graph, pair_u, pair_v, dist, u):
                matching += 1
    return pair_u, matching

def divide_vertices(n, graph):
    # Находим максимальное паросочетание в двудольном графе
    pair_u, matching = hopcroft_karp(graph)
    # Разделяем вершины на две доли
    part = [0] * n
    for u in range(n):
        if pair_u[u] is not None:
            part[u] = 1
    # Считаем сумму весов ребер, соединяющих вершины из разных долей
    weight = 0
    for u in range(n):
        for v in range(n):
            if graph[u][v] and part[u] != part[v]:
                weight += graph[u][v]
    return weight, part

n = int(input())
graph = [list(map(int, input().split())) for _ in range(n)]
weight, part = divide_vertices(n, graph)
print(weight)
print(' '.join(str(p + 1) for p in part))
*/
