#include <algorithm>
#include <climits>
#include <iostream>
#include <memory>

[[maybe_unused]] auto const FASTIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct TNode {
    TNode(int value)
        : value_(value)
    {
    }

    int value_;
    std::unique_ptr<TNode> left_;
    std::unique_ptr<TNode> right_;
};

auto Add(std::unique_ptr<TNode> tree, int value)->std::unique_ptr<TNode>;

auto Height(TNode* node) -> int;

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    std::unique_ptr<TNode> tree;
    int x;
    while (std::cin >> x && x != 0) {
        tree = Add(std::move(tree), x);
    }
    std::cout << Height(tree.get()) << std::endl;
    return 0;
}

auto Add(std::unique_ptr<TNode> tree, int value) -> std::unique_ptr<TNode>
{

    if (!tree) {
        return std::make_unique<TNode>(value);
    }
    if (tree->value_ == value) {
        return std::move(tree);
    }
    if (tree->value_ < value) {
        tree->right_ = Add(std::move(tree->right_), value);
    }
    else {
        tree->left_ = Add(std::move(tree->left_), value);
    }
    return std::move(tree);
}

auto Height(TNode* node) -> int
{
    if (node == nullptr) {
        return 0;
    }
    return 1 + std::max(Height(node->left_.get()), Height(node->right_.get()));
}
