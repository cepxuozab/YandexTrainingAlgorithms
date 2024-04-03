#include <bits/stdc++.h>

using namespace std;

auto main() -> int {
    ios::sync_with_stdio(false);
    cin.tie();

    int w, h, n;
    cin >> w >> h >> n;
    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i].first >> p[i].second;
    }
    sort(p.begin(), p.end());
    vector<int> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = p[i].second;
    }
    vector<int> pref_min_y = y, pref_max_y = y;
    vector<int> suf_min_y = y, suf_max_y = y;
    for (int i = 1; i < n; ++i) {
        pref_min_y[i] = min(pref_min_y[i - 1], pref_min_y[i]);
        pref_max_y[i] = max(pref_max_y[i - 1], pref_max_y[i]);
    }
    for (int i = n - 2; i >= 0; --i) {
        suf_min_y[i] = min(suf_min_y[i], suf_min_y[i + 1]);
        suf_max_y[i] = max(suf_max_y[i], suf_max_y[i + 1]);
    }

    int cl = 1, cr = min(w, h);
    while (cl < cr) {
        int mid = (cl + cr) >> 1;
        int l = 0;
        for (int r = 0; r < n; ++r) {
            while (p[r].first - p[l].first >= mid) {
                ++l;
            }

            int max_y = max(l > 0 ? pref_max_y[l - 1] : -1, r + 1 < n ? suf_max_y[r + 1] : -1);
            int min_y = min(l > 0 ? pref_min_y[l - 1] : h + 1, r + 1 < n ? suf_min_y[r + 1] : h + 1);

            if (min_y == -1 || max_y - min_y + 1 <= mid) {
                cr = mid;
                goto nxt;
            }
        }
        cl = mid + 1;
        nxt:;
    }
    cout << cl;
}
