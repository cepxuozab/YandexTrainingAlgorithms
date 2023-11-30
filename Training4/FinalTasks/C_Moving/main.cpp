#include <climits>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
struct Edge {
    int to {};
    int time {};
    int weight {};
};

using Graph = std::vector<std::vector<Edge>>;

Graph ReadGraph(int n, int m);
bool CheckCups(int start, int finish, Graph const& graph, int total_weight);

int main()
{
    int n, m;
    std::cin >> n >> m;
    auto graph = ReadGraph(n, m);
    int l = 0;
    int r = 10'000'000 + 1;
    int car_weight = 3000 * 1000;
    while (r - l > 1) {
        int m = (l + r) / 2;
        CheckCups(1, n, graph, car_weight + m * 100) ? l = m : r = m;
    }
    std::cout << l << std::endl;
}

Graph ReadGraph(int n, int m)
{
    Graph graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b, t, w;
        std::cin >> a >> b >> t >> w;
        graph[a].push_back({ b, t, w });
        graph[b].push_back({ a, t, w });
    }
    return graph;
}

bool CheckCups(int start, int finish, Graph const& graph, int total_weight)
{
    std::vector<int> time(graph.size(), INT_MAX);
    std::set<std::pair<int, int>> heap;
    heap.insert({ 0, start });
    time[start] = 0;
    while (!heap.empty()) {
        auto [v_time, v] = *heap.begin();
        heap.erase(heap.begin());
        if (time[v] != v_time) {
            continue;
        }
        if (v == finish) {
            break;
        }
        for (auto const& [to, t, w] : graph[v]) {
            auto new_time = v_time + t;
            if (new_time < time[to] && total_weight <= w) {
                time[to] = new_time;
                heap.insert({ new_time, to });
            }
        }
    }
    return time[finish] > 24 * 60 ? false : true;
}
