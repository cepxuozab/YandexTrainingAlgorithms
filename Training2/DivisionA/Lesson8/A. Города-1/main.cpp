#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

void bfs(const vector<vector<int>>& g, vector<pair<int, int>>& res, int a)
{
    res = vector<pair<int, int>>(g.size(), { -1, -1 });
    deque<int> q;
    res[a] = { a, 0 };
    q.push_back(a);
    while (!q.empty()) {
        int u = q.front();
        for (auto v : g[u]) {
            if (res[v].second == -1) {
                q.push_back(v);
                res[v].first = u;
                res[v].second = res[u].second + 1;
            }
        }
        q.pop_front();
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for (size_t i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<pair<int, int>> d(n);
    bfs(g, d, 0);
    int idx1 = max_element(d.begin(), d.end(),
                   [](const auto& lhs, const auto& rhs) {
                       return lhs.second < rhs.second;
                   })
        - d.begin();
    bfs(g, d, idx1);
    int idx2 = max_element(d.begin(), d.end(),
                   [](const auto& lhs, const auto& rhs) {
                       return lhs.second < rhs.second;
                   })
        - d.begin();

    int res_d = (d[idx2].second + d[idx2].second % 2) / 2;
    vector<int> res;
    while (idx2 != idx1) {
        res.push_back(idx2);
        idx2 = d[idx2].first;
    }
    res.push_back(idx1);

    if (res.size() % 2 == 0) {
        cout << res_d << " " << 2 << " " << res[res.size() / 2 - 1] + 1 << " "
             << res[res.size() / 2] + 1 << endl;
        return 0;
    }
    cout << res_d << " " << 1 << " " << res[res.size() / 2] + 1 << endl;

    return 0;
}
