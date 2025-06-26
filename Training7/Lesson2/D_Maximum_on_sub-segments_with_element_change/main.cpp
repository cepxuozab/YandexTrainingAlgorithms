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

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return INT_MIN;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left_val = query(2 * node + 1, start, mid, l, r);
        int right_val = query(2 * node + 2, mid + 1, end, l, r);
        return max(left_val, right_val);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx, val);
    }

    int query(int l, int r) {
        return query(0, 0, n - 1, l, r);
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
        if (type == 's') {
            int l, r;
            cin >> l >> r;
            // Переводим в 0-индексацию
            int max_val = st.query(l - 1, r - 1);
            results.push_back(max_val);
        } else if (type == 'u') {
            int idx, val;
            cin >> idx >> val;
            // Переводим в 0-индексацию
            st.update(idx - 1, val);
        }
    }

    for (int val : results) {
        cout << val << ' ';
    }
    cout << '\n';

    return 0;
}