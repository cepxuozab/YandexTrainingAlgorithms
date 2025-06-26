#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r, int x) {
        if (r < start || end < l) {
            return -1;
        }
        if (l <= start && end <= r) {
            if (tree[node] < x) {
                return -1;
            }
            if (start == end) {
                return start;
            }
        }
        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r, x);
        if (left != -1) {
            return left;
        }
        return query(2 * node + 2, mid + 1, end, l, r, x);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void set(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

    int get(int i, int x) {
        int res = query(0, 0, n - 1, i, n - 1, x);
        return res == -1 ? -1 : res + 1; // Переводим в 1-индексацию
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegmentTree st(a);

    for (int i = 0; i < m; ++i) {
        int t, idx, x;
        cin >> t >> idx >> x;
        if (t == 0) {
            st.set(idx - 1, x); // Переводим в 0-индексацию
        } else {
            int res = st.get(idx - 1, x); // Переводим в 0-индексацию
            cout << res << '\n';
        }
    }

    return 0;
}