#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

using namespace std;
#define len(v) (int) (v).size()
#define all(v) v.begin(), (v).end()
#define int long long

struct SegmentTree {
    vector<int> tree;
    int len1;

    void init(int n) {
        len1 = n;
        tree.assign(4 * n, (int) -1e18);
    }

    void build(vector<int>& a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            tree[x] = a[lx];
            return;
        } else {
            int m = (lx + rx) / 2;
            build(a, 2 * x + 1, lx, m);
            build(a, 2 * x + 2, m, rx);
            tree[x] = max(tree[2 * x + 1], tree[2 * x + 2]);
        }
    }

    void build(vector<int>& a) {
        init(len(a));
        build(a, 0, 0, len1);
    }

    auto maximum(int l, int r, int x, int lx, int rx) -> int {
        if (l >= rx || r <= lx) {
            return (int) -1e18;
        }
        if (lx >= l && rx <= r) {
            return tree[x];
        }
        int m = (lx + rx) / 2;
        int num1 = maximum(l, r, 2 * x + 1, lx, m);
        int num2 = maximum(l, r, 2 * x + 2, m, rx);
        return max(num1, num2);
    }

    auto get_max(int l, int r) -> int {
        return maximum(l, r, 0, 0, len1);
    }
};

void solve() {
    int n, H;
    cin >> n >> H;
    vector<pair<int, int>> a(n);
    bool k1 = true;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i].second;
        if (a[i].second != 1) k1 = false;
    }
    sort(all(a));
    if (k1) {
        if (H == 1) {
            cout << 0;
            return;
        }
        int ans = (int) 1e18;
        multiset<int> cur;
        for (int i = 0; i < H - 1; ++i) {
            cur.insert(a[i + 1].first - a[i].first);
        }
        ans = *cur.rbegin();
        int l = 0;
        for (int i = H - 1; i < n - 1; ++i) {
            cur.erase(cur.find(abs(a[l].first - a[l + 1].first)));
            l++;
            cur.insert(a[i + 1].first - a[i].first);
            ans = min(ans, *cur.rbegin());
        }
        cout << ans;
        return;
    }

    int ans = (int) 1e18;
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i].second;
        if (a[i].second >= H) {
            cout << 0;
            return;
        }
    }

    vector<int> raz(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        raz[i] = a[i + 1].first - a[i].first;
    }
    SegmentTree st;
    st.build(raz);
    for (int i = 0; i < n - 1; ++i) {
        int l = i, r = n;
        bool have = false;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            int sm = pref[mid + 1] - pref[i];
            if (sm >= H) {
                have = true;
                r = mid;
            } else {
                l = mid;
            }
        }
        if (!have) continue;
        int mx = st.get_max(i, r);
        ans = min(ans, mx);
    }
    cout << ans;
}

auto main() -> signed {  // NOLINT
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tt = 1;
    while (tt--) {
        solve();
    }
    return 0;
}