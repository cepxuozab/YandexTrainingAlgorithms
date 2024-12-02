#include <iostream>
#include <string>

struct Node {
  int val{};
  Node* left = nullptr;
  Node* right = nullptr;
};

class BinarySearchTree {
  Node* root = nullptr;

 public:
  bool Add(int val) { return Add(root, val); }
  bool Search(int val) { return Search(root, val); }
  void Print() { Print(root); }
  ~BinarySearchTree() { Clear(root); }

 private:
  static bool Add(Node*& node, int val);
  static bool Search(Node* node, int val);
  static void Print(Node* node, int level = 0);
  static void Clear(Node*& node);
};

int main() {
  BinarySearchTree tree;
  for (std::string str; std::cin >> str;) {
    if (str == "ADD") {
      int val;
      std::cin >> val;
      tree.Add(val) ? puts("DONE") : puts("ALREADY");
    } else if (str == "SEARCH") {
      int val;
      std::cin >> val;
      tree.Search(val) ? puts("YES") : puts("NO");
    } else {
      tree.Print();
    }
  }
}

bool BinarySearchTree::Add(Node*& node, int val) {
  if (node == nullptr) {
    node = new Node(val);
    return true;
  }
  if (node->val == val) {
    return false;
  }
  return node->val > val ? Add(node->left, val) : Add(node->right, val);
}
bool BinarySearchTree::Search(Node* node, int val) {
  if (!node) {
    return false;
  }
  if (node->val == val) {
    return true;
  }
  return node->val > val ? Search(node->left, val) : Search(node->right, val);
}
void BinarySearchTree::Print(Node* node, int level) {
  if (!node) {
    return;
  }
  Print(node->left, level + 1);
  std::cout << std::string(level, '.') << node->val << '\n';
  Print(node->right, level + 1);
}

void BinarySearchTree::Clear(Node*& node) {
  if (!node) {
    return;
  }
  Clear(node->left);
  Clear(node->right);
  delete node;
}
