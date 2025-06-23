#include <iostream>
#include <string>
#include <memory>

struct Node {
    int val;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    explicit Node(int v) : val(v) {}
};

bool add(Node* root, int val) {
    if (root->val == val) return false;
    if (val < root->val) {
        if (!root->left) {
            root->left = std::make_unique<Node>(val);
            return true;
        }
        return add(root->left.get(), val);
    } else {
        if (!root->right) {
            root->right = std::make_unique<Node>(val);
            return true;
        }
        return add(root->right.get(), val);
    }
}

bool find(const Node* root, int val) {
    if (!root) return false;
    if (root->val == val) return true;
    if (val < root->val) return find(root->left.get(), val);
    return find(root->right.get(), val);
}

void print_tree(const Node* root, int depth) {
    if (!root) return;
    print_tree(root->left.get(), depth + 1);
    std::cout << std::string(depth, '.') << root->val << '\n';
    print_tree(root->right.get(), depth + 1);
}

void binary_search_tree() {
    std::unique_ptr<Node> root = nullptr;
    std::string request;

    while (std::getline(std::cin, request)) {
        if (request.empty()) continue;

        if (request == "PRINTTREE") {
            print_tree(root.get(), 0);
            continue;
        }

        auto space_pos = request.find(' ');
        if (space_pos == std::string::npos) continue;  // Некорректная команда

        auto cmd = request.substr(0, space_pos);
        int val = std::stoi(request.substr(space_pos + 1));

        if (cmd == "ADD") {
            if (!root) {
                root = std::make_unique<Node>(val);
                std::cout << "DONE\n";
            } else if (add(root.get(), val)) {
                std::cout << "DONE\n";
            } else {
                std::cout << "ALREADY\n";
            }
        } else if (cmd == "SEARCH") {
            std::cout << (find(root.get(), val) ? "YES\n" : "NO\n");
        }
    }
}

int main() {
    binary_search_tree();
    return 0;
}
