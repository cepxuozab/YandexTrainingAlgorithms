#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int
{
    freopen("input.txt", "r", stdin);
    int m;
    int n;
    std::cin >> m >> n;
    std::vector<int> t(n);
    std::vector<int> y(n);
    std::vector<int> z(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> t[i] >> z[i] >> y[i];
    }
    std::vector<int> next(t);
    int time = 0;
    std::vector<int> done(n, 0);
    for (int i = 0; i < m; ++i) {
        auto it = std::min_element(next.begin(), next.end());
        time = *it;
        int k = it - next.begin();
        done[k]++;
        next[k] += t[k];
        if (done[k] % z[k] == 0) {
            next[k] += y[k];
        }
    }
    std::cout << time << '\n';
    for (int i : done) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
