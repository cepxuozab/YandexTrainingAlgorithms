#include <iostream>
#include <vector>
#include <numeric>  // std::iota
#include <unordered_set>

class DSU {
public:
    DSU(int n) : parent(n), size(n, 1) {
        std::iota(parent.begin(), parent.end(), 0); // parent[i] = i
    }

    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]); // path compression
        return parent[u];
    }

    void unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
        if (pu == pv) return;
        if (size[pu] < size[pv]) std::swap(pu, pv);
        parent[pv] = pu;
        size[pu] += size[pv];
    }

    int count_components() {
        std::unordered_set<int> roots;
        for (int i = 0; i < parent.size(); ++i) {
            roots.insert(find(i));
        }
        return roots.size();
    }

private:
    std::vector<int> parent;
    std::vector<int> size;
};

int main() {
    int n;
    std::cin >> n;

    std::vector<int> keys(n);
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        keys[i] = x - 1; // переводим в 0-индексацию
    }

    DSU dsu(n);
    for (int i = 0; i < n; ++i) {
        dsu.unite(i, keys[i]);
    }

    std::cout << dsu.count_components() << '\n';
    return 0;
}
