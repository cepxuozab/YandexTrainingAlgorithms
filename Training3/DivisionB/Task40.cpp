#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <climits>



int main()
{
    if (freopen("input.txt", "r", stdin) == 0) {
        puts("Can't open input.txt");
        return 0;
    }
    int n, m;
    std::cin >> n >> m;
    std::vector<int> vertex(m + 1, -1);
    std::map<int, std::set<int>> edges, stations;
    for (int i = 0; i < m; ++i) {
        int p;
        std::cin >> p;
        for (int u = 0; u < p; ++u) {
            int j;
            std::cin >> j;
            for (int k : stations[j]) {
                edges[k].insert(i);
                edges[i].insert(k);
            }
            stations[j].insert(i);
        }
    }
    int a, b;
    std::cin >> a >> b;
    auto starts = stations[a];
    auto ends = stations[b];
    std::vector<int> dist, curr_dist;
    for (int i : starts) {
        vertex[i] = 0;
        dist.push_back(i);
    }
    int curr = 0, ma = 0;
    while (curr <= ma) {
        for (int v : dist) {
            for (int next : edges[v]) {
                if (vertex[next] == -1) {
                    ma = curr + 1;
                    vertex[next] = curr + 1;
                    curr_dist.push_back(next);
                }
            }
        }
        dist.swap(curr_dist);
        curr++;
    }
    int ans = INT_MAX;
    for (int i : ends) {
        if (vertex[i]!=-1 && vertex[i] < ans) {
            ans = vertex[i];
        }
    }
    std::cout << (ans == INT_MAX ? -1 : ans);
}
