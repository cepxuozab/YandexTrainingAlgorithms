#include <iostream>
#include <set>

[[maybe_unused]] static auto const fastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
}();

int main()
{
    int n;
    int m;
    std::cin >> n >> m;
    std::set<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        if (a == b) {
            continue;
        }
        edges.emplace(a < b ? a : b, a > b ? a : b);
    }
    std::cout << n << ' ' << edges.size() << '\n';
    for (auto const& [a, b] : edges) {
        std::cout << a << ' ' << b << '\n';
    }
    return 0;
}
