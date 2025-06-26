#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Node {
    int value;
    int index;
};

class SegmentTree {
private:
    vector<Node> tree;
    int size;

    Node merge(Node a, Node b) {
        if (a.value > b.value) return a;
        else return b;
    }

    void build(const vector<int>& arr, int node, int left, int right) {
        if (left == right) {
            tree[node] = {arr[left], left + 1}; // +1 для 1-индексации
            return;
        }
        int mid = (left + right) / 2;
        build(arr, 2 * node + 1, left, mid);
        build(arr, 2 * node + 2, mid + 1, right);
        tree[node] = merge(tree[2 * node + 1], tree[2 * node + 2]);
    }

    Node query(int node, int node_left, int node_right, int query_left, int query_right) {
        if (node_right < query_left || node_left > query_right) {
            return {INT_MIN, -1}; // нейтральный элемент
        }
        if (query_left <= node_left && node_right <= query_right) {
            return tree[node];
        }
        int mid = (node_left + node_right) / 2;
        Node left_res = query(2 * node + 1, node_left, mid, query_left, query_right);
        Node right_res = query(2 * node + 2, mid + 1, node_right, query_left, query_right);
        return merge(left_res, right_res);
    }

public:
    SegmentTree(const vector<int>& arr) {
        size = arr.size();
        tree.resize(4 * size);
        build(arr, 0, 0, size - 1);
    }

    Node query(int l, int r) {
        return query(0, 0, size - 1, l - 1, r - 1); // переводим в 0-индексацию
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

    int K;
    cin >> K;
    while (K--) {
        int l, r;
        cin >> l >> r;
        Node result = st.query(l, r);
        cout << result.value << ' ' << result.index << '\n';
    }

    return 0;
}