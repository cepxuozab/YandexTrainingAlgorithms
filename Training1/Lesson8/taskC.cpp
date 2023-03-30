#include <climits>
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

auto Add(PtrNode tree, int value)->PtrNode;

auto SecondMax(TNode* root) -> int;

auto main() -> int
{
    freopen("input.txt", "r", stdin);

    PtrNode tree;
    int x;
    while (std::cin >> x && x != 0) {
        tree = Add(std::move(tree), x);
    }
    std::cout << SecondMax(tree.get()) << std::endl;
    return 0;
}

TNode::TNode(int value)
    : value_(value)
{
}

auto Add(PtrNode tree, int value) -> PtrNode
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

auto SecondMax(TNode* root) -> int
{
    TNode* pre = root;
    TNode* cur = root;
    while (cur->right_ != nullptr) {
        pre = cur;
        cur = cur->right_.get();
    }
    if (cur->left_ != nullptr) {
        cur = cur->left_.get();
        while (cur->right_ != nullptr) {
            cur = cur->right_.get();
        }
        return cur->value_;
    }

    return (cur == root && pre == root) ? INT_MIN : pre->value_;
}
