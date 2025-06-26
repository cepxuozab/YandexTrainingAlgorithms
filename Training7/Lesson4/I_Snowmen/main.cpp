#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class PersistentStack {
public:
    struct Node {
        Node* prev;
        T value;

        Node(Node* prev, T value) : prev(prev), value(value) {}
    };

    std::vector<Node*> tails_;
    std::vector<Node*> unique_tails_;

    PersistentStack() { tails_.push_back(nullptr); }

    inline void Push(size_t version, T value) {
        Node* tail = tails_[version];
        auto node = new Node(tail, value);
        tails_.push_back(node);
        unique_tails_.push_back(node);
    }

    inline void Pop(size_t version) {
        Node* tail = tails_[version];
        tails_.push_back(tail->prev);        
    }

    inline T Top(size_t version) {
        return tails_[version]->value;
    }

    ~PersistentStack() {
        for (const auto& tail : unique_tails_) {
            delete tail;
        }
    }
};

int main() {
    size_t n;
    std::cin >> n;
    PersistentStack<long long> st;
    std::vector<long long> masses(n + 1);
    long long total_mass = 0ll;
    for (size_t i = 1; i <= n; ++i) {
        size_t version;
        long long mass;
        std::cin >> version >> mass;
        if (mass != 0) {
            st.Push(version, mass);
            masses[i] = masses[version] + mass;
            total_mass += masses[i];
        } else {
            mass = st.Top(version);
            st.Pop(version);
            masses[i] = masses[version] - mass;
            total_mass += masses[i];
        }
    }

    std::cout << total_mass << '\n';

    return 0;
}