#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

const int INF = 1000000000;

int main()
{
    int n, start, finish, r;
    cin >> n >> start >> finish;
    vector<vector<tuple<int, int, int>>> g(n + 1);
    cin >> r;
    for (int i = 0; i < r; ++i) {
        int start, start_time, finish, finish_time;
        cin >> start >> start_time >> finish >> finish_time;
        g[start].push_back(make_tuple(start_time, finish, finish_time));
    }
    vector<int> time(n + 1, INF);
    time[start] = 0;
    vector<bool> used(n + 1);
    int min_time = 0;
    int min_village = start;
    while (min_time < INF) {
        used[min_village] = true;
        int start = min_village;
        for (auto v : g[start]) {
            int start_time = get<0>(v);
            int finish = get<1>(v);
            int finish_time = get<2>(v);
            if (time[start] <= start_time and finish_time < time[finish])
                time[finish] = finish_time;
        }
        min_time = INF;
        for (int v = 0; v < n; ++v)
            if (!used[v] && time[v] < min_time) {
                min_time = time[v];
                min_village = v;
            }
    }
    if (time[finish] == INF)
        cout << -1 << endl;
    else
        cout << time[finish] << endl;
}
