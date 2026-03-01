#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> a[i];
    }

    auto canWin = [&](int idx) -> bool {
        long long cur = a[idx];
        for (int j = 0; j < N; ++j) {
            if (j == idx)
                continue;
            if (cur > a[j]) {
                cur += a[j];
            } else {
                return false;
            }
        }
        return true;
    };

    int lo = 0, hi = N;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (canWin(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    std::vector<int> ans(N, 0);
    for (int i = lo; i < N; ++i) {
        ans[i] = 1;
    }

    for (int x : ans) {
        std::cout << x << '\n';
    }

    return 0;
}
