#include <algorithm>
#include <iostream>
#include <memory>

[[maybe_unused]] auto const FASTIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct TNode {
    TNode(int value);
    int value_;
    std::unique_ptr<TNode> left_;
    std::unique_ptr<TNode> right_;
};

using PtrNode = std::unique_ptr<TNode>;

auto Push(PtrNode tree, int value, int& depth, bool& success) -> PtrNode;

auto main() -> int
{
    PtrNode tree;
    int x;
    while (std::cin >> x && x != 0) {
        int depth = 1;
        bool success = false;
        tree = Push(std::move(tree), x, depth, success);
        if (success) {
            std::cout << depth << ' ';
        }
    }
    return 0;
}

TNode::TNode(int value)
    : value_(value)
{
}

auto Push(PtrNode tree, int value, int& depth, bool& success) -> PtrNode
{
    if (!tree) {
        success = true;
        return std::make_unique<TNode>(value);
    }
    if (tree->value_ == value) {
        success = false;
        return std::move(tree);
    }

    depth++;
    success = true;
    if (tree->value_ < value) {
        tree->right_ = Push(std::move(tree->right_), value, depth, success);
    } else {
        tree->left_ = Push(std::move(tree->left_), value, depth, success);
    }
    return std::move(tree);
}
