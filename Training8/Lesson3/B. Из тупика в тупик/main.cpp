#include <iostream>
#include <vector>
#include <queue>


int main() {
    int n;
    std::cin >> n;

    std::vector<std::vector < int>>
    g(n + 1);
    std::vector<int> deg(n + 1, 0);

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
        deg[a]++;
        deg[b]++;
    }

    // Multi-source BFS from leaves
    std::queue<int> q;
    std::vector<int> dist(n + 1, -1);
    std::vector<int> source(n + 1, -1);

    for (int i = 1; i <= n; i++) {
        if (deg[i] == 1) { // leaf
            q.push(i);
            dist[i] = 0;
            source[i] = i;
        }
    }

    int ans = n + 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v: g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                source[v] = source[u];
                q.push(v);
            } else if (source[v] != source[u]) {
                // found a connection between two leaves
                ans = std::min(ans, dist[u] + dist[v] + 1);
            }
        }
    }

    std::cout << ans << '\n';

    return 0;
}