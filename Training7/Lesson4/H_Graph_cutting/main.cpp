#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size;
    DSU(int n): parent(n), size(n,1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        while (x != parent[x]) parent[x] = parent[parent[x]], x = parent[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a,b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m,k; cin >> n >> m >> k;
    vector<pair<int,int>> edges(m);
    for (int i=0; i<m; i++) {
        int u,v; cin >> u >> v;
        --u; --v;
        if (u > v) swap(u,v);
        edges[i] = {u,v};
    }

    // Строим map для быстрого поиска индекса ребра по концам
    unordered_map<long long,int> edge_id;
    auto get_key = [](int a, int b) {
        return (long long)a * 500000 + b; // 500000 > max n
    };
    for (int i=0; i<m; i++) {
        edge_id[get_key(edges[i].first, edges[i].second)] = i;
    }

    vector<bool> removed(m, false);
    vector<tuple<string,int,int>> queries(k);
    for (int i=0; i<k; i++) {
        string cmd; int u,v;
        cin >> cmd >> u >> v;
        --u; --v;
        if (u > v) swap(u,v);
        queries[i] = {cmd,u,v};
        if (cmd == "cut") {
            int id = edge_id[get_key(u,v)];
            removed[id] = true;
        }
    }

    DSU dsu(n);
    // Объединяем все ребра, которые не удалены
    for (int i=0; i<m; i++) {
        if (!removed[i]) {
            dsu.unite(edges[i].first, edges[i].second);
        }
    }

    vector<string> answers;
    // Идём по запросам в обратном порядке
    for (int i=k-1; i>=0; i--) {
        auto& [cmd,u,v] = queries[i];
        if (cmd == "ask") {
            answers.push_back(dsu.find(u) == dsu.find(v) ? "YES" : "NO");
        } else if (cmd == "cut") {
            // Восстанавливаем ребро
            dsu.unite(u,v);
        }
    }

    reverse(answers.begin(), answers.end());
    for (auto& ans : answers) cout << ans << "\n";

    return 0;
}
