#include <iostream>
#include <queue>
#include <vector>

// Стандартный алгоритм Дейкстры
int main()
{
    int inf = 2000;
    int V_num, s, f;
    std::cin >> V_num >> s >> f;
    std::vector<std::vector<int>> graph(V_num, std::vector<int>(V_num));
    for (int i = 0; i < V_num; ++i) {
        for (int j = 0; j < V_num; ++j) {
            std::cin >> graph[i][j];
        }
    }
    std::priority_queue<std::pair<int, int>> pq;
    pq.push(std::make_pair(0, s - 1));
    std::vector<int> dist(V_num, V_num * inf);
    while (!pq.empty()) {
        auto temp = pq.top();
        pq.pop();
        int x = temp.second;
        for (int i = 0; i < V_num; ++i) {
            if (graph[x][i] != -1 && graph[x][i] - temp.first < dist[i]) {
                dist[i] = graph[x][i] - temp.first;
                pq.push({ -dist[i], i });
            }
        }
    }
    if (dist[f - 1] == V_num * inf) {
        std::cout << "-1";
    } else {
        std::cout << dist[f - 1] << '\n';
    }
    return 0;
}
