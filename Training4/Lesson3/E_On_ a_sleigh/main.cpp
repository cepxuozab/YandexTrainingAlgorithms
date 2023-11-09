#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

static int INF = 1e9;

void dijkstra(int v, std::vector<double>& times, std::vector<std::pair<int, int>>& data, std::vector<std::vector<int>>& dist,
    std::vector<int>& tmp)
{
    times[v] = 0;
    int n = int(times.size());
    std::set<std::pair<double, int>> q;
    q.insert({ 0, v });
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());
        for (int i = 1; i < n; ++i) {
            double what_to_plus = double(double(dist[u][i]) / double(data[i].second)) + data[i].first;
            if (times[i] > times[u] + what_to_plus) {
                q.erase({ times[i], i });
                times[i] = times[u] + what_to_plus;
                tmp[i] = u;
                q.insert({ times[i], i });
            }
        }
    }
}

void dfs(int v, int s, std::vector<std::vector<std::pair<int, int>>>& g, std::vector<bool>& vis,
    std::vector<std::vector<int>>& dist)
{
    vis[v] = true;
    for (auto& neighbour : g[v]) {
        if (!vis[neighbour.first]) {
            dist[s][neighbour.first] = dist[s][v] + neighbour.second;
            dfs(neighbour.first, s, g, vis, dist);
        }
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    std::vector<std::vector<std::pair<int, int>>> g(n + 1);
    std::vector<bool> vis(n + 1, false);
    std::vector<std::vector<int>> dist(n + 1, std::vector<int>(n + 1, INF));
    double ans = 0;
    int the_last_of_us = 0;
    std::vector<std::pair<int, int>> t_v;
    std::vector<int> path;
    int t = 0, v = 0;
    t_v.emplace_back(t, v);
    for (int i = 0; i < n; ++i) {
        std::cin >> t >> v;
        t_v.emplace_back(t, v);
    }
    for (int i = 1; i < n; ++i) {
        int from, to, s;
        std::cin >> from >> to >> s;
        g[from].emplace_back(to, s);
        g[to].emplace_back(from, s);
    }
    for (int i = 1; i <= n; ++i) {
        dist[i][i] = 0;
        dfs(i, i, g, vis, dist);
        std::fill(vis.begin(), vis.end(), false);
    }
    std::vector<double> times(n + 1, INF);
    std::vector<int> tmp(n + 1, -1);
    dijkstra(1, times, t_v, dist, tmp);
    for (int i = 1; i < n + 1; ++i) {
        if (times[i] > ans) {
            ans = times[i];
            the_last_of_us = i;
        }
    }
    std::cout << std::setprecision(11) << ans << "\n";
    while (tmp[the_last_of_us] != -1) {
        path.push_back(the_last_of_us);
        the_last_of_us = tmp[the_last_of_us];
    }
    path.push_back(1);
    for (int i : path) {
        std::cout << i << " ";
    }
    return 0;
}
