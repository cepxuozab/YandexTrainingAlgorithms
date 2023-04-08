#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

mt19937 rnd(1928);

class Tree {
public:
    class Node {
    public:
        Node* left;
        Node* right;
        int segLeft;
        int segRight;
        int heapKey;
        int size;
        Node() : left(nullptr), right(nullptr), segLeft(0), segRight(0),
            heapKey(rnd()), size(1) {}
        Node(int _segLeft, int _segRight) : left(nullptr), right(nullptr),
            segLeft(_segLeft), segRight(_segRight), heapKey(rnd()), size(1) {}
        ~Node() = default;
    };

private:
    Node* root;
    void delete_dfs(Node* cur) {
        if (!cur) {
            return;
        }
        if (cur->left) {
            delete_dfs(cur->left);
        }
        if (cur->right) {
            delete_dfs(cur->right);
        }
        delete(cur);
        return;
    }

    int get_size(Node* x) const {
        if (!x) {
            return 0;
        }
        else {
            return x->size;
        }
    }

    void relax(Node* root) const {
        root->size = get_size(root->left) + get_size(root->right) + 1;
    }

    Node* merge(Node* a, Node* b) {
        if (!a) {
            return b;
        }
        if (!b) {
            return a;
        }
        if (a->heapKey >= b->heapKey) {
            a->right = merge(a->right, b);
            relax(a);
            return a;
        }
        else {
            b->left = merge(a, b->left);
            relax(b);
            return b;
        }
    }

    pair<Node*, Node*> split_right(Node* r, int key) {
        if (!r) {
            return { nullptr, nullptr };
        }
        if (r->segLeft <= key) {
            Node* leftPart;
            Node* rightPart;
            tie(leftPart, rightPart) = split_right(r->right, key);
            r->right = leftPart;
            relax(r);
            return { r, rightPart };
        }
        else {
            Node* leftPart;
            Node* rightPart;
            tie(leftPart, rightPart) = split_right(r->left, key);
            r->left = rightPart;
            relax(r);
            return { leftPart, r };
        }
    }

    pair<Node*, Node*> split_left(Node* r, int key) {
        if (!r) {
            return { nullptr, nullptr };
        }
        if (r->segRight < key) {
            Node* leftPart;
            Node* rightPart;
            tie(leftPart, rightPart) = split_left(r->right, key);
            r->right = leftPart;
            relax(r);
            return { r, rightPart };
        }
        else {
            Node* leftPart;
            Node* rightPart;
            tie(leftPart, rightPart) = split_left(r->left, key);
            r->left = rightPart;
            relax(r);
            return { leftPart, r };
        }
    }

public:
    Tree() : root(nullptr) {}
    Tree(Node* _root) : root(_root) {}
    ~Tree() {
        delete_dfs(root);
    }

    void insert(int left, int right) {
        Node* lKey;
        Node* mKey;
        Node* gKey;
        tie(lKey, gKey) = split_right(root, right);
        tie(lKey, mKey) = split_left(lKey, left);
        delete_dfs(mKey);
        mKey = new Node(left, right);
        root = merge(lKey, mKey);
        root = merge(root, gKey);
    }

    int size() const {
        return get_size(root);
    }
};

int main() {
    Tree cartesianTree;
    int n, m;
    cin >> m >> n;
    int l, r;
    while (n--) {
        cin >> l >> r;
        cartesianTree.insert(l, r);
    }
    cout << cartesianTree.size();
}