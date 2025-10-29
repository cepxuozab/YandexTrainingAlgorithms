#include <iostream>
#include <vector>
#include <cmath>
#include <climits>


auto main() -> int {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Префиксные суммы: pref[i] = a[0] + ... + a[i-1]
    std::vector<long long> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }

    // Суффиксные суммы: suff[i] = a[i] + ... + a[n-1]
    std::vector<long long> suff(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        suff[i] = suff[i + 1] + a[i];
    }

    long long best_diff = LLONG_MAX;
    int best_l = -1, best_r = -1;

    int i = 0;          // Вася ест до i (включительно) → l = i+1
    int j = n - 1;      // Маша ест от j (включительно) → r = j+1

    while (i < j) {
        long long S_V = pref[i + 1];  // a[0]..a[i]
        long long S_M = suff[j];      // a[j]..a[n-1]

        long long diff = llabs(S_V - S_M);
        if (diff < best_diff) {
            best_diff = diff;
            best_l = i + 1;
            best_r = j + 1;
        }

        if (S_V < S_M) {
            ++i;
        } else {
            --j;
        }
    }

    std::cout << best_diff << " " << best_l << " " << best_r << "\n";

    return 0;
}