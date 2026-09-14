#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>

using namespace std;
using ll = long long;

int main() {
    int n;
    scanf("%d", &n);
    vector<int> xs(n), ys(n);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &xs[i], &ys[i]);

    vector<int> sx(xs), sy(ys);
    sort(sx.begin(), sx.end());
    sort(sy.begin(), sy.end());
    int mx = sx[(n - 1) / 2], my = sy[(n - 1) / 2]; // медианы
    int R = n + 2; // радиус поиска

    vector<ll> gy(2 * R + 1); // g(y) вокруг медианы
    for (int d = -R; d <= R; d++)
        for (int i = 0; i < n; i++)
            gy[d + R] += abs(my + d - ys[i]);

    set<pair<int, int>> occ;
    for (int i = 0; i < n; i++)
        occ.insert({ xs[i], ys[i] });

    ll best = LLONG_MAX;
    int bx = mx, by = my;
    for (int x = mx - R; x <= mx + R; x++) {
        ll f = 0; // f(x) — только для строк окна
        for (int i = 0; i < n; i++)
            f += abs(x - xs[i]);
        for (int d = -R; d <= R; d++) {
            if (occ.count({ x, my + d }))
                continue; // столица не на месте города
            if (f + gy[d + R] < best) {
                best = f + gy[d + R];
                bx = x;
                by = my + d;
            }
        }
    }
    printf("%d %d\n", bx, by);
}