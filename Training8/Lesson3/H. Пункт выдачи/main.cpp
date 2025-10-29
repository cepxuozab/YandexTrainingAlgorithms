#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    if (n == 1) {
        cout << 1 << "\n";
        return 0;
    }

    vector<long long> sub(n);
    vector<int> parent(n, -1);

    // DFS от 0
    function<void(int, int)> dfs1 = [&](int v, int p) {
        parent[v] = p;
        sub[v] = a[v];
        for (int to : g[v]) {
            if (to == p) continue;
            dfs1(to, v);
            sub[v] += sub[to];
        }
    };

    dfs1(0, -1);

    long long total = sub[0];
    long long best_max = LLONG_MAX;
    int best_vertex = -1;

    for (int v = 0; v < n; ++v) {
        long long max_queue = a[v]; // очередь самой вершины

        for (int to : g[v]) {
            long long comp_size;
            if (to == parent[v]) {
                comp_size = total - sub[v];
            } else {
                comp_size = sub[to];
            }
            if (comp_size > max_queue) {
                max_queue = comp_size;
            }
        }

        if (max_queue < best_max) {
            best_max = max_queue;
            best_vertex = v;
        }
    }

    cout << best_vertex + 1 << "\n";
    return 0;
}