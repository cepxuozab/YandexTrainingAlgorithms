#include <algorithm>
#include <iostream>
#include <vector>

static const auto FastIO = []() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr; }();

int main()
{
    if (freopen("input.txt", "r", stdin) == nullptr) {
        puts("Can't open input.txt");
        return 1;
    }
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1), b(n + 1), c(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i] >> b[i] >> c[i];
    }
    std::vector<int> t(n + 1, 0);
    t[1] = a[1];
    if (n > 1) {
        t[2] = std::min(a[1] + a[2], b[1]);
    }
    for (int i = 3; i <= n; ++i) {
        t[i] = std::min({ t[i - 1] + a[i], t[i - 2] + b[i - 1], t[i - 3] + c[i - 2] });
    }
    std::cout << t[n] << std::endl;
}
