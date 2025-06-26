#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

constexpr unsigned DEFAULT = numeric_limits<unsigned>::min();

struct SegmentTreeNode {
    unsigned value;
    unsigned to_add;
};

class SegmentTree {
private:
    vector<SegmentTreeNode> tree;
    int tree_size;
    int n;

    int closestPower2(int a) {
        --a;
        a |= a >> 1;
        a |= a >> 2;
        a |= a >> 4;
        a |= a >> 8;
        a |= a >> 16;
        return ++a;
    }

    void buildTree() {
        int i = tree.size() / 2;
        int count = i + n;

        tree[0] = {DEFAULT, 0};

        while (i < count) {
            cin >> tree[i].value;
            tree[i].to_add = 0;
            ++i;
        }

        while (i < (int)tree.size()) {
            tree[i] = {DEFAULT, 0};
            ++i;
        }

        for (int j = tree.size() / 2 - 1; j > 0; --j) {
            tree[j].value = max(tree[2*j].value, tree[2*j+1].value);
            tree[j].to_add = 0;
        }
    }

    SegmentTreeNode& maxNode(SegmentTreeNode& a, SegmentTreeNode& b) {
        return (a.value + a.to_add) > (b.value + b.to_add) ? a : b;
    }

    void pushLazy(size_t node, int low, int high) {
        if (tree[node].to_add == 0) return;
        
        tree[node].value += tree[node].to_add;
        
        if (low < high) {
            tree[2*node].to_add += tree[node].to_add;
            tree[2*node+1].to_add += tree[node].to_add;
        }
        
        tree[node].to_add = 0;
    }

public:
    SegmentTree(int size) : n(size) {
        tree_size = closestPower2(n);
        tree.resize(2 * tree_size);
        buildTree();
    }

    unsigned get(int index) {
        size_t node = 1;
        int low = 1, high = tree_size;
        
        while (low < high) {
            pushLazy(node, low, high);
            
            int mid = (low + high) / 2;
            if (index <= mid) {
                node = 2 * node;
                high = mid;
            } else {
                node = 2 * node + 1;
                low = mid + 1;
            }
        }
        
        pushLazy(node, low, high);
        return tree[node].value;
    }

    void rangeAdd(int l, int r, unsigned value) {
        updateTree(1, 1, tree_size, l, r, value);
    }

private:
    void updateTree(size_t node, int low, int high, int l, int r, unsigned value) {
        pushLazy(node, low, high);
        
        if (r < low || l > high) return;
        
        if (l <= low && high <= r) {
            tree[node].to_add += value;
            pushLazy(node, low, high);
            return;
        }
        
        int mid = (low + high) / 2;
        updateTree(2*node, low, mid, l, r, value);
        updateTree(2*node+1, mid+1, high, l, r, value);
        
        tree[node].value = max(tree[2*node].value + tree[2*node].to_add,
                             tree[2*node+1].value + tree[2*node+1].to_add);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    SegmentTree st(n);

    int k;
    cin >> k;
    vector<unsigned> results;
    while (k--) {
        char command;
        cin >> command;

        if (command == 'g') {
            int i;
            cin >> i;
            results.push_back(st.get(i));
        } else if (command == 'a') {
            int l, r, value;
            cin >> l >> r >> value;
            st.rangeAdd(l, r, value);
        }
    }

    for (auto res : results) {
        cout << res << ' ';
    }
    cout << '\n';

    return 0;
}