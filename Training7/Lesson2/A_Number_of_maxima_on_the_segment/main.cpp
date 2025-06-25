#include <iostream>
#include <vector>
#include <limits>

#define DEFAULT std::numeric_limits<int>::min()

struct SegmentTreeNode {
    int value;
    int count;
};

int ClosestPower2(int a) {
    --a;
    a |= a >> 1;
    a |= a >> 2;
    a |= a >> 4;
    a |= a >> 8;
    a |= a >> 16;
    ++a;

    return a;
}

void BuildTree(std::vector<SegmentTreeNode>& tree, int n) {
    size_t i = tree.size() / 2;
    size_t count = i + static_cast<size_t>(n);

    while (i < count) {
        std::cin >> tree[i].value;
        tree[i].count = 1;
        ++i;
    }

    while (i < tree.size()) {
        tree[i].value = DEFAULT;
        tree[i].count = 1;
        ++i;
    }

    for (size_t j = tree.size() / 2 - 1; j > 0; --j) {
        SegmentTreeNode& parent = tree[j];
        SegmentTreeNode& left = tree[2 * j];
        SegmentTreeNode& right = tree[2 * j + 1];

        if (left.value == right.value) {
            parent.value = left.value;
            parent.count = left.count + right.count;
        } else if (left.value > right.value) {
            parent = left;
        } else {
            parent = right;
        }
    }
}

SegmentTreeNode MaxNode(SegmentTreeNode& node1, SegmentTreeNode& node2) {
    if (node1.value == node2.value) {
        return {.value = node1.value, .count = node1.count + node2.count};
    } else if (node1.value > node2.value) {
        return node1;
    } else {
        return node2;
    }
}

SegmentTreeNode GetMax(std::vector<SegmentTreeNode>& tree, size_t i, int low, int high, int l, int r) {
    if (l <= low && r >= high) {
        return tree[i];
    } else if (r < low || l > high) {
        return {.value = DEFAULT, .count = 1};
    } else {
        SegmentTreeNode left = GetMax(tree, i * 2, low, (low + high) / 2, l, r);
        SegmentTreeNode right = GetMax(tree, i * 2 + 1, (low + high) / 2 + 1, high, l, r);
        return MaxNode(left, right);
    }
}

int main() {
    int n;
    std::cin >> n;
    int tree_size = ClosestPower2(n);
    std::vector<SegmentTreeNode> segment_tree(tree_size * 2);
    BuildTree(segment_tree, n);

    int k;
    std::cin >> k;
    while (k--) {
        int l, r;
        std::cin >> l >> r;
        SegmentTreeNode node = GetMax(segment_tree, 1, 1, tree_size, l, r);
        std::cout << node.value << ' ' << node.count << '\n';
    }

    return 0;
}