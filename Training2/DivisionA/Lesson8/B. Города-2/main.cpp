#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int dfs(vector<vector<size_t>>& g, size_t v, vector<bool>& visited,
    vector<ull>& subtree_size, vector<ull>& depth,
    vector<size_t>& parents) {
    visited[v] = true;
    subtree_size[v] += 1;
    for (auto u : g[v]) {
        if (visited[u]) {
            continue;
        }
        parents[u] = v;
        depth[u] = depth[v] + 1;
        subtree_size[v] += dfs(g, u, visited, subtree_size, depth, parents);
    }
    return subtree_size[v];
}

int main() {
    size_t n;
    cin >> n;

    vector<vector<size_t>> g(n);
    for (size_t i = 0; i < n - 1; ++i) {
        size_t a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<bool> visited(n, false);
    vector<ull> subtree_size(n, 0);
    vector<ull> depth(n, 0);
    vector<size_t> parents(n);
    dfs(g, 0, visited, subtree_size, depth, parents);

    ull s = 0;
    for (size_t i = 0; i < n; ++i) {
        s += depth[i];
        visited[i] = false;
    }
    vector<ull> res(n);
    res[0] = s;
    deque<size_t> st;
    st.push_back(0);
    while (!st.empty()) {
        auto v = st.back();
        visited[v] = true;
        st.pop_back();
        for (auto u : g[v]) {
            if (visited[u]) {
                continue;
            }
            res[u] = res[v] + n - 2 * subtree_size[u];
            st.push_back(u);
        }
    }

    vector<pair<ull, size_t>> tmp(n);
    for (size_t i = 0; i < n; ++i) {
        tmp[i] = { res[i], i };
    }
    sort(tmp.begin(), tmp.end());
    vector<size_t> res_idx;
    res_idx.push_back({ tmp[0].second });
    for (size_t i = 1; i < n; ++i) {
        if (tmp[i].first == tmp[0].first) {
            res_idx.push_back(tmp[i].second);
        }
        else {
            break;
        }
    }

    cout << tmp[0].first << " " << res_idx.size() << " ";
    for (auto idx : res_idx) {
        cout << idx + 1 << " ";
    }
    cout << endl;

    return 0;
}