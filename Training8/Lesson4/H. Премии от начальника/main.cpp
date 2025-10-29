#include <iostream>
#include <vector>


struct Fenwick {
    int n;
    std::vector<int> f;

    Fenwick(int n) : n(n), f(n + 1, 0) {}

    void add(int i, int v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }

    [[nodiscard]] auto sum(int i) const -> int {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }

    [[nodiscard]] auto rangeSum(int l, int r) const -> int {
        return sum(r) - sum(l - 1);
    }
};

auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];

    Fenwick bit(2 * n + 5);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        // count of j < i such that j + a[j] > i
        int cnt = bit.rangeSum(i + 1, 2 * n + 1);
        ans += 1LL * cnt * a[i];
        bit.add(i + a[i], 1);
    }

    std::cout << ans << "\n";
    return 0;
}
