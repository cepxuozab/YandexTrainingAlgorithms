#include <iostream>
#include <vector>

class DSU {
private:
    std::vector<size_t> parent;
    std::vector<size_t> size;
public:
    DSU(size_t n) : parent(n + 1), size(n + 1, 1) {
        for (size_t i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }

    size_t find(size_t v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);  // компрессия пути
    }

    bool unite(size_t a, size_t b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return false;
        if (size[a] < size[b])
            std::swap(a, b);
        parent[b] = a;
        size[a] += size[b];
        return true;
    }

    size_t get_size(size_t v) {
        return size[find(v)];
    }
};

int main() {
    size_t n, m;
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << 0 << '\n';
        return 0;
    }

    DSU dsu(n);
    for (size_t i = 1; i <= m; ++i) {
        size_t a, b;
        std::cin >> a >> b;
        if (dsu.unite(a, b)) {
            if (dsu.get_size(a) == n) {
                std::cout << i << '\n';
                break;
            }
        }
    }

    return 0;
}
