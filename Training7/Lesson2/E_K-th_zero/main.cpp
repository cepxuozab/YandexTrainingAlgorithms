#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = (arr[start] == 0) ? 1 : 0;
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = (val == 0) ? 1 : 0;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    int query(int node, int start, int end, int l, int r, int k) {
        if (start == end) {
            return (k == 1 && tree[node] == 1) ? start : -1;
        }
        int mid = (start + end) / 2;
        int left_zeros = (l <= mid) ? tree[2 * node + 1] : 0;
        if (left_zeros >= k) {
            return query(2 * node + 1, start, mid, l, r, k);
        } else {
            return query(2 * node + 2, mid + 1, end, l, r, k - left_zeros);
        }
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

    int query(int l, int r, int k) {
        if (query(0, 0, n - 1, l, r, 1) == -1) {
            return -1;
        }
        int total_zeros = query(0, 0, n - 1, l, r, k);
        if (total_zeros == -1) {
            return -1;
        }
        return total_zeros + 1; // Переводим в 1-индексацию
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
            int l, r, k;
            cin >> l >> r >> k;
            // Переводим в 0-индексацию
            int idx = st.query(l - 1, r - 1, k);
            results.push_back(idx);
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