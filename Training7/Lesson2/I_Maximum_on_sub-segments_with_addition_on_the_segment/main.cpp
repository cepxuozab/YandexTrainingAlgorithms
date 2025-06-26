#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    vector<int> lazy;
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

    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] += lazy[node];
            if (start != end) {
                lazy[2 * node + 1] += lazy[node];
                lazy[2 * node + 2] += lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(int node, int start, int end, int l, int r, int val) {
        push(node, start, end);
        if (start > end || start > r || end < l) {
            return;
        }
        if (start >= l && end <= r) {
            lazy[node] += val;
            push(node, start, end);
            return;
        }
        int mid = (start + end) / 2;
        update_range(2 * node + 1, start, mid, l, r, val);
        update_range(2 * node + 2, mid + 1, end, l, r, val);
        tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
    }

    int query_max(int node, int start, int end, int l, int r) {
        push(node, start, end);
        if (start > end || start > r || end < l) {
            return INT_MIN;
        }
        if (start >= l && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = query_max(2 * node + 1, start, mid, l, r);
        int right = query_max(2 * node + 2, mid + 1, end, l, r);
        return max(left, right);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    void add(int l, int r, int val) {
        update_range(0, 0, n - 1, l - 1, r - 1, val);
    }

    int max_query(int l, int r) {
        return query_max(0, 0, n - 1, l - 1, r - 1);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    SegmentTree st(arr);

    int M;
    cin >> M;
    vector<int> results;
    for (int i = 0; i < M; ++i) {
        char type;
        cin >> type;
        if (type == 'm') {
            int l, r;
            cin >> l >> r;
            results.push_back(st.max_query(l, r));
        } else if (type == 'a') {
            int l, r, add;
            cin >> l >> r >> add;
            st.add(l, r, add);
        }
    }

    for (int res : results) {
        cout << res << ' ';
    }
    cout << '\n';

    return 0;
}