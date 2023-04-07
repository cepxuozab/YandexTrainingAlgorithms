#include <iostream>
#include <memory>
#include <string>

using namespace std::string_literals;

struct TNode {
    TNode() = default;
    TNode(int value)
        : value_(value)
    {
    }

    int value_;
    std::unique_ptr<TNode> left_;
    std::unique_ptr<TNode> right_;
};

bool Contains(TNode* tree, int value)
{
    if (!tree) {
        return false;
    }
    else if (tree->value_ == value) {
        return true;
    }
    else if (tree->value_ < value) {
        return Contains(tree->right_.get(), value);
    }
    else {
        return Contains(tree->left_.get(), value);
    }
}

std::unique_ptr<TNode> Add(std::unique_ptr<TNode> tree, int value)
{
    if (!tree) {
        return std::make_unique<TNode>(value);
    }

    if (tree->value_ < value) {
        tree->right_ = Add(std::move(tree->right_), value);
    }
    else {
        tree->left_ = Add(std::move(tree->left_), value);
    }
    return std::move(tree);
}
void print_tree(TNode* p, int level)

{

    if (p == nullptr) {
        return;
    }

    print_tree(p->left_.get(), level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << ".";
    }

    std::cout << p->value_ << std::endl;

    print_tree(p->right_.get(), level + 1);
}

int main()
{
    freopen("input.txt", "r", stdin);
    std::unique_ptr<TNode> root = nullptr;
    for (std::string str; getline(std::cin, str);) {
        if (str == "PRINTTREE"s) {
            print_tree(root.get(), 0);
            continue;
        }
        std::string command = str.substr(0, str.find(' '));
        int value = stoi(str.substr(str.find(' ') + 1));
        bool isContain = Contains(root.get(), value);
        if (command == "ADD"s) {
            if (isContain) {
                puts("ALREADY");
            }
            else {
                puts("DONE");
                root = Add(std::move(root), value);
            }
        }
        else {
            isContain ? puts("YES") : puts("NO");
        }
    }
}
