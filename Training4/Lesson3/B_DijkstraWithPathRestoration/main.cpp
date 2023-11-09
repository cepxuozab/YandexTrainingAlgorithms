#include <iostream>
#include <set>
#include <stack>
#include <vector>
#define INF 1000000000
using namespace std;
int main()
{
    int n, i, f, j, s;
    set<pair<int, int>> c;
    cin >> n >> s >> f;
    s--;
    f--;
    vector<vector<int>> a(n, vector<int>(n));
    vector<int> d(n), p(n);
    vector<bool> b(n);
    for (i = 0; i < n; ++i) {
        d[i] = INF;
        b[i] = true;
        for (j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (a[i][j] < 0)
                a[i][j] = INF;
        }
    }
    d[s] = 0;
    p[s] = s;
    c.insert(make_pair(0, s));
    while (!c.empty()) {
        i = c.begin()->second;
        b[i] = false;
        c.erase(c.begin());
        for (j = 0; j < n; ++j)
            if (b[j] && d[j] > d[i] + a[i][j]) {
                c.erase(make_pair(d[j], j));
                d[j] = d[i] + a[i][j];
                p[j] = i;
                c.insert(make_pair(d[j], j));
            }
    }
    if (d[f] < INF) {
        stack<int> q;
        q.push(f);
        while (f != s) {
            f = p[f];
            q.push(f);
        }
        while (!q.empty()) {
            cout << q.top() + 1 << ' ';
            q.pop();
        }
    } else
        cout << -1;
    return 0;
}
