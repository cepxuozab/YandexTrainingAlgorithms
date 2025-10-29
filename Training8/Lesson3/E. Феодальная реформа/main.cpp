#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::vector<int>> children(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        children[p].push_back(i);
    }

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long ans = 0;

    auto dfs = [&](auto&& self, int v) -> long long {
        long long sum_children = 0;
        for (int to : children[v]) {
            sum_children += self(self, to);
        }
        long long k = -a[v] - sum_children;
        ans += std::llabs(k);
        return -a[v];
    };

    dfs(dfs, 0);
    std::cout << ans << '\n';
}
