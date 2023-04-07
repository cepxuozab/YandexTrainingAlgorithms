#include <iostream>
#include <string>
#include <vector>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

struct Node {
    Node* left_subtree = nullptr;
    Node* right_subtree = nullptr;
    Node* parent = nullptr;
    int child_type{};
};

void walk(Node* tree_root, std::vector<std::string>& res, std::string path = "") {
    if (tree_root != nullptr) {
        if (tree_root->left_subtree != nullptr) {
            walk(tree_root->left_subtree, res, path + "0");
        }
        if (tree_root->left_subtree == nullptr && tree_root->right_subtree == nullptr) {
            res.push_back(path + "\n");

        }
        if (tree_root->right_subtree != nullptr) {
            walk(tree_root->right_subtree, res, path + "1");
        }

    }
}
int main()
{
    freopen("input.txt", "r", stdin);
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        Node left{}, right{};
        Node tree = Node{ &left, &right, nullptr, 0 };
        Node* root = tree.left_subtree;
        Node* current = root;
        std::string line;
        std::cin >> line;
        for (char command : line) {
            if (command == 'D') {
                Node* new_elem = new Node{ nullptr, nullptr, current, -1 };
                current->left_subtree = new_elem;
                current = new_elem;
            }
            else if (command == 'U') {
                while (current->child_type == 1) {
                    current = current->parent;
                }
                current = current->parent;
                Node* new_element = new Node{ nullptr,nullptr,current,1 };
                current->right_subtree = new_element;
                current = new_element;
            }
        }
        tree = *tree.left_subtree;
        std::vector<std::string> results;
        walk(&tree, results);
        std::cout << results.size() << '\n';
        for (auto str : results) {
            std::cout << str;
        }

    }
}
