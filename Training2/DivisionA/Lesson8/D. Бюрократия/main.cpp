#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

ull dfs_depth(vector<vector<size_t>>& g, size_t v, vector<ull>& depth) {
    depth[v] += 1;
    for (auto u : g[v]) {
        depth[v] += dfs_depth(g, u, depth);
    }
    return depth[v];
}

ull dfs_res(vector<vector<size_t>>& g, size_t v, vector<ull>& depth,
    vector<ull>& res) {
    res[v] += 1;
    for (auto u : g[v]) {
        res[v] += dfs_res(g, u, depth, res) + depth[u];
    }
    return res[v];
}

int main() {
    size_t n;
    cin >> n;

    vector<vector<size_t>> g(n);
    for (size_t i = 1; i < n; ++i) {
        size_t a;
        cin >> a;
        --a;
        g[a].push_back(i);
    }

    vector<ull> depth(n, 0);
    dfs_depth(g, 0, depth);
    vector<ull> res(n, 0);
    dfs_res(g, 0, depth, res);

    for (size_t i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}