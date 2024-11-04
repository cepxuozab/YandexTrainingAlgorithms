#include <iostream>
#include <vector>
using namespace std;

auto main() -> int {  // NOLINT
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) cin >> x;

    int m, k;
    cin >> m >> k;
    vector<int> queries(m);
    for (auto& x : queries) cin >> x;

    const int LOG = 20;
    vector<vector<int>> jump(LOG, vector<int>(n, 0));
    vector<vector<int>> count(LOG, vector<int>(n, 0));

    for (int x = 0; x < n; ++x) {
        if (x == 0) {
            jump[0][x] = x;
            count[0][x] = 0;
        } else {
            if (a[x - 1] <= a[x]) {
                jump[0][x] = x - 1;
                if (a[x - 1] == a[x]) {
                    count[0][x] = 1;
                } else {
                    count[0][x] = 0;
                }
            } else {
                jump[0][x] = x;
                count[0][x] = 0;
            }
        }
    }

    for (int j = 1; j < LOG; ++j) {
        for (int x = 0; x < n; ++x) {
            int prev = jump[j - 1][x];
            jump[j][x] = jump[j - 1][prev];
            if (count[j - 1][x] >= (k + 1) || count[j - 1][prev] >= (k + 1)) {
                count[j][x] = k + 1;
            } else {
                count[j][x] = count[j - 1][x] + count[j - 1][prev];
                if (count[j][x] > k) {
                    count[j][x] = k + 1;
                }
            }
        }
    }

    vector<int> res;
    res.reserve(m);

    for (int i = 0; i < m; ++i) {
        int q = queries[i];
        int x = q - 1;
        int remaining_k = k;
        for (int j = LOG - 1; j >= 0; --j) {
            if (jump[j][x] != x && count[j][x] <= remaining_k) {
                remaining_k -= count[j][x];
                x = jump[j][x];
                if (remaining_k < 0) break;
            }
        }
        res.push_back(x + 1);
    }

    for (int i = 0; i < m; ++i) {
        if (i > 0) cout << ' ';
        cout << res[i];
    }
    cout << '\n';

    return 0;
}