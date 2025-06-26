#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr int X = 257;
constexpr int P = 1'000'000'007;

class SegmentTree {
    struct Node {
        int l, r;
        ll val = 0;
        int lazy = 0;
    };

    vector<Node> tree;
    vector<ll> xp, xpsum;
    int size;

    void build(int v, int tl, int tr, const vector<int>& arr) {
        tree[v].l = tl;
        tree[v].r = tr;
        if (tl == tr) {
            if (tl < (int)arr.size()) {
                tree[v].val = arr[tl];
            }
            return;
        }
        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, arr);
        build(v * 2 + 1, tm + 1, tr, arr);
        merge(v);
    }

    void push(int v) {
        if (tree[v].lazy) {
            apply(v * 2, tree[v].lazy);
            apply(v * 2 + 1, tree[v].lazy);
            tree[v].lazy = 0;
        }
    }

    void apply(int v, int value) {
        int len = tree[v].r - tree[v].l + 1;
        tree[v].val = (xpsum[len - 1] * value) % P;
        tree[v].lazy = value;
    }

    void merge(int v) {
        int lenR = tree[v * 2 + 1].r - tree[v * 2 + 1].l + 1;
        tree[v].val = (tree[v * 2].val * xp[lenR] + tree[v * 2 + 1].val) % P;
    }

    void assign(int v, int l, int r, int value) {
        if (r < tree[v].l || tree[v].r < l) return;
        if (l <= tree[v].l && tree[v].r <= r) {
            apply(v, value);
            return;
        }
        push(v);
        assign(v * 2, l, r, value);
        assign(v * 2 + 1, l, r, value);
        merge(v);
    }

    ll query(int v, int l, int r) {
        if (r < tree[v].l || tree[v].r < l) return 0;
        if (l <= tree[v].l && tree[v].r <= r) return tree[v].val;
        push(v);
        ll left = query(v * 2, l, r);
        ll right = query(v * 2 + 1, l, r);
        int rlen = max(0, min(tree[v * 2 + 1].r, r) - max(tree[v * 2 + 1].l, l) + 1);
        return (left * xp[rlen] + right) % P;
    }

public:
    SegmentTree(const vector<int>& arr) {
        int n = arr.size();
        size = 1;
        while (size < n) size <<= 1;
        tree.resize(size * 2);
        xp.assign(n + 2, 1);
        xpsum.assign(n + 2, 1);
        for (int i = 1; i <= n; ++i) {
            xp[i] = xp[i - 1] * X % P;
            xpsum[i] = (xpsum[i - 1] + xp[i]) % P;
        }
        build(1, 0, size - 1, arr);
    }

    void assign(int l, int r, int value) {
        assign(1, l, r, value);
    }

    bool compare(int l1, int l2, int len) {
        return query(1, l1, l1 + len - 1) == query(1, l2, l2 + len - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int& x : arr) cin >> x;

    SegmentTree st(arr);

    int q;
    cin >> q;
    while (q--) {
        int t, l, r, k;
        cin >> t >> l >> r >> k;
        --l; --r;
        if (t == 0) {
            st.assign(l, r, k);
        } else {
            if (st.compare(l, r, k))
                cout << '+';
            else
                cout << '-';
        }
    }
    cout << '\n';
}
