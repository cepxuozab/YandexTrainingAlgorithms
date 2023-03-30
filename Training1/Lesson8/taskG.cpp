#include <iostream>
#include <memory>

[[maybe_unused]] auto const FastIO = []() {
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

auto Add(std::unique_ptr<TNode> tree, int value) -> std::unique_ptr<TNode>;

template <typename Callback>
void InorderTraversal(TNode* root, Callback callback);

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    std::unique_ptr<TNode> tree;
    int x;

    while (std::cin >> x && x != 0) {
        tree = Add(std::move(tree), x);
    }
    auto predicate = [](TNode* node) {
        return node->left_ == nullptr ^ node->right_ == nullptr;
    };

    auto callback = [predicate](TNode* node) {
        if (predicate(node)) { std::cout << node->value_ << ' '; } };

    InorderTraversal(tree.get(), callback);

    return 0;
}

TNode::TNode(int value)
    : value_(value)
{
}

auto Add(std::unique_ptr<TNode> tree, int value) -> std::unique_ptr<TNode>
{

    if (tree == nullptr) {
        return std::make_unique<TNode>(value);
    }
    if (tree->value_ == value) {
        return std::move(tree);
    }
    if (tree->value_ < value) {
        tree->right_ = Add(std::move(tree->right_), value);
    } else {
        tree->left_ = Add(std::move(tree->left_), value);
    }
    return std::move(tree);
}

template <typename Callback>
void InorderTraversal(TNode* root, Callback callback)
{
    if (root == nullptr) {
        return;
    }
    InorderTraversal(root->left_.get(), callback);
    callback(root);
    InorderTraversal(root->right_.get(), callback);
}
