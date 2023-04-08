#include <iostream>
#include <memory>
#include <numeric>
#include <ranges>
#include <set>
#include <unordered_map>
#include <vector>

class DSU {
    std::vector<int> rank;
    std::vector<int> parent;

public:
    DSU(int n);

    auto findParent(int node) -> int;

    void Union(int x, int y);
};

auto main() -> int
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n;
    int m;
    std::cin >> n >> m;
    auto dsu = std::make_unique<DSU>(n);
    for (int i = 0; i < m; ++i) {
        int x;
        int y;
        std::cin >> x >> y;
        x--, y--;
        dsu->Union(x, y);
    }
    std::unordered_map<int, std::set<int>> maps;
    for (int i = 0; i < n; ++i) {
        maps[dsu->findParent(i)].insert(i);
    }

    std::cout << maps.size() << std::endl;

    for (auto const& val : std::views::values(maps)) {
        std::cout << val.size() << std::endl;
        for (int i : val) {
            std::cout << i + 1 << ' ';
        }
        std::cout << std::endl;
    }
}

DSU::DSU(int n)
    : rank(n + 1)
    , parent(n + 1)
{
    std::iota(parent.begin(), parent.end(), 0);
}

auto DSU::findParent(int node) -> int
{
    if (parent[node] == node) {
        return node;
    }
    return parent[node] = findParent(parent[node]);
}
void DSU::Union(int x, int y)
{
    int px = findParent(x);
    int py = findParent(y);
    if (px == py) {
        return;
    }
    if (rank[px] < rank[py]) {
        parent[px] = py;
    }
    else if (rank[px] > rank[py]) {
        parent[py] = px;
    }
    else {
        parent[px] = py;
        rank[py]++;
    }
}
