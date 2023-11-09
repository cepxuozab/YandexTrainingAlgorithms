#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

int main()
{
    freopen("input.txt", "r", stdin);
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<std::pair<int64_t, int>>> graph(n);
    for (int i = 0; i < k; ++i) {
        int a, b;
        int64_t l;
        std::cin >> a >> b >> l;
        a--, b--;
        graph[a].emplace_back(b, l);
        graph[b].emplace_back(a, l);
    }
    std::vector<int64_t> dist(n, std::numeric_limits<int64_t>::max());
    int start, finish;
    std::cin >> start >> finish;
    start--;
    finish--;
    std::priority_queue<std::pair<int64_t, int>,std::vector<std::pair<int64_t,int>>,std::greater<>> pq;
    pq.emplace(0, start);
    while (!pq.empty()) {
        auto temp = pq.top();
        pq.pop();
        int x = temp.second;
        for (auto const& [idx, cost] : graph[x]) {
            if (cost  < dist[idx] - temp.first) {
                dist[idx] = cost + temp.first;
                pq.emplace( dist[idx], idx );
            }
        }
    }
    if (dist[finish] == std::numeric_limits<int64_t>::max()) {
        std::cout << -1;
        return 0;
    }
    std::cout << dist[finish];
    return 0;
}
