#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int max_len;    // Максимальная длина последовательности нулей в поддереве
    int left_len;   // Длина последовательности нулей слева
    int right_len;  // Длина последовательности нулей справа
    int total_len;  // Длина отрезка
};

class SegmentTree {
private:
    vector<Node> tree;
    int n;

    Node combine(const Node& left, const Node& right) {
        Node res;
        res.total_len = left.total_len + right.total_len;
        res.left_len = left.left_len;
        if (left.left_len == left.total_len) {
            res.left_len += right.left_len;
        }
        res.right_len = right.right_len;
        if (right.right_len == right.total_len) {
            res.right_len += left.right_len;
        }
        res.max_len = max({left.max_len, right.max_len, left.right_len + right.left_len});
        return res;
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node].max_len = (arr[start] == 0) ? 1 : 0;
            tree[node].left_len = tree[node].max_len;
            tree[node].right_len = tree[node].max_len;
            tree[node].total_len = 1;
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node].max_len = (val == 0) ? 1 : 0;
            tree[node].left_len = tree[node].max_len;
            tree[node].right_len = tree[node].max_len;
            tree[node].total_len = 1;
        } else {
            int mid = (start + end) / 2;
            if (idx <= mid) {
                update(2 * node + 1, start, mid, idx, val);
            } else {
                update(2 * node + 2, mid + 1, end, idx, val);
            }
            tree[node] = combine(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return {0, 0, 0, 0};
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        Node left = query(2 * node + 1, start, mid, l, r);
        Node right = query(2 * node + 2, mid + 1, end, l, r);
        return combine(left, right);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    void update(int idx, int val) {
        update(0, 0, n - 1, idx - 1, val); // Переводим в 0-индексацию
    }

    int query(int l, int r) {
        Node res = query(0, 0, n - 1, l - 1, r - 1); // Переводим в 0-индексацию
        return res.max_len;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    SegmentTree st(A);

    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        string cmd;
        cin >> cmd;
        if (cmd == "UPDATE") {
            int idx, x;
            cin >> idx >> x;
            st.update(idx, x);
        } else if (cmd == "QUERY") {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << '\n';
        }
    }

    return 0;
}